#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pcap.h>
#include <arpa/inet.h>
#include "common.h"
#include "sniffertype.h"
#include "protocolnames.h"

#include <QDebug>

#define UDP_PORT_FLAG (0x1)
#define TCP_PORT_FLAG (0x2)
#define TCP_UDP_PORT_FLAG (0x3)
#define TRANS(type, ptr) (*(type *)(ptr))
#define IP2S(ptr) iptos(*(in_addr *)(ptr))

vector<string> & add_indent(int indent_len, vector<string> & protos)
{
    string indent = "";
    while(indent_len --) indent += " ";
    for(string & origin:protos)
    {
        const string line = origin;
        const int slen = line.size();
        int ptr = 0, last_ptr = 0;
        origin = "";
        while(ptr < slen)
        {
            if(line[ptr] == '\n')
            {
                origin += (indent + line.substr(last_ptr, ptr + 1 - last_ptr));
                last_ptr = ptr + 1;
            }
            ptr ++;
        }
        origin += (indent + line.substr(last_ptr, slen - last_ptr));
    }
    return protos;
}

int distribute_ip_port(const uchar *chr, int len, vector<string> &protocolStack,
                       ushort sport, ushort dport, uchar portFlags);
int distribute_protocol(const uchar * chr, int len, vector<string> &protocolStack, uchar proto);
const string iptos(in_addr ptr)
{
    char buffer[32]={0};
    inet_ntop(AF_INET, &ptr, buffer, INET_ADDRSTRLEN);
    return string(buffer);
}

const string ip6tos(struct sockaddr *sockaddr)
{
    char buffer[INET6_ADDRSTRLEN]={0};
    inet_ntop(AF_INET6, sockaddr, buffer, INET6_ADDRSTRLEN);
    return string(buffer);
}

const string haddrtos(const uchar * addr, const char * seperator="-", int len=6,
                      const char * formats="%s%02X")
{
    char buffer[512]={0}, *ptr=buffer;
    for(int i = 0; i < len; i++)
        ptr += sprintf(ptr, formats, i?seperator:"", addr[i]);
    return string(buffer);
}

const char * getIPProtocolName(ushort port)
{
    switch (port) {
    case FTP_PORT:
        return "(FTP)";
    case TELNET_PORT:
        return "(TELENET)";
    case SMTP_PORT:
        return "(SMTP)";
    case POP3_PORT:
        return "(POP3)";
    case HTTPS_PORT:
        return "(HTTPS)";
    case HTTP_PORT:
    case HTTP2_PORT:
        return  "(HTTP)";
    case DNS_PORT:
        return "(DNS)";
    case SNMP_PORT:
        return "(SNMP)";
    case DHCP_PORT:
    case DHCP2_PORT:
        return "(DHCP)";
    default:
        break;
    }
    return nullptr;
}

const char * getIPProtocolName(unsigned short srcPort, unsigned short dstPort)
{
    const char * ret = getIPProtocolName(srcPort);
    if(ret == nullptr)
        ret = getIPProtocolName(dstPort);
    if(ret == nullptr)
        ret = "";
    return ret;
}

ushort analyseEthernet(const uchar *chr, int len, vector<string> &protocolStack)
{
    if(len < 14)
        return -1;
    protocolStack.push_back("Data Link Layer: Ethernet");
    eth_header *eh = (eth_header *)chr;
    char buffer[64];
    const uchar *ptr = (const uchar *)eh->dstmac;
    sprintf(buffer, "  DST MAC: %02X-%02X-%02X-%02X-%02X-%02X",
            *ptr, *(ptr+1), *(ptr+2), *(ptr+3), *(ptr + 4), *(ptr+5));
    protocolStack.push_back(buffer);
    ptr = (const uchar *)eh->srcmac;
    sprintf(buffer, "  SRC MAC: %02X-%02X-%02X-%02X-%02X-%02X",
            *ptr, *(ptr+1), *(ptr+2), *(ptr+3), *(ptr + 4), *(ptr+5));
    protocolStack.push_back(buffer);
    sprintf(buffer, "  Ether Type: 0x%04X",ntohs(eh->eth_type));
    protocolStack.push_back(buffer);
    return ntohs(eh->eth_type);
}

int analyseARP(const uchar *chr, int len, vector<string> &protocolStack)
{
    char buffer[256]={0};
    arp_header * ah = (arp_header *) chr;
    ushort htype = ntohs(ah->arp_hrd);
    sprintf(buffer, "  Hardware Type: 0x%04X(%s)", htype, get_arp_hardware_type_name(htype));
    protocolStack.push_back(buffer);
    ushort ptype = ntohs(ah->arp_pro);
    sprintf(buffer, "  Ethertype : 0x%04X", ptype);
    protocolStack.push_back(buffer);
    uchar hard_len = ah->arp_hln, proto_len = ah->arp_pln;
    sprintf(buffer, "  Hardware Length: %d\n  Protocol Length: %d", hard_len, proto_len);
    protocolStack.push_back(buffer);
    ushort code = ntohs(ah->arp_op);
    sprintf(buffer, "  Operation Code: 0x%04X(%s)", code, get_arp_operation_code(code));
    protocolStack.push_back(buffer);
    if(proto_len != 4)
        protocolStack.push_back("  Unspported Protocol Length for Now!");
    else{
        uchar * ha = ah->arp_sha, *pa = ah->arp_spa;
        //        inet_ntop(AF_INET, &(sa.sin_addr), str, INET_ADDRSTRLEN)
        sprintf(buffer, "  Sender HardAddr: %02X-%02X-%02X-%02X-%02X-%02X\n"
                        "  Sender ProtoAddr: %d.%d.%d.%d", ha[0], ha[1], ha[2],
                ha[3], ha[4], ha[5], pa[0], pa[1], pa[2], pa[3]);
        protocolStack.push_back(buffer);
        ha = ah->arp_tha, pa = (uchar *)(& ah->arp_tpa);
        sprintf(buffer, "  Target HardAddr: %02X-%02X-%02X-%02X-%02X-%02X\n"
                        "  Target ProtoAddr: %d.%d.%d.%d", ha[0], ha[1], ha[2],
                ha[3], ha[4], ha[5], pa[0], pa[1], pa[2], pa[3]);
        protocolStack.push_back(buffer);
    }
    return 0;
}

int analyseRARP(const uchar *chr, int len, vector<string> &protocolStack)
{
    return analyseARP(chr,  len, protocolStack);
}

string & _analyse_snmp_pdu(const uchar * chr, int len, int & pdu_len, string & value, const ber_header * & bh)
{
    pdu_len = 0;
    value = "";
    if(len < 2)
        return value;
    char buffer[256] = {0}, *tmp = buffer;
    bh = (ber_header *) chr;
    pdu_len += bh->length + 2;
    qDebug() << "PDU type: "<< bh->type << " len: " << bh->length
             << " content: "<< haddrtos(bh->content, "", bh->length).c_str();
    switch(bh->type)
    {
    case 0x02:{
        int n = 0;
        for(uchar i = 0; i < bh->length; i++)
            n = (n << 8) | bh->content[i];
        sprintf(buffer, "%d", n);
        break;
    }
    case 0x04:{
        sprintf(buffer, "%s", haddrtos(bh->content,"", bh->length,"%s%c").c_str());
        break;
    }
    case 0x06:{ // OBJECT ID
        tmp += sprintf(tmp, "%d.%d", (int)bh->content[0]/40, (int)bh->content[0]%40);
        uint val = 0;
        for(uchar i = 1; i < bh->length; i++)
        {
            val = (val << 7) | (bh->content[i] & 0x7f);
            if((bh->content[i] & 0x80) == 0)
            {
                tmp += sprintf(tmp, ".%d", val);
                val = 0;
            }
        }
        qDebug() << buffer << "WAH" << bh->length << endl;
        break;
    }
    case 0x40:{ // IP Address
       tmp += sprintf(tmp , "%s", haddrtos(bh->content, ".", bh->length, "%s%d").c_str());
       break;
    }
    case 0x43:{ // TIMETICKS 0.01s
        uint n = 0;
        for(uchar i = 0; i < bh->length; i++)
            n = (n << 8) | bh->content[i];
        sprintf(buffer, "%d0ms", n);
        break;
    }
    default:
        sprintf(buffer, "0x%s", haddrtos(bh->content, "", bh->length).c_str());
        break;
    }
    value = string(buffer);
    return value;
}

int analyse_snmp_variable_bindings(const uchar * ptr, int len, vector<string> & protos, char * buffer)
{
    qDebug() << "VAR Length" << len << endl;
    if(len < 2)
        return -1;
    char *tmp = buffer;
    const ber_header * bh = NULL;
    string value;
    int pdu_len;
    while(len >= 2)
    {
        bh = (ber_header *) ptr;
        ptr += 2, len -= 2;
        tmp += sprintf(tmp, "\n    VAR Type: %s (%d bytes)",
                       get_snmp_encoding_type_name(bh->type), bh->length);
        _analyse_snmp_pdu(ptr, len, pdu_len, value, bh);
        ptr += pdu_len, len -= pdu_len;
        tmp += sprintf(tmp, "\n      Name: %s", value.c_str());
        _analyse_snmp_pdu(ptr, len, pdu_len, value, bh);
        ptr += pdu_len, len -= pdu_len;
        tmp += sprintf(tmp, "\n      Value: %s", (bh->length == 0)?"None":value.c_str());

    }
    protos.push_back(buffer);
    return 0;
}

int _analyse_snmp_get_set(const uchar * ptr, int len, vector<string> & protos)
{
    if(len < 2)
        return -1;
    char buffer[512], *tmp = buffer;
    const ber_header * bh = NULL;
    string value;
    int pdu_len;
    _analyse_snmp_pdu(ptr, len, pdu_len, value, bh);
    ptr += pdu_len, len -= pdu_len;
    tmp += sprintf(tmp, "  Request ID: %s", value.c_str());
    _analyse_snmp_pdu(ptr, len, pdu_len, value, bh);
    const char * err_names[] = {
        "No Error",
        "Too Big",
        "No Such Name",
        "Bad Value",
        "Read Only",
        "Gen Error",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
    };
    ptr += pdu_len, len -= pdu_len;
    tmp += sprintf(tmp, "\n  Error Status: %s", err_names[bh->content[0]&0x7]);
    _analyse_snmp_pdu(ptr, len, pdu_len, value, bh);
    ptr += pdu_len, len -= pdu_len;
    tmp += sprintf(tmp, "\n  Error Index: %s", value.c_str());
    bh = (ber_header *) ptr;
    ptr += 2, len -= 2;
    tmp += sprintf(tmp, "\n  VARRIABLES: %s (%d bytes)\n",
                   get_snmp_encoding_type_name(bh->type), bh->length);
    protos.push_back(buffer);
    analyse_snmp_variable_bindings(ptr, len, protos, buffer);
    return 0;
}

int _analyse_snmp_trap(const uchar *ptr, int len, vector<string> &protos, char * buffer)
{
    if(len < 2)
        return -1;
    char *tmp = buffer;
    const ber_header * bh = NULL;
    string value;
    int pdu_len;
    _analyse_snmp_pdu(ptr, len, pdu_len, value, bh);
    ptr += pdu_len, len -= pdu_len, tmp += sprintf(tmp, "  Enterprise ID: %s", value.c_str());
    _analyse_snmp_pdu(ptr, len, pdu_len, value, bh);
    ptr += pdu_len, len -= pdu_len, tmp += sprintf(tmp, "\n  Proxy Host: %s", value.c_str());
    _analyse_snmp_pdu(ptr, len, pdu_len, value, bh);
    uchar trap_type = bh->type;
    const char * trap_types[] = {
        "Cold Start",
        "Warm Start",
        "Link Down",
        "Link Up",
        "Authentication Failure",
        "EGP Neighbor Loss",
        "Enterprise Specific",
        "Unknown",
    };
    ptr += pdu_len, len -= pdu_len, tmp += sprintf(tmp, "\n  Trap Type: %s", trap_types[trap_type & 0x7]);
    _analyse_snmp_pdu(ptr, len, pdu_len, value, bh);
    ptr += pdu_len, len -= pdu_len, tmp += sprintf(tmp, "\n  Pointed Trap Type: %s",
                                                   trap_types[trap_type & 0x7]);
    // company oid

    return 0;
}

int analyseSNMP(const uchar *chr, int len, vector<string> &protocolStack)
{
    if( len <= 0)
        return -1;
    char buffer[256] ={0};
    const uchar * ptr = chr;
    uchar type = *(ptr++);
    uchar msg_len = *(ptr++);
    char *tmp = buffer + sprintf(buffer,"  TYPE: %s\n  Length: %d", get_snmp_encoding_type_name(type),
            msg_len);
    len -= 2;
    const ber_header * bh = 0;
    int pdu_len;
    string value;
    _analyse_snmp_pdu(ptr, len, pdu_len, value, bh); // version
    ptr += pdu_len, len -= pdu_len, tmp += sprintf(tmp, "\n  Version: %d", bh->content[0] + 1);
    _analyse_snmp_pdu(ptr, len, pdu_len, value, bh); // community
    ptr += pdu_len, len -= pdu_len, tmp += sprintf(tmp, "\n  Community Name: %s", value.c_str());
    uchar pdu_type = (*ptr++) & 0x0f;
    pdu_len = (int)(*ptr++);
    len -= 2;
    const char * type_names[] ={
        "get-request",
        "get-next-request",
        "get-respose",
        "set-request",
        "trap",
        "unknown",
        "unknown",
        "user defined trap",
    };
    tmp += sprintf(tmp, "\n  PDU Type: %s\n  PDU Length: %d", type_names[pdu_type & 0x07], pdu_len);
    protocolStack.push_back(buffer);
    if(pdu_type <= 3) // get set
        _analyse_snmp_get_set(ptr, pdu_len, protocolStack);
    else if(pdu_type == 4)
       _analyse_snmp_trap(ptr, pdu_len, protocolStack, buffer);
    else if(pdu_type == 7)
    {
        _analyse_snmp_get_set(ptr, pdu_len, protocolStack);
    }
    if(len > pdu_len)
    {
        qDebug() << "what the fuck" << endl;
    }
    return 0;
}

unsigned char analyseIPv4(const uchar *chr, int len, vector<string> &protocolStack)
{
    if(len < 20)
        return -1;
    ip_header  *ih = (ip_header *)chr;
    char buffer[128];
    uchar headerlen= (ih->head_len) << 2;
    uchar version = ih->version;
    sprintf(buffer, "  Version: %d\n  Header Length: %d bytes", version, headerlen);
    protocolStack.push_back(buffer);
    uchar tos = ih->tos;
    sprintf(buffer, "  Type of Service: 0x%02X", tos);
    protocolStack.push_back(buffer);
    sprintf(buffer, "    Precedence: %d\n    Delay: %s\n    Throughout: %s\n"
                    "    Reliability: %s\n    Cost: %s\n    MBZ: %s", tos>>5,
            (tos&0x10)?"Ture":"False", (tos&0x08)?"Ture":"False",
            (tos&0x04)?"Ture":"False", (tos&0x02)?"Ture":"False",
            (tos&0x01)?"Ture":"False");
    protocolStack.push_back(buffer);
    ushort total = ntohs(ih->tlen);
    sprintf(buffer, "  Total Length: %d bytes", total);
    protocolStack.push_back(buffer);
    sprintf(buffer, "  Identifier: %d", ntohs(ih->identification));
    protocolStack.push_back(buffer);
    ushort fo = ih->fo_1;
    fo = (fo << 8) | ih->fo_1;
    uchar flags = ih->flags;
    sprintf(buffer, "  Flags: %x\n    Unused: %s\n    DF: %s\n    More: %s",
            flags,(flags&0x4)?"True":"False", (flags&0x2)?"True":"False",
            (flags&0x1)?"True":"False");
    protocolStack.push_back(buffer);
    sprintf(buffer, "  Fragment offset: %d", fo);
    protocolStack.push_back(buffer);
    sprintf(buffer, "  Time to Live: %d", ih->ttl);
    protocolStack.push_back(buffer);
    sprintf(buffer, "  Protocol: 0x%02X (%s)", ih->proto, get_ip_protocol_name(ih->proto));
    protocolStack.push_back(buffer);
    sprintf(buffer, "  Header Checksump: 0x%04X",ntohs(ih->crc));
    protocolStack.push_back(buffer);
    protocolStack.push_back(string("  SRC IP Address: ") +
                            string(inet_ntoa({*(uint32_t *)ih->saddr})));
    protocolStack.push_back(string("  DST IP Address: ") +
                            string(inet_ntoa({*(uint32_t *)ih->daddr})));

    distribute_protocol(chr + headerlen, len - headerlen, protocolStack, ih->proto);
    return 0;
}

int analyseIPv6(const uchar *chr, int len, vector<string> &protocolStack)
{
    if(len < (int)sizeof(ipv6_header))
        return -1;
    ipv6_header * ip6 = (ipv6_header *) chr;
    char buffer[128];
    uint flow = ip6->flow;
    flow = (flow << 16) | ntohs(ip6->flow23);
    sprintf(buffer,"  Version: %d\n  Tranffic: 0x%04X\n  Flow: 0x%03X",
            ip6->version, (ip6->traffic_1 << 4) | ip6->traffic_2 >> 4, flow);
    protocolStack.push_back(buffer);
    ushort playload = ntohs(ip6->payload);
    sprintf(buffer, "  Playload: %d\n  Next Header: 0x%02X (%s)\n  Hop Limit: %d",
            playload, ip6->next, get_ip_protocol_name(ip6->next), ip6->hop_limit);
    protocolStack.push_back(buffer);
    protocolStack.push_back(string("  SRC IP Address: ") +
                            ip6tos((sockaddr*)ip6->saddr));
    protocolStack.push_back(string("  DST IP Address: ") +
                            ip6tos((sockaddr*)ip6->daddr));
    return distribute_protocol(chr + 40, playload, protocolStack, ip6->next);
}

int analyseTCP(const uchar *chr, int len, vector<string> &protocolStack)
{
    if(len < sizeof(tcp_header))
        return -1;
    char buffer[256];
    const tcp_header * th = (const tcp_header *) chr;
    ushort sport = ntohs(th->sport), dport = ntohs(th->dport);
    sprintf(buffer, "  SRC Port: %d\n  DST Port: %d", sport, dport);
    protocolStack.push_back(buffer);
    uint seq_no = ntohl(th->seq_no), ack_no = ntohl(th->ack_no);
    sprintf(buffer, "  SEQ No. %u\n  ACK No. %u", seq_no, ack_no);
    protocolStack.push_back(buffer);
    uchar headerlen = th->thl * 4;
    sprintf(buffer, "  TCP Header Length: %d", headerlen);
    protocolStack.push_back(buffer);
    uchar reserve = (th->reserved_1 << 1) | th->reseverd_2;
    sprintf(buffer, "  Reserved: 0x%02X", reserve);
    uchar flag = th->flag;
    sprintf(buffer, "  FLAGS: 0x%02X\n    URG: %s\n    ACK: %s\n"
                    "    PSH: %s\n    PST: %s\n    PYN: %s\n    RIN: %s",
            flag, (flag&0x20)?"TRUE":"FALSE", (flag&0x10)?"TRUE":"FALSE",
            (flag&0x08)?"TRUE":"FALSE",(flag&0x04)?"TRUE":"FALSE",
            (flag&0x02)?"TRUE":"FALSE",(flag&0x01)?"TRUE":"FALSE");
    protocolStack.push_back(buffer);
    ushort window = ntohs(th->wnd_size);
    ushort chk_sum = ntohs(th->chk_sum);
    ushort urgent = ntohs(th->urgt_p);
    sprintf(buffer, "  Window Size: %d\n  Check Sum: 0x%04X\n  Urgent Point: %d",
            window, chk_sum, urgent);
    protocolStack.push_back(buffer);
    int option_len = headerlen - 20;
    const uchar * toh = chr + 20;
    if(option_len > 0)
        protocolStack.push_back("  TCP Optional Part:");
    while(option_len > 0)
    {
        uchar option = *toh;
        sprintf(buffer,"    Option: %d (%s)", option,get_tcp_option_name(option));
        protocolStack.push_back(buffer);
        if(option < 2)
        {
            option_len -= 1;
            toh += 1;
            continue;
        }
        uchar length = *(toh + 1);
        sprintf(buffer,"      Length: %d byte(s)", length);
        protocolStack.push_back(buffer);
        if(length > 2)
        {
            char * tmp = buffer + sprintf(buffer, "      Option Content: 0x");
            for(int i = 0; i < length - 2; i++)
                tmp += sprintf(tmp, "%02X", *(toh + 2 + i));
            protocolStack.push_back(buffer);
        }
        toh += length;
        option_len -= length;
    }
    sprintf(buffer, "  TCP Data: %d byte(s)", len-headerlen);
    protocolStack.push_back(buffer);
    return distribute_ip_port(chr + headerlen, len - headerlen,
                              protocolStack, sport, dport, TCP_PORT_FLAG);
}

int analyseUDP(const uchar *chr, int len, vector<string> &protocolStack)
{
    if(len < (int) sizeof(udp_header))
        return -1;
    udp_header * uh = (udp_header *) chr;
    ushort sport = ntohs(uh->sport), dport = ntohs(uh->dport);
    ushort length =ntohs(uh->len), checksum = ntohs(uh->crc);
    char buffer[128];
    sprintf(buffer, "  SRC Port: %d\n  DST Port: %d\n  Length: %d\n  Check Sum: 0x%04X",
            sport, dport, length, checksum);
    protocolStack.push_back(buffer);
    sprintf(buffer, "  UDP Data: %d byte(s)", len - 8);
    protocolStack.push_back(buffer);
    return distribute_ip_port(chr+8, len-8, protocolStack,sport, dport, UDP_PORT_FLAG);
}

int analyseICMP(const uchar *chr, int len, vector<string> &protocolStack)
{
    icmp_header * ih = (icmp_header * ) chr;
    char buffer[128];
    sprintf(buffer,"  Type: %02d (%s)\n  Code: %02d(%s)\n  CheckSum: 0x%04X",
            ih->type, get_icmp_type_name(ih->type), ih->code,
            get_icmp_code_name(ih->type, ih->code), ntohs(ih->crc));
    protocolStack.push_back(buffer);
    vector<string> protos;
    ushort id = *(ushort *)(chr + 4), sequence = *(ushort *)(chr + 4 + 2);
    bool have_ip_header = false;
    switch(ih->type)
    {
    case 0: // echo reply
    case 8: // echo request
    {
        sprintf(buffer, "  Identifier: 0x%04X\n  Sequence Number: 0x%04X\n  Data: %d byte(s)",
                id, sequence, len - 8);
        protocolStack.push_back(buffer);
        break;
    }
    case 5: // Redirect
    {
        sprintf(buffer, "  Redirect IP: %s", IP2S(chr+4).c_str());
        protocolStack.push_back(buffer);
        have_ip_header = true;
        break;
    }
    case 3: // Destination unreachable
    case 4: // Source quenc
    case 11: // Time exceeded
    {
        uint unused = ntohl(TRANS(uint, (chr + 4)));
        sprintf(buffer, "  Unused: 0x%08X", unused);
        protocolStack.push_back(buffer);
        have_ip_header = true;
        break;
    }
    case 12: // Parameter Problem
    {
        sprintf(buffer, "  PTR: 0x%04X\n  Unused: 0x%02X%02X%02X", *(chr + 4),
                *(chr + 5), *(chr + 6), *(chr + 7));
        protocolStack.push_back(buffer);
        have_ip_header = true;
        break;
    }
    case 13: // Timestamp
    case 14:{ // Timestamp reply
        uint ot = ntohl(TRANS(uint, chr + 8)), rt = ntohl(TRANS(uint, chr + 12)),
                tt = ntohl(TRANS(uint, chr + 16));
        sprintf(buffer, "  Identifier: 0x%04X\n  Sequence Number: 0x%04X\n  Originate timestamp: %d\n"
                        "  Receive timestamp: %d\n  Transmit timestamp: %d", id, sequence, ot, rt, tt);
        protocolStack.push_back(buffer);
        break;
    }
    case 17: //Address mask request
    case 18:{ //Address mask reply
        sprintf(buffer, "  Identifier: 0x%04X\n  Sequence Number: 0x%04X\n  Mask ADDR IP: %s",
                id, sequence, iptos(*(in_addr*)(chr + 4)).c_str());
        protocolStack.push_back(buffer);
        break;
    }
    default:
        break;
    }
    int ret = 0;
    if(have_ip_header)
        ret = analyseIPv4(chr + 8, len - 8, protos);
    if(protos.size() > 0){
        sprintf(buffer, "  ICMP DATA Length: %d byte(s)\n    Network Layer: IPv4", len - 8);
        protocolStack.push_back(buffer);
     }
    for(const auto & line:add_indent(4, protos))
        protocolStack.push_back(line);
    return ret;
}

int analyseIGMP(const uchar *chr, int len, vector<string> &protocolStack)
{
    if(len < 8)
        return -1;
    char buffer[128];
    igmp_header_v2 * ih2 = (igmp_header_v2 *) chr;
    uchar type = ih2->type, mrt = ih2->mrt;
    ushort crc = ntohs(ih2->crc);
    sprintf(buffer, "  Type: 0x%02X  (%s)\n  Max Resp Time: %d\n  Check Sum: 0x%04X\n"
                    "  Group Adress: %s", type, get_igmp_type_name(type), mrt, crc,
            iptos(*(in_addr*)ih2->addr).c_str());
    protocolStack.push_back(buffer);
    return 0;
}

int parse_dns_query(const uchar * chr, int len, string & query, const uchar * origin)
{
    char buffer[1024] = {0};
    strcpy(buffer, (char *)chr+1);
    uchar count = *chr;
    if((count&0xc0) == 0xc0)
    {
        ushort jmp = ntohs(*(ushort *)(chr)) & 0x3fff;
        parse_dns_query(origin + jmp , len, query, origin);
        query = "    " + query;
        return 2;
    }
    int ptr = count + 1;
    while(count)
    {
        count = *(chr + ptr);
        if((count&0xc0) == 0xc0)
        {
            buffer[ptr-1] = '.';
            buffer[ptr] = '\0';
            ushort jmp = ntohs(*(ushort *)(chr + ptr)) & 0x3fff;
            parse_dns_query(origin + jmp , len, query, origin);
            query = string(buffer) + query;
            return ptr + 2;
        }
        if(count)
            buffer[ptr-1] = '.';
        ptr += (count + 1);
    }
    query = string(buffer);
    return ptr;
}

int analyse_dns_resource(
        const uchar * chr, int len, vector<string> &protocolStack,
        const uchar * origin)
{
    if(len < 12)
        return -1;
    uchar first = *chr;
    char buffer[256]={0};
    int rlen = 0;
    string name;
    if((first & 0xc0) == 0xc0)
    {
        ushort ptr = ntohs(*(ushort *)chr) & 0x3fff;
        parse_dns_query(origin + ptr, chr - origin + len, name, origin);
        rlen = 2;
    }
    else
    {
        rlen = parse_dns_query(chr, len, name, origin);
    }
    protocolStack.push_back("  Resource Name: " + name);
    ushort type = ntohs(*(ushort *)(chr + rlen)),
            cls = ntohs(*(ushort *)(chr + rlen + 2));

    uint ttl = ntohl(*(uint*)(chr + rlen + 4));
    rlen += 8;
    sprintf(buffer, "    Type: 0x%04X(%s)\n    Class: 0x%04X(%s)\n"
                    "    TTL: 0x%08X(%d)", type, get_dns_type_name(type),
            cls, get_dns_class_name(cls),  ttl, ttl);
    protocolStack.push_back(buffer);
    ushort rdata_len = ntohs(*(ushort *)(chr + rlen));
    rlen += 2;
    sprintf(buffer, "    RData Length: 0x%04X(%d)", rdata_len, rdata_len);
    protocolStack.push_back(buffer);
    if(cls == 1) // Internet
    {
        buffer[0] = 0;
        if(type == 1 && rdata_len == 4)
        {
            const uchar * addr = chr + rlen;
            sprintf(buffer, "    IP Address: %d.%d.%d.%d", addr[0], addr[1], addr[2], addr[3]);
        }
        else if(type == 5 || type == 2)
        {
            parse_dns_query(chr+rlen, len - rlen, name, origin);
            strcpy(buffer, "    RDATA:");
            strcpy(buffer+strlen(buffer), name.c_str());
        }
        protocolStack.push_back(buffer);
    }

    return rlen + rdata_len;
}

int analyseDNS(const uchar *chr, int len, vector<string> &protocolStack){
    if(len < (int)sizeof(dns_header))
        return -1;
    dns_header * dh = (dns_header *) chr;
    char buffer[256] = {0};
    ushort id = ntohs(dh->id);
    sprintf(buffer,"  ID: 0x%04X\n  QR: %s\n  Operation: %s\n"
                   "  AA: %s\n  TC: %s\n  RD: %s\n  RA: %s\n"
                   "  Zero: %X\n  Return Code: %s", id,
            dh->QR?"Response":"Query", get_dns_opcode_name(dh->opcode),
            dh->AA?"Authoritative":"Not authoritative",dh->TC?"Truncated":"Not truncated",
            dh->RD?"Recursion desired":"Recursion not desired",
            dh->RA?"Recursive query support available":"Recursive query support not available",
            dh->zero, get_dns_rcode_name(dh->rcode)
            );
    protocolStack.push_back(buffer);
    ushort ques_count = ntohs(dh->ques_count), reso_count = ntohs(dh->reso_count),
            auth_count = ntohs(dh->auth_count), extra_count = ntohs(dh->extra_count);
    sprintf(buffer, "  Question Count: %d\n  Resource Count: %d\n"
                    "  Authority Count: %d\n  Extra Count: %d",
            ques_count, reso_count, auth_count, extra_count);
    protocolStack.push_back(buffer);
    const uchar * base = chr + 12;
    int base_len = len - 12;
    string query;
    while(ques_count--)
    {
        int qlen = parse_dns_query(base, base_len, query, chr);
        protocolStack.push_back("  Query:\n    Domain Name: " + query);
        ushort type = ntohs(*(ushort * )(base + qlen));
        ushort cls = ntohs(*(ushort *)(base + qlen + 2));
        sprintf(buffer, "    Type: 0x%04X(%s)\n    Class: 0x%04X(%s)",
                type, get_dns_type_name(type), cls, get_dns_class_name(cls));
        protocolStack.push_back(buffer);
        base_len -= (qlen + 4);
        base += (qlen + 4);
    }
    int cnt = reso_count + auth_count + extra_count;
    while(cnt--)
    {
        int rlen = analyse_dns_resource(base, base_len, protocolStack, chr);
        base += rlen;
        base_len -= rlen;
    }
    return 0;
}

int analyse_ddhcp_options(const uchar *chr, int len, vector<string> & protos)
{
    if(len < 0)
        return -1;
    const uchar *ptr = chr;
    char buffer[256];
    int length = len;
    while(length)
    {
        uchar option = *(ptr++);
        length --;
        char *tmp = buffer + sprintf(buffer, "  Option: %d (%s)",
                                     option, get_dhcp_option_name(option));
        if(option != 255 && option != 0)
        {
            uchar oplen = *(ptr++);
            tmp += sprintf(tmp, "\n    Length: %d", oplen);
            if(option == 53)
                tmp += sprintf(tmp, "\n    Message Type: 0x%02X (%s)", *ptr,
                               get_dhcp_message_type_name(*ptr));
            else if(oplen > 0)
                tmp += sprintf(tmp, "\n    Content: 0x%s", haddrtos(ptr, "", oplen).c_str());
            ptr += oplen;
            length -= (oplen + 1);
        }
        protos.push_back(buffer);
        if(option==255)
            break;
    }
    if(length)
    {
        sprintf(buffer, "  Pad (%d bytes): %s", length, haddrtos(ptr, "", length).c_str());
        protos.push_back(buffer);
    }
    return 0;
}

int analyseDHCP(const uchar *chr, int len, vector<string> &protocolStack)
{
    const int dhcp_header_len = sizeof(dhcp_header);
    if(len < dhcp_header_len)
        return -1;
    const dhcp_header *dh = (dhcp_header *) chr;
    char buffer[512], *ptr=buffer;
    sprintf(buffer, "  OP: %d (%s)\n  Hardware Type: 0x%02X (%s)\n  Hardware ADDR Len: %d bytes\n"
                    "  HPOS: %d\n  Transaction ID: 0x%08X\n  Seconds elapsed: %d\n  Flags: 0x%04X"
                    "\n  Client IP ADDR: %s\n  Your IP ADDR: %s\n  Server IP ADDR: %s\n  Gateway "
                    "IP ADDR: %s", dh->op, dh->op == 1?"BOOTREQUEST":(dh->op==2?("BOOTREPLY"):("unknown")),
            dh->htype, get_arp_hardware_type_name((ushort)dh->htype), dh->hlen, dh->hpos,
            ntohl(dh->transaction_id), ntohs(dh->secs), ntohs(dh->flags), IP2S(dh->ci_addr).c_str(),
            IP2S(dh->yi_addr).c_str(), IP2S(dh->si_addr).c_str(), IP2S(dh->gi_addr).c_str());
    protocolStack.push_back(buffer);
    ptr += sprintf(ptr, "  Client Hardware ADDR(16 bytes): %s\n  Pad (%d bytes): %s", haddrtos(dh->ch_addr, "-", dh->hlen).c_str(),
            16-dh->hlen, haddrtos(dh->ch_addr+6, "", 16-dh->hlen).c_str());
    ptr += sprintf(ptr, "\n  Server Name(64 bytes): %s\n  Boot File Name (128 bytes): %s\n  Magic Cookie: 0x%08X",
                   dh->server_name[0]?(const char *)dh->server_name:"not given",
                   dh->bootp[0]?(const char *)dh->bootp:"not given", ntohl(dh->mcookie));
    protocolStack.push_back(buffer);
    return analyse_ddhcp_options(chr + dhcp_header_len, len - dhcp_header_len, protocolStack);
}

int analyseHTTP(const uchar *chr, int len, vector<string> &protocolStack)
{
    return 0;
}

int distribute_protocol(const uchar * chr, int len, vector<string> &protocolStack, uchar proto)
{
    switch(proto){
    case ICMP_SIG:
        protocolStack.push_back("Network Layer: ICMP");
        return analyseICMP(chr, len, protocolStack);
    case IGMP_SIG:
        protocolStack.push_back("Network Layer: IGMP");
        return analyseIGMP(chr, len, protocolStack);
    case TCP_SIG:
        protocolStack.push_back("Transport Layer: TCP");
        return analyseTCP(chr, len, protocolStack);
    case UDP_SIG:
        protocolStack.push_back("Transport Layer: UDP");
        return analyseUDP(chr, len, protocolStack);
    default:
        protocolStack.push_back("*");
        break;
    }
    return 0;
}

int _distribute_udp_port(const uchar *chr, int len, vector<string> &protocolStack, ushort port)
{
    switch(port)
    {
    case DNS_PORT:
        protocolStack.push_back("DNS");
        return analyseDNS(chr, len, protocolStack);
    case SNMP_PORT:
    case SNMP2_PORT:
        protocolStack.push_back("SNMP");
        return analyseSNMP(chr, len, protocolStack);
    case DHCP_PORT:
    case DHCP2_PORT:
        protocolStack.push_back("DHCP");
        return analyseDHCP(chr, len, protocolStack);
    default:
        break;
    }
    return FAIL_RETURN;
}

int _distribute_tcp_port(const uchar *chr, int len, vector<string> &protocolStack, ushort port)
{
    switch (port) {
    case POP3_PORT:
        protocolStack.push_back("POP3");
        return 0;
    case HTTP2_PORT:
    case HTTP_PORT:
        protocolStack.push_back("HTTP");
        return analyseHTTP(chr, len, protocolStack);
    case HTTPS_PORT:
        protocolStack.push_back("HTTPS");
        return 0;
    case SMTP_PORT:
        protocolStack.push_back("SMTP");
        return 0;
    case TELNET_PORT:
        protocolStack.push_back("TELNET");
        return 0;
    case FTP_PORT:
        protocolStack.push_back("FTP");
        return 0;
    default:
        break;
    }
    return FAIL_RETURN;
}

int distribute_ip_port(const uchar *chr, int len, vector<string> &protocolStack,
                       ushort sport, ushort dport, uchar portFlags)
{
    if(portFlags & UDP_PORT_FLAG)
    {
        int ret = _distribute_udp_port(chr, len, protocolStack, sport);
        if( ret != FAIL_RETURN)
            return ret;
        ret = _distribute_udp_port(chr, len, protocolStack, dport);
        if( ret != FAIL_RETURN)
            return ret;
    }
    if(portFlags & TCP_PORT_FLAG)
    {
        int ret = _distribute_tcp_port(chr, len, protocolStack, sport);
        if( ret != FAIL_RETURN)
            return ret;
        ret = _distribute_tcp_port(chr, len, protocolStack, dport);
        if( ret != FAIL_RETURN)
            return ret;
    }
    return -1;
}

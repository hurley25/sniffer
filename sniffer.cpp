
#include <sys/socket.h>
#include <netinet/in.h>
#include <pcap.h>
#include <arpa/inet.h>


#include <iostream>
#include <string>
#include <vector>
#include <QDebug>
#include <cctype>
#include <cstring>
#include "csniffer.h"
#include "sniffer.h"
#include "common.h"
#include "protocolnames.h"

using std::string;
using std::vector;

Sniffer::Sniffer()
{

}

Sniffer::~Sniffer()
{
}

Sniffer * Sniffer::get_sniffer()
{
    static Sniffer sniffer;
    return &sniffer;
}

bool Sniffer::updateDevList()
{
    if (!findAllNetDevs())
        return false;
    netDevInfo.clear();
    pcap_if_t	*index;
    pcap_addr_t *pAddr;
    NetDevInfo	tmpNetDevInfo;
    for (index = allNetDevList; index != NULL; index = index->next) {
        tmpNetDevInfo.name = index->name;
        if (index->description) {
            tmpNetDevInfo.describe = " ";
            tmpNetDevInfo.describe += index->description;
        } else {
            tmpNetDevInfo.describe = "";
        }
        for (pAddr = index->addresses; pAddr != NULL; pAddr = pAddr->next) {
            switch(pAddr->addr->sa_family) {
            case AF_INET:
                tmpNetDevInfo.ipv4FN = "          Address Family Name : "
                                                  "AF_INET (IPV4)";
                if (pAddr->addr) {
                    tmpNetDevInfo.ipv4addr  = "          IPV4 Address : ";
                    tmpNetDevInfo.ipv4addr += iptos(((struct sockaddr_in *)pAddr->addr)->sin_addr);
                }
                break;
            case AF_INET6:
                tmpNetDevInfo.ipv6FN = "         Address Family Name : "
                                                  "AF_INET6 (IPV6)";
                if (pAddr->addr) {
                    tmpNetDevInfo.ipv6addr = "          IPV6 Address : ";
                    tmpNetDevInfo.ipv6addr += ip6tos(pAddr->addr);
                }
                break;
            default:
                break;
            }
        }
        netDevInfo.push_back(tmpNetDevInfo);
    }
    return true;
}

void Sniffer::printDevInfo()
{
    for (std::vector<NetDevInfo>::iterator index = netDevInfo.begin();
         index < netDevInfo.end(); ++index) {
        std::cout << index->name << "\n" << index->describe << "\n"
                  << index->ipv4FN << "\n" << index->ipv4addr << "\n"
                  << index->ipv6FN << "\n" << index->ipv6addr << std::endl;
    }
}

void Sniffer::analyseAbstract(const uchar *chr, string &src_addr, string &dst_addr,
        string &protocol, string &info)
{
}

void Sniffer::analyse(int number, vector<string> & protocolStack)
{
    const unsigned char * pkt_data = (const unsigned char *) this->packets[number].c_str();
    size_t caplen = this->packets[number].length();
    unsigned short eth_type = analyseEthernet(pkt_data, caplen, protocolStack);
    pkt_data += 14;
    caplen -= 14;
    switch (eth_type) {
    case 0x0800: //IP
    {
        ip_header * ih = (ip_header *)(pkt_data);
        protocolStack.push_back("Network Layer: IPv4");
        analyseIPv4(pkt_data, caplen, protocolStack);
        pkt_data += size_t((ih->head_len) << 2);
        break;
    }

    case 0x0806: //ARP
    {
        protocolStack.push_back("Network Layer: ARP:");
        analyseARP(pkt_data, caplen, protocolStack);
        break;
    }
    case 0x8035: //RARP
    {
        protocolStack.push_back("Network Laye: RARP:");
        analyseRARP(pkt_data, caplen, protocolStack);
        break;
    }
    case 0x814c: // SNMP
    {
        protocolStack.push_back("Application Layer: SNMP:");
        analyseSNMP(pkt_data, caplen, protocolStack);
        break;
    }
    case 0x86dd: //IPv6
    {
        protocolStack.push_back("Network Layer: IPv6");
        analyseIPv6(pkt_data, caplen, protocolStack);
        pkt_data += 40;
        break;
    }
    default:
        break;
    }
}

void Sniffer::reset(){
    this->packets.clear();
    //    this->snifferDataVector.clear();
}

void Sniffer::deal_packet(CapTableView *mainTree, int num)
{
    struct  tm      *ltime;
    time_t          local_tv_sec;
    QString capTime, capNumber, capLength, capSource, capDestination, capProtocol;
    capNumber.setNum(num);
    capLength.setNum(this->header->len);
    this->saveCurrentPacket();
    this->packets.push_back(string((const char *)this->pkt_data, this->header->caplen));
    this->headers.push_back(*this->header);
    local_tv_sec = this->header->ts.tv_sec;
    ltime = localtime(&local_tv_sec);
    char buffer[128];
    strftime(buffer, sizeof(buffer), "%H:%M:%S", ltime);
    capTime = QString(buffer);

    eth_header      *eh;
    unsigned short   eth_type;
    const unsigned char * ptr;

    eh = (eth_header *)this->pkt_data; // 获得 Mac 头
    ptr = eh->srcmac;
    capSource = QString::asprintf("%02X-%02X-%02X-%02X-%02X-%02X", *(ptr), *(ptr+1), *(ptr+2), *(ptr+3), *(ptr+4), *(ptr+5));
    ptr = eh->dstmac;
    capDestination = QString::asprintf("%02X-%02X-%02X-%02X-%02X-%02X", *(ptr), *(ptr+1), *(ptr+2), *(ptr+3), *(ptr+4), *(ptr+5));
    eth_type = ntohs(eh->eth_type);
    switch(eth_type){
    case 0x0800: // IP
    {
        capProtocol = "IPv4 ";
        ip_header * ih = (ip_header *)(this->pkt_data + 14); //  获得 IP 协议头
        unsigned int ip_len = (ih->head_len) << 2; // 获得 IP 头的大小
        unsigned short   sport=0, dport=0;
        switch (ih->proto) {
        case TCP_SIG:{
            capProtocol += ">TCP";
            tcp_header * th = (tcp_header *)((unsigned char *)ih + ip_len);      // 获得 TCP 协议头
            sport = ntohs(th->sport);                               // 获得源端口和目的端口
            dport = ntohs(th->dport);
            capProtocol += getIPProtocolName(sport, dport);
            break;
        }
        case UDP_SIG:{
            capProtocol += ">UDP";
            udp_header *uh = (udp_header *)((unsigned char *)ih + ip_len);      // 获得 UDP 协议头
            sport = ntohs(uh->sport);                               // 获得源端口和目的端口
            dport = ntohs(uh->dport);
            capProtocol += getIPProtocolName(sport, dport);
            break;
        }
        case ICMP_SIG:{
            capProtocol += ">ICMP";
            break;
        }
        case IGMP_SIG:{
            capProtocol += ">IGMP";
            break;
        }
        default:
            mainTree->addOneCaptureItem(capNumber, capTime, capSource, capDestination, capProtocol, capLength);
            return;
        }
        ptr = ih->saddr;
        capSource = QString::asprintf("%d.%d.%d.%d",*(ptr), *(ptr+1), *(ptr+2), *(ptr+3));
        if(sport) capSource += QString::asprintf(":%d", sport);
        ptr = ih->daddr;
        capDestination = QString::asprintf("%d.%d.%d.%d",*(ptr), *(ptr+1), *(ptr+2), *(ptr+3));
        if(dport) capDestination += QString::asprintf(":%d", dport);
        break;
    }
    case 0x0806: //ARP
    {
        capProtocol = "ARP";
        break;
    }
    case 0x8035: //RARP
    {
        capProtocol = "RARP";
        break;
    }
    case 0x814c: // SNMP
    {
        capProtocol = "SNMP";
        break;
    }
    case 0x86dd: //IPv6
    {
        capProtocol = "IPv6";
        ipv6_header * i6 = (ipv6_header *)(this->pkt_data + 14);
        capSource = ip6tos((sockaddr*)i6->saddr).c_str();
        capDestination = ip6tos((sockaddr*)i6->daddr).c_str();
        string name = string(get_ip_protocol_name(i6->next));
        if(name.size() > 0)
            name = ">" + name;
       capProtocol += name.c_str();
        break;
    }
    default:
        break;
    }
    mainTree->addOneCaptureItem(capNumber, capTime, capSource, capDestination, capProtocol, capLength);
}

const string Sniffer::getPacket(const size_t number) const
{
    if(number > this->packets.size())
        return nullptr;
    return this->packets[number];
}

size_t Sniffer::getPacketsCount() const
{
    return this->packets.size();
}
const QString Sniffer::getExplainText(const int number) const
{
    const string & packet = this->packets[number];
    string data = string(packet.c_str(), packet.length());
    for(size_t i = 0; i < data.length(); i++)
    {
        unsigned char tmp = data[i];
        if(!isprint(tmp) || iscntrl(tmp) || tmp&128)
            data[i] = '.';
    }
    QString tmp = QString(data.c_str()), ret;
    int idx = 0;
    while(idx < tmp.length())
    {
        ret.push_back(tmp[idx]);
        idx ++;
        if((idx % 16) == 0)
           ret.push_back('\n');
    }
    return ret;
}

const QString Sniffer::getHexText(const int number) const
{
    const string & packet = this->packets[number];
    QByteArray data(packet.c_str(), packet.length());
    QString tmp = data.toHex().toUpper(), ret;
    int idx = 0;
    while(idx < tmp.length())
    {
        ret.push_back(tmp[idx]);
        idx ++;
        if((idx % 32) == 0)
           ret.push_back('\n');
    }
    return ret;
}

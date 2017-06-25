#include "protocolnames.h"
#include <QDebug>

const char *get_arp_hardware_type_name(ushort htype)
{
    static const char * names[] = {
        "Reserved",
        "Ethernet (10Mb)",
        "Experimental Ethernet (3Mb)",
        "Amateur Radio AX.25",
        "Proteon ProNET Token Ring",
        "Chaos",
        "IEEE 802 Networks",
        "ARCNET",
        "Hyperchannel",
        "Lanstar",
        "Autonet Short Address",
        "LocalTalk",
        "LocalNet (IBM PCNet or SYTEK LocalNET)",
        "Ultra link",
        "SMDS",
        "Frame Relay",
        "Asynchronous Transmission Mode (ATM)",
        "HDLC",
        "Fibre Channel",
        "Asynchronous Transmission Mode (ATM)",
        "Serial Line",
        "Asynchronous Transmission Mode (ATM)",
        "MIL-STD-188-220",
        "Metricom",
        "IEEE 1394.1995",
        "MAPOS",
        "Twinaxial",
        "EUI-64",
        "HIPARP",
        "IP and ARP over ISO 7816-3",
        "ARPSec",
        "IPsec tunnel",
        "InfiniBand (TM)",
        "TIA-102 Project 25 Common Air Interface (CAI)",
        "Wiegand Interface",
        "Pure IP",
        "HW_EXP1",
        "HFI",
    };
    if(htype <= 37)
        return names[htype];
    switch(htype){
    case 256:
        return "HW_EXP2";
    case 257:
        return "AEthernet";
    default:
        break;
    }
    return "Reserved";
    /*
0	Reserved
1	Ethernet (10Mb)
2	Experimental Ethernet (3Mb)
3	Amateur Radio AX.25
4	Proteon ProNET Token Ring
5	Chaos
6	IEEE 802 Networks
7	ARCNET
8	Hyperchannel
9	Lanstar
10	Autonet Short Address
11	LocalTalk
12	LocalNet (IBM PCNet or SYTEK LocalNET)
13	Ultra link
14	SMDS
15	Frame Relay
16	Asynchronous Transmission Mode (ATM)
17	HDLC
18	Fibre Channel
19	Asynchronous Transmission Mode (ATM)
20	Serial Line
21	Asynchronous Transmission Mode (ATM)
22	MIL-STD-188-220
23	Metricom
24	IEEE 1394.1995
25	MAPOS
26	Twinaxial
27	EUI-64
28	HIPARP
29	IP and ARP over ISO 7816-3
30	ARPSec
31	IPsec tunnel
32	InfiniBand (TM)
33	TIA-102 Project 25 Common Air Interface (CAI)
34	Wiegand Interface
35	Pure IP
36	HW_EXP1
37	HFI
38-255	Unassigned
256	HW_EXP2
257	AEthernet
258-65534	Unassigned
65535	Reserved
*/
}

const char *get_ip_protocol_name(uchar proto)
{
    static const char * protocol_names[] = {
        "HOPOPT",
        "ICMP",
        "IGMP",
        "GGP",
        "IPv4",
        "ST",
        "TCP",
        "CBT",
        "EGP",
        "IGP",
        "BBN-RCC-MON",
        "NVP-II",
        "PUP",
        "ARGUS (deprecated)",
        "EMCON",
        "XNET",
        "CHAOS",
        "UDP",
        "MUX",
        "DCN-MEAS",
        "HMP",
        "PRM",
        "XNS-IDP",
        "TRUNK-1",
        "TRUNK-2",
        "LEAF-1",
        "LEAF-2",
        "RDP",
        "IRTP",
        "ISO-TP4",
        "NETBLT",
        "MFE-NSP",
        "MERIT-INP",
        "DCCP",
        "3PC",
        "IDPR",
        "XTP",
        "DDP",
        "IDPR-CMTP",
        "TP++",
        "IL",
        "IPv6",
        "SDRP",
        "IPv6-Route",
        "IPv6-Frag",
        "IDRP",
        "RSVP",
        "GRE",
        "DSR",
        "BNA",
        "ESP",
        "AH",
        "I-NLSP",
        "SWIPE (deprecated)",
        "NARP",
        "MOBILE",
        "TLSP",
        "SKIP",
        "IPv6-ICMP",
        "IPv6-NoNxt",
        "IPv6-Opts",
        "",
        "CFTP",
        "",
        "SAT-EXPAK",
        "KRYPTOLAN",
        "RVD",
        "IPPC",
        "",
        "SAT-MON",
        "VISA",
        "IPCV",
        "CPNX",
        "CPHB",
        "WSN",
        "PVP",
        "BR-SAT-MON",
        "SUN-ND",
        "WB-MON",
        "WB-EXPAK",
        "ISO-IP",
        "VMTP",
        "SECURE-VMTP",
        "VINES",
        "TTP",
        "IPTM",
        "NSFNET-IGP",
        "DGP",
        "TCF",
        "EIGRP",
        "OSPFIGP",
        "Sprite-RPC",
        "LARP",
        "MTP",
        "AX.25",
        "IPIP",
        "MICP (deprecated)",
        "SCC-SP",
        "ETHERIP",
        "ENCAP",
        "",
        "GMTP",
        "IFMP",
        "PNNI",
        "PIM",
        "ARIS",
        "SCPS",
        "QNX",
        "A/N",
        "IPComp",
        "SNP",
        "Compaq-Peer",
        "IPX-in-IP",
        "VRRP",
        "PGM",
        "",
        "L2TP",
        "DDX",
        "IATP",
        "STP",
        "SRP",
        "UTI",
        "UTI",
        "SMP",
        "SM (deprecated)",
        "PTP",
        "ISIS over IPv4",
        "FIRE",
        "CRTP",
        "CRUDP",
        "SSCOPMCE",
        "IPLT",
        "SPS",
        "PIPE",
        "SCTP",
        "FC",
        "RSVP-E2E-IGNORE",
        "Mobility Header",
        "UDPLite",
        "MPLS-in-IP",
        "manet",
        "HIP",
        "Shim6",
        "WESP",
        "ROHC",
    };
    if(proto <= 142)
        return protocol_names[proto];
    return "Reserved";

    /*
(0,"HOPOPT","IPv6 Hop-by-Hop Option"),
(1,"ICMP","Internet Control Message"),
(2,"IGMP","Internet Group Management"),
(3,"GGP","Gateway-to-Gateway"),
(4,"IPv4","IPv4 encapsulation"),
(5,"ST","Stream"),
(6,"TCP","Transmission Control"),
(7,"CBT","CBT"),
(8,"EGP","Exterior Gateway Protocol"),
(9,"IGP","any private interior gateway
(used by Cisco for their IGRP)"),
(10,"BBN-RCC-MON","BBN RCC Monitoring"),
(11,"NVP-II","Network Voice Protocol"),
(12,"PUP","PUP"),
(13,"ARGUS (deprecated)","ARGUS"),
(14,"EMCON","EMCON"),
(15,"XNET","Cross Net Debugger"),
(16,"CHAOS","Chaos"),
(17,"UDP","User Datagram"),
(18,"MUX","Multiplexing"),
(19,"DCN-MEAS","DCN Measurement Subsystems"),
(20,"HMP","Host Monitoring"),
(21,"PRM","Packet Radio Measurement"),
(22,"XNS-IDP","XEROX NS IDP"),
(23,"TRUNK-1","Trunk-1"),
(24,"TRUNK-2","Trunk-2"),
(25,"LEAF-1","Leaf-1"),
(26,"LEAF-2","Leaf-2"),
(27,"RDP","Reliable Data Protocol"),
(28,"IRTP","Internet Reliable Transaction"),
(29,"ISO-TP4","ISO Transport Protocol Class 4"),
(30,"NETBLT","Bulk Data Transfer Protocol"),
(31,"MFE-NSP","MFE Network Services Protocol"),
(32,"MERIT-INP","MERIT Internodal Protocol"),
(33,"DCCP","Datagram Congestion Control Protocol"),
(34,"3PC","Third Party Connect Protocol"),
(35,"IDPR","Inter-Domain Policy Routing Protocol"),
(36,"XTP","XTP"),
(37,"DDP","Datagram Delivery Protocol"),
(38,"IDPR-CMTP","IDPR Control Message Transport Proto"),
(39,"TP++","TP++ Transport Protocol"),
(40,"IL","IL Transport Protocol"),
(41,"IPv6","IPv6 encapsulation"),
(42,"SDRP","Source Demand Routing Protocol"),
(43,"IPv6-Route","Routing Header for IPv6"),
(44,"IPv6-Frag","Fragment Header for IPv6"),
(45,"IDRP","Inter-Domain Routing Protocol"),
(46,"RSVP","Reservation Protocol"),
(47,"GRE","Generic Routing Encapsulation"),
(48,"DSR","Dynamic Source Routing Protocol"),
(49,"BNA","BNA"),
(50,"ESP","Encap Security Payload"),
(51,"AH","Authentication Header"),
(52,"I-NLSP","Integrated Net Layer Security  TUBA"),
(53,"SWIPE (deprecated)","IP with Encryption"),
(54,"NARP","NBMA Address Resolution Protocol"),
(55,"MOBILE","IP Mobility"),
(56,"TLSP","Transport Layer Security Protocol
using Kryptonet key management"),
(57,"SKIP","SKIP"),
(58,"IPv6-ICMP","ICMP for IPv6"),
(59,"IPv6-NoNxt","No Next Header for IPv6"),
(60,"IPv6-Opts","Destination Options for IPv6"),
(61,"","any host internal protocol"),
(62,"CFTP","CFTP"),
(63,"","any local network"),
(64,"SAT-EXPAK","SATNET and Backroom EXPAK"),
(65,"KRYPTOLAN","Kryptolan"),
(66,"RVD","MIT Remote Virtual Disk Protocol"),
(67,"IPPC","Internet Pluribus Packet Core"),
(68,"","any distributed file system"),
(69,"SAT-MON","SATNET Monitoring"),
(70,"VISA","VISA Protocol"),
(71,"IPCV","Internet Packet Core Utility"),
(72,"CPNX","Computer Protocol Network Executive"),
(73,"CPHB","Computer Protocol Heart Beat"),
(74,"WSN","Wang Span Network"),
(75,"PVP","Packet Video Protocol"),
(76,"BR-SAT-MON","Backroom SATNET Monitoring"),
(77,"SUN-ND","SUN ND PROTOCOL-Temporary"),
(78,"WB-MON","WIDEBAND Monitoring"),
(79,"WB-EXPAK","WIDEBAND EXPAK"),
(80,"ISO-IP","ISO Internet Protocol"),
(81,"VMTP","VMTP"),
(82,"SECURE-VMTP","SECURE-VMTP"),
(83,"VINES","VINES"),
(84,"TTP","Transaction Transport Protocol"),
(84,"IPTM","Internet Protocol Traffic Manager"),
(85,"NSFNET-IGP","NSFNET-IGP"),
(86,"DGP","Dissimilar Gateway Protocol"),
(87,"TCF","TCF"),
(88,"EIGRP","EIGRP"),
(89,"OSPFIGP","OSPFIGP"),
(90,"Sprite-RPC","Sprite RPC Protocol"),
(91,"LARP","Locus Address Resolution Protocol"),
(92,"MTP","Multicast Transport Protocol"),
(93,"AX.25","AX.25 Frames"),
(94,"IPIP","IP-within-IP Encapsulation Protocol"),
(95,"MICP (deprecated)","Mobile Internetworking Control Pro."),
(96,"SCC-SP","Semaphore Communications Sec. Pro."),
(97,"ETHERIP","Ethernet-within-IP Encapsulation"),
(98,"ENCAP","Encapsulation Header"),
(99,"","any private encryption scheme"),
(100,"GMTP","GMTP"),
(101,"IFMP","Ipsilon Flow Management Protocol"),
(102,"PNNI","PNNI over IP"),
(103,"PIM","Protocol Independent Multicast"),
(104,"ARIS","ARIS"),
(105,"SCPS","SCPS"),
(106,"QNX","QNX"),
(107,"A/N","Active Networks"),
(108,"IPComp","IP Payload Compression Protocol"),
(109,"SNP","Sitara Networks Protocol"),
(110,"Compaq-Peer","Compaq Peer Protocol"),
(111,"IPX-in-IP","IPX in IP"),
(112,"VRRP","Virtual Router Redundancy Protocol"),
(113,"PGM","PGM Reliable Transport Protocol"),
(114,"","any 0-hop protocol"),
(115,"L2TP","Layer Two Tunneling Protocol"),
(116,"DDX","D-II Data Exchange (DDX)"),
(117,"IATP","Interactive Agent Transfer Protocol"),
(118,"STP","Schedule Transfer Protocol"),
(119,"SRP","SpectraLink Radio Protocol"),
(120,"UTI","UTI"),
(121,"SMP","Simple Message Protocol"),
(122,"SM (deprecated)","Simple Multicast Protocol"),
(123,"PTP","Performance Transparency Protocol"),
(124,"ISIS over IPv4",""),
(125,"FIRE",""),
(126,"CRTP","Combat Radio Transport Protocol"),
(127,"CRUDP","Combat Radio User Datagram"),
(128,"SSCOPMCE",""),
(129,"IPLT",""),
(130,"SPS","Secure Packet Shield"),
(131,"PIPE","Private IP Encapsulation within IP"),
(132,"SCTP","Stream Control Transmission Protocol"),
(133,"FC","Fibre Channel"),
(134,"RSVP-E2E-IGNORE",""),
(135,"Mobility Header",""),
(136,"UDPLite",""),
(137,"MPLS-in-IP",""),
(138,"manet","MANET Protocols"),
(139,"HIP","Host Identity Protocol"),
(140,"Shim6","Shim6 Protocol"),
(141,"WESP","Wrapped Encapsulating Security Payload"),
(142,"ROHC","Robust Header Compression"),
(143-252,"","Unassigned"),
(253,"","Use for experimentation and testing"),
(254,"","Use for experimentation and testing"),
(255,"Reserved",""),
*/
}

const char *get_arp_operation_code(ushort code)
{
    static const char * codes[]  = {
        "Reserved",
        "REQUEST",
        "REPLY",
        "request",
        "reply",
        "DRARP-Request",
        "DRARP-Reply",
        "DRARP-Error",
        "InARP-Request",
        "InARP-Reply",
        "ARP-NAK",
        "MARS-Request",
        "MARS-Multi",
        "MARS-MServ",
        "MARS-Join",
        "MARS-Leave",
        "MARS-NAK",
        "MARS-Unserv",
        "MARS-SJoin",
        "MARS-SLeave",
        "MARS-Grouplist-Request",
        "MARS-Grouplist-Reply",
        "MARS-Redirect-Map",
        "MAPOS-UNARP",
        "OP_EXP1",
        "OP_EXP2",
    };
    if(code <= 25)
        return codes[code];
    switch(code){
    case 65535:
        return "Reserved";
    default:
        break;
    }
    return "Unassigned";

    /*
0	Reserved
1	REQUEST
2	REPLY
3	request Reverse
4	reply Reverse
5	DRARP-Request
6	DRARP-Reply
7	DRARP-Error
8	InARP-Request
9	InARP-Reply
10	ARP-NAK
11	MARS-Request
12	MARS-Multi
13	MARS-MServ
14	MARS-Join
15	MARS-Leave
16	MARS-NAK
17	MARS-Unserv
18	MARS-SJoin
19	MARS-SLeave
20	MARS-Grouplist-Request
21	MARS-Grouplist-Reply
22	MARS-Redirect-Map
23	MAPOS-UNARP
24	OP_EXP1
25	OP_EXP2
*/
}

const char *get_tcp_option_name(uchar option)
{
    static const char * options[] = {
        "End of Option List",
        "No-Operation",
        "Maximum Segment Size",
        "Window Scale",
        "SACK Permitted",
        "SACK",
        "Echo (obsoleted by option 8)",
        "Echo Reply (obsoleted by option 8)",
        "Timestamps",
        "Partial Order Connection Permitted (obsolete)",
        "Partial Order Service Profile (obsolete)",
        "CC (obsolete)",
        "CC.NEW (obsolete)",
        "CC.ECHO (obsolete)",
        "TCP Alternate Checksum Request (obsolete)",
        "TCP Alternate Checksum Data (obsolete)",
        "Skeeter",
        "Bubba",
        "Trailer Checksum Option",
        "MD5 Signature Option (obsoleted by option 29)",
        "SCPS Capabilities",
        "Selective Negative Acknowledgements",
        "Record Boundaries",
        "Corruption experienced",
        "SNAP",
        "Unassigned (released 2000-12-18)",
        "TCP Compression Filter",
        "Quick-Start Response",
        "User Timeout Option",
        "TCP Authentication Option (TCP-AO)",
        "Multipath TCP (MPTCP)",
        "Reserved",
        "Reserved",
        "Reserved",
        "TCP Fast Open Cookie",
    };
    if(option <= 34)
        return options[option];
    return "Reserved";
    /*
0	End of Option List
1	No-Operation
2	Maximum Segment Size
3	Window Scale
4	SACK Permitted
5	SACK
6	Echo (obsoleted by option 8)
7	Echo Reply (obsoleted by option 8)
8	Timestamps
9	Partial Order Connection Permitted (obsolete)
10	Partial Order Service Profile (obsolete)
11	CC (obsolete)
12	CC.NEW (obsolete)
13	CC.ECHO (obsolete)
14	TCP Alternate Checksum Request (obsolete)
15	TCP Alternate Checksum Data (obsolete)
16	Skeeter
17	Bubba
18	Trailer Checksum Option
19	MD5 Signature Option (obsoleted by option 29)
20	SCPS Capabilities
21	Selective Negative Acknowledgements
22	Record Boundaries
23	Corruption experienced
24	SNAP
25	Unassigned (released 2000-12-18)
26	TCP Compression Filter
27	Quick-Start Response
28	User Timeout Option (also, other known unauthorized use) [***][1]
29	TCP Authentication Option (TCP-AO)
30	Multipath TCP (MPTCP)
31	Reserved (known unauthorized use without proper IANA assignment) [**]
32	Reserved (known unauthorized use without proper IANA assignment) [**]
33	Reserved (known unauthorized use without proper IANA assignment) [**]
34	TCP Fast Open Cookie
35-75	Reserved
69	Reserved (known unauthorized use without proper IANA assignment) [**]
70	Reserved (known unauthorized use without proper IANA assignment) [**]
71-75	Reserved
76	Reserved (known unauthorized use without proper IANA assignment) [**]
77	Reserved (known unauthorized use without proper IANA assignment) [**]
78	Reserved (known unauthorized use without proper IANA assignment) [**]
79-252	Reserved
253	RFC3692-style Experiment 1 (also improperly used for shipping products) [*]
254	RFC3692-style Experiment 2 (also improperly used for shipping products) [*]
*/
}

const char *get_icmp_type_name(uchar type)
{
    static const char * types [] ={
        "Echo Reply",
        "Unassigned",
        "Unassigned",
        "Destination Unreachable",
        "Source Quench (Deprecated)",
        "Redirect",
        "Alternate Host Address (Deprecated)",
        "Unassigned",
        "Echo",
        "Router Advertisement",
        "Router Solicitation",
        "Time Exceeded",
        "Parameter Problem",
        "Timestamp",
        "Timestamp Reply",
        "Information Request (Deprecated)",
        "Information Reply (Deprecated)",
        "Address Mask Request (Deprecated)",
        "Address Mask Reply (Deprecated)",
        "Reserved (for Security)",
        "Reserved (for Robustness Experiment)",
        "Reserved (for Robustness Experiment)",
        "Reserved (for Robustness Experiment)",
        "Reserved (for Robustness Experiment)",
        "Reserved (for Robustness Experiment)",
        "Reserved (for Robustness Experiment)",
        "Reserved (for Robustness Experiment)",
        "Reserved (for Robustness Experiment)",
        "Reserved (for Robustness Experiment)",
        "Reserved (for Robustness Experiment)",
        "Traceroute (Deprecated)",
        "Datagram Conversion Error (Deprecated)",
        "Mobile Host Redirect (Deprecated)",
        "IPv6 Where-Are-You (Deprecated)",
        "IPv6 I-Am-Here (Deprecated)",
        "Mobile Registration Request (Deprecated)",
        "Mobile Registration Reply (Deprecated)",
        "Domain Name Request (Deprecated)",
        "Domain Name Reply (Deprecated)",
        "SKIP (Deprecated)",
        "Photuris",
        "ICMP messages utilized by experimental mobility protocols such as Seamoby",
    };
    if(type <= 41)
        return types[type];
    switch (type) {
    case 253:
    case 254:
        return "RFC3692-style Experiment 1";
    case 255:
        return "Reserved";
    default:
        break;
    }
    return "Unassigned";

    /*
0	Echo Reply
1	Unassigned
2	Unassigned
3	Destination Unreachable
4	Source Quench (Deprecated)
5	Redirect
6	Alternate Host Address (Deprecated)
7	Unassigned
8	Echo
9	Router Advertisement
10	Router Solicitation
11	Time Exceeded
12	Parameter Problem
13	Timestamp
14	Timestamp Reply
15	Information Request (Deprecated)
16	Information Reply (Deprecated)
17	Address Mask Request (Deprecated)
18	Address Mask Reply (Deprecated)
19	Reserved (for Security)
20-29	Reserved (for Robustness Experiment)
30	Traceroute (Deprecated)
31	Datagram Conversion Error (Deprecated)
32	Mobile Host Redirect (Deprecated)
33	IPv6 Where-Are-You (Deprecated)
34	IPv6 I-Am-Here (Deprecated)
35	Mobile Registration Request (Deprecated)
36	Mobile Registration Reply (Deprecated)
37	Domain Name Request (Deprecated)
38	Domain Name Reply (Deprecated)
39	SKIP (Deprecated)
40	Photuris
41	ICMP messages utilized by experimental mobility protocols such as Seamoby
42-252	Unassigned
253	RFC3692-style Experiment 1
254	RFC3692-style Experiment 2
255	Reserved
*/
}

const char *get_icmp_code_name(uchar type, uchar code)
{
    switch(type){
    case 0:{
        if(code == 0)
            return "No Code";
        break;
    }
    case 1:
    case 2:
        break;
    case 3:{
        static const char * ncodes[] = {
            "Net Unreachable",
            "Host Unreachable",
            "Protocol Unreachable",
            "Port Unreachable",
            "Fragmentation Needed and Don't Fragment was Set",
            "Source Route Failed",
            "Destination Network Unknown",
            "Destination Host Unknown",
            "Source Host Isolated",
            "Communication with Destination Network is Administratively Prohibited",
            "Communication with Destination Host is Administratively Prohibited",
            "Destination Network Unreachable for Type of Service",
            "Destination Host Unreachable for Type of Service",
            "Communication Administratively Prohibited",
            "Host Precedence Violation",
            "Precedence cutoff in effect",
        };
        if(code <= 15)
            return ncodes[code];
        break;
        /*
0	Net Unreachable
1	Host Unreachable
2	Protocol Unreachable
3	Port Unreachable
4	Fragmentation Needed and Don't Fragment was Set
5	Source Route Failed
6	Destination Network Unknown
7	Destination Host Unknown
8	Source Host Isolated
9	Communication with Destination Network is Administratively Prohibited
10	Communication with Destination Host is Administratively Prohibited
11	Destination Network Unreachable for Type of Service
12	Destination Host Unreachable for Type of Service
13	Communication Administratively Prohibited
14	Host Precedence Violation
15	Precedence cutoff in effect
*/
    }
    case 4:{
        if(code == 0)
            return "No Code";
        break;
    }
    case 5:{
        const char * ncodes5[] =  {
            "Redirect Datagram for the Network (or subnet)",
            "Redirect Datagram for the Host",
            "Redirect Datagram for the Type of Service and Network",
            "Redirect Datagram for the Type of Service and Host",
        };
        if(code <= 3)
            return ncodes5[code];
        break;
    }
    case 6:{
        if(code == 0)
            return "Alternate Address for Host";
        break;
    }
    case 7:
        break;
    case 8:{
        if(code == 0)
            return "No Code";
        break;
    }
    case 9:{
        if(code == 0)
            return "Normal router advertisement";
        else if(code == 16)
            return "Does not route common traffic";
        break;
    }
    case 10:{
        if(code == 0)
            return "No Code";
        break;
    }
    case 11:{
        if(code == 0)
            return "Time to Live exceeded in Transit";
        else if(code == 1)
            return "Fragment Reassembly Time Exceeded";
        break;
    }
    case 12:{
        const char * ncodes12 [] ={
            "Pointer indicates the error",
            "Missing a Required Option",
            "Bad Length",
        };
        if(code <= 2)
            return ncodes12[code];
        break;
    }
    case 13:
    case 14:
    case 15:
    case 16:
        return "No Code";
    default:
        break;
    }
    return "Unsiggned";
}

const char *get_igmp_type_name(uchar type)
{
    switch (type) {
    case 0x11:
        return "IGMP Membership Query";
    case 0x12:
        return "IGMPv1 Membership Report";
    case 0x13:
        return "DVMRP";
    case 0x14:
        return "PIM version 1";
    case 0x15:
        return "Cisco Trace Messages";
    case 0x16:
        return "IGMPv2 Membership Report";
    case 0x17:
        return "IGMPv2 Leave Group";
    case 0x1e:
        return "Multicast Traceroute Response";
    case 0x1f:
        return "Multicast Traceroute";
    case 0x22:
        return "IGMPv3 Membership Report";
    case 0x30:
        return "Multicast Router Advertisement";
    case 0x31:
        return "Multicast Router Solicitation";
    case 0x32:
        return "Multicast Router Termination";
    default:
        break;
    }
    if (type <= 0x08)
        return "Reserved";
    if (type >= 0xf0)
        return "Reserved for experimentation";
    return "Unassigned";
    /*
    0x00	Reserved
    0x01-0x08	Reserved (Obsolete)	[RFC988]
    0x09-0x10	Unassigned
    0x11	IGMP Membership Query	[RFC1112]
    0x12	IGMPv1 Membership Report	[RFC1112]
    0x13	DVMRP	[draft-ietf-idmr-dvmrp-v3-11]
    0x14	PIM version 1	[draft-ietf-idmr-pim-spec-02]
    0x15	Cisco Trace Messages
    0x16	IGMPv2 Membership Report	[RFC2236]
    0x17	IGMPv2 Leave Group	[RFC2236]
    0x1e	Multicast Traceroute Response	[Bill_Fenner]
    0x1f	Multicast Traceroute	[Bill_Fenner]
    0x22	IGMPv3 Membership Report	[RFC3376]
    0x30	Multicast Router Advertisement	[RFC4286]
    0x31	Multicast Router Solicitation	[RFC4286]
    0x32	Multicast Router Termination	[RFC4286]
    0xf0-0xff	Reserved for experimentation	[RFC3228][BCP57]
*/
}

const char *get_dns_opcode_name(uchar code)
{
    static const char * names[] = {
        "QUERY, Standard query.",
        "IQUERY, Inverse query.",
        "STATUS, Server status request.",
        "",
        "Notify.",
        "Update.",
    };
    if(code <= 5)
        return names[code];
    else if(code == 15)
        return "reserved.";
    else
        return "unknown";
    /*
0	QUERY, Standard query.	RFC 1035
1	IQUERY, Inverse query.	RFC 1035, RFC 3425
2	STATUS, Server status request.	RFC 1035
3
4	Notify.	RFC 1996
5	Update.	RFC 2136
6
-
15	reserved.
*/
}

const char *get_dns_rcode_name(uchar code)
{
    static const char * names[] = {
        "No error",
        "Format error",
        "Server failure",
        "Name Error",
        "Not Implemented",
        "Refused",
        "YXDomain",
        "YXRRSet",
        "NXRRSet",
        "NotAuth",
        "NotZone",
    };
    if(code <= 10)
        return names[code];
    else
        return "unkonwn";
    /*
0	No error. The request completed successfully.	RFC 1035
1	Format error. The name server was unable to interpret the query.	RFC 1035
2	Server failure. The name server was unable to process this query due to a problem with the name server.	RFC 1035
3	Name Error. Meaningful only for responses from an authoritative name server, this code signifies that the domain name referenced in the query does not exist.	RFC 1035
4	Not Implemented. The name server does not support the requested kind of query.	RFC 1035
5	Refused. The name server refuses to perform the specified operation for policy reasons. For example, a name server may not wish to provide the information to the particular requester, or a name server may not wish to perform a particular operation (e.g., zone transfer) for particular data.	RFC 1035
6	YXDomain. Name Exists when it should not.	RFC 2136
7	YXRRSet. RR Set Exists when it should not.	RFC 2136
8	NXRRSet. RR Set that should exist does not.	RFC 2136
9	NotAuth. Server Not Authoritative for zone.	RFC 2136
10	NotZone. Name not contained in zone.
*/
}

const char *get_dns_type_name(ushort type)
{
    static const char * names[] = {
        "",
        "A, IPv4 address",
        "NS, Authoritative name server",
        "MD, Mail destination",
        "MF, Mail forwarder",
        "CNAME",
        "SOA, Start of authority",
        "MB, Mailbox domain name",
        "MG, Mail group member",
        "MR, Mail rename domain name",
        "NULL, Null resource record",
        "WKS, Well known service",
        "PTR, Domain name pointer",
        "HINFO, Host information",
        "MINFO, Mail list information",
        "MX, Mail exchange",
        "TXT, Text strings",
        "RP, Responsible Person",
        "AFSDB, AFS Data Base location",
        "X25, X.25 PSDN address",
        "ISDN, ISDN address",
        "RT, Route Through",
        "NSAP, NSAP address",
        "NSAP-PTR",
        "SIG, Security signature",
        "KEY, Security key",
        "PX, X.400 mail mapping information",
        "GPOS, Geographical Position",
        "AAAA, IPv6 Address",
        "LOC, Location Information",
        "NXT, Next Domain (obsolete)",
        "EID, Endpoint Identifier",
        "NIMLOC, Nimrod Locator NB",
        "SRV, Server Selection",
    };
    if(type <= 33)
        return names[type];
    return "unkonwn";
    /*
0
1	A, IPv4 address.	RFC 1035
2	NS, Authoritative name server.	RFC 1035
3	MD, Mail destination. Obsolete use MX instead.	RFC 1035
4	MF, Mail forwarder. Obsolete use MX instead.	RFC 1035
5	CNAME, Canonical name for an alias.	RFC 1035
6	SOA, Marks the start of a zone of authority.	RFC 1035
7	MB, Mailbox domain name.	RFC 1035
8	MG, Mail group member.	RFC 1035
9	MR, Mail rename domain name.	RFC 1035
10	NULL, Null resource record.	RFC 1035
11	WKS, Well known service description.	RFC 1035
12	PTR, Domain name pointer.	RFC 1035
13	HINFO, Host information.	RFC 1035
14	MINFO, Mailbox or mail list information.	RFC 1035
15	MX, Mail exchange.	RFC 1035
16	TXT, Text strings.	RFC 1035
17	RP, Responsible Person.	RFC 1183
18	AFSDB, AFS Data Base location.	RFC 1183, RFC 5864
19	X25, X.25 PSDN address.	RFC 1183
20	ISDN, ISDN address.	RFC 1183
21	RT, Route Through.	RFC 1183
22	NSAP, NSAP address. NSAP style A record.	RFC 1706
23	NSAP-PTR.	RFC 1348
24	SIG, Security signature.	RFC 2931, RFC 4034
25	KEY, Security key.	RFC 3445, RFC 4034
26	PX, X.400 mail mapping information.	RFC 2163
27	GPOS, Geographical Position.	RFC 1712
28	AAAA, IPv6 Address.	RFC 3596
29	LOC, Location Information.	RFC 1876
30	NXT, Next Domain (obsolete).	RFC 2535
31	EID, Endpoint Identifier.
32	NIMLOC, Nimrod Locator.
NB, NetBIOS general Name Service.
RFC 1002
33	SRV, Server Selection.
NBSTAT, NetBIOS NODE STATUS.	RFC 2052, RFC 2782
RFC 1002
34	ATMA, ATM Address.
35	NAPTR, Naming Authority Pointer.	RFC 3403
36	KX, Key Exchanger.	RFC 2230
37	CERT.	RFC 2538, RFC 4398
38	A6.	RFC 2874, RFC 3226, RFC 6563
39	DNAME.	RFC 2672
40	SINK.
41	OPT.	RFC 2671
42	APL.	RFC 3123
43	DS, Delegation Signer.	RFC 3658
44	SSHFP, SSH Key Fingerprint.	RFC 4255
45	IPSECKEY.	RFC 4025
46	RRSIG.	RFC 3755
47	NSEC, NextSECure.	RFC 3755, RFC 3845
48	DNSKEY.	RFC 3755
49	DHCID, DHCP identifier.	RFC 4701
50	NSEC3.	RFC 5155
51	NSEC3PARAM.	RFC 5155
52	TLSA
53
54
55	HIP, Host Identity Protocol.	RFC 5205
56	NINFO.
57	RKEY.
58	TALINK, Trust Anchor LINK.
59	Child DS.
60
-
98
99	SPF, Sender Policy Framework.	RFC 4408
100	UINFO.
101	UID.
102	GID.
103	UNSPEC.
104
-
248
249	TKEY.	RFC 2930
250	TSIG, Transaction Signature.	RFC 2845, RFC 3645
251	IXFR, Incremental transfer.	RFC 1995
252	AXFR, A request for a transfer of an entire zone.	RFC 1035
253	MAILB, A request for mailbox-related records (MB, MG or MR).	RFC 1035
254	MAILA, A request for mail agent RRs. Obsolete.	RFC 1035
255	*. A request for all records.	RFC 1035
256	URI.
257	CAA, Certification Authority Authorization.
*/
}

const char *get_dns_class_name(ushort cls)
{
    static const char * names[] = {
        "Reserved",
        "IN, Internet",
        "",
        "CH, Chaos",
        "HS, Hesiod",
    };
    if(cls <= 4)
        return names[cls];
    else if(cls == 254)
        return "None";
    else if(cls == 255)
        return "Any";
    else
        return "";
    /*
0	Reserved.	RFC 5395
1	IN, Internet.	RFC 1035.
2
3	CH, Chaos.	RFC 1035.
4	HS, Hesiod.	RFC 1035.
5
-
253
254	None.	RFC 2136.
255	Any (QCLASS only).	RFC 1035.
*/
}

const char *get_dhcp_option_name(uchar option)
{
    static const char * options[] = {
        "Pad.",
        "Subnet Mask.",
        "Time Offset (deprecated).",
        "Router.",
        "Time Server.",
        "Name Server.",
        "Domain Name Server.",
        "Log Server.",
        "Quote Server.",
        "LPR Server.",
        "Impress Server.",
        "Resource Location Server.",
        "Host Name.",
        "Boot File Size.",
        "Merit Dump File.",
        "Domain Name.",
        "Swap Server.",
        "Root Path.",
        "Extensions Path.",
        "IP Forwarding enable/disable.",
        "Non-local Source Routing enable/disable.",
        "Policy Filter.",
        "Maximum Datagram Reassembly Size.",
        "Default IP Time-to-live.",
        "Path MTU Aging Timeout.",
        "Path MTU Plateau Table.",
        "Interface MTU.",
        "All Subnets are Local.",
        "Broadcast Address.",
        "Perform Mask Discovery.",
        "Mask supplier.",
        "Perform router discovery.",
        "Router solicitation address.",
        "Static routing table.",
        "Trailer encapsulation.",
        "ARP cache timeout.",
        "Ethernet encapsulation.",
        "Default TCP TTL.",
        "TCP keepalive interval.",
        "TCP keepalive garbage.",
        "Network Information Service Domain.",
        "Network Information Servers.",
        "NTP servers.",
        "Vendor specific information.",
        "NetBIOS over TCP/IP name server.",
        "NetBIOS over TCP/IP Datagram Distribution Server.",
        "NetBIOS over TCP/IP Node Type.",
        "NetBIOS over TCP/IP Scope.",
        "X Window System Font Server.",
        "X Window System Display Manager.",
        "Requested IP Address.",
        "IP address lease time.",
        "Option overload.",
        "DHCP message type.",
        "Server identifier.",
        "Parameter request list.",
        "Message.",
        "Maximum DHCP message size.",
        "Renew time value.",
        "Rebinding time value.",
        "Class-identifier.",
        "Client-identifier.",
        "NetWare/IP Domain Name.",
        "NetWare/IP information.",
        "Network Information Service+ Domain.",
        "Network Information Service+ Servers.",
        "TFTP server name.",
        "Bootfile name.",
        "Mobile IP Home Agent.",
        "Simple Mail Transport Protocol Server.",
        "Post Office Protocol Server.",
        "Network News Transport Protocol Server.",
        "Default World Wide Web Server.",
        "Default Finger Server.",
        "Default Internet Relay Chat Server.",
        "StreetTalk Server.",
        "StreetTalk Directory Assistance Server.",
        "User Class Information.",
        "SLP Directory Agent.",
        "SLP Service Scope.",
        "Rapid Commit.",
        "FQDN, Fully Qualified Domain Name.",
        "Relay Agent Information.",
        "Internet Storage Name Service.",
        "",
        "NDS servers.",
        "NDS tree name.",
        "NDS context.",
        "BCMCS Controller Domain Name list.",
        "BCMCS Controller IPv4 address list.",
        "Authentication.",
        "client-last-transaction-time.",
        "associated-ip.",
        "Client System Architecture Type.",
        "Client Network Interface Identifier",
        "LDAP, Lightweight Directory Access Protocol.",
        "",
        "Client Machine Identifier.",
        "Open Group's User Authentication.",
        "GEOCONF_CIVIC.",
        "IEEE 1003.1 TZ String.",
        "Reference to the TZ Database.",
    };
    if(option <= 101)
        return options[option];
    if(option == 255)
        return "End";
    return "";

/*
Code	Data length	Description	References
0	0	Pad.	RFC 2132
1	4	Subnet Mask.	RFC 2132
2	4	Time Offset (deprecated).	RFC 2132
3	4+	Router.	RFC 2132
4	4+	Time Server.	RFC 2132
5	4+	Name Server.	RFC 2132
6	4+	Domain Name Server.	RFC 2132
7	4+	Log Server.	RFC 2132
8	4+	Quote Server.	RFC 2132
9	4+	LPR Server.	RFC 2132
10	4+	Impress Server.	RFC 2132
11	4+	Resource Location Server.	RFC 2132
12	1+	Host Name.	RFC 2132
13	2	Boot File Size.	RFC 2132
14	1+	Merit Dump File.	RFC 2132
15	1+	Domain Name.	RFC 2132
16	4	Swap Server.	RFC 2132
17	1+	Root Path.	RFC 2132
18	1+	Extensions Path.	RFC 2132
19	1	IP Forwarding enable/disable.	RFC 2132
20	1	Non-local Source Routing enable/disable.	RFC 2132
21	8+	Policy Filter.	RFC 2132
22	2	Maximum Datagram Reassembly Size.	RFC 2132
23	1	Default IP Time-to-live.	RFC 2132
24	4	Path MTU Aging Timeout.	RFC 2132
25	2+	Path MTU Plateau Table.	RFC 2132
26	2	Interface MTU.	RFC 2132
27	1	All Subnets are Local.	RFC 2132
28	4	Broadcast Address.	RFC 2132
29	1	Perform Mask Discovery.	RFC 2132
30	1	Mask supplier.	RFC 2132
31	1	Perform router discovery.	RFC 2132
32	4	Router solicitation address.	RFC 2132
33	8+	Static routing table.	RFC 2132
34	1	Trailer encapsulation.	RFC 2132
35	4	ARP cache timeout.	RFC 2132
36	1	Ethernet encapsulation.	RFC 2132
37	1	Default TCP TTL.	RFC 2132
38	4	TCP keepalive interval.	RFC 2132
39	1	TCP keepalive garbage.	RFC 2132
40	1+	Network Information Service Domain.	RFC 2132
41	4+	Network Information Servers.	RFC 2132
42	4+	NTP servers.	RFC 2132
43	1+	Vendor specific information.	RFC 1533, RFC 2132
44	4+	NetBIOS over TCP/IP name server.	RFC 1533, RFC 2132
45	4+	NetBIOS over TCP/IP Datagram Distribution Server.	RFC 1533, RFC 2132
46	1	NetBIOS over TCP/IP Node Type.	RFC 1533, RFC 2132
47	1+	NetBIOS over TCP/IP Scope.	RFC 1533, RFC 2132
48	4+	X Window System Font Server.	RFC 1533, RFC 2132
49	4+	X Window System Display Manager.	RFC 1533, RFC 2132
50	4	Requested IP Address.	RFC 1533, RFC 2132
51	4	IP address lease time.	RFC 1533, RFC 2132
52	1	Option overload.	RFC 1533, RFC 2132
53	1	DHCP message type.	RFC 1533, RFC 2132, RFC 3203, RFC 4388
54	4	Server identifier.	RFC 1533, RFC 2132
55	1+	Parameter request list.	RFC 1533, RFC 2132
56	1+	Message.	RFC 1533, RFC 2132
57	2	Maximum DHCP message size.	RFC 1533, RFC 2132
58	4	Renew time value.	RFC 1533, RFC 2132
59	4	Rebinding time value.	RFC 1533, RFC 2132
60	1+	Class-identifier.	RFC 1533, RFC 2132
61	2+	Client-identifier.	RFC 1533, RFC 2132, RFC 4361
62	1 to 255	NetWare/IP Domain Name.	RFC 2242
63		NetWare/IP information.	RFC 2242
64	1+	Network Information Service+ Domain.	RFC 2132
65	4+	Network Information Service+ Servers.	RFC 2132
66	1+	TFTP server name.	RFC 2132
67	1+	Bootfile name.	RFC 2132
68	0+	Mobile IP Home Agent.	RFC 2132
69	4+	Simple Mail Transport Protocol Server.	RFC 2132
70	4+	Post Office Protocol Server.	RFC 2132
71	4+	Network News Transport Protocol Server.	RFC 2132
72	4+	Default World Wide Web Server.	RFC 2132
73	4+	Default Finger Server.	RFC 2132
74	4+	Default Internet Relay Chat Server.	RFC 2132
75	4+	StreetTalk Server.	RFC 2132
76	4+	StreetTalk Directory Assistance Server.	RFC 2132
77	Variable.	User Class Information.	RFC 3004
78	Variable.	SLP Directory Agent.	RFC 2610
79	Variable.	SLP Service Scope.	RFC 2610
80	0	Rapid Commit.	RFC 4039
81	4+.	FQDN, Fully Qualified Domain Name.	RFC 4702
82	Variable.	Relay Agent Information.	RFC 3046, RFC 5010
83	14+	Internet Storage Name Service.	RFC 4174
84	 	 	RFC 3679
85	Variable.	NDS servers.	RFC 2241
86	Variable.	NDS tree name.	RFC 2241
87	Variable.	NDS context.	RFC 2241
88	Variable.	BCMCS Controller Domain Name list.	RFC 4280
89	4+	BCMCS Controller IPv4 address list.	RFC 4280
90	Variable.	Authentication.	RFC 3118
91	4	client-last-transaction-time.	RFC 4388
92	4n	associated-ip.	RFC 4388
93	Variable.	Client System Architecture Type.	RFC 4578
94	Variable.	Client Network Interface Identifier.	RFC 4578
95	Variable.	LDAP, Lightweight Directory Access Protocol.	RFC 3679
96	 	 	RFC 3679
97	Variable.	Client Machine Identifier.	RFC 4578
98	 	Open Group's User Authentication.	RFC 2485
99	 	GEOCONF_CIVIC.	RFC 4776
100	 	IEEE 1003.1 TZ String.	RFC 4833
101	 	Reference to the TZ Database.	RFC 4833
102
-
111	 	 	RFC 3679
112	Variable.	NetInfo Parent Server Address.	RFC 3679
113	Variable.	NetInfo Parent Server Tag.	RFC 3679
114	Variable.	URL.	RFC 3679
115	 	 	RFC 3679
116	1	Auto-Configure	RFC 2563
117	2+	Name Service Search.	RFC 2937
118	4	Subnet Selection.	RFC 3011
119	Variable	DNS domain search list.	RFC 3397
120	Variable	SIP Servers DHCP Option.	RFC 3361
121	5+	Classless Static Route Option.	RFC 3442
122	Variable	CCC, CableLabs Client Configuration.	RFC 3495, RFC 3594, RFC 3634
123	16	GeoConf.	RFC 3825
124	 	Vendor-Identifying Vendor Class.	RFC 3925
125	 	Vendor-Identifying Vendor-Specific.	RFC 3925
126	 	 	RFC 3679
127	 	 	RFC 3679
128	 	TFTP Server IP address.	RFC 4578
129	 	Call Server IP address.	RFC 4578
130	 	Discrimination string.	RFC 4578
131	 	Remote statistics server IP address.	RFC 4578
132	 	802.1P VLAN ID.	RFC 4578
133	 	802.1Q L2 Priority.	RFC 4578
134	 	Diffserv Code Point.	RFC 4578
135	 	HTTP Proxy for phone-specific applications.	RFC 4578
136	4+	PANA Authentication Agent.	RFC 5192
137	variable	LoST Server.	RFC 5223
138	 	CAPWAP Access Controller addresses.	RFC 5417
139	 	OPTION-IPv4_Address-MoS.	RFC 5678
140	 	OPTION-IPv4_FQDN-MoS.	RFC 5678
141	2+	SIP UA Configuration Service Domains.	RFC 6011
142	 	OPTION-IPv4_Address-ANDSF.	RFC 6153
143	 	OPTION-IPv6_Address-ANDSF.	RFC 6153
144
-
149	 	 	RFC 3942
150	 	TFTP server address.	RFC 5859
150	 	Etherboot.
GRUB configuration path name.
151	 	status-code.
152	 	base-time.
153	 	start-time-of-state.
154	 	query-start-time.
155	 	query-end-time.
156	 	dhcp-state.
157	 	data-source.
158
-
174	 	 	RFC 3942
175	 	Etherboot.
176	 	IP Telephone.
177	 	Etherboot.
PacketCable and CableHome.
178
-
207	 	 	RFC 3942
208	 	pxelinux.magic (string) = F1:00:74:7E (241.0.116.126).	RFC 5071
209	 	pxelinux.configfile (text).	RFC 5071
210	 	pxelinux.pathprefix (text).	RFC 5071
211	 	pxelinux.reboottime (unsigned integer 32 bits).	RFC 5071
212	18+	OPTION_6RD.	RFC 5969
213	 	OPTION_V4_ACCESS_DOMAIN.	RFC 5986
214
-
219
220	 	Subnet Allocation.
221
1+

Virtual Subnet Selection.	RFC 6607
222
223	 	 	RFC 3942
224
-
254	 	Private use.
255	0	End.	RFC 2132

*/
}

const char *get_dhcp_message_type_name(uchar type)
{
    static const char * names[] = {
        "",
        "DHCPDISCOVER",
        "DHCPOFFER",
        "DHCPREQUEST",
        "DHCPDECLINE",
        "DHCPACK",
        "DHCPNAK",
        "DHCPRELEASE",
        "DHCPINFORM",
        "DHCPFORCERENEW",
        "DHCPLEASEQUERY",
        "DHCPLEASEUNASSIGNED",
        "DHCPLEASEUNKNOWN",
        "DHCPLEASEACTIVE",
        "DHCPBULKLEASEQUERY",
        "DHCPLEASEQUERYDONE",
        "DHCPACTIVELEASEQUERY",
        "DHCPLEASEQUERYSTATUS",
        "DHCPTLS",
    };
    if(type <= 18)
        return names[type];
    return "unknown";
/*
1   DHCPDISCOVER
2   DHCPOFFER
3   DHCPREQUEST
4   DHCPDECLINE
5   DHCPACK
6   DHCPNAK
7   DHCPRELEASE
8   DHCPINFORM
9   DHCPFORCERENEW
10  DHCPLEASEQUERY
11  DHCPLEASEUNASSIGNED
12  DHCPLEASEUNKNOWN
13  DHCPLEASEACTIVE
14  DHCPBULKLEASEQUERY
15  DHCPLEASEQUERYDONE
16  DHCPACTIVELEASEQUERY
17  DHCPLEASEQUERYSTATUS
18  DHCPTLS
*/
}

const char *get_snmp_encoding_type_name(uchar type)
{
    static const int values[] ={
        0x01, 0x02, 0x04, 0x05, 0x06,
        0x0A, 0x30, 0x31, 0x40, 0x41,
        0x42, 0x43, 0x44, 0xA0, 0xA1,
        0xA2, 0xA3, 0xA4,
    };
    static const char * names[] = {
        "BOOL", "INT", "OCTSTR", "NULL", "OBJID",
        "ENUM", "SEQ", "SETOF", "IPADDR", "COUNTER",
        "GAUGE", "TIMETICKS", "OPAQUE", "GET", "GETNEXT",
        "GETResp", "SET", "TRAP",
    };
    for(uint i = 0; i < sizeof(values); i++)
        if(values[i] == type)
            return names[i];
    return "Undefine";
}

#ifndef SNIFFERTYPE_H_
#define SNIFFERTYPE_H_

#include <string>
#include "common.h"

#define FAIL_RETURN (-0x1243fe)

/* TODO:
ARP Done
RARP Done
IP   Done
ICMP, Done
TCP Done
UDP Done
IGMP Done
BOOTP Done
DHCP Done
SNMP
DNS done
IPv6 done
*/
typedef struct _eth_header  // MAC头部（14字节）
{  
    uchar dstmac[6];	// 目标mac地址
    uchar srcmac[6];	// 来源mac地址
    ushort eth_type;	// 以太网类型
}eth_header;


typedef struct _arp_header  // ARP 头部（28字节）
{
    ushort arp_hrd;		// 硬件类型
    ushort arp_pro;		// 协议类型
    uchar arp_hln;		// 硬件地址长度
    uchar arp_pln;		// 协议地址长度
    ushort arp_op;		// ARP操作类型
    uchar arp_sha[6];	// 发送者的硬件地址
    uchar arp_spa[4];		// 发送者的协议地址
    uchar arp_tha[6];	// 目标的硬件地址
    uchar arp_tpa[4];		// 目标的协议地址
}arp_header;

// IP 协议头 协议(Protocol) 字段标识含义
//      协议      协议号

#define IP_SIG			(0)
#define ICMP_SIG		(1)
#define IGMP_SIG		(2)
#define GGP_SIG			(3)
#define IP_ENCAP_SIG	(4)
#define ST_SIG			(5)
#define TCP_SIG			(6)
#define EGP_SIG			(8)
#define PUP_SIG			(12)
#define UDP_SIG			(17)
#define HMP_SIG			(20)
#define XNS_IDP_SIG		(22)
#define RDP_SIG			(27)
#define TP4_SIG			(29)
#define XTP_SIG			(36)
#define DDP_SIG			(37)
#define IDPR_CMTP_SIG	(39)
#define RSPF_SIG		(73)
#define VMTP_SIG		(81)
#define OSPFIGP_SIG		(89)
#define IPIP_SIG		(94)
#define ENCAP_SIG		(98)


typedef struct _ip_header{ // IPv4头部（20字节）
    uchar head_len:4;  // 首部长度 (4 bits)
    uchar version:4; // 版本 (4 bits)
    uchar tos;     // 服务类型(Type of service)
    ushort tlen;    // 总长(Total length)
    ushort identification; // 标识(Identification)
    uchar fo_1:5;
    uchar flags:3; // 标志位(Flags) (3 bits)
    uchar fo_2; // 段偏移量(Fragment offset) (13 bits)
    uchar ttl;  // 存活时间(Time to live)
    uchar proto; // 协议(Protocol)
    ushort crc; // 首部校验和(Header checksum)
    uchar saddr[4]; // 源地址(Source address)
    uchar daddr[4]; // 目标地址(Destination address)
}ip_header;

typedef struct _ipv6_header{
    uchar traffic_1:4;
    uchar version:4;
    uchar flow:4;
    uchar traffic_2:4;
    ushort flow23;
    ushort payload;
    uchar next;
    uchar hop_limit;
    uchar saddr[16];
    uchar daddr[16];
}ipv6_header;

// 位域现排列低位再高位
// 网络是大端序
typedef struct _tcp_header{  // TCP头部（20字节）
    ushort	sport;				// 源端口号
    ushort	dport;				// 目的端口号
    uint	seq_no;				// 序列号
    uint	ack_no;				// 确认号
    uchar	reserved_1:4;		// 保留6位中的4位首部长度
    uchar	thl:4;				// tcp头部长度
    uchar	flag:6;				// 6位标志
    uchar	reseverd_2:2;		// 保留6位中的2位
    ushort	wnd_size;			// 16位窗口大小
    ushort	chk_sum;			// 16位TCP检验和
    ushort	urgt_p;				// 16为紧急指针
}tcp_header;

// UDP头部（8字节）
typedef struct _udp_header{
    ushort	sport;		// 源端口(Source port)
    ushort	dport;		// 目的端口(Destination port)
    ushort	len;		// UDP数据包长度(Datagram length)
    ushort	crc;		// 校验和(Checksum)
}udp_header;

typedef struct _icmp_header{
    uchar type;
    uchar code;
    ushort crc;
}icmp_header;

typedef struct _igmp_header{
    uchar type:4;
    uchar version:4;
    uchar unused;
    ushort crc;
    uchar addr[4];
}igmp_header;

typedef struct _igmp_header_v2{
    uchar type;
    uchar mrt;
    ushort crc;
    uchar addr[4];
}igmp_header_v2;

typedef struct _dns_header{
    ushort id;
    uchar RD:1;
    uchar TC:1;
    uchar AA:1;
    uchar opcode:4;
    uchar QR:1;
    uchar rcode:4;
    uchar zero:3;
    uchar RA:1;
    ushort ques_count;
    ushort reso_count;
    ushort auth_count;
    ushort extra_count;
}dns_header;

typedef struct _dhcp_header{
    uchar op; // operation
    uchar htype; // hardware type
    uchar hlen; // hardware address length
    uchar hpos; //
    uint transaction_id;
    ushort secs;
    ushort flags;
    uchar ci_addr[4]; // client ip address
    uchar yi_addr[4]; // your ip
    uchar si_addr[4]; // server ip
    uchar gi_addr[4]; // gateway ip
    uchar ch_addr[16]; // client hardware addr
    uchar server_name[64];
    uchar bootp[128]; //
    uint mcookie; // magic cookie
}dhcp_header;

typedef struct _ber_header{
    uchar type;
    uchar length;
    uchar content[1];
}ber_header;

// 定义一些应用层协议使用的端口号

// TCP 协议
#define FTP_PORT 		(21)
#define TELNET_PORT 	(23)
#define SMTP_PORT 		(25) 
#define HTTP_PORT  		(80) 
#define HTTPS_PORT		(443) 
#define HTTP2_PORT 		(8080)
#define POP3_PORT 		(110)

// UDP 协议
#define DNS_PORT		(53)
#define SNMP_PORT		(161)
#define SNMP2_PORT      (162)

#define DHCP_PORT       (67)
#define DHCP2_PORT      (68)

// 网络设备信息结构
typedef struct _NetDevInfo
{
    std::string name;
    std::string describe;
    std::string ipv4FN;
    std::string ipv4addr;
    std::string ipv6FN;
    std::string ipv6addr;
}NetDevInfo;



#endif	// SNIFFERTYPE_H_

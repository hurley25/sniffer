#ifndef PROTOCOLNAMES_H
#define PROTOCOLNAMES_H
#include "common.h"
const char *get_arp_hardware_type_name(ushort htype);
const char *get_ip_protocol_name(uchar proto);
const char *get_arp_operation_code(ushort code);
const char *get_tcp_option_name(uchar option);
const char *get_icmp_type_name(uchar type);
const char *get_icmp_code_name(uchar type, uchar code);
const char *get_igmp_type_name(uchar type);
const char *get_dns_opcode_name(uchar code);
const char *get_dns_rcode_name(uchar code);
const char *get_dns_type_name(ushort type);
const char *get_dns_class_name(ushort cls);
const char *get_dhcp_option_name(uchar option);
const char *get_dhcp_message_type_name(uchar type);
const char *get_snmp_encoding_type_name(uchar type);


#endif // PROTOCOLNAMES_H

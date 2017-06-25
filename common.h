#ifndef COMMON_H
#define COMMON_H

#include <vector>
#include <string>
using std::vector;
using std::string;
typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned short ushort;

struct sockaddr;
struct in_addr;
const string iptos(struct in_addr);
const string ip6tos(struct sockaddr *sockaddr);

const char * getIPProtocolName(unsigned short srcPort, unsigned short dstPort);
ushort analyseEthernet(const uchar * chr, int len, vector<string> & protocolStack);
uchar analyseIPv4(const uchar * chr, int len, vector<string> & protocolStack);
int analyseIPv6(const uchar * chr, int len, vector<string> & protocolStack);
int analyseTCP(const uchar *chr, int len, vector<string> & protocolStack);
int analyseUDP(const uchar *chr, int len, vector<string> & protocolStack);
int analyseHTTP(const uchar *chr, int len, vector<string> & protocolStack);
int analyseSNMP(const uchar *chr, int len, vector<string> & protocolStack);
int analyseARP(const uchar *chr, int len, vector<string> & protocolStack);
int analyseRARP(const uchar *chr, int len, vector<string> & protocolStack);
int analyseICMP(const uchar *chr, int len, vector<string> & protocolStack);

#endif // TOOLS_H

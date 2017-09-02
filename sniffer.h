
#ifndef SNIFFER_H_
#define SNIFFER_H_

#include "csniffer.h"
#include "sniffertype.h"
#include "captureview.h"
#include "common.h"

using std::vector;
using std::string;

class Sniffer : public CSniffer
{
private:
    Sniffer();
public:

	~Sniffer();

    bool updateDevList();
    void printDevInfo();
    const QString getExplainText(const int number) const;
    const QString  getHexText(const int number) const;
    const string getPacket(const size_t number) const;
    size_t getPacketsCount() const;
    void deal_packet(CapTableView *mainTree, int num);
    void analyseAbstract(
            const uchar *chr, string &src_addr, string &dst_addr,
            string &protocol, string &info);
    void analyse(int number, vector<string> & infos);
    void reset();

public:
	std::vector<NetDevInfo>  netDevInfo;

public:
    static Sniffer * get_sniffer();

private:

};

#endif	// SNIFFER_H_

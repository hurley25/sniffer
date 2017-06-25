#ifndef CSNIFFER_H_
#define CSNIFFER_H_

#include <vector>
#include <string>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pcap.h>
#define PCAP_BUF_SIZE 					1024
#define PCAP_SRC_IF_STRING 				"rpcap://"
#define PCAP_OPENFLAG_PROMISCUOUS		1
#define PCAP_SRC_FILE					2
#define PCAP_OPENFLAG_NOCAPTURE_LOCAL	8



class CSniffer
{
public:
	CSniffer();
	~CSniffer();

	typedef void (*pSnifferCB)(u_char *, const struct pcap_pkthdr *, const u_char *);

	bool findAllNetDevs();											// 获取全部网络设备列表信息

	void freeNetDevsMem();											// 释放网络设备信息占据的堆内存

    bool openOffline(const char * fileName);
	bool openNetDev(char *szDevName, 								// 根据名称打开网络设备
						int flag = PCAP_OPENFLAG_PROMISCUOUS,
							int iLengthLimit = 65536);

	bool openNetDev(int iDevNum, 									// 根据序号打开网络设备
						int flag = PCAP_OPENFLAG_PROMISCUOUS,
							int iLengthLimit = 65536);

	bool closeNetDev();												// 关闭当前打开的网络设备
	bool setDevsFilter(const char *szFilter);						// 对当前打开设备设置过滤器
    bool checkCaptureFilter(const char * filter);
	int	 captureOnce();												// 捕获一次网络数据包
	bool captureByCallBack(pSnifferCB func);						// 以回调函数方式捕获数据

	// 只有当接口打开时，调用 openDumpFile() 才是有效的
	bool openDumpFile(const char *szFileName);						// 打开堆文件（文件保存数据包）

    void saveToDumpFile(u_char *dumpfile, 							// 保存捕获的数据到文件
							struct pcap_pkthdr *header,
						 	u_char *pkt_data);

    void saveCurrentPacket();											// 保存捕获的数据到文件
					
	void closeDumpFile();											// 关闭堆文件

    void printDevInfo();											// 控制台打印网络设备信息
    bool haveDevHandle() const;
    const char * getDumpFileName() const;
    bool haveDumpFile() const;
    bool dumpFlush() const;
public:
	struct	pcap_pkthdr *header;
	const u_char		*pkt_data;

protected:
    pcap_if_t		*allNetDevList;					// 网络设备列表信息链表指针
    int				netDevCount;					// 网络设备数量
    pcap_t			*devHandle;						// 当前打开的设备句柄（指针）
    pcap_dumper_t	*dumpFile;						// 要保存到的文件指针
    std::string dumpFileName;
    char errbuf[PCAP_ERRBUF_SIZE];   // 错误信息缓冲
    std::vector<std::string> packets;
    std::vector<struct pcap_pkthdr> headers;
};

#endif	// CSNIFFER_H_

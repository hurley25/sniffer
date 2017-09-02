#include <sys/socket.h>
#include <netinet/in.h>
#include <pcap.h>
#include <netdb.h>

#include <QDebug>

#include "csniffer.h"



CSniffer::CSniffer()
{
    allNetDevList = NULL;
    netDevCount = 0;
    devHandle    = NULL;
    dumpFile   = NULL;
}

CSniffer::~CSniffer()
{
    freeNetDevsMem();
    closeDumpFile();
}

bool CSniffer::findAllNetDevs()
{
    freeNetDevsMem();

    if (pcap_findalldevs(&allNetDevList, errbuf) == -1)
    {
        return false;
    }

    for (pcap_if_t *index = allNetDevList; index != NULL; index = index->next)
    {
        netDevCount++;
    }

    return true;
}


bool CSniffer::openNetDev(char *szDevName, int flag, int iLengthLimit)
{
    if (devHandle != NULL)
    {
        closeNetDev();
    }
    devHandle = pcap_open_live(  szDevName,          // 设备名
                                iLengthLimit,       // 数据包大小限制
                                flag,               // 网卡设置打开模式
                                1000,               // 读取超时时间
                                errbuf);            // 错误缓冲


    if (devHandle == NULL)
    {
        return false;
    }

    return true;
}

bool CSniffer::openOffline(const char * fileName)
{
    if (fileName == NULL)
        return false;
    if (devHandle != NULL)
        closeNetDev();
    devHandle = pcap_open_offline(fileName, errbuf);
    return devHandle != NULL;
}

bool CSniffer::openNetDev(int iDevNum, int flag, int iLengthLimit)
{
    if (iDevNum < 1 || iDevNum > netDevCount)
    {
        return false;
    }

    pcap_if_t *index = allNetDevList;

    for (int i = 1; i < iDevNum; i++)
    {
        index = index->next;
    }

    if (devHandle != NULL)
    {
        closeNetDev();
    }

    devHandle = pcap_open_live(  index->name,        // 设备名
                                iLengthLimit,       // 数据包大小限制
                                flag,               // 网卡设置打开模式
                                1000,               // 读取超时时间
                                errbuf);            // 错误缓冲

    return devHandle != NULL;
}

bool CSniffer::closeNetDev()
{
    if (devHandle != NULL)
    {
        pcap_close(devHandle);
        devHandle = NULL;
        return true;
    }

    return false;
}

void CSniffer::freeNetDevsMem()
{
    if (allNetDevList)
    {
        pcap_freealldevs(allNetDevList);
        allNetDevList = NULL;
    }
}

bool CSniffer::setDevsFilter(const char *szFilter)
{
    // 检查数据链路层，只考虑以太网
    if (pcap_datalink( devHandle ) != DLT_EN10MB )
        return false;
    u_int netmask = 0xFFFFFF;
    struct bpf_program fcode;
    if (pcap_compile(devHandle, &fcode, szFilter, 1, netmask) < 0)
    {
        qDebug() << "Filter Failed" <<endl;
        return false;
    }
    if (pcap_setfilter(devHandle, &fcode) < 0)
    {
        qDebug() << "Filter Failed" <<endl;
        return false;
    }
    return true;
}

bool CSniffer::checkCaptureFilter(const char *filter)
{
    u_int netmask = 0xFFFFFF;
    struct bpf_program fcode;
    return pcap_compile(devHandle, &fcode, filter, 1, netmask) >= 0;
}

bool CSniffer::captureByCallBack(pSnifferCB func)
{
    if (devHandle != NULL)
        pcap_loop(devHandle, 0, func, (unsigned char *)dumpFile);
    return devHandle != NULL;
}

int CSniffer::captureOnce()
{
    if (devHandle == NULL)
        return -2;
    return pcap_next_ex( devHandle, &header, &pkt_data);
}

bool CSniffer::openDumpFile(const char *szFileName)
{
    closeDumpFile();
    dumpFile = pcap_dump_open(devHandle, szFileName);
    if(dumpFile != NULL)
        dumpFileName = szFileName;
    return (dumpFile != NULL);
}

void CSniffer::saveToDumpFile(u_char *dumpfile, struct pcap_pkthdr *header, u_char *pkt_data)
{
    if (dumpfile != NULL)
        pcap_dump(dumpfile, header, pkt_data);
}

void CSniffer::saveCurrentPacket()
{
    if (dumpFile != NULL)
        pcap_dump((uchar *)dumpFile, header, pkt_data);
}

void CSniffer::closeDumpFile()
{
    if (dumpFile != NULL)
    {
        pcap_dump_close(dumpFile);
        dumpFile = NULL;
    }
}

void CSniffer::printDevInfo()
{
    pcap_if_t   *index;
    pcap_addr_t *pAddr;
    char ip6str[128];
    int i = 0;
    for (index = allNetDevList; index != NULL; index = index->next)
    {
        printf( "%d. %s\n", ++i, index->name );

        if (index->description)
        {
            printf(" (%s)\n\n", index->description);
        }
        else
        {
            printf(" (No description available)\n\n");
        }

        for (pAddr = index->addresses; pAddr != NULL; pAddr = pAddr->next)
        {
            printf("Address Family: #%d\n", pAddr->addr->sa_family);

            switch (pAddr->addr->sa_family)
            {
            case AF_INET:
                printf("\tAddress Family Name: AF_INET(IPV4)\n");
                break;
            case AF_INET6:
                printf("\tAddress Family Name: AF_INET6(IPV6)\n");
                break;
            default:
                printf("\tAddress Family Name: Unknown\n");
            }
            printf("\n");
        }
    }
}

bool CSniffer::haveDevHandle() const
{
    return this->devHandle != NULL;
}

const char * CSniffer::getDumpFileName() const
{
    return this->dumpFileName.c_str();
}

bool CSniffer::haveDumpFile() const
{
    return this->dumpFile != NULL;
}

bool CSniffer::dumpFlush() const
{
    if(this->haveDumpFile())
    {
        return pcap_dump_flush(dumpFile) == 0;
    }
    return false;
}

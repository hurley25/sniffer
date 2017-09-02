#ifndef SETTINGINFO_H_
#define SETTINGINFO_H_

#include <string>

struct SettingInfo
{
    int  		openDevNumber; // 要打开的适配器编号
    bool 		isPromiscuous; // 是否以混杂模式打开适配器
    bool 		autoBegin;	// 选择适配器后自动捕获
    int			packetSizeLimit; // 捕获数据包大小限制
    std::string	filterString; // 过滤器设置字符串

    SettingInfo()
    {
        openDevNumber  = 0;
        isPromiscuous = true;
        autoBegin   = false;
        packetSizeLimit   = 65536;
    	filterString = "ip";
    }
};

#endif	// SETTINGINFO_H_

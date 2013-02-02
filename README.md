sniffer
=======

一个跨平台的网络数据嗅探&抓包程序，基于Qt 4.x 以及 libpcap 库（Linux下）和 Winpcap库（Windows 下）。

 * 关于TCP协议发送的数据的解析也许会有乱码，一是暂时没有处理编码，二来有加密数据

编译方法：

<一> Windows 平台：

        1. 下载 WinPcap 驱动和DLL安装包并安装

            http://www.winpcap.org/install/bin/WinPcap_4_1_2.exe

        2. 下载解压缩 Winpcap 开发包

            http://www.winpcap.org/install/bin/WpdPack_4_1_2.zip
           
           并将Windows平台的项目文件sniffer_win32.pro中的

                INCLUDEPATH += winpcap
                LIBS += lib/Packet.lib lib/wpcap.lib

           两行修改到正确的指向，或者直接放置头文件的 pcap 目录和 lib 目录放到代码源文件目录

        3. 需要安装配置 Qt 开发环境，详请请自行参照官网，建议使用 Qt 4.8.x 版本

        4. 编译步骤：
                1) 打开开始菜单中的 "Visual Studio with Qt 4.8.x" 快捷方式
                2) 输入 "qmake sniffer_win32.pro" （不含引号）以生成 makefile 文件
                3) 执行 "nmake" 或 "nmake release" 命令以调用 VS 的 nmake 工具编译
                4) 在源码的 debug 或者 release 目录会生成可执行文件

<二> Linux平台（以fedora为例，其余系统类似）：

        * 代码在Windows下编写，头文件部分为GBK编码，Linux下请自行转换为UTF-8编码

        1. 安装 libpcap 库和开发包，如 sudo yum install libpcap libpcap-dev

        2. 安装 Qt 相关组件，详请请自行参照官网

        3. 执行 "qmake-qt4 sniffer_linux.pro" 生成 Makefile 文件

        4. 执行 "make" 命令编译

        5. 源码目录下会有可执行文件 sniffer_linux，注意必须以root权限运行才能正常工作
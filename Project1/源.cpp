#include <stdio.h>
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <iostream>
#include <string>

using namespace std;
#pragma comment(lib, "WS2_32.lib")

#define SERVER_IP "192.168.1.2"         //
#define CLIENT_PORT 2022


SOCKET serverSocket;        //
sockaddr_in sockAddr;       //服务器地址
char nickName[16];  //昵称



bool init() {
    /*windows 系统网络服务初始化*/
    WORD sockVersion = MAKEWORD(1, 1);   //调用1.1版本的Socket
    WSADATA data;                       //异步套接字

    int InitRet = WSAStartup(sockVersion, &data);
    if (InitRet != 0)
    {
        return false;
    }

    /*2.网络套接字  int socket(int domain,int type,int protocol);
    domain–协议簇   type–传输类型   protocal–指定协议
    */
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);       //初始化为TCP流套接字

    /*物理地址*/
    sockAddr.sin_family = PF_INET;                          //网络套接字
    sockAddr.sin_addr.S_un.S_addr = inet_addr(SERVER_IP);   //指定IP地址将差分十进制转换为二进制地址

    /*端口号*/
    sockAddr.sin_port = htons(CLIENT_PORT);

    return true;
}


void GBKToUTF8(string& strGBK)
{
    int len = MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, NULL, 0);
    wchar_t* wszUtf8 = new wchar_t[len];            //在堆中创建了wszUtf8,国际字符串类型
    memset(wszUtf8, 0, len);
    MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, wszUtf8, len);
    len = WideCharToMultiByte(CP_UTF8, 0, wszUtf8, -1, NULL, 0, NULL, NULL);
    char* szUtf8 = new char[len + 1];
    memset(szUtf8, 0, len + 1);
    WideCharToMultiByte(CP_UTF8, 0, wszUtf8, -1, szUtf8, len, NULL, NULL);
    strGBK = szUtf8;
    delete[] szUtf8;
    delete[] wszUtf8;
}

void login() {
    system("mode can lines = 5 cols =30\n");
    cout << "欢迎进入聊天室\n" << endl;
    cout << "     昵称:" << endl;
    cin.get(nickName, sizeof(nickName));

    /*清理缓冲区，多余的回车符号*/
    while (getchar() != '\n');

    string name = nickName;

    /*由于是很多服务器四使用的是Linux服务器，是UTF8编码，所以需要将中文昵称转换*/
    GBKToUTF8(name);

    /*send数据发送，将流式套接字（TCP）的数据发送出去*/
    send(serverSocket, name.c_str(), strlen(name.c_str()) + 1, 0);
}

int main() {
    if (!init()) {            //启动异步套接字失败，IP地址初始化失败，端口号初始化失败
        cout << "初始化失败" << endl;
        return -1;
    }

    /*Connect函数，三次握手的实现阶段，通过之前配置的Socket，IP，PORT建立稳定的连接*/
    int ret = connect(serverSocket, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
    if (ret != 0) {
        cout << "连接服务器失败，请检查网络连接" << endl;
        return -2;
    }

    /*登录聊天室*/
    login();


    return 0;

}

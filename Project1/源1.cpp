#include <string>
#include<WinSock2.h>
#include<iostream>
using namespace std;


#pragma comment(lib, "WS2_32.lib")
/*Socket初始化*/


SOCKET serverSocket;        //
sockaddr_in sockAddr;       //服务器地址

bool init() 
{
	WORD sockVersion = MAKEWORD(1, 1);   //调用1.1版本的Socket
	WSADATA data;						 //创建异步Socket
	int ret = WSAStartup(sockVersion, &data);		//ret == 1 则初始化失败，ret == 初始化成功
	if (ret)
	{
		cout << "Socket初始化失败" << endl;
		return false;
	}

	/*2.网络套接字，创建TCP套接字*/
	
}
#include <string>
#include<WinSock2.h>
#include<iostream>
using namespace std;


#pragma comment(lib, "WS2_32.lib")
/*Socket��ʼ��*/


SOCKET serverSocket;        //
sockaddr_in sockAddr;       //��������ַ

bool init() 
{
	WORD sockVersion = MAKEWORD(1, 1);   //����1.1�汾��Socket
	WSADATA data;						 //�����첽Socket
	int ret = WSAStartup(sockVersion, &data);		//ret == 1 ���ʼ��ʧ�ܣ�ret == ��ʼ���ɹ�
	if (ret)
	{
		cout << "Socket��ʼ��ʧ��" << endl;
		return false;
	}

	/*2.�����׽��֣�����TCP�׽���*/
	
}
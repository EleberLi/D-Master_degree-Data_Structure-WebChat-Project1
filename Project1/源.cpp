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
sockaddr_in sockAddr;       //��������ַ
char nickName[16];  //�ǳ�



bool init() {
    /*windows ϵͳ��������ʼ��*/
    WORD sockVersion = MAKEWORD(1, 1);   //����1.1�汾��Socket
    WSADATA data;                       //�첽�׽���

    int InitRet = WSAStartup(sockVersion, &data);
    if (InitRet != 0)
    {
        return false;
    }

    /*2.�����׽���  int socket(int domain,int type,int protocol);
    domain�CЭ���   type�C��������   protocal�Cָ��Э��
    */
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);       //��ʼ��ΪTCP���׽���

    /*�����ַ*/
    sockAddr.sin_family = PF_INET;                          //�����׽���
    sockAddr.sin_addr.S_un.S_addr = inet_addr(SERVER_IP);   //ָ��IP��ַ�����ʮ����ת��Ϊ�����Ƶ�ַ

    /*�˿ں�*/
    sockAddr.sin_port = htons(CLIENT_PORT);

    return true;
}


void GBKToUTF8(string& strGBK)
{
    int len = MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, NULL, 0);
    wchar_t* wszUtf8 = new wchar_t[len];            //�ڶ��д�����wszUtf8,�����ַ�������
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
    cout << "��ӭ����������\n" << endl;
    cout << "     �ǳ�:" << endl;
    cin.get(nickName, sizeof(nickName));

    /*��������������Ļس�����*/
    while (getchar() != '\n');

    string name = nickName;

    /*�����Ǻܶ��������ʹ�õ���Linux����������UTF8���룬������Ҫ�������ǳ�ת��*/
    GBKToUTF8(name);

    /*send���ݷ��ͣ�����ʽ�׽��֣�TCP�������ݷ��ͳ�ȥ*/
    send(serverSocket, name.c_str(), strlen(name.c_str()) + 1, 0);
}

int main() {
    if (!init()) {            //�����첽�׽���ʧ�ܣ�IP��ַ��ʼ��ʧ�ܣ��˿ںų�ʼ��ʧ��
        cout << "��ʼ��ʧ��" << endl;
        return -1;
    }

    /*Connect�������������ֵ�ʵ�ֽ׶Σ�ͨ��֮ǰ���õ�Socket��IP��PORT�����ȶ�������*/
    int ret = connect(serverSocket, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
    if (ret != 0) {
        cout << "���ӷ�����ʧ�ܣ�������������" << endl;
        return -2;
    }

    /*��¼������*/
    login();


    return 0;

}

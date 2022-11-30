#pragma once

#ifndef GBK_TO_UTF8
#define GBK_TO_UTF8
#include<string.h>
#include <iostream>
#include <stdio.h>
#include <winsock2.h>
using namespace std;
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
#endif // !GBK_TO_UTF8


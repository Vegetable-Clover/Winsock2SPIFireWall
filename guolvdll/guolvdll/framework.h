#pragma once

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
// Windows 头文件
#include <windows.h>

#include <WS2spi.h>
#include <iostream>
#include <winsock2.h>     
#include <ws2tcpip.h>
#include <mstcpip.h>
#include <string.h>
#include <tchar.h>
#include <atlstr.h>

#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <time.h>
using namespace std;

#pragma comment(lib, "Ws2_32.lib")

/*
	WSCEnumProtocols
	int WSCEnumProtocols(
			LPINT               lpiProtocols,
			LPWSAPROTOCOL_INFOW lpProtocolBuffer,
			LPDWORD             lpdwBufferLength,
			LPINT               lpErrno
	);

	LPINT   lpiProtocols:
	----->  一个以空结尾的iProtocol值数组。
			可选参数;如果lpiProtocols为空，
			则返回所有可用协议的信息。否则，
			只检索数组中列出的那些协议的信息。

	LPWSAPROTOCOL_INFOW lpProtocolBuffer:
	----->	指向被WSAPROTOCOL_INFOW结构填充的缓冲区的指针。

	LPDWORD     lpdwBufferLength:
	-----> LPDWORD:指向一个无符号双字(32位)的指针
		   参数：输入时，传递给WSCEnumProtocols的
		   lpProtocolBuffer缓冲区的大小，以字节为
		   单位。输出时，可以传递给WSCEnumProtocols
		   以检索所有请求信息的最小缓冲区大小(以字节为单位)。
	LPINT               lpErrno
	-----> 参数：指向错误代码的指针。
		   LPINT：	指向一个符号整数的指针

*/

/*
	lpnTotalProtocols : 用于返回协议数
	LPWSAPROTOCOL_INFOW：指向WSAPROTOCOL_INFO的指针 是一个WSAPROTOCOL_INFO结构体数组
*/

//获取所有协议的函数
//协议个数存在 lpnTotalProtocols
//返回存有所有协议的W结构的数组
LPWSAPROTOCOL_INFOW GetProvider(LPINT lpnTotalProtocols)
{

	//遍历所有协议
	int nError = 0;
	DWORD dwSize = 0;
	LPWSAPROTOCOL_INFOW pProtoInfo = NULL;
	if (WSCEnumProtocols(NULL, pProtoInfo, &dwSize, &nError) == SOCKET_ERROR)
	{
		if (nError != WSAENOBUFS)
			return NULL;
	}
	pProtoInfo = (LPWSAPROTOCOL_INFOW)new WSAPROTOCOL_INFOW[dwSize / sizeof(WSAPROTOCOL_INFOW)];
	if (!pProtoInfo)
		return NULL;
	ZeroMemory(pProtoInfo, dwSize);
	*lpnTotalProtocols = WSCEnumProtocols(NULL, pProtoInfo, &dwSize, &nError);
	return pProtoInfo;
}

void FreeProvider(LPWSAPROTOCOL_INFOW pProtoInfo)
{
	delete[] pProtoInfo;
}


//写日志函数
void WriteTheLog(string s) {

	ofstream out("C:\\mydll\\Comm\\Log.txt", ios::app);
	time_t nowtime;
	nowtime = time(NULL); //获取日历时间
	//cout << nowtime << endl; //输出nowtime
	struct tm local;

	localtime_s(&local, &nowtime); //获取当前系统时间

	//string s = local.tm_year + 1900 + "年" + (local.tm_mon + 1) + "月" + local.tm_mday + "日 "
	out << "---------------------------------------------------------------------------------\n";
	out << local.tm_year + 1900 << "年" << local.tm_mon + 1 << "月" << local.tm_mday << "日 ";
	out << local.tm_hour << ":" << local.tm_min << ":" << local.tm_sec << " " << "\n";
	out << s << "\n";
	out << "---------------------------------------------------------------------------------\n";
}



//从Port.txt文件读取端口
void ReadFromPortFile(vector<string>& word) {
	//fstream f("C:\\mydll\\Comm\\Port.txt");
	//vector<int> word; //创建一个vector<string>对象
	//string  line; //保存读入的每一行 
	/*
	while (getline(f, line))//会自动把\n换行符去掉 
	{
		int n = atoi(line.c_str());
		word.push_back(n);
	}
	*/
	//cout << word.size() << endl;
	/*
	for (int i = 0; i < word.size(); i++) {
		cout << port_vector.at(i) << endl;
	}
	*/
	//f.close();
	/*
	char buffer[256];
	ifstream in("C:\\mydll\\Comm\\Port.txt");
	if (!in.is_open())
	{
		//cout << "Error opening file";
		exit(1);
	}
	while (!in.eof())
	{
		in.getline(buffer, 10);
		string str = string(buffer);
		cout << str << endl;
	}
	in.close();
	*/
	char buffer[256];
	word.clear();
	ifstream in("C:\\mydll\\Comm\\Port.txt");
	if (!in.is_open())
	{
		//cout << "Error opening file"; 
		exit(1);
	}
	while (!in.eof())
	{
		in.getline(buffer, 100);
		string str = string(buffer);
		word.push_back(str);
	}
	in.close();
}

//从URL.txt文件读取URL，目前测试没有用到
void ReadFromURLFile(vector<string>& word) {
	char buffer[256];
	word.clear();
	ifstream in("C:\\mydll\\Comm\\URL.txt");
	if (!in.is_open())
	{
		//cout << "Error opening file"; 
		exit(1);
	}
	while (!in.eof())
	{
		in.getline(buffer, 100);
		string str = string(buffer);
		word.push_back(str);
	}
	in.close();
}

//URL过滤函数
BOOL filtUrl(SOCKET s, vector<string>& word) {
	
	if (word.size() == 0) {
		return FALSE;
	}
	
	SOCKADDR_IN local_addr, remote_addr;
	int local_addr_len = sizeof(local_addr);
	int remote_addr_len = sizeof(remote_addr);
	getsockname(s, (SOCKADDR*)&local_addr, &local_addr_len);
	getpeername(s, (SOCKADDR*)&remote_addr, &remote_addr_len);

	CString sTemp;
	CString strLocalIP, strRemoteIP;

	strLocalIP.Format(_T("%u.%u.%u.%u"), local_addr.sin_addr.S_un.S_un_b.s_b1
		, local_addr.sin_addr.S_un.S_un_b.s_b2
		, local_addr.sin_addr.S_un.S_un_b.s_b3
		, local_addr.sin_addr.S_un.S_un_b.s_b4);

	strRemoteIP.Format(_T("%u.%u.%u.%u"), remote_addr.sin_addr.S_un.S_un_b.s_b1
		, remote_addr.sin_addr.S_un.S_un_b.s_b2
		, remote_addr.sin_addr.S_un.S_un_b.s_b3
		, remote_addr.sin_addr.S_un.S_un_b.s_b4);


	//strRemoteIP.Format(_T("112.80.248.75"));
	//strLocalIP.Format(_T("112.80.248.75"));

	//现在是以固定的IP做测试
	//string ss = "120.79.88.157";
	
	//将端口中读取的IP转换成string以便比较
	string STDStr1(CW2A(strLocalIP.GetString()));
	string STDStr2(CW2A(strRemoteIP.GetString()));

	WriteTheLog("In the Func of filtUrl");
	WriteTheLog("本地IP: " + STDStr1);
	WriteTheLog("远端IP: " + STDStr2);

	for (auto item : word) {
		if (item.compare(STDStr1) == 0) {
			return TRUE;
		}
		if (item.compare(STDStr2) == 0) {
			return TRUE;
		}
	}
	/*
	for (string s : word) {
		string STDStr1(CW2A(strLocalIP.GetString()));
		string STDStr2(CW2A(strRemoteIP.GetString()));

		if (ss.compare(STDStr1) == 0) {
			return TRUE;
		}
		if (ss.compare(STDStr2) == 0) {
			return TRUE;
		}
	}
	*/

	return FALSE;
}





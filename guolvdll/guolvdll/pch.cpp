// pch.cpp: 与预编译标头对应的源文件

#include "pch.h"

// 当使用预编译的头时，需要使用此源文件，编译才能成功。
/*
	全局变量

*/
WSPPROC_TABLE g_NextProcTable;  //下层提供者的函数表        全局

//最终实现，会从文件读取url和端口
//目前以具体的URL做测试，以百度的ip做测试
//端口
vector<string> port_vector;

//URL
vector<string> url_vector;


//端口拦截函数
BOOL CompareThePort(const sockaddr* name, vector<string>& port_in, LPINT lpErrno, SOCKET s) {
	sockaddr_in* info = (sockaddr_in*)name;
	USHORT port = ntohs(info->sin_port);
	string port_str = to_string(port);
	
	if (port_in.size() == 0) {
		return FALSE;
	}
	for (auto p : port_in) {
		//WriteTheLog("we are judging the port : ");
		//WriteTheLog(to_string(port));
		if (port_str.compare(p) == 0)   //如果是目标端口,那么拦截
		{
			int nError = 0;
			//WriteTheLog("sorry,we shutdown you tcp protocol port! : ");
			//WriteTheLog(to_string(port));
			g_NextProcTable.lpWSPShutdown(s, SD_BOTH, &nError);
			//设置错误信息
			*lpErrno = WSAECONNABORTED;
			return TRUE;
		}
	}
	
	/*
	if (port == 8000||port == 139)   //如果是目标端口,那么拦截
	{
		int nError = 0;
		//因为整个dll已经加载进程序里,这里对我的控制台程序进行测试
		CString sTemp;
		WriteTheLog("sorry,we shutdown you tcp protocol port! : ");
		WriteTheLog(to_string(port));
		g_NextProcTable.lpWSPShutdown(s, SD_BOTH, &nError);
		//设置错误信息
		*lpErrno = WSAECONNABORTED;
		return TRUE;
	}
	*/
	

	return FALSE;
}


int WSPAPI WSPBind(
	SOCKET s,
	const struct sockaddr FAR* name,
	int namelen,
	LPINT lpErrno
) {
	//端口过滤
	//WriteTheLog("start in bind");
	ReadFromPortFile(port_vector);
	if (CompareThePort(name, port_vector, lpErrno, s)) {
		return SOCKET_ERROR;
	}
	
	return g_NextProcTable.lpWSPBind(s, name, namelen, lpErrno);
}


//拦截
int WSPAPI WSPConnect(       //自定义的WSPConnect函数
	SOCKET s,
	const struct sockaddr FAR* name,
	int namelen,
	LPWSABUF lpCallerData,
	LPWSABUF lpCalleeData,
	LPQOS lpSQOS,
	LPQOS lpGQOS,
	LPINT lpErrno
)
{
	//端口拦截
	//WriteTheLog("Work in the WSPConnect");
	ReadFromPortFile(port_vector);
	if (CompareThePort(name, port_vector, lpErrno, s)) {
		return SOCKET_ERROR;
	}
	
	WriteTheLog("Start in the WSPConnect");


	ReadFromURLFile(url_vector);
	//URL拦截
	if (filtUrl(s, url_vector)) {
		WriteTheLog("The result of guolv is true! guolv url chenggong le!!!");
		return SOCKET_ERROR;
	}
	
	//WriteTheLog("If you see me,means terrible thing happened");
	/*
	//URL拦截
	if (filtUrl(s, url_vector)) {
		g_NextProcTable.lpWSPShutdown(s, SD_BOTH, lpErrno);
		return SOCKET_ERROR;
	}
	*/
	//return SOCKET_ERROR;
	//return SOCKET_ERROR;
	//如果不是,调用下层提供者的函数表中的WSPConnect函数
	return g_NextProcTable.lpWSPConnect(s, name, namelen, lpCallerData, lpCalleeData, lpSQOS, lpGQOS, lpErrno);
}



/*
	TCP过滤
	WSPSend()

*/
int WSPAPI WSPSend(
	SOCKET s,
	LPWSABUF lpBuffers,
	DWORD dwBufferCount,
	LPDWORD lpNumberOfBytesSent,
	DWORD dwFlags,
	LPWSAOVERLAPPED lpOverlapped,
	LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
	LPWSATHREADID lpThreadId,
	LPINT lpErrno
)
{

	WriteTheLog("Start in the WSPSend");

	ReadFromURLFile(url_vector);
	//URL拦截
	if (filtUrl(s, url_vector)) {
		WriteTheLog("The result of guolv is true! guolv url chenggong le!!!");
		return SOCKET_ERROR;
	}

	return g_NextProcTable.lpWSPSend(s, lpBuffers, dwBufferCount, lpNumberOfBytesSent, dwFlags, lpOverlapped, lpCompletionRoutine, lpThreadId, lpErrno);


}


//WSPRecv()
int WSPAPI WSPRecv(
	SOCKET s,
	LPWSABUF lpBuffers,
	DWORD dwBufferCount,
	LPDWORD lpNumberOfBytesRecvd,
	LPDWORD lpFlags,
	LPWSAOVERLAPPED lpOverlapped,
	LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
	LPWSATHREADID lpThreadId,
	LPINT lpErrno
)
{

	//ReadFromURLFile(url_vector);

	//URL拦截
	/*
	if (filtUrl(s, url_vector)) {
		g_NextProcTable.lpWSPShutdown(s, SD_BOTH, lpErrno);
		return SOCKET_ERROR;
	}
	*/
	//WriteTheLog("Work in the WSPRecv");
	return g_NextProcTable.lpWSPRecv(s, lpBuffers, dwBufferCount, lpNumberOfBytesRecvd, lpFlags, lpOverlapped, lpCompletionRoutine, lpThreadId, lpErrno);

}





/*-----------------------------------------------------------------------------------------------
	UDP过滤操作
	WSPSendTo()
*/

int WSPAPI WSPSendTo         //自定义的WSPSendTo函数
(
	SOCKET s,
	LPWSABUF lpBuffers,
	DWORD dwBufferCount,
	LPDWORD lpNumberOfBytesSent,
	DWORD dwFlags,
	const struct sockaddr FAR* lpTo,
	int iTolen,
	LPWSAOVERLAPPED lpOverlapped,
	LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
	LPWSATHREADID lpThreadId,
	LPINT lpErrno
)
{
	/*
	//ReadFromPortFile(port_vector);
	//端口拦截
	if (CompareThePort(lpTo, port_vector, lpErrno, s)) {

		return SOCKET_ERROR;
	}

	//ReadFromURLFile(url_vector);
	//URL拦截
	if (filtUrl(s, url_vector)) {
		g_NextProcTable.lpWSPShutdown(s, SD_BOTH, lpErrno);
		return SOCKET_ERROR;
	}
	*/
	//WriteTheLog("Work in the WSPSendTo");
	//如果不是,调用下层提供者的函数表中的WSPSendTo函数
	return g_NextProcTable.lpWSPSendTo(s, lpBuffers, dwBufferCount, lpNumberOfBytesSent, dwFlags,
		lpTo, iTolen, lpOverlapped, lpCompletionRoutine, lpThreadId, lpErrno);

}


//WSPRecvFrom
int WSPAPI WSPRecvFrom(
	SOCKET s,
	LPWSABUF lpBuffers,
	DWORD dwBufferCount,
	LPDWORD lpNumberOfBytesRecvd,
	LPDWORD lpFlags,
	struct sockaddr FAR* lpFrom,
	LPINT lpFromlen,
	LPWSAOVERLAPPED lpOverlapped,
	LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
	LPWSATHREADID lpThreadId,
	LPINT lpErrno
)
{
	//ReadFromURLFile(url_vector);
	/*
	if (filtUrl(s, url_vector)) {
		g_NextProcTable.lpWSPShutdown(s, SD_BOTH, lpErrno);
		return SOCKET_ERROR;
	}
	*/
	//WriteTheLog("Work in the WSPRecvFrom");
	return g_NextProcTable.lpWSPRecvFrom(s, lpBuffers, dwBufferCount, lpNumberOfBytesRecvd, lpFlags,
		lpFrom, lpFromlen, lpOverlapped, lpCompletionRoutine, lpThreadId, lpErrno);

}


//------------------------------------------------------------------------------------------------



/**
*这是入口  |
*函数      |
*          |
*          V
*/


//LSP的初始化函数（唯一的导出函数）
int WSPAPI WSPStartup(
	WORD wVersionRequested,                          //用户程序加载套接字库的版本号(in)
	LPWSPDATA lpWSPData,                               //用于取得Winsock服务的详细信息
	LPWSAPROTOCOL_INFO lpProtocolInfo,			//指定想得到的协议的特征
	WSPUPCALLTABLE UpcallTable,                 //Ws2_32.dll向上调用转发的函数表
	LPWSPPROC_TABLE lpProTable                 //下层提供者的函数表（一般为基础协议,共30个服务函数）
)
{
	//只处理协议链
	//如果协议为分层协议或基础协议,那么返回错误
	if (lpProtocolInfo->ProtocolChain.ChainLen <= 1)
	{   //无法加载或初始化请求的服务提供程序
		return WSAEPROVIDERFAILEDINIT;
	}

	//找到下层协议的WSAPROTOCOL_INFOW结构体
	//用来存放下层协议的WSAPROTOCOL_INFOW结构体指针
	WSAPROTOCOL_INFOW NextProtocolInfo;

	int nTotalProtols;

	//WSADATA wsa;
	//WSAStartup(MAKEWORD(2, 2), &wsa);

	//获取所有协议
	LPWSAPROTOCOL_INFOW pProtoInfo = GetProvider(&nTotalProtols);


	//下层提供者的入口ID (传入的是协议链)
	//W结构的ID
	DWORD dwBaseEntryId = lpProtocolInfo->ProtocolChain.ChainEntries[1];



	//遍历所有协议
	int i = 0;
	for (; i < nTotalProtols; i++)
	{//找到下层提供者协议
		if (pProtoInfo[i].dwCatalogEntryId == dwBaseEntryId)
		{
			memcpy(&NextProtocolInfo, &pProtoInfo[i], sizeof(WSAPROTOCOL_INFOW));
			break;
		}
	}
	//找到下层基础服务者的W结构ID : NextProtocolInfo

	//如果没找到
	if (i >= nTotalProtols)
		return WSAEPROVIDERFAILEDINIT;



	//加载下层协议的Dll
	int nError = 0;
	//下层协议DLL的存放路径
	TCHAR szBaseProviderDll[MAX_PATH];
	int nLen = MAX_PATH;



	//取得下层提供者的DLL路径（可能包含坏境变量）
	if (WSCGetProviderPath(&NextProtocolInfo.ProviderId, szBaseProviderDll, &nLen, &nError) == SOCKET_ERROR)
		return WSAEPROVIDERFAILEDINIT;


	//环境变量转换字符串
	if (!ExpandEnvironmentStrings(szBaseProviderDll, szBaseProviderDll, MAX_PATH))
		return WSAEPROVIDERFAILEDINIT;

	//加载dll
	HMODULE hModdule = LoadLibrary(szBaseProviderDll);
	if (hModdule == NULL)
		return WSAEPROVIDERFAILEDINIT;

	//取出下层提供者的WSPStartup函数
	//存在pfnWSPStartup中
	LPWSPSTARTUP pfnWSPStartup = (LPWSPSTARTUP)GetProcAddress(hModdule, "WSPStartup");
	if (NULL == pfnWSPStartup)
		return WSAEPROVIDERFAILEDINIT;


	//调用下层服务提供者的WSPStartup函数;
	LPWSAPROTOCOL_INFOW pInfo = lpProtocolInfo;

	//如果下层提供者是基础协议
	//赋给pInfo指针
	if (NextProtocolInfo.ProtocolChain.ChainLen == BASE_PROTOCOL)
		pInfo = &NextProtocolInfo;


	//调用下层提供者的初始化函数 ！！！！！
	int nRet = pfnWSPStartup(wVersionRequested, lpWSPData, pInfo, UpcallTable, lpProTable);
	//初始化失败
	if (nRet != ERROR_SUCCESS)
		return nRet;

	//初始化完成后,复制下层提供者(基础协议)的整个函数表
	g_NextProcTable = *lpProTable;
	//将基础协议的SendTo函数指针,指向我们的WSPSendTo函数,在我们的函数内,再确定要不要调用回基础协议的Sendto函数

	lpProTable->lpWSPBind = WSPBind;
	lpProTable->lpWSPConnect = WSPConnect;
	lpProTable->lpWSPRecv = WSPRecv;
	lpProTable->lpWSPSend = WSPSend;
	lpProTable->lpWSPRecvFrom = WSPRecvFrom;
	lpProTable->lpWSPSendTo = WSPSendTo;

	FreeProvider(pProtoInfo);
	return nRet;
}

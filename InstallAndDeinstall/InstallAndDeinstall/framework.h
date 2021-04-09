#pragma once

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
// Windows 头文件

#include <WS2spi.h>
#include <winsock2.h>
#include <process.h>
#include <ws2tcpip.h>
#include <mstcpip.h>
#include <Windows.h>
#include <iostream>
#include <tchar.h>
#include <string.h>
#include <combaseapi.h>
using namespace std;
#pragma warning(disable:4996)
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib,"Sporder.lib")
#include <sporder.h>



//安装LSP
class installLSP
{
	/*
	GUID Layered_guid;        //分层协议GUID
	GUID AgreementChain_guid; //协议链GUID

	*/


public:
	//初始化：生成分层协议GUID 和 协议链GUID
	installLSP()
	{
		WSADATA wsa;
		WSAStartup(MAKEWORD(2, 2), &wsa);
		CoCreateGuid(&this->Layered_guid);
		CoCreateGuid(&this->AgreementChain_guid);
	}
	~installLSP()
	{
		WSACleanup();
	}
public:
	//安装LSP,并安装3个协议链
	BOOL InstallProvider(WCHAR* wszDllPath)  //参数：LSP的DLL的地址  参数：WCHAR* wszDllPath
	{
		WCHAR wszLSPName[] = L"AaronLSP";

		LPWSAPROTOCOL_INFOW pProtoInfo = NULL;   //WSAPROTOCOL_INFO结构体指针

		int nProtocols = 0; //分层协议     取出来的模板

		WSAPROTOCOL_INFOW OriginalProtocolInfo[3]; //数组成员为TCP、UDP、RAW的目录入口信息

		WSAPROTOCOL_INFOW OriginalProtocolInfo_IPV6[3]; //数组成员为TCP_IPV6、UDP_IPV6、RAW_IPV6的目录入口信息

		DWORD dwOrigCatalogId[3]; //记录入口ID号  (3个协议链接的入口ID??)

		DWORD dwOrigCatalogId_IPV6[3];  //记录入口ID号  (3个协议链接_IPV6的入口ID??)

		int nArrayCount = 0;      //数组个数索引

		int nArrayCount_IPV6 = 0;  //IPV6数组个数索引

		DWORD dwLayeredCatalogId; //分层协议的入口ID号

		int nError;

		pProtoInfo = GetProvider(&nProtocols);    //获取所有的协议

		if (nProtocols < 1 || pProtoInfo == NULL)
			return FALSE;

		BOOL bFindUdp = FALSE;

		BOOL bFindTcp = FALSE;

		BOOL bFindRaw = FALSE;

		BOOL bFindUdp_IPV6 = FALSE;

		BOOL bFindTcp_IPV6 = FALSE;

		BOOL bFindRaw_IPV6 = FALSE;

		//寻找合适的基础服务提供者  存储到OriginalProtocolInfo
		for (int i = 0; i < nProtocols; i++)
		{
			if (pProtoInfo[i].iAddressFamily == AF_INET) //查找地址族为AF_INET的协议（IPv4）
			{
				//处理UDP 找到一个符合要求的对应UDP协议的LSP
				if (!bFindUdp && pProtoInfo[i].iProtocol == IPPROTO_UDP)
				{
					memcpy(&OriginalProtocolInfo[nArrayCount], &pProtoInfo[i], sizeof(WSAPROTOCOL_INFOW));
					//去除XP1_IFS_HANDLES标志,防止提供者返回的句柄是真正的操作系统句柄？？？？

					/*
					如有XP1_IFS_HANDLES标志,从dwServiceFlags1域中移除
					XP1_IFS_HANDLES标志表示此提供者返回的句柄是真正地
					操作系统句柄,可能会被传递到内部API.此提供者必须关
					联内核模式组件,创建TCPIP.SYS一样的句柄.
					*/

					OriginalProtocolInfo[nArrayCount].dwServiceFlags1 &= (~XP1_IFS_HANDLES);
					//记录目录入口ID
					dwOrigCatalogId[nArrayCount++] = pProtoInfo[i].dwCatalogEntryId;
					bFindUdp = TRUE;
				}

				//处理TCP 找到一个符合要求的对应TCP协议的LSP
				if (!bFindTcp && pProtoInfo[i].iProtocol == IPPROTO_TCP) //处理TCP
				{
					memcpy(&OriginalProtocolInfo[nArrayCount], &pProtoInfo[i], sizeof(WSAPROTOCOL_INFOW));
					//去除XP1_IFS_HANDLES标志,防止提供者返回的句柄是真正的操作系统句柄
					OriginalProtocolInfo[nArrayCount].dwServiceFlags1 &= (~XP1_IFS_HANDLES);
					//记录目录入口ID
					dwOrigCatalogId[nArrayCount++] = pProtoInfo[i].dwCatalogEntryId;
					bFindTcp = TRUE;
				}

				//处理RAW  找到一个符合要求的对应RAW协议的LSP
				if (!bFindRaw && pProtoInfo[i].iProtocol == IPPROTO_IP)
				{
					memcpy(&OriginalProtocolInfo[nArrayCount], &pProtoInfo[i], sizeof(WSAPROTOCOL_INFOW));
					//去除XP1_IFS_HANDLES标志,防止提供者返回的句柄是真正的操作系统句柄
					OriginalProtocolInfo[nArrayCount].dwServiceFlags1 &= (~XP1_IFS_HANDLES);
					//记录目录入口ID
					dwOrigCatalogId[nArrayCount++] = pProtoInfo[i].dwCatalogEntryId;
					bFindRaw = TRUE;
				}
			}
		}

		if (nArrayCount == 0)
		{
			FreeProvider(pProtoInfo);
			return FALSE;
		}


		//寻找合适的基础服务提供者_IPV6  存储到OriginalProtocolInfo_IPV6
		for (int i = 0; i < nProtocols; i++) {
			if (pProtoInfo[i].iAddressFamily == AF_INET6) //查找地址族为AF_INET的协议（IPv4）
			{
				//处理UDP 找到一个符合要求的对应UDP协议的LSP
				if (!bFindUdp_IPV6 && pProtoInfo[i].iProtocol == IPPROTO_UDP)
				{
					memcpy(&OriginalProtocolInfo_IPV6[nArrayCount_IPV6], &pProtoInfo[i], sizeof(WSAPROTOCOL_INFOW));
					//去除XP1_IFS_HANDLES标志,防止提供者返回的句柄是真正的操作系统句柄？？？？

					/*
					如有XP1_IFS_HANDLES标志,从dwServiceFlags1域中移除
					XP1_IFS_HANDLES标志表示此提供者返回的句柄是真正地
					操作系统句柄,可能会被传递到内部API.此提供者必须关
					联内核模式组件,创建TCPIP.SYS一样的句柄.
					*/

					OriginalProtocolInfo_IPV6[nArrayCount_IPV6].dwServiceFlags1 &= (~XP1_IFS_HANDLES);
					//记录目录入口ID
					dwOrigCatalogId_IPV6[nArrayCount_IPV6++] = pProtoInfo[i].dwCatalogEntryId;
					bFindUdp_IPV6 = TRUE;
				}

				//处理TCP 找到一个符合要求的对应TCP协议的LSP
				if (!bFindTcp_IPV6 && pProtoInfo[i].iProtocol == IPPROTO_TCP) //处理TCP
				{
					memcpy(&OriginalProtocolInfo_IPV6[nArrayCount_IPV6], &pProtoInfo[i], sizeof(WSAPROTOCOL_INFOW));
					//去除XP1_IFS_HANDLES标志,防止提供者返回的句柄是真正的操作系统句柄
					OriginalProtocolInfo_IPV6[nArrayCount_IPV6].dwServiceFlags1 &= (~XP1_IFS_HANDLES);
					//记录目录入口ID
					dwOrigCatalogId_IPV6[nArrayCount_IPV6++] = pProtoInfo[i].dwCatalogEntryId;
					bFindTcp_IPV6 = TRUE;
				}

				//处理RAW  找到一个符合要求的对应RAW协议的LSP
				if (!bFindRaw_IPV6 && pProtoInfo[i].iProtocol == IPPROTO_IP)
				{
					memcpy(&OriginalProtocolInfo_IPV6[nArrayCount_IPV6], &pProtoInfo[i], sizeof(WSAPROTOCOL_INFOW));
					//去除XP1_IFS_HANDLES标志,防止提供者返回的句柄是真正的操作系统句柄
					OriginalProtocolInfo_IPV6[nArrayCount_IPV6].dwServiceFlags1 &= (~XP1_IFS_HANDLES);
					//记录目录入口ID
					dwOrigCatalogId_IPV6[nArrayCount_IPV6++] = pProtoInfo[i].dwCatalogEntryId;
					bFindRaw_IPV6 = TRUE;
				}
			}
		}
		if (nArrayCount_IPV6 == 0)
		{
			FreeProvider(pProtoInfo);
			return FALSE;
		}


		//int a = 0;







		//安装LSP分层协议
		WSAPROTOCOL_INFOW LayeredProtocolInfo;

		//No.1 修改第一个协议
		memcpy(&LayeredProtocolInfo, &OriginalProtocolInfo[0], sizeof(WSAPROTOCOL_INFOW));

		//修改协议名称的字符串
		wcscpy(LayeredProtocolInfo.szProtocol, wszLSPName);


		//表示分层协议
		LayeredProtocolInfo.ProtocolChain.ChainLen = LAYERED_PROTOCOL; //0  设置标识符为LSP


		//表示方式为由提供者自己设置
		LayeredProtocolInfo.dwProviderFlags = PFL_HIDDEN;

		//LayeredProtocolInfo.dwCatalogEntryId = 1000;

		//安装分层协议
		/*
		完成安装功能的WindowsAPI

		int WSCInstallProvider(
			const LPGUID lpProviderId,                                    // 要安装的提供者的GUID
			const LPWSTR lpszProviderDllPath,                           // 指向提供者DLL的路径
			const LPWSAPROTOCOL_INFO lpProtocolInfoList,        // 指向一个WSAPROTOCOL_INFOW结构数组
			DWORD dwNumberOfEntries,                                    // lpProtocolInfoList数组中入口的数量,即数组大小
			LPINT lpErrno                                                        // 返回可能的失败代码
		);                                                                          // 只有UNICODE版本,失败则返回SOCKET_ERROR
		*/
		//Layered_guid ---->   是新生成的ID

		//wszDllPath为我们自己的LSP的路径
		//安装LSP
		if (SOCKET_ERROR == WSCInstallProvider(&Layered_guid, wszDllPath, &LayeredProtocolInfo, 1, &nError))
		{
			//安装失败
			FreeProvider(pProtoInfo);
			std::cout << nError << std::endl;
			return FALSE;
		}
		//安装成功
		FreeProvider(pProtoInfo);


		//-------------------------------------------------------------------------------------


		//重新遍历协议,获取分层协议的目录ID号
		pProtoInfo = GetProvider(&nProtocols);
		if (nProtocols < 1 || pProtoInfo == NULL)
			return FALSE;
		for (int i = 0; i < nProtocols; i++)//一般安装新入口后,会排在最低部
		{
			if (memcmp(&pProtoInfo[i].ProviderId, &Layered_guid, sizeof(GUID)) == 0)
			{
				//找到刚刚安装的LSP
				//取出分层协议的目录入口ID (WSAPROTOCOL_INFO的唯一标识符)
				dwLayeredCatalogId = pProtoInfo[i].dwCatalogEntryId;
				break;
			}
		}


		//安装协议链                 256
		WCHAR wszChainName[WSAPROTOCOL_LEN + 1];//新分层协议的名称  over   取出来的入口模板的名称

		//nArrayCount == 3
		for (int i = 0; i < nArrayCount; i++)
		{
			//OriginalProtocolInfo包含了3个取出来的合适的备选LSP的信息
			//是拷贝一份的
			//dwLayeredCatalogId 储存的是已经安装完成的LSP的W结构的ID标识

			//获得LSP命名字符串
			swprintf(wszChainName, _T("%s over %s"), wszLSPName, OriginalProtocolInfo[i].szProtocol);

			wcscpy(OriginalProtocolInfo[i].szProtocol, wszChainName);  //将这个模板的名称改成新名称↑

			if (OriginalProtocolInfo[i].ProtocolChain.ChainLen == 1)//这是基础协议的模板
			{
				//修改基础协议模板的协议链, 在协议链[1]写入真正UDP[基础协议]的入口ID
				OriginalProtocolInfo[i].ProtocolChain.ChainEntries[1] = dwOrigCatalogId[i];
			}
			else
			{//如果大于1,相当于是个协议链,表示：将协议链中的入口ID,全部向后退一格,留出[0]
				for (int j = OriginalProtocolInfo[i].ProtocolChain.ChainLen; j > 0; j--)
					OriginalProtocolInfo[i].ProtocolChain.ChainEntries[j] = OriginalProtocolInfo[i].ProtocolChain.ChainEntries[j - 1];
			}
			//让新分层协议排在基础协议的前面（如果为协议链排就排在开头了）
			OriginalProtocolInfo[i].ProtocolChain.ChainLen++;
			OriginalProtocolInfo[i].ProtocolChain.ChainEntries[0] = dwLayeredCatalogId;
		}


		/*
		//一次安装3个协议链
		if (SOCKET_ERROR == WSCInstallProvider(&AgreementChain_guid, wszDllPath, OriginalProtocolInfo, nArrayCount, &nError))
		{
			FreeProvider(pProtoInfo);
			return FALSE;
		}
		*/


		//int b = 0;

		//FreeProvider(pProtoInfo);


		//IPV6的协议链安装设置
		//nArrayCount_IPV6 == 3
		for (int i = 0; i < nArrayCount_IPV6; i++)
		{
			//OriginalProtocolInfo_IPV6包含了3个取出来的合适的备选LSP的信息(LPV6)
			//是拷贝一份的
			//dwLayeredCatalogId 储存的是已经安装完成的LSP的W结构的ID标识

			//获得LSP命名字符串
			swprintf(wszChainName, _T("%s over %s IPV6"), wszLSPName, OriginalProtocolInfo_IPV6[i].szProtocol);

			wcscpy(OriginalProtocolInfo_IPV6[i].szProtocol, wszChainName);  //将这个模板的名称改成新名称↑

			if (OriginalProtocolInfo_IPV6[i].ProtocolChain.ChainLen == 1)//这是基础协议的模板
			{
				//修改基础协议模板的协议链, 在协议链[1]写入真正UDP[基础协议]的入口ID
				OriginalProtocolInfo_IPV6[i].ProtocolChain.ChainEntries[1] = dwOrigCatalogId_IPV6[i];
			}
			else
			{
				//如果大于1,相当于是个协议链,表示：将协议链中的入口ID,全部向后退一格,留出[0]
				for (int j = OriginalProtocolInfo_IPV6[i].ProtocolChain.ChainLen; j > 0; j--)
					OriginalProtocolInfo_IPV6[i].ProtocolChain.ChainEntries[j] = OriginalProtocolInfo_IPV6[i].ProtocolChain.ChainEntries[j - 1];
			}
			//让新分层协议排在基础协议的前面（如果为协议链排就排在开头了）
			OriginalProtocolInfo_IPV6[i].ProtocolChain.ChainLen++;
			OriginalProtocolInfo_IPV6[i].ProtocolChain.ChainEntries[0] = dwLayeredCatalogId;
		}

		//合并,以便一次性安装协议链
		int num = 0;
		WSAPROTOCOL_INFOW OriginalProtocolInfo_SUM[6];
		for (int i = 0; i < 3; i++) {
			OriginalProtocolInfo_SUM[num++] = OriginalProtocolInfo[i];
		}
		for (int i = 0; i < 3; i++) {
			OriginalProtocolInfo_SUM[num++] = OriginalProtocolInfo_IPV6[i];
		}


		//wszDllPath是我们自己的LSP的DLL的路径
		//安装IPV6的协议链
		if (SOCKET_ERROR == WSCInstallProvider(&AgreementChain_guid, wszDllPath, OriginalProtocolInfo_SUM, num, &nError))
		{
			FreeProvider(pProtoInfo);
			return FALSE;
		}


		FreeProvider(pProtoInfo);



		//第三步：将所有3种协议进行重新排序,以让系统先调用我们的协议（让协议链排第一,协议链中[0]是新分层协议,[1]基础UDP、TCP、RAW协议）
		//重新遍历所有协议
		pProtoInfo = GetProvider(&nProtocols);
		if (nProtocols < 1 || pProtoInfo == NULL)
			return FALSE;
		DWORD dwIds[30];
		int nIndex = 0;

		//添加我们的协议链
		for (int i = 0; i < nProtocols; i++)
		{
			//如果是我们新创建的协议链(不包含 刚刚安装的LSP)
			if (pProtoInfo[i].ProtocolChain.ChainLen > 1 && pProtoInfo[i].ProtocolChain.ChainEntries[0] == dwLayeredCatalogId)
				dwIds[nIndex++] = pProtoInfo[i].dwCatalogEntryId;//将6个协议链排在前6
		}
		//添加其他协议
		for (int i = 0; i < nProtocols; i++)
		{
			//如果是基础协议,分层协议(不包括我们的协议链,但包括我们的分层协议)
			if (pProtoInfo[i].ProtocolChain.ChainLen <= 1 || pProtoInfo[i].ProtocolChain.ChainEntries[0] != dwLayeredCatalogId)
				dwIds[nIndex++] = pProtoInfo[i].dwCatalogEntryId;
		}

		//重新排序Winsock目录
		//调用排序函数
		if (WSCWriteProviderOrder(dwIds, nIndex) != ERROR_SUCCESS)
			return FALSE;
		FreeProvider(pProtoInfo);

		int c = 0;

		return TRUE;
	}



	//卸载LSP
	BOOL RemoveProvider()
	{
		BOOL eye = false;
		LPWSAPROTOCOL_INFOW pProtoInfo = NULL;
		int nProtocols = 0;
		DWORD dwLayeredCatalogId = 0; //分层协议提供者的入口ID号
		 //遍历出所有协议
		pProtoInfo = GetProvider(&nProtocols);
		if (nProtocols < 1 || pProtoInfo == NULL)
			return false;
		int nError = 0;
		int i = 0;
		for (i = 0; i < nProtocols; i++)
		{
			//查找到刚刚安装的分层协议提供者
			//根据LSP的GUID来查找到刚刚安装的LSP
			if (memcmp(&Layered_guid, &pProtoInfo[i].ProviderId, sizeof(GUID)) == 0)
			{
				dwLayeredCatalogId = pProtoInfo[i].dwCatalogEntryId;
				break;
			}
		}
		if (i < nProtocols)
		{
			for (i = 0; i < nProtocols; i++)
			{
				//查找协议链(这个协议链的[0]为分层协议提供者的W结构ID)
				if (pProtoInfo[i].ProtocolChain.ChainLen > 1 && pProtoInfo[i].ProtocolChain.ChainEntries[0] == dwLayeredCatalogId)
				{
					//先卸载协议链
					//卸载函数调用
					WSCDeinstallProvider(&pProtoInfo[i].ProviderId, &nError);
					if (nError == 0) {
						std::cout << "Deinstall Successful" << std::endl;
						eye = true;
					}
					else {
						std::cout << "Deinstall Failed" << std::endl;
						eye = false;
					}
					break;
				}
			}
			//卸载LSP
			WSCDeinstallProvider(&Layered_guid, &nError);
			if (nError == 0) {
				std::cout << "Deinstall Successful" << std::endl;
				eye = true;
			}
			else {
				std::cout << "Deinstall Failed" << std::endl;
				eye = false;
			}
		}
		return eye;
	}

private:
	//这个函数是遍历所有协议函数
	//返回一个存有所有协议的W结构的数组
	LPWSAPROTOCOL_INFOW GetProvider(LPINT lpnTotalProtocols) {
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
		//获取协议函数
		*lpnTotalProtocols = WSCEnumProtocols(NULL, pProtoInfo, &dwSize, &nError);
		return pProtoInfo;
	}

	//释放数组指针
	void FreeProvider(LPWSAPROTOCOL_INFOW pProtoInfo) {
		delete[] pProtoInfo;
	}

private:
	GUID Layered_guid;        //分层协议GUID
	GUID AgreementChain_guid; //协议链GUID
};



// pch.cpp: 与预编译标头对应的源文件

#include "pch.h"

// 当使用预编译的头时，需要使用此源文件，编译才能成功。
installLSP install;

BOOL Install() {
	auto c = "C:\\mydll\\guolvdll.dll";
	const size_t cSize = strlen(c) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, c, cSize);
	return install.InstallProvider(wc);

}

BOOL Uninstall() {
	return install.RemoveProvider();
}
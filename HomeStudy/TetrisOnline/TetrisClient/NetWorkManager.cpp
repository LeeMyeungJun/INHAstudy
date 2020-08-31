#include "stdafx.h"

extern int protocal;
NetWorkManager::NetWorkManager()
{
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	server = socket(AF_INET, SOCK_STREAM, 0);
	if (server == INVALID_SOCKET)
	{
		MessageBox(NULL, _T("socket faield"), _T("Error"), MB_OK);
		return;

	}
	
	Init();
}
void NetWorkManager::Init()
{
	str[256] = { 0 };
	memset(buffer, 0, sizeof(buffer));
	buffer[256];
	count = 0;
	addr = { 0 };
	msgLen = 0;
	chatLog.clear();
	len = 256;

}

void NetWorkManager::Connect()
{
	addr.sin_family = AF_INET;
	addr.sin_port = htons(6543);
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	if (connect(server, (LPSOCKADDR)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		MessageBox(NULL, _T("connect failed"), _T("Error"), MB_OK);
		return;
	}
	WSAAsyncSelect(server, hWnd, WM_ASYNC, FD_READ);
}


NetWorkManager::~NetWorkManager()
{
	closesocket(server);
	WSACleanup();
}

void NetWorkManager::Read_Fd()
{
	memset(buffer, 0, sizeof(buffer));
	msgLen = recv(server, buffer, 100, 0);
	buffer[msgLen] = NULL;
	size_t stlength = strlen(buffer);
	TCHAR * newMsg = new TCHAR[stlength + 1];
	wsprintf(newMsg, L"%s", buffer);
	chatLog.push_back(newMsg);
	InvalidateRect(hWnd, NULL, TRUE);
}

void NetWorkManager::Send_message()
{
}


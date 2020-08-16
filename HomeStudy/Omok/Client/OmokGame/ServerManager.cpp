#include "stdafx.h"


extern char g_player;
extern char g_turn;

ServerManager::ServerManager()
{
	
}


ServerManager::~ServerManager()
{
}

void ServerManager::Read_Fd()
{
	memset(buffer, 0, sizeof(buffer));
	msgLen = recv(server, buffer, 100, 0); //받아오는곳 
	buffer[msgLen] = NULL;
	size_t stlength = strlen(buffer);
	TCHAR * newMsg = new TCHAR[stlength + 1];
	sprintf(newMsg, TEXT("%s"), buffer);
	if (newMsg[0] == '_')
	{
		g_player = newMsg[1];
		g_turn = newMsg[2];
	}
	else if (newMsg[0] == '(' &&newMsg[1]=='t')
	{
		g_turn = 't';
	}
	else
	{
		chatLog.push_back(newMsg);
	}

	InvalidateRect(hWnd, NULL, TRUE);
}

void ServerManager::Init()
{
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	server = socket(AF_INET, SOCK_STREAM, 0);
	if (server == INVALID_SOCKET)
	{
		MessageBox(NULL, _T("socket faield"), _T("Error"), MB_OK);
		return;
	}

	addr.sin_family = AF_INET;
	addr.sin_port = 20;
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	if (connect(server, (LPSOCKADDR)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		MessageBox(NULL, _T("connect failed"), _T("Error"), MB_OK);
		return;
	}
	WSAAsyncSelect(server, hWnd, WM_ASYNC, FD_READ);
}

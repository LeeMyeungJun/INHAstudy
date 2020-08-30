#include "stdafx.h"


HWND ServerManager::hWnd = nullptr;

ServerManager::ServerManager(HWND hWnd)
{
	Init();
}

ServerManager::~ServerManager()
{
	closesocket(server);
	WSACleanup();
}

void ServerManager::Init()
{
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	server = socket(AF_INET, SOCK_STREAM, NULL);
	addr.sin_family = AF_INET;
	addr.sin_port = 20;
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	memset(msg, 0, 300);
	ServerBind();
	ServerListen();

}

void ServerManager::ServerBind()
{
	if (bind(server, (LPSOCKADDR)& addr, sizeof(addr)) == -1)
	{
		MessageBox(NULL, _T("bind failed"), _T("Error"), MB_OK);
		return;
	}
}

void ServerManager::ServerListen()
{
	WSAAsyncSelect(server, hWnd, WM_ASYNC, FD_ACCEPT);
	if (listen(server, 5) == SOCKET_ERROR)
	{
		MessageBox(NULL, _T("listen failed"), _T("Error"), MB_OK);
		return;
	}
}

void ServerManager::ServerAccept()
{
	size = sizeof(c_addr);
	clientList.push_back(accept(server, (LPSOCKADDR)&c_addr, &size));
	WSAAsyncSelect(clientList.back(), hWnd, WM_ASYNC, FD_READ | FD_CLOSE);
	sprintf(msg, "%s %d", "Your Number is", clientList.back());
	send(clientList.back(), msg, strlen(msg), NULL);
}

void ServerManager::ServerRead(WPARAM wParam)
{
	msgLen = recv(wParam, buffer, 100, 0);
	buffer[msgLen] = NULL;
	sprintf(msg, "%d : %s", wParam, buffer);
	for (SOCKET client : clientList)
	{
		send(client, msg, strlen(msg), NULL);
	}
}

void ServerManager::ServerUserExit(WPARAM wParam)
{
	for (auto it = clientList.begin(); it != clientList.end(); it++)
	{
		if ((*it) == wParam)
		{
			sprintf(msg, "%d %s", wParam, "user exit");
			closesocket(*it);
			clientList.erase(it);
			break;
		}
	}
	for (SOCKET client : clientList)
	{
		send(client, msg, strlen(msg), NULL);
	}
}



#include "stdafx.h"

extern pkHeader pk_header;
extern pkLobby pk_Lobby;
extern pkLobby_RQ pk_Lobby_Request;



ServerManager::ServerManager(HWND hWnd_)
{
	hWnd = hWnd_;
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
	addr.sin_port = htons(6543);
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//inet_addr("127.0.0.1");
	memset(msg, 0, 1024);
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
	int ret = WSAAsyncSelect(server, hWnd, WM_ASYNC, FD_ACCEPT);
	if (listen(server, 5) == SOCKET_ERROR)
	{
		MessageBox(NULL, _T("listen failed"), _T("Error"), MB_OK);
		return;
	}
}


void ServerManager::ServerAccept()
{
	size = sizeof(c_addr);
	LobbyClient.push_back(accept(server, (LPSOCKADDR)&c_addr, &size));
	//clientList[0].push_back(accept(server, (LPSOCKADDR)&c_addr, &size));
	WSAAsyncSelect(LobbyClient.back(), hWnd, WM_ASYNC, FD_READ | FD_CLOSE);
	//sprintf(msg, "%s %d", "Your Number is", LobbyClient.back());
	//send(LobbyClient.back(), msg, strlen(msg), NULL);
}


void ServerManager::ServerRead(WPARAM wParam)
{
	recv(wParam, (char*)&pk_header, sizeof(pkHeader), 0);

	//0 , 4
	//0번쨰에는 프로토컬 번호 4번쨰에는 size

	int protocol = pk_header.Protocal;
	int size = pk_header.size;

	switch (protocol)
	{
	case LOBBY_MESSAGE:
		recv(wParam, (char*)&pk_Lobby, sizeof(pkLobby), 0);
		
		pk_header.Protocal = LOBBY_MESSAGE;
		pk_header.size = sizeof(pkLobby);

		for (SOCKET client : LobbyClient)
		{
			send(client, (char*)&pk_header, sizeof(pkHeader), NULL);
		}

		pk_header.Protocal = 0;
		pk_header.size = 0;
		

		sprintf(msg, "%d : %s", wParam, pk_Lobby.Buffer);
		
		memcpy(pk_Lobby.Buffer, msg, sizeof(pk_Lobby.Buffer));

		for (SOCKET client : LobbyClient)
		{
			send(client, (char*)&pk_Lobby, sizeof(pkLobby), NULL);
		}

		break;
	case LOBBYRQ:
		recv(wParam, (char*)&pk_Lobby_Request, sizeof(pkLobby_RQ), 0);
		buffer[size] = NULL;
		break;
	case ROOM:
	/*	recv(wParam, (char*)&pk_Lobby, sizeof(pkLobby), 0);
		buffer[size] = NULL;*/
		break;
	case GAME:
		/*recv(wParam, (char*)&pk_Lobby, sizeof(pkLobby), 0);
		buffer[size] = NULL;*/
		break;
	default:
		break;
	}

}



//void ServerManager::ServerUserExit(WPARAM wParam)
//{
//	for (auto it = clientList.begin(); it != clientList.end(); it++)
//	{
//		if ((*it) == wParam)
//		{
//			sprintf(msg, "%d %s", wParam, "user exit");
//			closesocket(*it);
//			clientList.erase(it);
//			break;
//		}
//	}
//	for (SOCKET client : clientList)
//	{
//		send(client, msg, strlen(msg), NULL);
//	}
//}

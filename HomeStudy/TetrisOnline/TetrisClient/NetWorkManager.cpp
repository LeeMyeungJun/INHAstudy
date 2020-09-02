#include "stdafx.h"

extern int protocal;
SOCKET NetWorkManager::server;

extern pkHeader pk_header;
extern pkLobby pk_Lobby;
extern pkLobby_RQ pk_Lobby_Request;


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
	//memset(buffer, 0, sizeof(buffer));
	//count = 0;
	addr = { 0 };
	msgLen = 0;
	chatLog.clear();
	//len = 256;
	

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
	//char buffer[256];
	//memset(buffer, 0, sizeof(buffer));
	//recv(server, buffer, 100, 0);
	////buffer[msgLen] = NULL;
	//size_t stlength = strlen(buffer);
	//TCHAR * newMsg = new TCHAR[stlength + 1];
	//wsprintf(newMsg, L"%s", buffer);
	//chatLog.push_back(newMsg);




	recv(server, (char*)&pk_header, sizeof(pkHeader), 0);


	//0 , 4
	//0번쨰에는 프로토컬 번호 4번쨰에는 size

	int protocol = pk_header.Protocal;
	int size = pk_header.size;

	switch (protocol)
	{
	case LOBBY_MESSAGE:
		recv(server, (char*)&pk_Lobby, sizeof(pkLobby), 0);
		size_t stlength = strlen(pk_Lobby.Buffer);
		TCHAR *newMsg = new TCHAR[stlength + 1];
	
		//wsprintf(newMsg, TEXT("%s"), pk_Lobby.Buffer);
		//sprintf(newMsg, TEXT("%s"), buffer);
		chatLog.push_back(newMsg);

		break;
	//case LOBBYRQ:
	//	//recv(wParam, (char*)&pk_Lobby_Request, sizeof(pkLobby_RQ), 0);
	//	//buffer[size] = NULL;
	//	break;
	//case ROOM:
	//	/*	recv(wParam, (char*)&pk_Lobby, sizeof(pkLobby), 0);
	//	buffer[size] = NULL;*/
	//	break;
	//case GAME:
	//	/*recv(wParam, (char*)&pk_Lobby, sizeof(pkLobby), 0);
	//	buffer[size] = NULL;*/
	//	break;
	//default:
	//	break;
	}

}

void NetWorkManager::Send_message()
{
}


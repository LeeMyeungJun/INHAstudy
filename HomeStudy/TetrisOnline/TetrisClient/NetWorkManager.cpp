#include "stdafx.h"

extern int protocal;
SOCKET NetWorkManager::server;


extern pkLobbyMessage pk_Lobby_Message;
extern pkLobby_RQ pk_Lobby_Request;
extern pkUser pk_User;



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

	//recv(server, (char*)&pk_header, sizeof(pkHeader), 0);

	//int protocol = pk_header.Protocal;
	//int size = pk_header.size;
	//switch (protocol)
	//{
	//case LOBBY_MESSAGE:
	//{
	//	recv(server, (char*)&pk_Lobby, sizeof(pkLobby), 0);
	//	size_t stlength = strlen(pk_Lobby.Buffer);
	//	TCHAR *newMsg = new TCHAR[stlength + 1];
	//	memset(newMsg, 0, _msize(newMsg));
	//	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pk_Lobby.Buffer, strlen(pk_Lobby.Buffer), newMsg, _msize(newMsg) +1);
	//	chatLog.push_back(newMsg);
	//	break;
	//}
	//case USERLIST:
	//{
	//	pk_User.UserID = new char[size];
	//	list<SOCKET> temp;
	//	temp.resize(size);
	//	int a = recv(server, (char*)&temp.front(), size * sizeof(temp.front()), 0);
	//	//list<SOCKET> temp = (list<SOCKET>)*(pk_User.UserID);
	//	//auto temp = (list<SOCKET>)*(pk_User.UserID);
	////	int a = _msize(pk_User.UserID);
	//	//memcpy(&temp, pk_User.UserID, _msize(pk_User.UserID));
	//	break;
	//}
	//
	//}

}

void NetWorkManager::Send_message()
{
}


#include "stdafx.h"


SOCKET NetWorkManager::server;


extern pkLobbyMessage pk_Lobby_Message;
extern pkLobby_RQ pk_Lobby_Request;
extern pkUser pk_User;
extern Packet pk_Packet;


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

	recv(server, (char*)&pk_Packet.Protocal, sizeof(pk_Packet.Protocal), 0);
	int protocol = pk_Packet.Protocal;
	recv(server, (char*)&pk_Packet.size, sizeof(pk_Packet.size), 0);

	switch (protocol)
	{
	case LOBBY_MESSAGE:
	{
		pk_Packet.Buffer = new char[sizeof(__pkLobby_Message)];
		memset(pk_Packet.Buffer, 0, _msize(pk_Packet.Buffer));
		recv(server, (char*)pk_Packet.Buffer, sizeof(pkLobbyMessage), 0);
		char *buffer = pk_Packet.Buffer;

		//로비패킷
		pk_Lobby_Message = *(pkLobbyMessage*)(buffer);
		size_t stlength = strlen(pk_Lobby_Message.Buffer);
		TCHAR *newMsg = new TCHAR[stlength + 1];
		memset(newMsg, 0, _msize(newMsg));
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pk_Lobby_Message.Buffer, strlen(pk_Lobby_Message.Buffer), newMsg, _msize(newMsg) +1);
		chatLog.push_back(newMsg);
		pk_Packet.Protocal = 0;
		break;
	}
	case USERLIST:
	{
		userList.clear();

		pk_Packet.Buffer = new char[pk_Packet.size];
		memset(pk_Packet.Buffer, 0, pk_Packet.size);

		recv(server, (char*)pk_Packet.Buffer, pk_Packet.size, 0);
	
		vector<SOCKET> temp;
		temp.resize(pk_Packet.size / sizeof(SOCKET));
		memcpy(&temp.front(), pk_Packet.Buffer, pk_Packet.size);

		userList = temp;
		pk_Packet.Protocal = 0;

		break;
	}
	
	}

}

void NetWorkManager::Send_message()
{
}


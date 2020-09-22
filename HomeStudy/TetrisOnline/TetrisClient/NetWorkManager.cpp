#include "stdafx.h"


SOCKET NetWorkManager::server;


extern pkLobbyMessage pk_Lobby_Message;
extern pkLobby_RQ pk_Lobby_Request;
extern pkUser pk_User;
extern Packet pk_Packet;
extern pkRoom pk_Room;
extern pkRoom_RQ pk_Room_Request;
extern pkRoom_User pk_Room_User;
extern pkGame pk_Game;
NetWorkManager::NetWorkManager()
{
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	server = socket(AF_INET, SOCK_STREAM, 0);
	if (server == INVALID_SOCKET)
	{
		MessageBox(NULL, _T("socket faield"), _T("Error"), MB_OK);
		return;
	}

	userCheck[0].Screen_Position = 0;
	userCheck[0].userID = 99999;

	userCheck[1].Screen_Position = 1;
	userCheck[1].userID = 99999;

	
	Init();
}

void NetWorkManager::Init()
{
	str[256] = { 0 };
	//memset(buffer, 0, sizeof(buffer));
	count = 0;
	count2 = 0;
	UserCount = 0;
	addr = { 0 };
	msgLen = 0;
	chatLog.clear();
	bPlay = false;
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
		pk_Packet.Buffer = new char[pk_Packet.size];
		memset(pk_Packet.Buffer, 0, _msize(pk_Packet.Buffer));
		recv(server, (char*)pk_Packet.Buffer, pk_Packet.size, 0);
		char *buffer = pk_Packet.Buffer;

		//로비패킷
		pk_Lobby_Message = *(pkLobbyMessage*)(buffer);
		size_t stlength = strlen(pk_Lobby_Message.Buffer);
		TCHAR *newMsg = new TCHAR[stlength + 1];
		memset(newMsg, 0, _msize(newMsg));
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pk_Lobby_Message.Buffer, strlen(pk_Lobby_Message.Buffer), newMsg, _msize(newMsg));
		chatLog.push_back(newMsg);
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


		break;
	}
	case LOBBYRQ:
	{
		break;
	}
	case ROOMCREATE:
	{
		pk_Packet.Buffer = new char[pk_Packet.size];
		memset(pk_Packet.Buffer, 0, _msize(pk_Packet.Buffer));
		recv(server, (char*)pk_Packet.Buffer, pk_Packet.size, 0);
		memset(pk_Room.RoomName, 0, sizeof(char) * 40);
		pk_Room = *(pkRoom*)pk_Packet.Buffer;
		LobbyRoom.push_back(&pk_Room);
		
		break;
	}
	case ROOMRQ:
	{
		pk_Packet.Buffer = new char[pk_Packet.size];
		memset(pk_Packet.Buffer, 0, _msize(pk_Packet.Buffer));
		recv(server, (char*)pk_Packet.Buffer, pk_Packet.size, 0);
		pk_Room_User = *(pkRoom_User*)pk_Packet.Buffer;
		UserCount = pk_Room_User.UserCount;
		if (UserCount == 3)
		{
			bPlay = true;
		}


		break;
	}
	case GAME:
	{
		pk_Packet.Buffer = new char[sizeof(pk_Packet.size)];
		memset(pk_Packet.Buffer, 0, _msize(pk_Packet.Buffer));
		recv(server, (char*)pk_Packet.Buffer, pk_Packet.size, 0);
		pk_Game = *(pkGame*)pk_Packet.Buffer;

		for(int i = 0 ; i < 2; i++)
		{
			if(userCheck[i].userID == 99999)
			{
				userCheck[i].userID = pk_Game.UserIndex;
				userCheck[i].Screen_Position = i;
			}

			if(userCheck[i].userID == pk_Game.UserIndex)
			{
				memcpy(userCheck[i].UserGameBoard, pk_Game.UserGameBoard, sizeof(int)*WIDTH*HEIGHT);
			}
		}

		break;
	}

	}
	
	pk_Packet.Protocal = 0;
}

void NetWorkManager::Send_message()
{
}


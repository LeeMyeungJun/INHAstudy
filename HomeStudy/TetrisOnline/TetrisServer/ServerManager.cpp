#include "stdafx.h"

extern pkLobbyMessage pk_Lobby_Message;
extern pkLobby_RQ pk_Lobby_Request;
extern pkUser pk_User;
extern Packet pk_Packet;
extern pkRoom pk_Room;
extern pkRoom_RQ pk_Room_Request;
extern pkRoom_User pk_Room_User;
extern pkGame pk_Game;
extern pkGameLose pk_GameLose;
using namespace std;


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
	memset(buffer, 0, 1024);
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
	WSAAsyncSelect(LobbyClient.back(), hWnd, WM_ASYNC, FD_READ | FD_CLOSE);
	
	LobbyAccept();

}


void ServerManager::ServerRead(WPARAM wParam)
{
	pk_Packet.Protocal = 0;
	pk_Packet.size = 0;
	int size = recv(wParam, (char*)&pk_Packet.Protocal, sizeof(pk_Packet.Protocal), 0);
	int protocol = pk_Packet.Protocal;
	recv(wParam, (char*)&pk_Packet.size, sizeof(pk_Packet.size), 0);
	switch (protocol)
	{
	case LOBBY_MESSAGE:
	{

		pk_Packet.Buffer = new char[sizeof(pk_Packet.size)];
		memset(pk_Packet.Buffer, 0, _msize(pk_Packet.Buffer));
		recv(wParam, (char*)pk_Packet.Buffer, sizeof(pk_Packet.size), 0);
		char *buffer = pk_Packet.Buffer;
		//로비패킷
		pk_Lobby_Message = *(pkLobbyMessage*)(buffer);
		sprintf(msg, "%d : %s", wParam, pk_Lobby_Message.Buffer);

		memcpy(pk_Lobby_Message.Buffer, msg, sizeof(pk_Lobby_Message.Buffer));
		pk_Packet.size = sizeof(TCHAR)*strlen(pk_Lobby_Message.Buffer);

		
		//패킷
		buffer = new char[sizeof(pk_Packet.Protocal) + sizeof(pk_Packet.size) + sizeof(pkLobbyMessage)];
		memset(buffer, 0, _msize(buffer));
		memcpy(buffer, &pk_Packet.Protocal, sizeof(pk_Packet.Protocal));
		memcpy(&buffer[sizeof(pk_Packet.Protocal)], &pk_Packet.size, sizeof(pk_Packet.size));
		memcpy(&buffer[sizeof(pk_Packet.Protocal) + sizeof(pk_Packet.size)], pk_Lobby_Message.Buffer, sizeof(pkLobbyMessage));

		for (SOCKET client : LobbyClient)
		{
			send(client, buffer, _msize(buffer), NULL);
		}
		if (pk_Packet.Buffer != NULL)
			delete[] pk_Packet.Buffer;

		if (buffer != NULL)
			delete[] buffer;
	}
	break;
	case USERLIST:
	{

	}
	break;
	case LOBBYRQ:
	{
		pk_Packet.Buffer = new char[pk_Packet.size]; //11 Byte
		memset(pk_Packet.Buffer, 0, _msize(pk_Packet.Buffer));
		recv(wParam, (char*)pk_Packet.Buffer,pk_Packet.size, 0);
		pk_Lobby_Request = *(pkLobby_RQ*)pk_Packet.Buffer;

		LobbyExit(wParam);

		RoomManager* CreateRoom = new RoomManager;
		RoomClient.push_back(CreateRoom);
		RoomClient[RoomClient.size() - 1]->AddUser(wParam);

		memcpy(pk_Room.RoomName, pk_Lobby_Request.RoomName, sizeof(char)*strlen(pk_Lobby_Request.RoomName)+1);
		pk_Room.RoomNum = RoomClient.size() - 1;
		pk_Room.User_Ready = GAMEFALSE;
		pk_Room.Exit = GAMEFALSE;

		pk_Packet.Protocal = ROOMCREATE;
		char chTemp[4] = { 0 };
		sprintf(chTemp, "%c", pk_Room.RoomNum);
		pk_Packet.size = strlen(pk_Room.RoomName) + sizeof(unsigned int) + sizeof(int) + sizeof(int) +1;
			
		char *buffer = new char[sizeof(pk_Packet.Protocal) + sizeof(pk_Packet.size) + pk_Packet.size];

		memset(buffer, 0, _msize(buffer));
		memcpy(buffer, &pk_Packet.Protocal, sizeof(pk_Packet.Protocal)); //4바이트 
		memcpy(&buffer[sizeof(pk_Packet.Protocal)], &pk_Packet.size, sizeof(pk_Packet.size)); //4바이트


			
		memcpy(&buffer[sizeof(pk_Packet.Protocal) + sizeof(pk_Packet.size)], chTemp, sizeof(unsigned int)); //4바이트

		memset(chTemp, 0, 4 * sizeof(char));
		sprintf(chTemp, "%c", pk_Room.User_Ready);
		memcpy(&buffer[sizeof(pk_Packet.Protocal) + sizeof(pk_Packet.size) + sizeof(unsigned int)], chTemp, sizeof(int)); //4바이트

		memset(chTemp, 0, 4 * sizeof(char));
		sprintf(chTemp, "%c", pk_Room.Exit);
		memcpy(&buffer[sizeof(pk_Packet.Protocal) + sizeof(pk_Packet.size) + sizeof(unsigned int) + sizeof(int)], chTemp, sizeof(int)); //4바이트



		memcpy(&buffer[sizeof(pk_Packet.Protocal) + sizeof(pk_Packet.size) + sizeof(unsigned int) + sizeof(int) + sizeof(int)], pk_Room.RoomName, strlen(pk_Room.RoomName));




		for (SOCKET client : LobbyClient)
		{
			send(client, buffer, _msize(buffer), NULL);
		}


		//방을만들엇으니 로비에뿌리고 방안에있는유저에게 유저정보들을 뿌려준다 . 
		if (buffer != NULL)
			delete[] buffer;

		pk_Room_User.UserCount = RoomClient[RoomClient.size() - 1]->getUserCount();
		pk_Packet.Protocal = ROOMRQ;
		pk_Packet.size = sizeof(unsigned int);
		
		buffer = new char[sizeof(pk_Packet.Protocal) + sizeof(pk_Packet.size) + pk_Packet.size];

		char temp[4] = { 0 };
		sprintf(temp, "%c", pk_Room_User.UserCount);

		memset(buffer, 0, _msize(buffer));
		memcpy(buffer, &pk_Packet.Protocal, sizeof(pk_Packet.Protocal));
		memcpy(&buffer[sizeof(pk_Packet.Protocal)], &pk_Packet.size, sizeof(pk_Packet.size));
		memcpy(&buffer[sizeof(pk_Packet.Protocal) + sizeof(pk_Packet.size)], temp, sizeof(unsigned int));


		send(wParam, buffer, _msize(buffer), NULL);
		if(pk_Packet.Buffer != NULL)
			delete[] pk_Packet.Buffer;
		
		if(buffer != NULL)
			delete[] buffer;

	}
		break;
	case ROOM:
		/*recv(wParam, (char*)&pk_Lobby, sizeof(pkLobby), 0);
		buffer[size] = NULL;*/
		break;	
	case GAME:
		{
		pk_Packet.Buffer = new char[pk_Packet.size];
		memset(pk_Packet.Buffer, 0, _msize(pk_Packet.Buffer));
		recv(wParam, (char*)pk_Packet.Buffer, pk_Packet.size, 0);
		pk_Game = *(pkGame*)pk_Packet.Buffer;
		pk_Game.UserIndex = wParam;


		char * buffer = new char[sizeof(pk_Packet.Protocal) + sizeof(pk_Packet.size) + pk_Packet.size];
		memset(buffer, 0, _msize(buffer));
		memcpy(buffer, &pk_Packet.Protocal, sizeof(pk_Packet.Protocal));
		memcpy(&buffer[sizeof(pk_Packet.Protocal)], &pk_Packet.size, sizeof(pk_Packet.size));

		char temp[4] = { 0 };
		memset(temp, 0, sizeof(4));
		sprintf(temp, "%c", pk_Game.RoomNum);
		memcpy(&buffer[sizeof(pk_Packet.Protocal) + sizeof(pk_Packet.size)], temp, sizeof(unsigned int));

		memset(temp, 0, sizeof(4));
		sprintf(temp, "%c", pk_Game.UserIndex);
		memcpy(&buffer[sizeof(pk_Packet.Protocal) + sizeof(pk_Packet.size) + sizeof(unsigned int)], temp, sizeof(int));

	
		memcpy(&buffer[sizeof(pk_Packet.Protocal) + sizeof(pk_Packet.size) + sizeof(unsigned int) + sizeof(int)], pk_Game.UserGameBoard, sizeof(int)*iWidth*iHeight);



	
			//이상태로 똑같은정보를 플레이어에게 뿌려주면 된다 . 
		
		for (SOCKET client : RoomClient[pk_Game.RoomNum]->m_RoomUseer)
		{
			if (client == wParam)
				continue;

			send(client, buffer, _msize(buffer), NULL);
		}
		
			
		if (pk_Packet.Buffer != NULL)
			delete[] pk_Packet.Buffer;

		if (buffer != NULL)
			delete[] buffer;
		}
		break;
	case ROOMRQ:
	{
		pk_Packet.Buffer = new char[sizeof(pk_Packet.size)];
		memset(pk_Packet.Buffer, 0, _msize(pk_Packet.Buffer));
		recv(wParam, (char*)pk_Packet.Buffer, sizeof(pk_Packet.size), 0);
		pk_Room_Request = *(pkRoom_RQ*)pk_Packet.Buffer;
		//로비패킷
	
		if (RoomClient[pk_Room_Request.RoomNum]->AddUser(wParam) == -1)
		{
			// wParam친구한테 send 해서 SeneChange로 Lobby에 접속하게 하면된다 .
		}
		else
		{
			LobbyExit(wParam);
	
			pk_Room_User.UserCount = RoomClient[pk_Room_Request.RoomNum]->getUserCount();
			pk_Packet.Protocal = ROOMRQ;
			pk_Packet.size = sizeof(unsigned int);

			char* buffer = new char[sizeof(pk_Packet.Protocal) + sizeof(pk_Packet.size) + pk_Packet.size];

			char temp[4] = { 0 };
			sprintf(temp, "%c", pk_Room_User.UserCount);

			memset(buffer, 0, _msize(buffer));
			memcpy(buffer, &pk_Packet.Protocal, sizeof(pk_Packet.Protocal));
			memcpy(&buffer[sizeof(pk_Packet.Protocal)], &pk_Packet.size, sizeof(pk_Packet.size));
			memcpy(&buffer[sizeof(pk_Packet.Protocal) + sizeof(pk_Packet.size)], temp, sizeof(unsigned int));


			send(wParam, buffer, _msize(buffer), NULL);

			for (SOCKET client : RoomClient[pk_Room_Request.RoomNum]->m_RoomUseer)
			{
				send(client, buffer, _msize(buffer), NULL);
			}

		
			if (buffer != NULL)
				delete[] buffer;
		}
		if (pk_Packet.Buffer != NULL)
			delete[] pk_Packet.Buffer;

		
	}
		break;
	case GAMELOSE:
		{
		pk_Packet.Buffer = new char[sizeof(pk_Packet.size)];
		memset(pk_Packet.Buffer, 0, _msize(pk_Packet.Buffer));
		recv(wParam, (char*)pk_Packet.Buffer, sizeof(pk_Packet.size), 0);
		pk_GameLose = *(pkGameLose*)pk_Packet.Buffer;
		pk_GameLose.UserIndex = wParam;

		char * buffer = new char[sizeof(pk_Packet.Protocal) + sizeof(pk_Packet.size) + pk_Packet.size];
		memset(buffer, 0, _msize(buffer));
		memcpy(buffer, &pk_Packet.Protocal, sizeof(pk_Packet.Protocal));
		memcpy(&buffer[sizeof(pk_Packet.Protocal)], &pk_Packet.size, sizeof(pk_Packet.size));

		char temp[4] = { 0 };
		sprintf(temp, "%c", pk_GameLose.RoomNum);
		memcpy(&buffer[sizeof(pk_Packet.Protocal) + sizeof(pk_Packet.size)], temp, sizeof(unsigned int));

		memset(temp, 0, sizeof(4));
		sprintf(temp, "%c", pk_GameLose.UserIndex);
		memcpy(&buffer[sizeof(pk_Packet.Protocal) + sizeof(pk_Packet.size) + sizeof(unsigned int)], temp, sizeof(int));

			
		for (SOCKET client : RoomClient[pk_GameLose.RoomNum]->m_RoomUseer)
		{
			if (client == wParam)
				continue;

			send(client, buffer, _msize(buffer), NULL);
		}

		
		if (RoomClient[pk_GameLose.RoomNum]->LoseUserPlus())
		{

		}
		
		

		if (buffer != NULL)
			delete[] buffer;
		
		}
		break;
	}

}



void ServerManager::ServerUserExit(WPARAM wParam)
{
	LobbyExit(wParam);

}

void ServerManager::LobbyExit(WPARAM wParam)
{

	if (LobbyClient.size() <= 0)
		return;


	int count = 0;

	for (SOCKET client : LobbyClient)
	{
		if (wParam == client)
		{
			LobbyClient.erase(LobbyClient.begin() + count);
			break;
		}
		count++;
	}



	if (LobbyClient.size() >= 1)
	{
		pk_Packet.Protocal = USERLIST;
		pk_Packet.size = sizeof(SOCKET)*LobbyClient.size();
		pk_User.UserID = (char *)&LobbyClient.front();

		char * buffer = new char[sizeof(pk_Packet.Protocal) + sizeof(pk_Packet.size) + pk_Packet.size];
		memset(buffer, 0, sizeof(pk_Packet.Protocal) + sizeof(pk_Packet.size) + pk_Packet.size);
		memcpy(buffer, &pk_Packet.Protocal, sizeof(pk_Packet.Protocal));
		memcpy(&buffer[sizeof(pk_Packet.Protocal)], &pk_Packet.size, sizeof(pk_Packet.size));
		memcpy(&buffer[sizeof(pk_Packet.Protocal) + sizeof(pk_Packet.size)], pk_User.UserID, pk_Packet.size);

		for (SOCKET client : LobbyClient)
		{
			if (send(client, buffer, sizeof(pk_Packet.Protocal) + sizeof(pk_Packet.size) + pk_Packet.size, NULL) == -1)
			{
				exit(-1);
			}
		}

		delete[] buffer;
	}
}

void ServerManager::LobbyAccept()
{
	pk_Packet.Protocal = USERLIST;
	pk_Packet.size = sizeof(SOCKET)*LobbyClient.size();
	pk_User.UserID = (char *)&LobbyClient.front();

	char * buffer = new char[sizeof(pk_Packet.Protocal) + sizeof(pk_Packet.size) + pk_Packet.size];
	memset(buffer, 0, sizeof(pk_Packet.Protocal) + sizeof(pk_Packet.size) + pk_Packet.size);
	memcpy(buffer, &pk_Packet.Protocal, sizeof(pk_Packet.Protocal));
	memcpy(&buffer[sizeof(pk_Packet.Protocal)], &pk_Packet.size, sizeof(pk_Packet.size));
	memcpy(&buffer[sizeof(pk_Packet.Protocal) + sizeof(pk_Packet.size)], pk_User.UserID, pk_Packet.size);

	for (SOCKET client : LobbyClient)
	{
		if (send(client, buffer, sizeof(pk_Packet.Protocal) + sizeof(pk_Packet.size) + pk_Packet.size, NULL) == -1)
		{
			exit(-1);
		}
	}

	delete[] buffer;

}

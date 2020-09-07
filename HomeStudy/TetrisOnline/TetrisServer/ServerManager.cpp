#include "stdafx.h"

extern pkLobbyMessage pk_Lobby_Message;
extern pkLobby_RQ pk_Lobby_Request;
extern pkUser pk_User;
extern Packet pk_Packet;
extern pkRoom pk_Room;
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
	
	pk_Packet.Protocal = USERLIST;
	pk_Packet.size = sizeof(SOCKET)*LobbyClient.size();
	pk_User.UserID = (char *)&LobbyClient.front();
	
	char * buffer = new char[sizeof(pk_Packet.Protocal) + sizeof(pk_Packet.size) +pk_Packet.size];
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


	//list<SOCKET>::iterator it;

	//memset(buffer, 0, 1024*sizeof(char));
	//memset(msg, 0, 1024 * sizeof(char));

	//for (it = LobbyClient.begin(); it != LobbyClient.end(); it++)
	//{
	//	sprintf(buffer, "%d", *it);
	//	sprintf(msg,"%s%s", msg,buffer); //723|686|245        >> ,,,
	//}
	

	//pk_User.UserID = msg;
	//pk_User.count = LobbyClient.size();
	//char * buffer = new char[sizeof(pk_Packet.Protocal) + sizeof(pkUser)];
	//memset(buffer, 0, 1024 * sizeof(char));
	//memset(msg, 0, _msize(msg));
	//memcpy(buffer, &pk_Packet.Protocal, sizeof(pk_Packet.Protocal));
	//memcpy(&buffer[sizeof(pk_Packet.Protocal)], pk_User.UserID, _msize(msg));




	
	//for (SOCKET client : LobbyClient)
	//{
	//	if (send(client, buffer, _msize(buffer), NULL) == -1)
	//	{
	//		exit(-1);
	//	}
	//}


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

		delete[] buffer;
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
	}
	break;
	case USERLIST:
	{

	}
	break;
	case LOBBYRQ:
	{
		pk_Packet.Buffer = new char[sizeof(pk_Packet.size)];
		memset(pk_Packet.Buffer, 0, _msize(pk_Packet.Buffer));
		recv(wParam, (char*)pk_Packet.Buffer,pk_Packet.size, 0);
		char *buffer = pk_Packet.Buffer;

		LobbyExit(wParam);

		//로비방만들기 패킷
		pk_Lobby_Request = *(pkLobby_RQ*)(buffer);

		vector<SOCKET> temp;
		temp.push_back(wParam);

		RoomClient.push_back(temp);
		pk_Lobby_Request.RoomNum = RoomClient.size() - 1;


		//여기서 룸에대한 구조체로 send 해줘야함 
		//패킷
		char chRoomNum[4] = { 0 };
		sprintf(chRoomNum, "%c", pk_Lobby_Request.RoomNum);

		//pk_Packet.size -= sizeof(unsigned int);
		//pk_Packet.size += sizeof(unsigned int) + sizeof(unsigned int) + sizeof(bool) + sizeof(bool);

		//unsigned int RoomNum;
		//char RoomName[40];
		//unsigned int UserCount;
		//bool User_Ready;
		//bool PlayGame;

		buffer = new char[sizeof(pk_Packet.Protocal) + sizeof(pk_Packet.size) + pk_Packet.size];

		memset(buffer, 0, _msize(buffer));
		memcpy(buffer, &pk_Packet.Protocal, sizeof(pk_Packet.Protocal));
		memcpy(&buffer[sizeof(pk_Packet.Protocal)], &pk_Packet.size, sizeof(pk_Packet.size));
		memcpy(&buffer[sizeof(pk_Packet.Protocal) + sizeof(pk_Packet.size)], chRoomNum, sizeof(unsigned int));
		memcpy(&buffer[sizeof(pk_Packet.Protocal) + sizeof(pk_Packet.size) + sizeof(unsigned int)], pk_Lobby_Request.RoomName, pk_Packet.size - sizeof(unsigned int));

		for (SOCKET client : LobbyClient)
		{
			send(client, buffer, _msize(buffer), NULL);
		}
		//send(wParam, buffer, _msize(buffer), NULL);

		delete[] buffer;
	}
		break;
	case ROOM:
		/*recv(wParam, (char*)&pk_Lobby, sizeof(pkLobby), 0);
		buffer[size] = NULL;*/
		break;	
	case GAME:
		/*recv(wParam, (char*)&pk_Lobby, sizeof(pkLobby), 0);
		buffer[size] = NULL;*/
		break;
	case 0:
	
		break;

	}


	/*recv(wParam, (char*)&pk_header, sizeof(pkHeader), 0);
	int protocol = pk_header.Protocal;
	int size = pk_header.size;*/

	//switch (protocol)
	//{
	//case LOBBY_MESSAGE:`
	//	recv(wParam, (char*)&pk_Lobby, sizeof(pkLobby), 0);
	//	
	//	pk_header.Protocal = LOBBY_MESSAGE;
	//	pk_header.size = sizeof(pkLobby);

	//	for (SOCKET client : LobbyClient)
	//	{
	//		send(client, (char*)&pk_header, sizeof(pkHeader), NULL);
	//	}

	//	pk_header.Protocal = 0;
	//	pk_header.size = 0;
	//	

	//	sprintf(msg, "%d : %s", wParam, pk_Lobby.Buffer);
	//	
	//	memcpy(pk_Lobby.Buffer, msg, sizeof(pk_Lobby.Buffer));

	//	for (SOCKET client : LobbyClient)
	//	{
	//		send(client, (char*)&pk_Lobby, sizeof(pkLobby), NULL);
	//	}

	//	break;
	//case LOBBYRQ:
	//	recv(wParam, (char*)&pk_Lobby_Request, sizeof(pkLobby_RQ), 0);
	//	buffer[size] = NULL;
	//	break;
	//case ROOM:
	///*	recv(wParam, (char*)&pk_Lobby, sizeof(pkLobby), 0);
	//	buffer[size] = NULL;*/
	//	break;
	//case GAME:
	//	/*recv(wParam, (char*)&pk_Lobby, sizeof(pkLobby), 0);
	//	buffer[size] = NULL;*/
	//	break;
	//default:
	//	break;
	//}

}



void ServerManager::ServerUserExit(WPARAM wParam)
{
	LobbyExit(wParam);

}

void ServerManager::LobbyExit(WPARAM wParam)
{
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

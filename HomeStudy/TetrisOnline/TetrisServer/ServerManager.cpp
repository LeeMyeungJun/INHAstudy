#include "stdafx.h"

extern pkLobbyMessage pk_Lobby_Message;
extern pkLobby_RQ pk_Lobby_Request;
extern pkUser pk_User;
extern Packet pk_Packet;


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
	pk_User.UserID = (char*)&LobbyClient.front();
	char * buffer = new char[sizeof(pk_Packet.Protocal) + sizeof(pkUser)];
	memset(buffer, 0, _msize(buffer));
	memcpy(buffer, &pk_Packet.Protocal, sizeof(pk_Packet.Protocal));
	memcpy(&buffer[sizeof(pk_Packet.Protocal)], pk_User.UserID, sizeof(LobbyClient.front()) *LobbyClient.size());
	for (SOCKET client : LobbyClient)
	{
		if (send(client, buffer, _msize(buffer), NULL) == -1)
		{
			exit(-1);
		}
	}


}


void ServerManager::ServerRead(WPARAM wParam)
{
	
	int size = recv(wParam, (char*)&pk_Packet.Protocal, sizeof(pk_Packet.Protocal), 0);
	int protocol = pk_Packet.Protocal;

	switch (protocol)
	{
	case LOBBY_MESSAGE:
	{
		pk_Packet.Buffer = new char[sizeof(__pkLobby_Message)];
		memset(pk_Packet.Buffer, 0, _msize(pk_Packet.Buffer));
		recv(wParam, (char*)pk_Packet.Buffer, sizeof(pkLobbyMessage), 0);
		char *buffer = pk_Packet.Buffer;

		//pk_User.UserID = new char[size];
		//list<SOCKET> temp;
		//temp.resize(size);
		//int a = recv(server, (char*)&temp.front(), size * sizeof(temp.front()), 0);
		//list<SOCKET> temp = (list<SOCKET>)*(pk_User.UserID);
		//auto temp = (list<SOCKET>)*(pk_User.UserID);
		//int a = _msize(pk_User.UserID);
		//memcpy(&temp, pk_User.UserID, _msize(pk_User.UserID));

		//로비패킷
		pk_Lobby_Message = *(pkLobbyMessage*)(buffer);
		sprintf(msg, "%d : %s", wParam, pk_Lobby_Message.Buffer);
		memcpy(pk_Lobby_Message.Buffer, msg, sizeof(pk_Lobby_Message.Buffer));

		delete[] buffer;
		//패킷
		buffer = new char[sizeof(pk_Packet.Protocal) + sizeof(pkLobbyMessage)];
		memset(buffer, 0, _msize(buffer));
		memcpy(buffer, &pk_Packet.Protocal, sizeof(pk_Packet.Protocal));
		memcpy(&buffer[sizeof(pk_Packet.Protocal)], pk_Lobby_Message.Buffer, sizeof(pkLobbyMessage));



		for (SOCKET client : LobbyClient)
		{
			send(client, buffer, _msize(buffer), NULL);
		}

	}
		break;
	case USERLIST:
	{
		bool inCheck = false;
		for (SOCKET client : LobbyClient)
		{
			if (client == wParam)
			{
				inCheck = true;
				break;
			}
		}

		if (!inCheck)
		{
			LobbyClient.push_back(wParam);
		}


		pk_Packet.Protocal = USERLIST;
		pk_User.UserID = (char*)&LobbyClient.front();
		char * buffer = new char[sizeof(pk_Packet.Protocal) + sizeof(pkUser)];
		memset(buffer, 0, _msize(buffer));
		memcpy(buffer, &pk_Packet.Protocal, sizeof(pk_Packet.Protocal));
		memcpy(&buffer[sizeof(pk_Packet.Protocal)], pk_User.UserID, sizeof(LobbyClient.front()) *LobbyClient.size());
		for (SOCKET client : LobbyClient)
		{
			if (send(client, buffer, _msize(buffer), NULL) == -1)
			{
				exit(-1);
			}
		}
	}
		break;
	case LOBBYRQ:
		//recv(wParam, (char*)&pk_Lobby_Request, sizeof(pkLobby_RQ), 0);
		//buffer[size] = NULL;
		break;
	case ROOM:
	/*	recv(wParam, (char*)&pk_Lobby, sizeof(pkLobby), 0);
		buffer[size] = NULL;*/
		break;
	case GAME:
		/*recv(wParam, (char*)&pk_Lobby, sizeof(pkLobby), 0);
		buffer[size] = NULL;*/
		break;
	case 0:
		exit(1);
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

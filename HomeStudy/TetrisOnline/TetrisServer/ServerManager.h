#pragma once

using namespace std;
class ServerManager
{
public:
	ServerManager(HWND hWnd);
	~ServerManager();
	void Init();



	void ServerBind();
	void ServerListen();
	void ServerAccept();
	void ServerRead(WPARAM wParam);
//	void ServerUserExit(WPARAM wParam);
private:
	HDC hdc;
	HWND hWnd;
private:
	WSADATA wsaData;
	SOCKET server;
	//std::vector<SOCKET> clientList;
	SOCKADDR_IN addr = { 0 }, c_addr;
	char msg[1024];
	int count;
	TCHAR str[1024];
	char buffer[1024];
	int size;

	vector<SOCKET> LobbyClient;
	vector<SOCKET> RoomClient;


};


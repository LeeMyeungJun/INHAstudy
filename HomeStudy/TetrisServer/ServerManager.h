#pragma once
class ServerManager
{
public:
	ServerManager();
	~ServerManager();
	void Init();

	void ServerBind();
	void ServerListen(HWND hWnd);
	void ServerAccept(HWND hWnd);
	void ServerRead(WPARAM wParam);
	void ServerUserExit(WPARAM wParam);
private:
	HDC hdc;
private:
	WSADATA wsaData;
	SOCKET server;
	std::vector<SOCKET> clientList;
	SOCKADDR_IN addr = { 0 }, c_addr;
	char msg[1024];
	int count;
	TCHAR str[1024];
	char buffer[1024];
	int size, msgLen;


public:
	static ServerManager* GetInstance()
	{
		static ServerManager instance;
		return &instance;
	}

};


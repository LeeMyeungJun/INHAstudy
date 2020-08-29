#pragma once
class NetWorkManager
{
private:
	HWND hWnd;
	UINT message;
public:
	NetWorkManager();
	~NetWorkManager();

	WSADATA wsaData;
	SOCKET server;
	SOCKADDR_IN addr = { 0 };
	int msgLen = 0;
	TCHAR str[100] = { 0 };
	char buffer[100];
	int count = 0;
	bool BWturn;
	std::vector<TCHAR *> chatLog;



	void Read_Fd();
	void Init();
	void setHwnd(HWND hWnd)
	{
		this->hWnd = hWnd;
	}
	HWND getHwnd() { return hWnd; }


	void setMessage(UINT hWnd)
	{
		this->message = hWnd;
	}
	UINT getMessage() { return message; }




	static NetWorkManager* GetInstance()
	{
		static NetWorkManager instance;
		return &instance;
	}
};


#pragma once
#include <vector>

#include "GameScene.h"
using namespace std;
typedef struct __pkRoom;
#define WIDTH 16
#define HEIGHT 26
class NetWorkManager
{
private:
	struct RoomUser
	{
		int userID;
		int Screen_Position;
		int	UserGameBoard[HEIGHT][WIDTH];
		bool bDead;
	};
	
private:
	HWND hWnd;
	UINT message;
public:
	NetWorkManager();
	~NetWorkManager();

public:
	WSADATA wsaData;
	static SOCKET server;

	TCHAR str[256] = { 0 };
	TCHAR str2[256] = { 0 };

	RoomUser userCheck[2];
	bool bPlay;
	int count;
	int count2;
	int UserCount;
	SOCKADDR_IN addr = { 0 };
	int msgLen;
	vector<wchar_t *> chatLog;
	vector<SOCKET> userList;
	vector<__pkRoom*> LobbyRoom;
	
	
	
public:
	void Init();
	void Connect();
	void Read_Fd();
	void Send_message();


	void setHwnd(HWND hWnd)
	{
		this->hWnd = hWnd;
	}
	HWND getHwnd() { return hWnd; }

	void setMessage(UINT message)
	{
		this->message = message;
	}
	UINT getMessage() { return message; }

	size_t getChatLogSize() {
		return chatLog.size(); 
	}


	static NetWorkManager* GetInstance()
	{
		static NetWorkManager instance;
		return &instance;
	}
};


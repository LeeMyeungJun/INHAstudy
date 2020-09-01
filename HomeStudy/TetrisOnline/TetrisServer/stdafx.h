// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <vector>
#include <list>
#include <map>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

#define WM_ASYNC WM_USER + 2

//class
#include "TetrisServer.h"
#include "ServerManager.h"
// TODO: reference additional headers your program requires here


const int iWidth = 16;
const int iHeight = 26;


//vector<list>   0: Lobby 1:Room 2:Game
enum RoomRequestId
{
	CreateRoom = 0, //���� ��û
	JoinRoom, //���� ��û
	StartSession // ���� ��û

};

#define LOBBY_MESSAGE 100
#define LOBBYRQ 99
#define ROOM 200
#define GAME 300


typedef struct __pkHeader {
	unsigned int Protocal;
	unsigned int size;
} pkHeader;

//100
typedef struct __pkLobby {
	unsigned int User_Position;
	char Buffer[64];
} pkLobby;
//99
typedef struct __pkLobby_RQ {
	char RooName[40];
	unsigned int RoomNum;
} pkLobby_RQ;

//200
typedef struct __pkRoom {
	unsigned int User_Position;
	char Buffer[64];
	bool User_Ready;
} pkRoom;

//300
typedef struct __pkGame {
	unsigned int User_Position;
	int User_GameBoard[iHeight][iWidth];
	bool User_Survive;
} pkGame;


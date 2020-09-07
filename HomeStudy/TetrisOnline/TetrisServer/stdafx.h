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
#include <iostream>
#pragma comment(lib, "ws2_32.lib")

#define WM_ASYNC WM_USER + 2

//class
#include "TetrisServer.h"
#include "ServerManager.h"
// TODO: reference additional headers your program requires here

const int iWidth = 16;
const int iHeight = 26;

enum RoomRequestId
{
	CreateRoom = 0, //생성 요청
	JoinRoom, //참가 요청
	StartSession // 시작 요청

};

#define USERLIST 88
#define LOBBYRQ 99
#define LOBBY_MESSAGE 100
#define ROOM 200
#define GAME 300


typedef struct __Packet {
	unsigned int Protocal;
	unsigned int size;
	char* Buffer;
} Packet;


typedef struct __pkUser {
	char* UserID;
} pkUser;

typedef struct __pkLobby_Message {
	char Buffer[64];
} pkLobbyMessage;

typedef struct __pkLobby_RQ {
	unsigned int RoomNum;
	char RoomName[40];
} pkLobby_RQ;



typedef struct __pkRoom {
	unsigned int RoomNum;
	char RoomName[40];
	unsigned int UserCount;
	bool User_Ready;
	bool PlayGame;
} pkRoom;


typedef struct __pkGame {
	unsigned int User_Position;
	int User_GameBoard[iHeight][iWidth];
	bool User_Survive;
} pkGame;

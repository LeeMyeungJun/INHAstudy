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

#include <crtdbg.h>

#define WM_ASYNC WM_USER + 2

//class
#include "RoomManager.h"
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
#define ROOM 70
#define ROOMRQ 74
#define ROOMCREATE 71
#define GAME 68
#define GAMETRUE 12
#define GAMEFALSE 11


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
	int User_Ready;
	int Exit;
	char RoomName[40];
} pkRoom;

typedef struct __pkRoom_RQ {
	unsigned int RoomNum;
} pkRoom_RQ;

typedef struct __pkRoom_User {
	unsigned int UserCount;
} pkRoom_User;

typedef struct __pkGame {
	unsigned int RoomNum;
	int UserIndex;
	BITMAP Bitmap;
} pkGame;

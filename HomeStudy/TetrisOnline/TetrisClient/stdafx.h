// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"



#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

#include "resource.h"

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <WinSock2.h>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <math.h>
#include <string.h>
#include <tchar.h>
#include <wchar.h>

#pragma comment(lib, "ws2_32.lib")


//class
#include "UI.h"
#include "SoundManager.h"
#include "NetWorkManager.h"
#include "GameCenter.h"
#include "Scene.h"
#include "RoomScene.h"
#include "LoginScene.h"
#include "LobbyScene.h"
#include "GameScene.h"

#pragma comment(lib,"msimg32.lib")

using namespace std;
const int MOVE_DELAY = 100;
const float BtnZoom = 1.3;
#define WM_ASYNC WM_USER + 2

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
#define ROOMCREATE 71
#define ROOMRQ 74
#define GAME 68
#define GAMETRUE 12
#define GAMEFALSE 11
#define GAMELOSE 43

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
	int UserGameBoard[iHeight][iWidth];
} pkGame;

typedef struct __pkGameLose {
	unsigned int RoomNum;
	int UserIndex;
} pkGameLose;

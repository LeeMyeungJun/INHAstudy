// stdafx.cpp : source file that includes just the standard includes
// TetrisPrj.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file


NetWorkManager *g_NetworkManager;
SoundManager* g_theSoundManager;

int protocol = 0;



const int iWidth  = 16;
const int iHeight = 26;
typedef struct __pkHeader { 
	unsigned int Protocal;
} pkHeader; 

typedef struct __pkLobby {  
	unsigned int User_Position;
	char Buffer[64];
} pkLobby;

typedef struct __pkLobby_RQ {
	char RooName[40];
	unsigned int RoomNum;
} pkLobby_RQ;


typedef struct __pkRoom {
	unsigned int User_Position;
	char Buffer[64];
	bool User_Ready;
} pkRoom;


typedef struct __pkGame {
	unsigned int User_Position;
	int User_GameBoard[iHeight][iWidth];
	bool User_Survive;
} pkGame;



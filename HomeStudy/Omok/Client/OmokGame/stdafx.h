// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <WinSock2.h>
#include <string>


#pragma comment(lib, "ws2_32.lib")


//main
#include "OmokGame.h"

//class
#include "GameCenter.h"
#include "Scene.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "Bitmap.h"
#include "GameScene.h"
#include "ServerManager.h"

#define MAX_LOADSTRING 100
#define WM_ASYNC WM_USER + 2

#define OMOKLINE 19
#define BLOCKSIZE 40
#define SUBWIDTH 30

#define STONE_SIZE 15

// TODO: reference additional headers your program requires here

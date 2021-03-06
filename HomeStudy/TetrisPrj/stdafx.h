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
#include <math.h>

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


const int MOVE_DELAY = 100;


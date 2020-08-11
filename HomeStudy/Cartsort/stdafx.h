// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

//Main
#include "Cartsort.h"

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

//Class
#include "GameCenter.h"

#include "Scene.h"
#include "UI.h"
#include "Bitmap.h"
#include "LobbyScene.h"
#include "GameScene.h"
#include "EndScene.h"

//Enemy
#include "Enemy.h"
#include "CarEnemy.h"
#include "ChildEnemy.h"
#include "AdultEnemy.h"
#include "OldmanEnemy.h"

//DataManager
#include "DataManager.h"

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 800


enum class SceneState : int
{
	Enum_Lobby,
	Enum_Game,
	Enum_End,
	Enum_Quit

};
// TODO: reference additional headers your program requires here

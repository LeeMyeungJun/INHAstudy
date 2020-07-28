// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#pragma comment(lib,"msimg32.lib") 

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



//main
#include "galspans.h"

//Manager
#include "GameManager.h"
#include "BitMap.h"
//Font
#include "FontManager.h"

//UI
#include "UI.h"
#include "EndUI.h"
#include "GameUI.h"
#include "MenuUI.h"

//Scene
#include "Scene.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "EndScene.h"


//Object
#include "Object.h"




#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 800



// TODO: reference additional headers your program requires here

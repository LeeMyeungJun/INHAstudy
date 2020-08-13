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

//main
#include "OmokGame.h"

//class
#include "GameCenter.h"
#include "Scene.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "Bitmap.h"

//trans¹¹½Ã±â
#pragma comment(lib,"msimg32.lib") 

#define OMOKLINE 19
#define BLOCKSIZE 40
#define SUBWIDTH 30

#define STONE_SIZE 10

// TODO: reference additional headers your program requires here

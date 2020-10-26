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
#include <string>
#include <vector>

using namespace std;


enum enum_state
{
	NONE,WALL,CLOSED,OPEN,START,END
};

struct ST_FGH
{
	int st_iF;
	int st_iG;
	int st_iH;

	ST_FGH() :st_iF(0), st_iG(0), st_iH(0) {}

};

struct ST_BOARD_STATE
{
	enum_state st;
	ST_FGH fgh;
	POINT parent;
	ST_BOARD_STATE() :st(NONE), parent({0,0}) { fgh.st_iF = 0; fgh.st_iG = 0; fgh.st_iH = 0; }

};

struct ST_BOARD_MANAGER
{
	//마우스상태
	POINT					st_ptStart, st_ptEnd;
	enum_state				st_enMouseState;
	bool					st_bStart, st_bEnd;
	ST_BOARD_MANAGER()
		:st_ptStart({ 0,0 }), st_ptEnd({0,0}),st_enMouseState(START),st_bStart(false),st_bEnd(false) {}
	
};

//class
#include "Astar.h"
#define BOARDMAX 40
#define BOARDMIN 4
// TODO: reference additional headers your program requires here

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

#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

#define WM_ASYNC WM_USER + 2

//class
#include "TetrisServer.h"
#include "ServerManager.h"
// TODO: reference additional headers your program requires here

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
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <list>
#include <assert.h> //경고에 관련된 헤더파일 예외처리해주려고 넣음.
#include <complex.h>

using namespace std;

// TODO: reference additional headers your program requires here
#include <d3dx9.h>
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

extern HWND g_hWnd;

#define SafeRelease(p) {if(p) p->Release() ; p = NULL;} //애는 컴과 연결을 끊는거다 .

#define SafeDelete(p){if(p) delete p; p = NULL;} //애는 메모리를 그냥 지혼자삭제하는거고
//com객체를쓰면그 new가 메모리 장치를 생성하는게아니라 그친구를 가져다가 쓸거야 .
//>> :싱글톤 매크로
#define Singletone(class_name) \
private: \
	class_name(void);\
	~class_name(void);\
public:\
	static class_name* GetInstance() \
	{ \
		static class_name instance;\
		return &instance;\
	}
//<< :

struct ST_PC_VERTEX //point & color의미
{
	D3DXVECTOR3		p; //xyz값을 가질수잇슴
	D3DCOLOR		c; //r, g ,b , a값을 가지고있음
	enum { FVF = D3DFVF_XYZ |D3DFVF_DIFFUSE };
};

#include "cDeviceManager.h"
#include "Player.h"


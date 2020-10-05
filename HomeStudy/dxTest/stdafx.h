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

using namespace std;
extern HWND g_hWnd;

// TODO: reference additional headers your program requires here
#include <d3dx9.h>
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")	


//매크로 


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


//>> : 컴과 연결끊기 
#define SafeRelease(p) {if(p) p->Release() ; p = NULL;}
// << :

//>> : delete 매크로 
#define SafeDelete(p) {if(p) delete p; p= NULL;}
//<< : 


//>> : GETSET

#define Synthesize(varType , varName, funName) \
	protected: varType varName; \
	public: inline varType Get##funName(void) const{ return varName;}\
	public: inline void Set##funName(varType var) {varName = var;}

#define Synthesize_pass_by_Ref(varType , varName, funName) \
	protected: varType varName; \
	public: inline varType& Get##funName(void) const{ return varName;}\
	public: inline void Set##funName(varType& var) {varName = var;}

//<< :
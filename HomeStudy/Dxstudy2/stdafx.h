// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")


#endif #define WIN32_LEAN_AND_MEAN
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


#include "iMap.h"
#include "cDeviceManager.h"
#include "cObject.h"
#include "cObjectManager.h"
#include "cTextureManager.h"


struct ST_PC_VERTEX //point & color의미
{
	D3DXVECTOR3		p; //xyz값을 가질수잇슴
	D3DCOLOR		c; //r, g ,b , a값을 가지고있음
	enum { FVF = D3DFVF_XYZ |D3DFVF_DIFFUSE };
};

struct ST_PNT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	D3DXVECTOR2 t;
	enum{FVF = D3DFVF_XYZ |D3DFVF_NORMAL | D3DFVF_TEX1};
};


struct ST_PT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR2 t;
	enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 };
};

struct ST_PN_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL};
};
//>>:AnimationStruct
struct ST_POS_SAMPLE
{
	int			n;
	D3DXVECTOR3	v;
	ST_POS_SAMPLE()//구조체에도  초기화작업을 해줄수있다.
		: n(0)
		, v(0,0,0)
	{}
};

struct ST_ROT_SAMPLE
{
	int				n;
	D3DXQUATERNION	q;
	ST_ROT_SAMPLE()//구조체에도  초기화작업을 해줄수있다.
		: n(0)
	{
		D3DXQuaternionIdentity(&q); //x y z값은 0 w는 1로 
	}
};

//>>: MousePicking

struct Ray
{
	D3DXVECTOR3 _origin;
	D3DXVECTOR3 _direction;
};

struct BoundingSphere
{
	D3DXVECTOR3 center;
	float radius;
	bool bLight;
	BoundingSphere():bLight (false) , radius(0), center(D3DXVECTOR3(0,0,0))
	{};
};


struct ST_Rect
{
	
};
//<<:

#define SafeAddRef(p) {if(p) p->AddRef();}

#define Synthesize(varType , varName, funName) \
	protected: varType varName; \
	public: inline varType Get##funName(void) const{ return varName;}\
	public: inline void Set##funName(varType var) {varName = var;}

#define Synthesize_Pass_by_Ref(varType, varName, funName) \
   protected:varType varName; \
   public : inline varType& Get##funName(void) {return varName;} \
   public : inline void Set##funName(varType& var){varName = var;}

#define Synthesize_Add_Ref(varType, varName, funName) \
	protected : varType varName; \
	public: virtual varType Get##funName(void)const{return varName;}\
	public: virtual void Set##funName(varType var ){ \
	if(varName != var)\
	{\
	 SafeAddRef(var); \
	 SafeRelease(varName);\
	 varName = var;\
	}\
}


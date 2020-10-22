#pragma once

#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif #define WIN32_LEAN_AND_MEAN

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN
#define CELL 256
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// TODO: reference additional headers your program requires here
#include <d3dx9.h>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <list>
#include <assert.h>
#include <time.h>
#include <iostream>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")


using namespace std;
extern HWND g_hWnd;


#define SafeRelease(p)      { if(p) p->Release();   p = NULL; }
#define SafeDelete(p) { if(p) delete p; p = NULL; }
#define SafeDeleteArray(p) {if(p) delete[] p ; p=NULL;}
#define  Singleton(class_name) \
   private : \
      class_name(void); \
      ~class_name(void); \
   public : \
      static class_name* GetInstance() \
      { \
         static class_name instance; \
         return &instance; \
      }

struct ST_PC_VERTEX   //포인트, 컬러
{
	D3DXVECTOR3 p;
	D3DCOLOR   c;
	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };
};

struct ST_PT_VERTEX
{
	D3DXVECTOR3   p;
	D3DXVECTOR2 t;
	enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 };
};

struct ST_PNT_VERTEX
{
	D3DXVECTOR3   p;
	D3DXVECTOR3 n;
	D3DXVECTOR2 t;
	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 };
};

struct ST_PN_VERTEX
{
	D3DXVECTOR3   p;
	D3DXVECTOR3 n;
	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL };
};

struct ST_POS_SAMPLE
{
	int         n;
	D3DXVECTOR3 v;
	ST_POS_SAMPLE() : n(0), v(0, 0, 0)
	{}
};

struct ST_ROT_SAMPLE
{
	int            n;
	D3DXQUATERNION   q;
	ST_ROT_SAMPLE() : n(0)
	{
		D3DXQuaternionIdentity(&q);
	}
};

struct ST_Ray
{
	D3DXVECTOR3 _origin;
	D3DXVECTOR3 _direction;
};

struct ST_SPHERE
{
	float      fRadius;
	D3DXVECTOR3 vCenter;
	bool      isPicked;

	ST_SPHERE() : vCenter(0, 0, 0), fRadius(0.0f), isPicked(false) {}
};

struct ST_Tile
{
	vector<ST_PC_VERTEX> vecVertex;
	bool   isPicked;

	ST_Tile() : isPicked(false) {}
};

#define Synthesize(varType, varName, funName) \
   protected:   varType varName; \
   public:   inline varType Get##funName(void) const {return varName;} \
   public:   inline void Set##funName(varType var) {varName = var;}

#define Synthesize_Pass_by_Ref(varType, varName, funName) \
   protected:   varType varName; \
   public:   \
   inline varType& Get##funName(void) {return varName;} \
   public:   \
   inline void Set##funName(varType& var) {varName = var;}

enum MY_TOKEN_TYPE { TOKEN_STRING = 0, TOKEN_NUMBER };

#define SafeAddRef(p)   { if(p) p->AddRef(); }

#define Synthesize_Add_Ref(varType, varName, funName) \
   protected : varType varName; \
   public : virtual varType Get##funName(void) const {return varName; } \
   public : virtual void Set##funName(varType var) { \
   if(varName != var) \
   { \
      SafeAddRef(var); \
      SafeRelease(varName); \
      varName = var; \
   } \
   }

#include "cMainGame.h"
#include "cDeviceManager.h"
#include "cTextureManager.h"
#include "cTimerManager.h"
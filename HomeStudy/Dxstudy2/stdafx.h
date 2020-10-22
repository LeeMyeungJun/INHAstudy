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
#include <assert.h> //��� ���õ� ������� ����ó�����ַ��� ����.
#include <complex.h>

using namespace std;

// TODO: reference additional headers your program requires here
#include <d3dx9.h>
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

extern HWND g_hWnd;

#define SafeRelease(p) {if(p) p->Release() ; p = NULL;} //�ִ� �İ� ������ ���°Ŵ� .

#define SafeDelete(p){if(p) delete p; p = NULL;} //�ִ� �޸𸮸� �׳� ��ȥ�ڻ����ϴ°Ű�
//com��ü������� new�� �޸� ��ġ�� �����ϴ°Ծƴ϶� ��ģ���� �����ٰ� ���ž� .
//>> :�̱��� ��ũ��
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

struct ST_PC_VERTEX //point & color�ǹ�
{
	D3DXVECTOR3		p; //xyz���� �������ս�
	D3DCOLOR		c; //r, g ,b , a���� ����������
	enum { FVF = D3DFVF_XYZ |D3DFVF_DIFFUSE };
};

#include "cDeviceManager.h"
#include "Player.h"


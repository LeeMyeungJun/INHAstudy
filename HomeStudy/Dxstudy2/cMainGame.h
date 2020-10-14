#pragma once
#include "stdafx.h"
class cFrame;
class cCubeMan;
class cCubePC;
class cCamera;
class cGrid;
class cLight;
class cGroup;

class cMainGame
{
public:
	cMainGame();
	~cMainGame();

private:
	vector<ST_PC_VERTEX> m_vecLineVertex;
	vector<ST_PC_VERTEX> m_vecTriangleVertex;

	//À§¿¡²«¾È¾¸

	cCubePC*		m_pCubePC;
	cCamera*		m_pCamera;
	cGrid*			m_pGrid;
	cCubeMan*		m_pCubeMan;
	cLight*			m_pLight;
	iMap*			m_pMap;
	

	//:>>AseLoader
	cFrame*			m_pRootFrame;
	//<:

	//::texture
	LPDIRECT3DTEXTURE9		m_pTexture;
	vector<ST_PT_VERTEX>	m_vecVertex;
	//<<:

	//>>:
	vector<cGroup*>			m_vecGroup;

	
public:
	void Setup();
	void Update();
	void Render();
	void wndProc(HWND hWnd,UINT message,WPARAM wParam, LPARAM lParam);

	void Setup_Line();
	void Draw_Line();


	void Setup_Triangle();
	void Draw_Triangle();

	void Set_Light();
	void Draw_Texture();

	void Setup_Obj();
	void Obj_Render();

	void Load_Surface();

};


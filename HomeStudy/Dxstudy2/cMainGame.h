#pragma once
#include "stdafx.h"
class iMap;
class Player;
class cCubePC;
class cCamera;
class cGrid;
class xFileLoader;
class cSkinnedMesh;
class Frustum;
class cZeloat;

class cMainGame
{
public:
	cMainGame();
	~cMainGame();

private:
	vector<ST_PC_VERTEX> m_vecLineVertex;
	vector<ST_PC_VERTEX> m_vecTriangleVertex;

	//À§¿¡²«¾È¾¸
	Player*			m_pPlayer;
	//cCubePC*		m_pCubePC;
	cCamera*		m_pCamera;
	cGrid*			m_pGrid;
	xFileLoader*	m_pXFile;
	cSkinnedMesh*	m_pSkinnedMesh;




	//>>:
	LPD3DXMESH			m_pSphere;
	D3DMATERIAL9		m_stCullingMtl;
	vector<ST_SPHERE*>	m_vecCullingSphere;
	Frustum*			m_pFrustum;
	//<<:
public:
	void Setup();
	void Update();
	void Render();
	void wndProc(HWND hWnd,UINT message,WPARAM wParam, LPARAM lParam);

	void Setup_Line();
	void Draw_Line();


	void Setup_Triangle();
	void Draw_Triangle();

	void setLight();

	//
	void SkinnedMesh_Render();

	//>>:
	void Setup_Frustum();
	void Frustum_Render();
	//<<:


	// >>:
private:
	cZeloat* m_pHoldZealot;
	cZeloat* m_pMoveZealot;
	iMap*	 m_pMap;
public:
	void Setup_OBB();
	void OBB_Render();
	
	//<<:

};


#pragma once
#include "stdafx.h"
class Player;
class cCubePC;
class cCamera;
class cGrid;
class xFileLoader;
class cSkinnedMesh;

class cMainGame
{
public:
	cMainGame();
	~cMainGame();

private:
	vector<ST_PC_VERTEX> m_vecLineVertex;
	vector<ST_PC_VERTEX> m_vecTriangleVertex;

	//�������Ⱦ�
	Player*			m_pPlayer;
	//cCubePC*		m_pCubePC;
	cCamera*		m_pCamera;
	cGrid*			m_pGrid;
	xFileLoader*	m_pXFile;
	cSkinnedMesh*	m_pSkinnedMesh;

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

};


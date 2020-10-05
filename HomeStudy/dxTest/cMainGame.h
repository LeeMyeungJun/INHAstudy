#pragma once
#include "stdafx.h"
class cCubeMan;
class cCamera;
class cGrid;

class cMainGame
{
private:
	cCamera*		m_pCamera;
	cGrid*			m_pGrid;
	cCubeMan*		m_pCubeMan;

public:
	cMainGame();
	~cMainGame();

public:
	void Setup();
	void Update();
	void Render();
	void wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void Setup_Line();
	void Draw_Line();
};


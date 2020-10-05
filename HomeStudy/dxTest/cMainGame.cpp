#include "stdafx.h"
#include "cMainGame.h"
#include "cDeviceManager.h"
#include "cCamera.h"
#include "cGrid.h"
#include "cCubeMan.h"

cMainGame::cMainGame()
	: m_pCamera(NULL)
	, m_pGrid(NULL)
	, m_pCubeMan(NULL)
{
}


cMainGame::~cMainGame()
{
	SafeDelete(m_pCamera);
	SafeDelete(m_pGrid);
	SafeDelete(m_pCubeMan);
	g_pDeveceManager->Destroy();
}

void cMainGame::Setup()
{
	m_pCubeMan = new cCubeMan;
	m_pCamera = new cCamera;
	m_pGrid = new cGrid;



}

void cMainGame::Update()
{
}

void cMainGame::Render()
{
}

void cMainGame::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}

void cMainGame::Setup_Line()
{
}

void cMainGame::Draw_Line()
{
}

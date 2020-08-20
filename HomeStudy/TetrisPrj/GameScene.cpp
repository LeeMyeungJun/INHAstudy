#include "stdafx.h"



GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Init(void)
{
}

void GameScene::Update(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_LBUTTONDOWN)
	{
		int Clickx = LOWORD(lParam);
		int Clicky = HIWORD(lParam);

	}
}

void GameScene::Render(HWND hWnd, HDC hdc)
{
}

void GameScene::Free(void)
{
}

void GameScene::UI(HDC hdc)
{
}

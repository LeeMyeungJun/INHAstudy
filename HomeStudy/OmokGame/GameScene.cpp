#include "stdafx.h"
#include "GameScene.h"


GameScene::GameScene()
{
	for (int i = 0; i <= OMOKLINE; i++)
	{
		for(int j = 0 ; j <= OMOKLINE; j++)
			boardPoint.push_back({ SUBWIDTH +j*BLOCKSIZE ,SUBWIDTH + i*BLOCKSIZE });
	}
}


GameScene::~GameScene()
{
}

void GameScene::Init(void)
{
}

void GameScene::Update(UINT message, WPARAM wParam, LPARAM lParam)
{
	Clickx = LOWORD(lParam);
	Clicky = HIWORD(lParam);

	_ltow(Clickx, tcharx, 10);
	_ltow(Clicky, tchary, 10);

	if (message == WM_LBUTTONDOWN)
	{

	}

}

void GameScene::Render(HWND hWnd, HDC hdc)
{
	UI(hdc);

	TextOut(hdc, 700, 30, tcharx, lstrlen(tcharx));
	TextOut(hdc, 700, 50, tchary, lstrlen(tchary));
}

void GameScene::Free(void)
{
}

void GameScene::UI(HDC hdc)
{
	HBRUSH myBrush, oldBrush;
	myBrush = (HBRUSH)CreateSolidBrush(RGB(250, 203, 125));
	oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

	Rectangle(hdc, SUBWIDTH, SUBWIDTH, BLOCKSIZE*OMOKLINE + SUBWIDTH, SUBWIDTH + BLOCKSIZE*OMOKLINE);

	SelectObject(hdc, oldBrush);
	DeleteObject(myBrush);

	for (int i = 0; i <= OMOKLINE; i++)
	{
		MoveToEx(hdc, 0 + SUBWIDTH, BLOCKSIZE * i + SUBWIDTH, NULL);
		LineTo(hdc, BLOCKSIZE * OMOKLINE + SUBWIDTH, BLOCKSIZE * i + SUBWIDTH);

		MoveToEx(hdc, BLOCKSIZE * i + SUBWIDTH, 0 + SUBWIDTH, NULL);
		LineTo(hdc, BLOCKSIZE * i + SUBWIDTH, SUBWIDTH + BLOCKSIZE*OMOKLINE);
	}
	
	POINT pt = {0,0};
	BlackStone(hdc,pt);

}

void GameScene::BlackStone(HDC hdc,POINT pt)
{
	Ellipse(hdc, 30 - STONE_SIZE, 30 - STONE_SIZE, 30 + STONE_SIZE, 30 + STONE_SIZE);

}

void GameScene::WhiteStone(HDC hdc, POINT pt)
{
}

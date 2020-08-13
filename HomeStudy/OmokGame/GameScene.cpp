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
		POINT pt = { Clickx,Clicky };
		for (int i = 0; i <= OMOKLINE; i++)
		{
			for (int j = 0; j <= OMOKLINE; j++)
			{
				if (Distance(pt, boardPoint[i + j]) < 5)
				{
					BlackStone(hdc, boardPoint[i + j]);
				}

			}

		}

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
	Ellipse(hdc, pt.x - STONE_SIZE, pt.y - STONE_SIZE, pt.x + STONE_SIZE, pt.y + STONE_SIZE);

}

void GameScene::WhiteStone(HDC hdc, POINT pt)
{
}

int Distance(const POINT& p1, const POINT& p2) {

	double distance;

	// 피타고라스의 정리
	// pow(x,2) x의 2승,  sqrt() 제곱근
	distance = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));

	return distance;
}
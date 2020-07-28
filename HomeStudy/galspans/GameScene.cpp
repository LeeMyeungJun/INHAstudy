#include "stdafx.h"



GameScene::GameScene()
{
	m_Bitmap = new BitMap;
//	player = new Player;
	m_SceneUI = m_GameUI;
	hOldBitmap = NULL;
	hNewBitmap = NULL;
	

	
}


GameScene::~GameScene()
{
	delete m_Bitmap;
//	delete player;
}

void GameScene::Init(void)
{
	
	vecPolygon.clear();
	vecPolygon.push_back({ 100,100 });
	vecPolygon.push_back({ 200,100 });
	vecPolygon.push_back({ 200,200 });
	vecPolygon.push_back({ 100,200 });
//	player->PlayerPotion = { 100,100 };
	bLand[SCREEN_WIDTH][SCREEN_HEIGHT] = { false };
}

void GameScene::Update(UINT message, WPARAM wParam, LPARAM lParam)
{
}

void GameScene::Render(HWND hWnd, HDC hdc)
{
	m_Bitmap->DrawBitmapDoubleBuffering(hWnd, hdc);
	{
		HDC tempDC;
		HBRUSH myBrush, oldBrush;

		tempDC = CreateCompatibleDC(hdc);

		if (hNewBitmap == NULL)
			hNewBitmap = CreateCompatibleBitmap(hdc, SCREEN_WIDTH, SCREEN_HEIGHT); //초기화를해준다 처음들어가면 사이즈만큼

		hOldBitmap = (HBITMAP)SelectObject(tempDC, hNewBitmap);

		myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 255, 0));
		oldBrush = (HBRUSH)SelectObject(tempDC, myBrush);

		Rectangle(tempDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

		SelectObject(tempDC, oldBrush);
		DeleteObject(myBrush);


		myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 50, 255));
		oldBrush = (HBRUSH)SelectObject(tempDC, myBrush);

		/*구멍뚫을부분 */
		Polygon(tempDC, &vecPolygon[0], vecPolygon.size());
		/*여기까지 */
		SelectObject(tempDC, oldBrush);
		DeleteObject(myBrush);

		TransparentBlt(hdc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, tempDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, RGB(255, 50, 255));

		DeleteDC(tempDC);
	}
	
	

/*
	HBRUSH hBrushCircle = CreateSolidBrush(RGB(255, 0, 255));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hMemDC, hBrushCircle);
	Ellipse(hMemDC, 400, 200, 450, 250);
	SelectObject(hMemDC2, oldBrush);
	DeleteObject(hBrushCircle);

	TransparentBlt(hdc, 200, 100, bx, by, hMemDC2, 0, 0, bx, by, RGB(255, 0, 255));*/
	
}

void GameScene::Free(void)
{
}

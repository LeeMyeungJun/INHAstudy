#include "stdafx.h"



GameScene::GameScene()
{
	m_Bitmap = new BitMap;
	m_Player = new PlayerManager;

	m_SceneUI = m_GameUI;

	hOldBitmap = NULL;
	hNewBitmap = NULL;	
}


GameScene::~GameScene()
{
	delete m_Bitmap;
	delete m_Player;
}

void GameScene::Init(void)
{
	
	vecPolygon.clear();
	vecPolygon.push_back({ 100,100 });
	vecPolygon.push_back({ 200,100 });
	vecPolygon.push_back({ 200,200 });
	vecPolygon.push_back({ 100,200 });

	
	for (int i = 100; i <= 200; i++)
	{
		for (int j = 100; j <= 200; j++)
		{
			bLand[i][j] = false;
		}
	}

	m_Player->ptPosition.x = 100;
	m_Player->ptPosition.y = 100;


}

void GameScene::Update(UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
		case WM_KEYDOWN:
		{
			if (GetKeyState(VK_RIGHT) & 0x8000)
			{
				m_Player->ptPosition.x += 1;
				if (GetKeyState(VK_UP) & 0x8000)
				{
					m_Player->ptPosition.y -= 1;
				}
				else if (GetKeyState(VK_DOWN) & 0x8000)
				{
					m_Player->ptPosition.y += 1;
				}
			}
			else if (GetKeyState(VK_LEFT) & 0x8000)
			{
				m_Player->ptPosition.x -= 1;
				if (GetKeyState(VK_UP) & 0x8000)
				{
					m_Player->ptPosition.y -= 1;
				}
				else if (GetKeyState(VK_DOWN) & 0x8000)
				{
					m_Player->ptPosition.y += 1;
				}
			}
			else if (GetKeyState(VK_UP) & 0x8000)
			{
				m_Player->ptPosition.y -= 1;
			}
			else if (GetKeyState(VK_DOWN) & 0x8000)
			{
				m_Player->ptPosition.y += 1;
			}
		}
		break;
	}





}

void GameScene::Render(HWND hWnd, HDC hdc)
{

	HDC tempDC;
	HBRUSH myBrush, oldBrush;


	/*�����κ�*/
	m_Bitmap->DrawBitmapDoubleBuffering(hWnd, hdc);


	/*���۶ձ�κ�*/
	{
		

		tempDC = CreateCompatibleDC(hdc);

		if (hNewBitmap == NULL)
			hNewBitmap = CreateCompatibleBitmap(hdc, SCREEN_WIDTH, SCREEN_HEIGHT); //�ʱ�ȭ�����ش� ó������ �����ŭ

		hOldBitmap = (HBITMAP)SelectObject(tempDC, hNewBitmap);

		myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 255, 0));
		oldBrush = (HBRUSH)SelectObject(tempDC, myBrush);

		Rectangle(tempDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

		SelectObject(tempDC, oldBrush);
		DeleteObject(myBrush);


		myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 50, 255));
		oldBrush = (HBRUSH)SelectObject(tempDC, myBrush);

		/*���۶����κ� */
		Polygon(tempDC, &vecPolygon[0], vecPolygon.size());
		/*������� */
		SelectObject(tempDC, oldBrush);
		DeleteObject(myBrush);

		TransparentBlt(hdc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, tempDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, RGB(255, 50, 255));

		DeleteDC(tempDC);
	}
	
	/*�÷��̾� �κ� */
	myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
	oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

	m_Player->DrawPlayerCharacter(hdc);

	SelectObject(hdc, oldBrush);
	DeleteObject(myBrush);

}

void GameScene::Free(void)
{
}

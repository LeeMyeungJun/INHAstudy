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
	vecTemp.clear();
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
	PlayerMove(message);
	
}

void GameScene::Render(HWND hWnd, HDC hdc)
{

	HDC tempDC;
	HBRUSH myBrush, oldBrush;


	/*사진부분*/
	m_Bitmap->DrawBitmapDoubleBuffering(hWnd, hdc);


	/*구멍뚫기부분*/
	{
		

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
	
	/*플레이어 부분 */
	myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
	oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

	m_Player->DrawPlayerCharacter(hdc);

	SelectObject(hdc, oldBrush);
	DeleteObject(myBrush);

}

void GameScene::Free(void)
{
}

void GameScene::PlayerMove(UINT message)
{
	switch (message)
	{
	case WM_KEYDOWN:
	{
		if (GetKeyState(VK_RIGHT) & 0x8000)
		{
			if (PlayerInsideCheck(m_Player->ptPosition.x + 1, m_Player->ptPosition.y))
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

bool GameScene::PlayerInsideCheck(int x, int y)
{
	int crosses = 0;
	for (int i = 0; i < vecTemp.size(); i++) {
		int j = (i + 1) % vecTemp.size();
		//점 B가 선분 (p[i], p[j])의 y좌표 사이에 있음
		if ((vecTemp[i].y > y) != (vecTemp[j].y > y)) {
			//atX는 점 B를 지나는 수평선과 선분 (p[i], p[j])의 교점
			double atX = (vecTemp[j].x - vecTemp[i].x)*(y - vecTemp[i].y) / (vecTemp[j].y - vecTemp[i].y) + vecTemp[i].x;
			//atX가 오른쪽 반직선과의 교점이 맞으면 교점의 개수를 증가시킨다.
			if (x < atX)
				crosses++;
		}
	} //true면 안에있다는뜻
	return crosses % 2 > 0;
}

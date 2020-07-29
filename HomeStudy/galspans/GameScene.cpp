#include "stdafx.h"


const int PlayerSpeed = 1;
extern GameManager * g_GameManager;
GameScene::GameScene()
{
	m_GameUI = new GameUI;
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
	delete m_GameUI;
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
	g_GameManager->SceneChange(Scene_enum::SCENE_END);
	
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
		if (vecTemp.size() > 2)
		{
			Polygon(tempDC, &vecTemp[0], vecTemp.size());
		}
		
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

void GameScene::PlayerMove(UINT message)
{
	switch (message)
	{
	case WM_KEYDOWN:
	{
		if (GetKeyState(VK_RIGHT) & 0x8000)
		{
			if (PlayerInsideCheck())
			{
				m_Player->ptPosition.x -= PlayerSpeed;
			}
			else
			{
				m_Player->ptPosition.x += PlayerSpeed;
			}
		}
		else if (GetKeyState(VK_LEFT) & 0x8000)
		{
			if (PlayerInsideCheck())
			{
				m_Player->ptPosition.x += PlayerSpeed;
			}
			else
			{
				m_Player->ptPosition.x -= PlayerSpeed;
			}		
		}
		else if (GetKeyState(VK_UP) & 0x8000)
		{
			if (PlayerInsideCheck())
			{
				m_Player->ptPosition.y += PlayerSpeed;
			}
			else
			{
				m_Player->ptPosition.y -= PlayerSpeed;
			}	
		}
		else if (GetKeyState(VK_DOWN) & 0x8000)
		{
			if (PlayerInsideCheck())
			{
				m_Player->ptPosition.y -= PlayerSpeed;
			}
			else
			{
				m_Player->ptPosition.y += PlayerSpeed;
			}
			
		}
		else if (GetKeyState(VK_SPACE) & 0x8000)
		{
			vecTemp.push_back({ m_Player->ptPosition.x ,m_Player->ptPosition.y });
		}
	}
	break;
	}

}

bool GameScene::PlayerInsideCheck()
{
	int crosses = 0;
	int i = 0, j = 0;
	//for (i = 0; i < vecPolygon.size(); i++)
	//{
	//	for (j = 0; j < vecPolygon.size(); j++)
	//	{
	//		if (m_Player->ptPosition.x == vecPolygon[i].x && (m_Player->ptPosition.y == vecPolygon[j].y))
	//		{
	//			return false;
	//		}
	//			
	//	}
	//}
	for ( i = 0; i < vecPolygon.size(); i++) {
		int j = (i + 1) % vecPolygon.size();
		//�� B�� ���� (p[i], p[j])�� y��ǥ ���̿� ����
		if ((vecPolygon[i].y > m_Player->ptPosition.y) != (vecPolygon[j].y > m_Player->ptPosition.y)) {
			//atX�� �� B�� ������ ���򼱰� ���� (p[i], p[j])�� ����
			double atX = (vecPolygon[j].x - vecPolygon[i].x)*(m_Player->ptPosition.y - vecPolygon[i].y) / (vecPolygon[j].y - vecPolygon[i].y) + vecPolygon[i].x;
			//atX�� ������ ���������� ������ ������ ������ ������ ������Ų��.
			if (m_Player->ptPosition.x <= atX)
				crosses++;
		}
	} //true�� �ȿ��ִٴ¶�
	return crosses % 2 > 0;
}

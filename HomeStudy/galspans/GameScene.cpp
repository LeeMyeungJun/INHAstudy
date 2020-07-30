#include "stdafx.h"

//	int iDirection; //< LEFT 0  UP 1 RIGHT 2 DOWN 3
// �迭 a.�׵θ� b.���� c.�ȸ����� d.����

const int PlayerSpeed = 2;
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
	memset(arrLand, 'c', sizeof(arrLand));
	
	for (int i = 100; i <= 200; i++)
	{
		for (int j = 100; j <= 200; j++)
		{	
			if (i ==100 || i == 200 || j == 100 || j == 200)
			{
				arrLand[i][j] = 'a';
			}
			else
			{
				arrLand[i][j] = 'b';
			}
			
		}
	}


	m_Player->ptPosition.x = 100;
	m_Player->ptPosition.y = 100;

	m_Player->ptTemp.x = 0;
	m_Player->ptTemp.y = 0;

	bMoveFlag = false;
	bDrawFlag = false;

}

void GameScene::Update(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
	{
		if (GetKeyState(VK_RIGHT) & 0x8000)
		{
			PlayerMove(VK_RIGHT);
		}
		else if (GetKeyState(VK_LEFT) & 0x8000)
		{
			PlayerMove(VK_LEFT);
		}
		else if (GetKeyState(VK_UP) & 0x8000)
		{
			PlayerMove(VK_UP);
		}
		else if (GetKeyState(VK_DOWN) & 0x8000)
		{
			PlayerMove(VK_DOWN);
		}
	}
	break;
	}
	//vecTemp.push_back({ m_Player->ptPosition.x ,m_Player->ptPosition.y });
	//g_GameManager->SceneChange(Scene_enum::SCENE_END);
	
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
		if (bDrawFlag)
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
	LONG tempX = m_Player->ptPosition.x;
	LONG tempY = m_Player->ptPosition.y;

	switch (message)
	{
	case VK_RIGHT :
		tempX += PlayerSpeed;
		break;
	case VK_LEFT:
		tempX -= PlayerSpeed;
		break;
	case VK_UP:
		tempY -= PlayerSpeed;
		break;
	case VK_DOWN:
		tempY += PlayerSpeed;
		break;
	}

	if (GetKeyState(VK_SPACE) & 0x8000 && bMoveFlag == false && LandEmptyCheck(tempY, tempX))
	{

		/*�������� �ε����� ���ƿ����ҰŸ� ���⼭ ������ָ��
		�÷��̾� ������ POINT ���� �ϳ����������� ����������*/
		
		m_Player->ptPosition.x = tempX;
		m_Player->ptPosition.y = tempY;
		bMoveFlag = true;

		vecTemp.push_back({ m_Player->ptPosition.x ,m_Player->ptPosition.y }); //���� ������� ����ش� .
		PlayerFirstDirection(message); //���� ���� üũ
		
	}
	else if (LandBorderCheck(tempY, tempX))
	{
		/*
		if(bMoveFlag == true)
		{
		�����ٰ� ���ƿ°�. ����
		bMoveFlag = false; �޽��δٽùٲ�����c
		}
		*/
		m_Player->ptPosition.x = tempX;
		m_Player->ptPosition.y = tempY;
	}
	else if (bMoveFlag) //�̹̹��̿��� ����üũ��������Ѵ�.
	{
		switch (message)
		{
		case VK_RIGHT:
			m_Player->tempDirection = m_Player->Direction::RIGHT;
			break;
		case VK_LEFT:
			m_Player->tempDirection = m_Player->Direction::LEFT;
			break;
		case VK_UP:
			m_Player->tempDirection = m_Player->Direction::UP;
			break;
		case VK_DOWN:
			m_Player->tempDirection = m_Player->Direction::DOWN;
			break;
		}

		if (m_Player->tempDirection != m_Player->iDirection)
		{
			vecTemp.push_back({ m_Player->ptPosition.x ,m_Player->ptPosition.y });
		}

		m_Player->ptPosition.x = tempX;
		m_Player->ptPosition.y = tempY;

	}
}


void GameScene::PlayerFirstDirection(UINT message)
{
	switch (message)
	{
	case VK_RIGHT:
		m_Player->iDirection = m_Player->Direction::RIGHT;
		m_Player->tempDirection = m_Player->Direction::RIGHT;
		break;
	case VK_LEFT:
		m_Player->iDirection = m_Player->Direction::LEFT;
		m_Player->tempDirection = m_Player->Direction::LEFT;
		break;
	case VK_UP:
		m_Player->iDirection = m_Player->Direction::UP;
		m_Player->tempDirection = m_Player->Direction::UP;
		break;
	case VK_DOWN:
		m_Player->iDirection = m_Player->Direction::DOWN;
		m_Player->tempDirection = m_Player->Direction::DOWN;
		break;
	}
}

bool GameScene::LandEmptyCheck(int y , int x)
{
	if (arrLand[y][x] == 'c')
		return true;
	return false;
}

//�׵θ� üũ
bool GameScene::LandBorderCheck(int y,int x) 
{
	if (arrLand[y][x] == 'a')
	{
		if (bMoveFlag && vecTemp.size() > 3)
		{
			//���⿡ ��ġ�°��� 
			bDrawFlag = true;
		}

		return true;
	}
		
	return false;
}

void GameScene::PlayerLineCheck()
{


}
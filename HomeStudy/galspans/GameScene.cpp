#include "stdafx.h"

//	int iDirection; //< LEFT 0  UP 1 RIGHT 2 DOWN 3
// 배열 a.테두리 b.내부 c.안먹은땅 d.꼬리

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
		if (bDrawFlag)
		{
			Polygon(tempDC, &vecTemp[0], vecTemp.size());
			
		}
		
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

		/*꼬리끼리 부딛혀서 돌아오게할거면 여기서 만들어주면됨
		플레이어 씬에서 POINT 변수 하나더가져오삼 지금은안함*/
		
		m_Player->ptPosition.x = tempX;
		m_Player->ptPosition.y = tempY;
		bMoveFlag = true;

		vecTemp.push_back({ m_Player->ptPosition.x ,m_Player->ptPosition.y }); //최초 출발점을 찍어준다 .
		PlayerFirstDirection(message); //최초 기울기 체크
		
	}
	else if (LandBorderCheck(tempY, tempX))
	{
		/*
		if(bMoveFlag == true)
		{
		나갔다가 돌아온것. 판정
		bMoveFlag = false; 펄스로다시바꿔줘야홤
		}
		*/
		m_Player->ptPosition.x = tempX;
		m_Player->ptPosition.y = tempY;
	}
	else if (bMoveFlag) //이미밖이여서 기울기체크를해줘야한다.
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

//테두리 체크
bool GameScene::LandBorderCheck(int y,int x) 
{
	if (arrLand[y][x] == 'a')
	{
		if (bMoveFlag && vecTemp.size() > 3)
		{
			//여기에 합치는공식 
			bDrawFlag = true;
		}

		return true;
	}
		
	return false;
}

void GameScene::PlayerLineCheck()
{


}
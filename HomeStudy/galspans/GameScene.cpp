#include "stdafx.h"

//	int iDirection; //< LEFT 0  UP 1 RIGHT 2 DOWN 3
// 배열 a.테두리 c.안먹은땅 d.꼬리

const int PlayerSpeed = 2;


extern GameManager * g_GameManager;
using namespace std;
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
	vecPoint.clear();
	vecPolygon.clear();
	
	vecPolygon.push_back({ 0,0 });
	vecPolygon.push_back({ 100,0 });
	vecPolygon.push_back({ 100,100 });
	vecPolygon.push_back({ 0,100 });
	memset(arrLand, 'c', sizeof(arrLand));
	
	for (int i = 0; i <= 100; i++)
	{
		for (int j = 0; j <= 100; j++)
		{	
			if (i ==0 || i == 100 || j == 0 || j == 100)
			{
				arrLand[i][j] = 'a';
			}
			else
			{
				continue;
			}
		}
	}


	m_Player->ptPosition.x = 100;
	m_Player->ptPosition.y = 100;

	m_Player->ptTemp.x = 0;
	m_Player->ptTemp.y = 0;

	bOutMoveFlag = false;


	arrStartEndCheck[START_LINE] = 0;
	arrStartEndCheck[END_LINE] = 0;

	
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

}

void GameScene::Render(HWND hWnd, HDC hdc)
{
	m_Bitmap->DrawBitmapDoubleBuffering(hWnd, hdc);


	HDC tempDC;
//	HDC tempDC2;

	HBRUSH myBrush, oldBrush;

	//HBITMAP hOldBitmap;
	//HBITMAP hNewBitmap;
	/*사진부분*/



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

		TransparentBlt(hdc, 0, 0, SCREEN_WIDTH- 50, SCREEN_HEIGHT- 50, tempDC, 0, 0, SCREEN_WIDTH - 50, SCREEN_HEIGHT - 50, RGB(255, 50, 255));

		DeleteDC(tempDC);
	}
	
	{
		//tempDC = CreateCompatibleDC(hdc);

		//if (hNewBitmap == NULL)
		//	hNewBitmap = CreateCompatibleBitmap(hdc, SCREEN_WIDTH, SCREEN_HEIGHT); //초기화를해준다 처음들어가면 사이즈만큼


		//hOldBitmap = (HBITMAP)SelectObject(tempDC, hNewBitmap);

		//tempDC2 = CreateCompatibleDC(tempDC);	//이미지 찢어짐 방지
		//hOldBitmap2 = (HBITMAP)SelectObject(tempDC2, hBackImage);



		//myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 255, 0));
		//oldBrush = (HBRUSH)SelectObject(tempDC, myBrush);

		//Rectangle(tempDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

		//SelectObject(tempDC, oldBrush);
		//DeleteObject(myBrush);


		//myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 50, 255));
		//oldBrush = (HBRUSH)SelectObject(tempDC, myBrush);

		///*구멍뚫을부분 */
		//Polygon(tempDC, &vecPolygon[0], vecPolygon.size());
		///*여기까지 */
		//SelectObject(tempDC, oldBrush);
		//DeleteObject(myBrush);

		//TransparentBlt(hdc, 0, 0, SCREEN_WIDTH - 50, SCREEN_HEIGHT - 50, tempDC, 0, 0, SCREEN_WIDTH - 50, SCREEN_HEIGHT - 50, RGB(255, 50, 255));

		//DeleteDC(tempDC);
	}













	/*플레이어 부분 */
	myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
	oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

	m_Player->DrawPlayerCharacter(hdc);

	SelectObject(hdc, oldBrush);
	DeleteObject(myBrush);


	TCHAR tcharx[30];
	TCHAR tchary[30];

	TCHAR tcharm[30];
	TCHAR tcharl[30];


	TCHAR tchars[30];
	TCHAR tchare[30];


	_ltow(m_Player->ptPosition.x, tcharx, 10);
	_ltow(m_Player->ptPosition.y, tchary, 10);

	_ltow(m_Player->iDirection, tcharm, 10);
	_ltow(m_Player->PlayerLinePosition, tcharl, 10);
	_ltow(arrStartEndCheck[START_LINE], tchars, 10);
	_ltow(arrStartEndCheck[END_LINE], tchare, 10);


	TextOut(hdc, 10, 30, tcharx, lstrlen(tcharx));
	TextOut(hdc, 10, 50, tchary, lstrlen(tchary));

	TextOut(hdc, 10, 70, tcharm, lstrlen(tcharm));
	TextOut(hdc, 10, 90, tcharl, lstrlen(tcharl));
	TextOut(hdc, 10, 110, tchars, lstrlen(tchars));
	TextOut(hdc, 10, 130, tchare, lstrlen(tchare));

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

	//if(tempY <0 || tempY >r)

	if (LandBorderCheck(tempY, tempX))
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
		
		if (bOutMoveFlag && vecPoint.size() >1)
		{
			//여기에 합치는공식 
			PlayerLineCheck();
			arrStartEndCheck[END_LINE] = m_Player->PlayerLinePosition;
			vecPoint.push_back({ m_Player->ptPosition.x ,m_Player->ptPosition.y });
			std::vector<POINT> vecTemp(vecPolygon);

			int temp = 0;


			if (arrStartEndCheck[START_LINE] != arrStartEndCheck[END_LINE])
			{
				if (arrStartEndCheck[START_LINE] < arrStartEndCheck[END_LINE])
				{
					vecTemp.erase(vecTemp.begin() + arrStartEndCheck[START_LINE] + 1, vecTemp.begin() + arrStartEndCheck[END_LINE] + 1);
						
					reverse(vecPoint.begin(), vecPoint.end());
					
					temp = arrStartEndCheck[START_LINE];
					
				}
				else
				{
					vecTemp.erase(vecTemp.begin() + arrStartEndCheck[END_LINE] + 1, vecTemp.begin() + arrStartEndCheck[START_LINE] + 1);
					temp = arrStartEndCheck[END_LINE];
				}
			}
			else if (arrStartEndCheck[START_LINE] == arrStartEndCheck[END_LINE])
			{
				if (vecPoint[0].y == vecPoint[vecPoint.size() - 1].y)
				{
					if (vecPoint[0].x < vecPoint[vecPoint.size() - 1].x)
					{
						reverse(vecPoint.begin(), vecPoint.end());// 시계방향이면 하고 아니면 하지마

					}
				}
				else if (vecPoint[0].x == vecPoint[vecPoint.size() - 1].x)
				{
					if (vecPoint[0].y < vecPoint[vecPoint.size() - 1].y)
					{
						reverse(vecPoint.begin(), vecPoint.end());// 시계방향이면 하고 아니면 하지마
					}
				}

				temp = arrStartEndCheck[START_LINE];
			}

		
				for (int i = 0; i < vecPoint.size(); i++)
				{
					vecTemp.insert(vecTemp.begin() + temp + 1 , vecPoint[i]);
			
				}
			vecPolygon = vecTemp;
			RebuildLand();
			bOutMoveFlag = false;
			vecTemp.clear();
			vecPoint.clear();
		}
	}
	else if (LandEmptyCheck(tempY, tempX) && GetKeyState(VK_SPACE) & 0x8000 && !bOutMoveFlag)
	{
		PlayerLineCheck();
		arrStartEndCheck[START_LINE] = m_Player->PlayerLinePosition;
		vecPoint.push_back({ m_Player->ptPosition.x ,m_Player->ptPosition.y });
		m_Player->ptPosition.x = tempX;
		m_Player->ptPosition.y = tempY;
		arrLand[tempY][tempX] = 'a';
		bOutMoveFlag = true;
		PlayerFirstDirection(message);
		
	}
	else if (bOutMoveFlag) //이미밖이여서 기울기체크를해줘야한다.
	{
		PlayerDirectionCheck(message);

		if (m_Player->tempDirection != m_Player->iDirection)
		{
			vecPoint.push_back({ m_Player->ptPosition.x ,m_Player->ptPosition.y });
			m_Player->iDirection = m_Player->tempDirection;
		}

		m_Player->ptPosition.x = tempX;
		m_Player->ptPosition.y = tempY;
		arrLand[tempY][tempX] = 'a';

	}

	//800 , 900
	PlayerLineCheck();
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

void GameScene::PlayerDirectionCheck(UINT message)
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
		return true;
	}
	return false;
}

void GameScene::PlayerLineCheck()
 {
	for (int i = 0; i < vecPolygon.size(); i++)
	{
		if (i + 1 >= vecPolygon.size())
		{
			if (vecPolygon[i].y == m_Player->ptPosition.y && vecPolygon[0].y == m_Player->ptPosition.y)
			{
				if (vecPolygon[i].x <= m_Player->ptPosition.x && vecPolygon[0].x >= m_Player->ptPosition.x)
				{
					m_Player->PlayerLinePosition = i;
					break;
				}
				if (vecPolygon[i].x >= m_Player->ptPosition.x && vecPolygon[0].x <= m_Player->ptPosition.x)
				{
					m_Player->PlayerLinePosition = i;
					break;
				}
			
			}
			else if (vecPolygon[i].x == m_Player->ptPosition.x && vecPolygon[0].x == m_Player->ptPosition.x)
			{
				if (vecPolygon[i].y <= m_Player->ptPosition.y && vecPolygon[0].y >= m_Player->ptPosition.y)
				{
					m_Player->PlayerLinePosition = i;
					break;
				}	
				else if (vecPolygon[i].y >= m_Player->ptPosition.y && vecPolygon[0].y <= m_Player->ptPosition.y)
				{
					m_Player->PlayerLinePosition = i;
					break;
				}
			}
		}
		else if (vecPolygon[i].y == m_Player->ptPosition.y && vecPolygon[i + 1].y == m_Player->ptPosition.y)
		{
			if ((vecPolygon[i].x <= m_Player->ptPosition.x && vecPolygon[i + 1].x >= m_Player->ptPosition.x) || (vecPolygon[i].x >= m_Player->ptPosition.x && vecPolygon[i + 1].x <= m_Player->ptPosition.x))
			{
				m_Player->PlayerLinePosition = i;
				break;
			}
			
		}
		else if (vecPolygon[i].x == m_Player->ptPosition.x && vecPolygon[i + 1].x == m_Player->ptPosition.x) 
		{
			if ((vecPolygon[i].y <= m_Player->ptPosition.y && vecPolygon[i +1].y >= m_Player->ptPosition.y) || (vecPolygon[i].y >= m_Player->ptPosition.y && vecPolygon[i + 1].y <= m_Player->ptPosition.y))
			{
				m_Player->PlayerLinePosition = i;
				break;
			}
			
		}
		else
		{
			m_Player->PlayerLinePosition = -1;
		}
	}

 }

void GameScene::RebuildLand()
{
	//다 지운다. 
	memset(arrLand, 'c', sizeof(arrLand));
	

	int length = 0, i , j;
	for ( i = 0; i < vecPolygon.size(); i++)
	{
		if (i+1 == vecPolygon.size())
		{
			if (vecPolygon[i].x == vecPolygon[0].x)
			{
				if (vecPolygon[i].y < vecPolygon[0].y)
				{
					length = vecPolygon[0].y - vecPolygon[i].y;

					for (j = 0; j <= length; j++)
					{
						arrLand[vecPolygon[i].y + j][vecPolygon[i].x] = 'a';
					}
				}
				else
				{
					length = vecPolygon[i].y - vecPolygon[0].y;

					for (int j = 0; j <= length; j++)
					{
						arrLand[vecPolygon[0].y + j][vecPolygon[i].x] = 'a';
					}
				}
			}
		}
		else if (vecPolygon[i].x == vecPolygon[i + 1].x)
		{
			if (vecPolygon[i].y < vecPolygon[i + 1].y)
			{
				length = vecPolygon[i + 1].y - vecPolygon[i].y;

				for (j = 0; j <= length; j++)
				{
					arrLand[vecPolygon[i].y + j][vecPolygon[i].x ] = 'a';
				}
			}
			else
			{
				length = vecPolygon[i].y - vecPolygon[i + 1].y;

				for (int j = 0; j <= length; j++)
				{
					arrLand[vecPolygon[i + 1].y + j][vecPolygon[i].x] = 'a';
				}
			}
		}
		else if(vecPolygon[i].y == vecPolygon[i+1].y)
		{
			if (vecPolygon[i].x < vecPolygon[i + 1].x)
			{
				length = vecPolygon[i + 1].x - vecPolygon[i].x;
				for (j = 0; j <= length; j++)
				{
					arrLand[vecPolygon[i].y][vecPolygon[i].x + j] = 'a';
				}
			}
			else
			{
				length = vecPolygon[i].x - vecPolygon[i + 1].x;
				for (int j = 0; j <= length; j++)
				{
					arrLand[vecPolygon[i].y][vecPolygon[i + 1].x + j] = 'a';
				}

			}


		}
		
			

	}

}


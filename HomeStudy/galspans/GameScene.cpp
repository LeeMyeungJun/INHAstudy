#include "stdafx.h"

//	int iDirection; //< LEFT 0  UP 1 RIGHT 2 DOWN 3
// 배열 a.테두리 c.안먹은땅 d.꼬리

const int PlayerSpeed = 10;


extern GameManager * g_GameManager;
using namespace std;
GameScene::GameScene()
{
	m_GameUI = new GameUI;
	m_Bitmap = new BitMap;
	m_Player = new PlayerManager;
	m_SceneUI = m_GameUI;
	hDoubleBufferImage = NULL;

	stage = STAGE_ONE;
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
			if (i == 0 || i == 100 || j == 0 || j == 100)
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
	bWin = false;
	fArea = 100 * 100;
	GamePercent = 1;
	arrStartEndCheck[START_LINE] = 0;
	arrStartEndCheck[END_LINE] = 0;


	switch (stage)
	{
	case STAGE_ONE:
	{
		tempImage = MapSetting.hBackImage1;
		tempBack = MapSetting.bitBack1;
	}
	break;
	case STAGE_TWO:
	{
		tempImage = MapSetting.hBackImage2;
		tempBack = MapSetting.bitBack2;
	}
	break;
	}

	hDoubleBufferImage = NULL;


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

	
	if (bWin)
	{
		stage++;
		if (stage > STAGE_TWO)
			g_GameManager->SceneChange(Scene_enum::SCENE_END);
		Init();
		bWin = false;
		
	}

	

}

void GameScene::Render(HWND hWnd, HDC hdc)
{
	GetClientRect(hWnd, &rectView);

	/*그리기*/
	DrawBitmapDoubleBuffering(hWnd, hdc);

	/*플레이어 부분 */
	HBRUSH myBrush, oldBrush;
	myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
	oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

	m_Player->DrawPlayerCharacter(hdc);


	for (int i = 0; i < vecPoint.size(); i++)
	{
		//if (vecPoint.size() ==1)
		//{
		//	MoveToEx(hdc, vecPoint[0].x, vecPoint[0].y, NULL);
		//	LineTo(hdc, m_Player->ptPosition.x, m_Player->ptPosition.y);
		//}


		if (i == vecPoint.size() - 1)
		{
			MoveToEx(hdc, vecPoint[i].x, vecPoint[i].y, NULL);
			LineTo(hdc, m_Player->ptPosition.x, m_Player->ptPosition.y);

		}
		else
		{
			MoveToEx(hdc, vecPoint[i].x, vecPoint[i].y, NULL);
			LineTo(hdc, vecPoint[i + 1].x, vecPoint[i + 1].y);

		}



	}

	SelectObject(hdc, oldBrush);
	DeleteObject(myBrush);

	TCHAR tcPercent[30];


	//TCHAR tcharx[30];
	//TCHAR tchary[30];
	//TCHAR tcharm[30];
	//TCHAR tcharl[30];
	//TCHAR tchars[30];
	//TCHAR tchare[30];

	_ltow(GamePercent, tcPercent, 10);
	//_ltow(m_Player->ptPosition.x, tcharx, 10);
	//_ltow(m_Player->ptPosition.y, tchary, 10);
	//_ltow(m_Player->iDirection, tcharm, 10);
	//_ltow(m_Player->PlayerLinePosition, tcharl, 10);
	//_ltow(arrStartEndCheck[START_LINE], tchars, 10);
	//_ltow(arrStartEndCheck[END_LINE], tchare, 10);

	//m_rc_GamePercent = { 350,750,450,850 };
	TextOut(hdc, 350, 750, tcPercent, lstrlen(tcPercent));
	//TextOut(hdc, 700, 30, tcharx, lstrlen(tcharx));
	//TextOut(hdc, 700, 50, tchary, lstrlen(tchary));

	//TextOut(hdc, 10, 70, tcharm, lstrlen(tcharm));
	//TextOut(hdc, 10, 90, tcharl, lstrlen(tcharl));
	//TextOut(hdc, 10, 110, tchars, lstrlen(tchars));
	//TextOut(hdc, 10, 130, tchare, lstrlen(tchare));

}

void GameScene::Free(void)
{
	stage = STAGE_ONE;
}

void GameScene::PlayerMove(UINT message)
{
	LONG tempX = m_Player->ptPosition.x;
	LONG tempY = m_Player->ptPosition.y;

	int iCheckX = 0, iCheckY = 0;
	switch (message)
	{
	case VK_RIGHT:
		tempX += PlayerSpeed;
		iCheckX = 1;
		break;
	case VK_LEFT:
		tempX -= PlayerSpeed;
		iCheckX = -1;
		break;
	case VK_UP:
		tempY -= PlayerSpeed;
		iCheckY = -1;
		break;
	case VK_DOWN:
		tempY += PlayerSpeed;
		iCheckY = 1;
		break;
	}

	if (tempX >= rectView.left && tempX <= rectView.right && tempY <= rectView.bottom && tempY >= rectView.top)
	{
		if (LandBorderCheck(tempY, tempX))
		{

			if (bOutMoveFlag)
			{
				//넓이
				//여기에 합치는공식 

				PlayerDirectionCheck(message);
				if (m_Player->tempDirection != m_Player->iDirection)
				{
					vecPoint.push_back({ m_Player->ptPosition.x ,m_Player->ptPosition.y });
					m_Player->iDirection = m_Player->tempDirection;
				}

				m_Player->ptPosition.x = tempX;
				m_Player->ptPosition.y = tempY;
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
							}
							else if (vecPolygon[i].y == m_Player->ptPosition.y && vecPolygon[i + 1].y == m_Player->ptPosition.y)
							{
								//윗변 
								if ((vecPolygon[i].x <= m_Player->ptPosition.x && vecPolygon[i + 1].x >= m_Player->ptPosition.x))
								{
									if (vecPoint[0].x < vecPoint[vecPoint.size() - 1].x)
									{
										reverse(vecPoint.begin(), vecPoint.end());// 시계방향이면 하고 아니면 하지마
										break;
									}

								}
								else if ((vecPolygon[i].x >= m_Player->ptPosition.x && vecPolygon[i + 1].x <= m_Player->ptPosition.x))
								{
									if (vecPoint[0].x > vecPoint[vecPoint.size() - 1].x)
									{
										reverse(vecPoint.begin(), vecPoint.end());// 시계방향이면 하고 아니면 하지마
										break;
									}
								}

							}


						}


					}
					else if (vecPoint[0].x == vecPoint[vecPoint.size() - 1].x)
					{
						for (int i = 0; i < vecPolygon.size() - 1; i++)
						{

							//오른쪽
							if ((vecPolygon[i].y <= m_Player->ptPosition.y && vecPolygon[i + 1].y >= m_Player->ptPosition.y) && vecPolygon[i].x == m_Player->ptPosition.x && vecPolygon[i + 1].x == m_Player->ptPosition.x)
							{
								if (vecPoint[0].y > vecPoint[vecPoint.size() - 1].y)
								{

								}
								else
								{
									reverse(vecPoint.begin(), vecPoint.end());// 시계방향이면 하고 아니면 하지마
									break;
								}
							}//왼쪽
							else if ((vecPolygon[i].y >= m_Player->ptPosition.y && vecPolygon[i + 1].y <= m_Player->ptPosition.y) && vecPolygon[i].x == m_Player->ptPosition.x && vecPolygon[i + 1].x == m_Player->ptPosition.x)
							{
								if (vecPoint[0].y < vecPoint[vecPoint.size() - 1].y)
								{

								}
								else
								{
									reverse(vecPoint.begin(), vecPoint.end());// 시계방향이면 하고 아니면 하지마
									break;
								}
							}


						}

					}


					temp = arrStartEndCheck[START_LINE];
				}


				for (int i = 0; i < vecPoint.size(); i++)
				{
					vecTemp.insert(vecTemp.begin() + temp + 1, vecPoint[i]);

				}
				vecPolygon = vecTemp;
				RebuildLand();
				bOutMoveFlag = false;
				vecTemp.clear();
				vecPoint.clear();

				PolygonArea();

				GamePercent = (fabs(fArea) / (rectView.right * rectView.bottom)) * 100;

				if (GamePercent > 80)
				{
					bWin = true;
				}

			}
			else if (!LandBorderCheck(m_Player->ptPosition.y + iCheckY, m_Player->ptPosition.x + iCheckX) && GetKeyState(VK_SPACE) & 0x8000 && !PolygonInsideCheck({ m_Player->ptPosition.x + iCheckX ,m_Player->ptPosition.y + iCheckY }))
			{

				PlayerDirectionCheck(message);
				if (m_Player->tempDirection != m_Player->iDirection)
				{
					vecPoint.push_back({ m_Player->ptPosition.x ,m_Player->ptPosition.y });
					m_Player->iDirection = m_Player->tempDirection;
				}
				PlayerLineCheck();
				arrStartEndCheck[START_LINE] = m_Player->PlayerLinePosition;

				m_Player->ptPosition.x = tempX;
				m_Player->ptPosition.y = tempY;
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


				for (int i = 0; i < vecPoint.size(); i++)
				{
					vecTemp.insert(vecTemp.begin() + temp + 1, vecPoint[i]);

				}
				vecPolygon = vecTemp;
				RebuildLand();
				vecTemp.clear();
				vecPoint.clear();

				PolygonArea();

			}
			else if (!LandBorderCheck(m_Player->ptPosition.y + iCheckY, m_Player->ptPosition.x + iCheckX))
			{

			}
			else
			{
				m_Player->ptPosition.x = tempX;
				m_Player->ptPosition.y = tempY;
			}



		}
		else if (LandEmptyCheck(tempY, tempX) && GetKeyState(VK_SPACE) & 0x8000 && !bOutMoveFlag && !PolygonInsideCheck({ tempX,tempY }))
		{
			PlayerLineCheck();
			arrStartEndCheck[START_LINE] = m_Player->PlayerLinePosition;
			vecPoint.push_back({ m_Player->ptPosition.x ,m_Player->ptPosition.y });
			arrLand[m_Player->ptPosition.y][m_Player->ptPosition.x] = 'd'; //꼬리 첫부분
			m_Player->ptPosition.x = tempX;
			m_Player->ptPosition.y = tempY;
			arrLand[m_Player->ptPosition.y][m_Player->ptPosition.x] = 'd'; //꼬리 앞으로나가는부분
			bOutMoveFlag = true;
			PlayerFirstDirection(message);

		}
		else if (bOutMoveFlag) //이미밖이여서 기울기체크를해줘야한다.
		{

			if (arrLand[tempY][tempX] != 'd')
			{
				PlayerDirectionCheck(message);

				if (m_Player->tempDirection != m_Player->iDirection)
				{
					vecPoint.push_back({ m_Player->ptPosition.x ,m_Player->ptPosition.y });
					m_Player->iDirection = m_Player->tempDirection;
				}

				m_Player->ptPosition.x = tempX;
				m_Player->ptPosition.y = tempY;
				arrLand[tempY][tempX] = 'd';
			}


		}

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

bool GameScene::LandEmptyCheck(int y, int x)
{
	if (arrLand[y][x] == 'c')
		return true;
	return false;
}

//테두리 체크
bool GameScene::LandBorderCheck(int y, int x)
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
			if ((vecPolygon[i].y <= m_Player->ptPosition.y && vecPolygon[i + 1].y >= m_Player->ptPosition.y) || (vecPolygon[i].y >= m_Player->ptPosition.y && vecPolygon[i + 1].y <= m_Player->ptPosition.y))
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


	int length = 0, i, j;
	for (i = 0; i < vecPolygon.size(); i++)
	{
		if (i + 1 == vecPolygon.size())
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
					arrLand[vecPolygon[i].y + j][vecPolygon[i].x] = 'a';
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
		else if (vecPolygon[i].y == vecPolygon[i + 1].y)
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

void GameScene::DrawBitmapDoubleBuffering(HWND hwnd, HDC hdc)
{
	GetClientRect(hwnd, &rectView);


	HDC hMemDC;
	HBITMAP hOldBitmap;

	HDC hMemDC2;
	HBITMAP hOldBitmap2;
	int bx = 0, by = 0;


	hMemDC = CreateCompatibleDC(hdc);
	if (hDoubleBufferImage == NULL)
		hDoubleBufferImage = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom); //초기화를해준다 처음들어가면 사이즈만큼

	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hDoubleBufferImage);

	//사진부분 
	{
		hMemDC2 = CreateCompatibleDC(hMemDC);	//이미지 찢어짐 방지
		hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, tempImage); //여기 사진넣기

		bx = tempBack.bmWidth;
		by = tempBack.bmHeight;

		BitBlt(hMemDC, 0, 0, bx, by, hMemDC2, 0, 0, SRCCOPY);

		SelectObject(hMemDC2, hOldBitmap2);

		DeleteObject(hOldBitmap2);
		DeleteDC(hMemDC2);

	}

	{
		HBITMAP hDoubleTemp = NULL;

		if (hDoubleTemp == NULL)
			hDoubleTemp = CreateCompatibleBitmap(hMemDC, rectView.right, rectView.bottom); //초기화를해준다 처음들어가면 사이즈만큼

		hMemDC2 = CreateCompatibleDC(hMemDC); //똑같이만들어
		hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hDoubleTemp); //도화자에 그릴준비

		HBRUSH myBrush, oldBrush;
		myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 255, 0));
		oldBrush = (HBRUSH)SelectObject(hMemDC2, myBrush);

		Rectangle(hMemDC2, 0, 0, rectView.right, rectView.bottom); //화면전체출력 가리기용도 . 

		SelectObject(hMemDC2, oldBrush);
		DeleteObject(myBrush);
		myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 50, 255));
		oldBrush = (HBRUSH)SelectObject(hMemDC2, myBrush);

		/*구멍뚫을부분 */
		Polygon(hMemDC2, &vecPolygon[0], vecPolygon.size());
		/*여기까지 */

		SelectObject(hMemDC2, oldBrush);
		DeleteObject(myBrush);

		//BitBlt(hMemDC, 0, 0, rectView.right, rectView.bottom, hMemDC2, 0, 0, SRCCOPY);

		TransparentBlt(hMemDC, 0, 0, rectView.right, rectView.bottom, hMemDC2, 0, 0, rectView.right, rectView.bottom, RGB(255, 50, 255)); //hMemDC에 HMemDC2에 쓴것을 쓰겟다 . 255 50 255 색깔만뺴고.
		SelectObject(hMemDC2, hOldBitmap2);

		DeleteObject(hOldBitmap2);
		DeleteDC(hMemDC2);

	}

	//TransparentBlt(hdc, 0, 0, rectView.right, rectView.bottom, hMemDC, 0, 0, rectView.right, rectView.bottom, RGB(255, 50, 255)); //hMemDC에 HMemDC2에 쓴것을 쓰겟다 . 255 50 255 색깔만뺴고.

	StretchBlt(hdc, 0, 0, rectView.right, rectView.bottom, hMemDC, 0, 0, rectView.right, rectView.bottom, SRCCOPY); //hMemDC에 쓴것을 hdc에 쓰겟다. 

	SelectObject(hMemDC, hOldBitmap);


	DeleteDC(hMemDC);




}

void GameScene::PolygonArea()
{
	vector<POINT> vecTempArea;
	vecTempArea = vecPolygon;

	vecTempArea.insert(vecTempArea.begin() + vecTempArea.size(), vecTempArea.front());
	fArea = 0;
	for (int i = 0; i < vecTempArea.size() - 1; i++)
		fArea += (((float)vecTempArea[i].x * (float)vecTempArea[i + 1].y) / 2 - ((float)vecTempArea[i + 1].x * (float)vecTempArea[i].y) / 2);



	//int PolygonArea(vector<POINT> poly)
	//{
	//	int result = 0;
	//	int areaX = 0;
	//	int areaY = 0;
	//	for (int i = 0; i < poly.size(); i++)
	//	{
	//		if (i == poly.size() - 1)
	//		{
	//			areaX += poly[i].x * poly[0].y;
	//			areaY += poly[i].y * poly[0].x;
	//		}
	//		else
	//		{
	//			areaX += poly[i].x * poly[i + 1].y;
	//			areaY += poly[i].y * poly[i + 1].x;
	//		}
	//	}
	//	result = areaX - (areaY);
	//	return abs(result*0.5);
	//}

}

bool GameScene::PolygonInsideCheck(POINT p)
{
	//bool isInside(vector2 B, const polygon& p) {
	//crosses는 점q와 오른쪽 반직선과 다각형과의 교점의 개수
	int crosses = 0;
	for (int i = 0; i < vecPolygon.size(); i++) {
		int j = (i + 1) % vecPolygon.size();
		//점 B가 선분 (p[i], p[j])의 y좌표 사이에 있음
		if ((vecPolygon[i].y > p.y) != (vecPolygon[j].y > p.y)) {
			//atX는 점 B를 지나는 수평선과 선분 (p[i], p[j])의 교점
			double atX = (vecPolygon[j].x - vecPolygon[i].x)*(p.y - vecPolygon[i].y) / (vecPolygon[j].y - vecPolygon[i].y) + vecPolygon[i].x;
			//atX가 오른쪽 반직선과의 교점이 맞으면 교점의 개수를 증가시킨다.
			if (p.x < atX)
				crosses++;
		}
	}
	return crosses % 2 > 0;
}


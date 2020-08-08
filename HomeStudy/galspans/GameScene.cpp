#include "stdafx.h"

//	int iDirection; //< LEFT 0  UP 1 RIGHT 2 DOWN 3
// 배열 a.테두리 c.안먹은땅 d.꼬리

const int PlayerSpeed = 10;


extern GameManager * g_GameManager;

using namespace std;
vector<Monster*> vecMonster;
list<Monster*> dieMonster;

int GameScene::stage = 0;

GameScene::GameScene() 
{
	m_GameUI = new GameUI;
	m_SceneUI = m_GameUI;
	m_Bitmap = new BitMap;
	m_Player = new PlayerManager;

	n_rc_reStart_btn = { 200,300 - 10,400,370 - 10 };
	m_rc_menu_btn = { 500,300 - 10,700,370 - 10 };


	hDoubleBufferImage = NULL;

	for (int i = 0; i < MONSTER_COUNT; i++)
	{
		if (i > 6)
		{
			m_Monster = new Monster((i-6) * 100 + 100, 500);
		}
		else
		{
			m_Monster = new Monster(i * 100 + 100, 300);
		}
	
		vecMonster.push_back(m_Monster);
	}

	
}

GameScene::~GameScene()
{
	delete m_Bitmap;
	delete m_Player;
	delete m_GameUI;

}

void GameScene::Init(void)
{
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
		bLose = false;
		fArea = 100 * 100;
		GamePercent = 1;
		arrStartEndCheck[START_LINE] = 0;
		arrStartEndCheck[END_LINE] = 0;
		iTimer = 0;


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


		WinImage = MapSetting.WinImage;
		WinBack = MapSetting.WinBack;

		LoseImage = MapSetting.LoseImage;
		LoseBack = MapSetting.LoseBack;

		hDoubleBufferImage = NULL;

		list<Monster*>::iterator it = dieMonster.begin();
		for (it = dieMonster.begin(); it != dieMonster.end(); it++)
		{
			(*it)->setDead(false);
			vecMonster.push_back(*it);
		}
		dieMonster.clear();


		for (int i = 0; i < vecMonster.size(); i++)
		{
			vecMonster[i]->Init();
		}
	}
	SetTimer(g_GameManager->getHwnd(), 999, 1000 / 30, MonsterUpdate);
}

void GameScene::Update(UINT message, WPARAM wParam, LPARAM lParam)
{


	if (bWin)
	{
		iTimer++;
		if (iTimer > 100)
		{
			stage++;
			NextStageFreeInit();
		}
		
	}
	else if (bLose)
	{
		//stage++;
		//g_GameManager->SceneChange(Scene_enum::SCENE_GAME);
		if (message == WM_LBUTTONDOWN)
		{
			int Clickx = LOWORD(lParam);
			int Clicky = HIWORD(lParam);

			if (Clickx >= n_rc_reStart_btn.left &&Clickx <= n_rc_reStart_btn.right
				&& Clicky >= n_rc_reStart_btn.top && Clicky <= n_rc_reStart_btn.bottom)
			{
				g_GameManager->SceneChange(Scene_enum::SCENE_GAME);
			}
			else if (Clickx >= m_rc_menu_btn.left &&Clickx <= m_rc_menu_btn.right
				&& Clicky >= m_rc_menu_btn.top && Clicky <= m_rc_menu_btn.bottom)
			{
				g_GameManager->SceneChange(Scene_enum::SCENE_MENU);

			}


		}

		
	}
	else
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
	
}

void GameScene::Render(HWND hWnd, HDC hdc)
{

		GetClientRect(hWnd, &rectView);
		/*그리기*/
		DrawBitmapDoubleBuffering(hWnd, hdc);
		/*플레이어 부분 */
		HBRUSH myBrush, oldBrush;
		if (bOutMoveFlag)
		{
			myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
			oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

			m_Player->DrawPlayerCharacter(hdc);

			SelectObject(hdc, oldBrush);
			DeleteObject(myBrush);
		}
		else
		{
			myBrush = (HBRUSH)CreateSolidBrush(RGB(0,255, 0));
			oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

			m_Player->DrawPlayerCharacter(hdc);

			SelectObject(hdc, oldBrush);
			DeleteObject(myBrush);
		}

		for (int i = 0; i < vecPoint.size(); i++)
		{
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


		//몬스터그리기
		{
			for (int i = 0; i < vecMonster.size(); i++)
			{
				vecMonster[i]->Render(hdc);
			}
		}
		

		HFONT oldFont = (HFONT)SelectObject(hdc,font.GameFont);
		TCHAR tcPercent[30];
		//TCHAR tcharx[30];
		//TCHAR tchary[30];
		_ltow(GamePercent, tcPercent, 10);
		//_ltow(m_Player->ptPosition.x, tcharx, 10);
		//_ltow(m_Player->ptPosition.y, tchary, 10);
		TextOut(hdc, 350, 400, tcPercent, lstrlen(tcPercent));
		//TextOut(hdc, 700, 30, tcharx, lstrlen(tcharx));
		//TextOut(hdc, 700, 50, tchary, lstrlen(tchary));

		if(bLose)
		{
			m_SceneUI->draw(hdc);
		}
	


	
}

void GameScene::Free(void)
{
	stage = STAGE_ONE;
	KillTimer(g_GameManager->getHwnd(), 999);

	for (int i = 0; i < vecMonster.size(); i++)
	{
		dieMonster.push_back(vecMonster[i]);
		vecMonster.erase(vecMonster.begin() + i);
	}

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

				if (GamePercent > VICTORY_PERCENT)
				{
					bWin = true;
				}
				if (!bWin)
				{
					for (int j = 0; j < vecMonster.size(); j++)
					{
						if (PolygonInsideCheck(vecMonster[j]->getPosition()))
						{
							vecMonster[j]->setDead(true);
							dieMonster.push_back(vecMonster[j]);
							vecMonster.erase(vecMonster.begin() + j);
							continue;
						}
					}
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


	}
	//가리기부분
	{
		static HBITMAP hDoubleTemp = NULL;

		if (hDoubleTemp == NULL)
			hDoubleTemp = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom); //초기화를해준다 처음들어가면 사이즈만큼

		//hMemDC2 = CreateCompatibleDC(hMemDC); //똑같이만들어
		hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hDoubleTemp); //도화자에 그릴준비

		HBRUSH myBrush, oldBrush;
		myBrush = (HBRUSH)CreateSolidBrush(RGB(100, 100, 100));
		oldBrush = (HBRUSH)SelectObject(hMemDC2, myBrush);

		Rectangle(hMemDC2, 0, 0, rectView.right, rectView.bottom); //화면전체출력 가리기용도 . 

		SelectObject(hMemDC2, oldBrush);
		DeleteObject(myBrush);
		myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 255));
		oldBrush = (HBRUSH)SelectObject(hMemDC2, myBrush);

		/*구멍뚫을부분 */
		Polygon(hMemDC2, &vecPolygon[0], vecPolygon.size());
		/*여기까지 */

		SelectObject(hMemDC2, oldBrush);
		DeleteObject(myBrush);

		//BitBlt(hMemDC, 0, 0, rectView.right, rectView.bottom, hMemDC2, 0, 0, SRCCOPY);

		TransparentBlt(hMemDC, 0, 0, rectView.right, rectView.bottom, hMemDC2, 0, 0, rectView.right, rectView.bottom, RGB(255, 0, 255)); //hMemDC에 HMemDC2에 쓴것을 쓰겟다 . 255 50 255 색깔만뺴고.
		SelectObject(hMemDC2, hOldBitmap2);

		DeleteObject(hOldBitmap2);
		DeleteDC(hMemDC2);

	}

	//Win 사진  
	if(bWin)
	{
		hMemDC2 = CreateCompatibleDC(hdc);
		hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, WinImage); //여기 사진넣기

		bx = WinBack.bmWidth;
		by = WinBack.bmHeight;
		TransparentBlt(hMemDC, 200,100, bx, by, hMemDC2, 0, 0, bx, by, RGB(255, 0, 255));//분홍색을 제외하고 출력을한다.
		SelectObject(hMemDC2, hOldBitmap2);
		DeleteObject(hOldBitmap2);
		DeleteDC(hMemDC2);
	}
	else if (bLose)
	{
		hMemDC2 = CreateCompatibleDC(hdc);
		hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, LoseImage); //여기 사진넣기

		bx = LoseBack.bmWidth;
		by = LoseBack.bmHeight;
		TransparentBlt(hMemDC, 0, 0, bx/2, by/2, hMemDC2, 0, 0, bx, by, RGB(255, 0, 255));//분홍색을 제외하고 출력을한다.
		SelectObject(hMemDC2, hOldBitmap2);
		DeleteObject(hOldBitmap2);
		DeleteDC(hMemDC2);
	}
	BitBlt(hdc, 0, 0, rectView.right, rectView.bottom, hMemDC, 0, 0, SRCCOPY); //hMemDC에 쓴것을 hdc에 쓰겟다. 

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

bool GameScene::Polygon_Line_Collision(POINT p ,int index) 
{
	int i, j;
	for (i = 0; i < vecPolygon.size(); i++)
	{
		if (i + 1 == vecPolygon.size())
		{
			if (vecPolygon[i].x == vecPolygon[0].x)
			{
				if ((vecPolygon[i].y <= p.y  && vecPolygon[0].y >= p.y) ||
					(vecPolygon[i].y >= p.y  && vecPolygon[0].y <= p.y))
				{
					if (vecPolygon[i].x == p.x - MONSTER_SIZE || vecPolygon[i].x == p.x + MONSTER_SIZE)
					{
						vecMonster[index]->PolygonCollide(SIDE_LEFT);
						return true;
					}

				}
			}
			else if (vecPolygon[i].y == vecPolygon[0].y)
			{
				if ((vecPolygon[i].x <= p.x  && vecPolygon[0].x >= p.x) ||
					(vecPolygon[i].x >= p.x  && vecPolygon[0].x <= p.x))
				{
					if (vecPolygon[i].y == p.y - MONSTER_SIZE || vecPolygon[i].y == p.y + MONSTER_SIZE)
					{
						vecMonster[index]->PolygonCollide(SIDE_LEFT);
						return true;
					}

				}
			}
		}
		else if (vecPolygon[i].x == vecPolygon[i + 1].x)
		{
			if ((vecPolygon[i].y <= p.y  && vecPolygon[i + 1].y >= p.y)) //오른쪽일경우지.
			{
				if (vecPolygon[i].x == p.x - MONSTER_SIZE)
				{
					vecMonster[index]->PolygonCollide(SIDE_RIGHT);
					return true;
				}
			}
			else if ((vecPolygon[i].y >= p.y  && vecPolygon[i + 1].y <= p.y)) //왼쪽
			{
				if (vecPolygon[i].x == p.x + MONSTER_SIZE)
				{
					vecMonster[index]->PolygonCollide(SIDE_LEFT);
					return true;
				}
			}
		}
		else if (vecPolygon[i].y == vecPolygon[i + 1].y)
		{
			if ((vecPolygon[i].x <= p.x  && vecPolygon[i + 1].x >= p.x)) //위쪽
			{
				if (vecPolygon[i].y == p.y + MONSTER_SIZE)
				{
					vecMonster[index]->PolygonCollide(SIDE_TOP);
					return true;
				}
			}
			else if ((vecPolygon[i].x >= p.x  && vecPolygon[i + 1].x <= p.x)) //아래쪽
			{
				if (vecPolygon[i].y == p.y - MONSTER_SIZE)
				{
					vecMonster[index]->PolygonCollide(SIDE_BOTTOM);
					return true;
				}
			}

		}

		if (vecPolygon[i].x == p.x && vecPolygon[i].y == p.y)
		{
			int dir = vecMonster[index]->getDirection();
			switch (dir)
			{
			case DIR_LT:
				vecMonster[index]->setDirection(DIR_RB);
				break;
			case DIR_RT:
				vecMonster[index]->setDirection(DIR_LB);
				break;
			case DIR_LB:
				vecMonster[index]->setDirection(DIR_RT);
				break;
			case DIR_RB:
				vecMonster[index]->setDirection(DIR_LT);
				break;
			}
			
			return true;
		}
	}

	
	return false;
}

bool GameScene::Player_Collsion(POINT p)
{
	float deltaX = p.x - m_Player->ptPosition.x;
	float deltaY = p.y - m_Player->ptPosition.y;

	float length = sqrt(deltaX *deltaX + deltaY*deltaY);

	if (length > (MONSTER_SIZE + CHARACTER_SIZE))
	{
		return false;
	}
		
	if (arrLand[m_Player->ptPosition.y][m_Player->ptPosition.x] == 'a')
		return false;

	return true;
}

bool GameScene::Tail_Collsion(POINT p)
{
	if (arrLand[p.y][p.x] == 'd')
		return true;

	return false;
}

void GameScene::NextStageFreeInit()
{
	//free
	for (int i = 0; i < vecMonster.size(); i++)
	{
		dieMonster.push_back(vecMonster[i]);
		vecMonster.erase(vecMonster.begin() + i);
	}
	//Init

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
	bLose = false;
	fArea = 100 * 100;
	GamePercent = 1;
	arrStartEndCheck[START_LINE] = 0;
	arrStartEndCheck[END_LINE] = 0;
	iTimer = 0;


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
	case STAGE_END:
	{
		g_GameManager->SceneChange(Scene_enum::SCENE_MENU);
	}
	break;
	}

	list<Monster*>::iterator it = dieMonster.begin();
	for (it = dieMonster.begin(); it != dieMonster.end(); it++)
	{
		(*it)->setDead(false);
		vecMonster.push_back(*it);
	}
	dieMonster.clear();


	for (int i = 0; i < vecMonster.size(); i++)
	{
		vecMonster[i]->Init();
	}


}

void GameScene::nonStaticMonsterUpdate()
{
	
	for (int i = 0; i < vecMonster.size(); i++)
	{
		vecMonster[i]->Update();
		if (!bWin)
		{
			Polygon_Line_Collision(vecMonster[i]->getPosition(), i);
			vecMonster[i]->ObjectCollide(vecMonster);

			if (Player_Collsion(vecMonster[i]->getPosition()))
			{
				bLose = true;
			}
			else if (bOutMoveFlag)
			{
				if (Tail_Collsion(vecMonster[i]->getPosition()))
				{
					bLose = true;
				}
			}
		}
	}
	

}

void CALLBACK MonsterUpdate(HWND, UINT, UINT_PTR, DWORD)
{
	g_GameManager->getGameScene()->nonStaticMonsterUpdate();
}

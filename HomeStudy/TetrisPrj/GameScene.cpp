#include "stdafx.h"


char *str[] = { "Game Over", "Next Block", "Score : ", "Level : ", "F2 : Start Game","F3 : Game Pause","HOLD" };

GameScene::GameScene()
{
	

}

GameScene::~GameScene()
{
}

void GameScene::Init(void)
{
	memset(m_iGameBoard, 0, sizeof(m_iGameBoard));
	m_iLevel = 1;	
	m_GameStart = true;
	m_GamePause = false;
	m_bHold = false;
	m_iBlockWidth = 30;
	m_iCurBlocksType = 0;
	m_iCurBlocksState = 0;
	m_iGostType = 0;
	m_iGostState = 0;
	m_iNextBlocksType = -1;
	m_iHoldBlocksType = -1;
	m_iSpeed = 500;
	m_iScore = 0;
	m_iTotalClearBlocks = 0;
	m_iStartClearBlocks = 5;
	m_iStepClearBlocks = 2;

	//m_rcLocal_borderLine = { m_rcclient.left + 400 - 1,m_rcclient.top + 50,m_rcclient.left + 850 + 1,m_rcclient.top + 770 };
	int i, j;
	for ( i = 0; i < HEIGHT-1; i++)
	{
		for (j = 0; j < WIDTH-2; j++)
		{
			BoardPoint[i][j] = { 400 + (m_iBlockWidth*j) ,50 + (m_iBlockWidth*i) };
		}
	}
	//	m_rcLocal_NextBlock = { m_rcclient.left + 880,m_rcclient.top + 50,m_rcclient.left + 1000 , m_rcclient.top + 170 };
	
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			NextBlockPosition[i][j] = { 910 + m_iBlockWidth *j ,80 + (m_iBlockWidth*i) };
		}
	}

	for (i = 0; i < HEIGHT; i++)
	{
		for (j = 0; j < WIDTH; j++)
		{
			m_iGameBoard[i][j] = (j == 0 || i == HEIGHT - 1 || j == WIDTH - 1) ? -1 : 0;
		}
	}

	m_iNextBlocksType = rand() % 7;
	CreateRandomBlocks();



}

void GameScene::Update(UINT message, WPARAM wParam, LPARAM lParam)
{
	ClickEvent(lParam);
	


	switch (message)
	{
	case WM_KEYDOWN:
		Input();
		break;
	}
	switch (GameCenter::GetInstance()->getScene())
	{
	case GameCenter::Scene_enum::GAME_SCENE:

		break;
	case GameCenter::Scene_enum::LOCALGAME_SCENE:
		BlockMove();
		break;
	}
	

}

void GameScene::Render(HWND hWnd, HDC hdc)
{
	UI(hdc);

}

void GameScene::Free(void)
{
}

void GameScene::UI(HDC hdc)
{

	switch (GameCenter::GetInstance()->getScene())
	{
	case GameCenter::Scene_enum::GAME_SCENE:

		break;
	case GameCenter::Scene_enum::LOCALGAME_SCENE:
		GameCenter::GetInstance()->getUI()->UIRender(hdc);
		//PrintScore(hdc);
		//PrintLevel(hdc);

		DrawBlock(hdc);
		break;
	}
	//PreviewBlocks(hdc);


}

void GameScene::ClickEvent(LPARAM lParam)
{
	int Clickx = LOWORD(lParam);
	int Clicky = HIWORD(lParam);

	if (Clickx >= GameCenter::GetInstance()->getUI()->getRCLocal_ExitBtn().left &&Clickx <= GameCenter::GetInstance()->getUI()->getRCLocal_ExitBtn().right
		&& Clicky >= GameCenter::GetInstance()->getUI()->getRCLocal_ExitBtn().top && Clicky <= GameCenter::GetInstance()->getUI()->getRCLocal_ExitBtn().bottom)
	{
		GameCenter::GetInstance()->SceneChange(GameCenter::Scene_enum::LOGIN_SCENE);
	}
}

void GameScene::PrintScore(HDC hdc)
{
}

void GameScene::PrintLevel(HDC hdc)
{
}

void GameScene::DrawBlock(HDC hdc)
{
	HBITMAP hBitmap;
	hBlocks = (HBITMAP)LoadImage(NULL, TEXT("IMG/Block.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hBlocks, sizeof(BITMAP), &bitBlcok);

	hBlocksDc = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)SelectObject(hBlocksDc, hBlocks);

	int bx, by;
	bx = bitBlcok.bmWidth;
	by = bitBlcok.bmHeight;

	int i, j;
	for (i = 0; i < HEIGHT; i++)
		for (j = 0; j < WIDTH-2; j++)
		{
			if (m_iGameBoard[i][j] > 0)   //블럭이 존재할 때
				StretchBlt(hdc, BoardPoint[i][j].x, BoardPoint[i][j].y, m_iBlockWidth, m_iBlockWidth, hBlocksDc,16 * (m_iGameBoard[i][j] -1), 0,16,by, SRCCOPY);   //각 블럭의 색
		}

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
		{
			if (m_BlockList[m_iNextBlocksType][0][i][j] > 0)
			{
				StretchBlt(hdc, NextBlockPosition[i][j].x, NextBlockPosition[i][j].y, m_iBlockWidth, m_iBlockWidth, hBlocksDc, 16 * (8 - 1), 0, 16, by, SRCCOPY);   //각 블럭의 색
			}
		}
	ReleaseDC(GameCenter::GetInstance()->getHwnd(), hdc);
}

int GameScene::DrawCurBlock()
{
	
	return TRUE;
}

void GameScene::PreviewBlocks(HDC hdc)
{
	int i, j, bitmapX;
	if (m_iNextBlocksType >= 0 && m_iNextBlocksType < 7)
	{
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				if (m_BlockList[m_iNextBlocksType][0][i][j] > 0)   //회전되지 않은 블럭이 있을 때
					bitmapX = m_iNextBlocksType * 16;
				else
					bitmapX = 16 * 8;

				BitBlt(hdc, 280 + j * 16, 10 + i * 16, 16, 16, hBlocksDc, bitmapX, 0, SRCCOPY);   //hBlockDc에 저장된 비트맵을 bitmapX값에 따라 출력
			}
		}
		//TextOut(hdc, 275, 70, (LPCWSTR)str[1], strlen(str[1]));
		ReleaseDC(GameCenter::GetInstance()->getHwnd(), hdc);
	}
}

void GameScene::PositionSave()
{

	int i, j;
	int cnt = 0;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (m_BlockList[m_iCurBlocksType][m_iCurBlocksState][i][j] > 0)
			{
				Position[cnt] = { m_iCurBlocksX + j ,m_iCurBlocksY + i };
				cnt++;
			}

		}
	}
}

void GameScene::SetBlockToGameBoard()
{
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (m_BlockList[m_iCurBlocksType][m_iCurBlocksState][i][j] > 0)
			{
				m_iGameBoard[i + m_iCurBlocksY][j + m_iCurBlocksX ] = m_BlockList[m_iCurBlocksType][m_iCurBlocksState][i][j];

			}
		}
	}

}

bool GameScene::CheckCollision()
{
	int i, j;
	int max = 0;

	for (i = 0; i < 4; i++)
	{
		if (max < Position[i].y)
		{
			max = Position[i].y;
		}
	}

	for (i = 0; i < 4; i++)
	{
		if (max == Position[i].y)
		{
			if (m_iGameBoard[Position[i].y  ][Position[i].x] == -1)
			{
				return true;
			}
			else if (m_iGameBoard[Position[i].y ][Position[i].x] > 0)
			{
				return true;
			}
		}
	}

	return false;
}

bool GameScene::TurnCheckCollision()
{
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (m_iGameBoard[m_iCurBlocksY + i + 1][m_iCurBlocksX + j] == -1 && m_BlockList[m_iCurBlocksType][m_iCurBlocksState][i][j] > 0)
			{             //정확한 위치를 위해 더해줌
				return true;
			}
		}
	}
	return false;
}

void GameScene::CreateRandomBlocks()
{
	m_iCurBlocksX = 7;
	m_iCurBlocksY = 0;
	m_iCurBlocksType = m_iNextBlocksType;
	m_iCurBlocksState = 0;
	m_iNextBlocksType = rand() % 7;

	//if (CheckCollision())
	//	GameOver();
	//else
	//	DrawCurBlock();

	SetBlockToGameBoard();
	
}

void GameScene::GameOver()
{
}

void GameScene::BlockMove()
{
	m_iCurBlocksY++;
	PositionSave();

	if (CheckCollision())
	{
		LineFullCheck();
		CreateRandomBlocks();
	}
	else
	{

		ClearCurBlocks(0,+1);


		SetBlockToGameBoard();
	}
		

}

void GameScene::ClearCurBlocks(int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		m_iGameBoard[Position[i].y - (y)][Position[i].x - (x) ] = 0;
	}
}

void GameScene::RotateBlocks()   //현재 블록 회전
{
	PositionSave();
	ClearCurBlocks(0,0);
	m_iCurBlocksState = (m_iCurBlocksState == 3) ? 0 : m_iCurBlocksState + 1;
	if (TurnCheckCollision())
		m_iCurBlocksState = (m_iCurBlocksState == 0) ? 3 : m_iCurBlocksState - 1;   //회전 제한

	return;
}

void GameScene::Input()
{
	PositionSave();
	int x = 0, y = 0;
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		RotateBlocks();
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		ClearCurBlocks(x, y);
		m_iCurBlocksX--;
		
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		ClearCurBlocks(x, y);
		m_iCurBlocksX++;
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		ClearCurBlocks(x, y);
		m_iCurBlocksY++;
	}

	
	if (CheckCollision())
	{
		LineFullCheck();
		CreateRandomBlocks();
	}
	else
	{
		SetBlockToGameBoard();
	}



}

void GameScene::LineFullCheck()
{
	int i, j,k,t,cnt = 0;
	for (i = 0; i < HEIGHT-1; i++)
	{
		cnt = 0;

		for (j = 1; j < WIDTH-1; j++)
		{
			//1 ~ 15
			if (m_iGameBoard[i][j] > 0)
				cnt++;
			if (cnt == 15)
			{
				for (t = i; t > 0; t--)
				{
					for (k = 1; k < WIDTH - 1; k++)
					{
						m_iGameBoard[t][k] = m_iGameBoard[t - 1][k];
						//m_iGameBoard[i][k] = 0;
					}
				}
				
			}
		}
	}
}

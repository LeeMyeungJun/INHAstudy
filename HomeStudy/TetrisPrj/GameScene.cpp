#include "stdafx.h"


//char *str[] = { "Game Over", "Next Block", "Score : ", "Level : ", "F2 : Start Game","F3 : Game Pause","HOLD" };

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
		for (j = 0; j < WIDTH; j++)
		{
			BoardPoint[i][j] = { 370 + (m_iBlockWidth*j) ,50 + (m_iBlockWidth*i) };
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
	

	if (!m_GameStart)
		return;
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
	DrawBackGround(hWnd,hdc);
	if (!m_GameStart)
		return;
	UI(hdc);

}

void GameScene::Free(void)
{
	DeleteObject(hBlocks);
	DeleteObject(hBackGround);
}

void GameScene::UI(HDC hdc)
{

	switch (GameCenter::GetInstance()->getScene())
	{
	case GameCenter::Scene_enum::GAME_SCENE:

		break;
	case GameCenter::Scene_enum::LOCALGAME_SCENE:
		GameCenter::GetInstance()->getUI()->UIRender(hdc);
		PrintScore(hdc);
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
		for (j = 0; j < WIDTH; j++)
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
	DeleteDC(hBlocksDc);
}

int  GameScene::DrawCurBlock()
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
	int i, j,temp;
	bool CheckFlag = false;

	for (i = 0; i < 4; i++)
	{
		CheckFlag = false;
		for (j = 0; j < 4; j++)
		{
			if (Position[i].x == Position[j].x)
			{

				if (Position[j].y > Position[i].y)
				{
					temp = j;
					CheckFlag = true;
				}
					
			}
		}
		if (!CheckFlag)
			temp = i;
		if (m_iGameBoard[Position[temp].y][Position[temp].x] == -1 || m_iGameBoard[Position[temp].y][Position[temp].x] > 0)
		{
			return true;
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
	if (GameOver())
	{
		m_GameStart = false;
	}

	SetBlockToGameBoard();
	
}

bool GameScene::GameOver()
{
	for (int i = 1; i < WIDTH; i++)
	{
		if (m_iGameBoard[0][i] > 0)
			return true;
	}
	return false;
}

void GameScene::BlockMove()
{
	m_iCurBlocksY++;
	PositionSave();

	if (CheckCollision())
	{
		m_iCurBlocksY--;
		SetBlockToGameBoard();

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
	ClearCurBlocks(0, 0);

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		RotateBlocks();
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		
		InputProcess(VK_LEFT);
		
		
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{

		InputProcess(VK_RIGHT);
		
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{

		InputProcess(VK_DOWN);
		
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{

		InputProcess(VK_SPACE);

	}

	



}

void GameScene::InputProcess(UINT message)
{
	int i, j ,temp;
	bool CheckFlag = false;
	switch (message)
	{
	case VK_LEFT:
		for (i = 3; i >= 0; i--)
		{
			for (j = 3; j >= 0; j--)
			{
				if (Position[i].y == Position[j].y)
				{
					if (Position[j].x < Position[i].x)
						i = j;
				}
			}

			if (m_iGameBoard[Position[i].y][Position[i].x - 1] == -1 || m_iGameBoard[Position[i].y][Position[i].x - 1] > 0)
			{
				return;
			}
		}
		m_iCurBlocksX--;
		break;
	case VK_RIGHT:
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				if (Position[i].y == Position[j].y)
				{
					if (Position[j].x > Position[i].x)
						i = j;
				}
			}
			if (m_iGameBoard[Position[i].y][Position[i].x +1] == -1 || m_iGameBoard[Position[i].y][Position[i].x +1] > 0)
			{
				return;
			}
		}
		m_iCurBlocksX++;
		break;
	case VK_DOWN:
		for (i = 0; i < 4; i++)
		{
			CheckFlag = false;
			for (j = 0; j < 4; j++)
			{
				if (Position[i].x == Position[j].x)
				{

					if (Position[j].y > Position[i].y)
					{
						temp = j;
						CheckFlag = true;
					}

				}
			}
			if (!CheckFlag)
				temp = i;
			if (m_iGameBoard[Position[temp].y +1 ][Position[temp].x] == -1 || m_iGameBoard[Position[temp].y +1][Position[temp].x] > 0)
			{
				return;
			}
		}
		m_iCurBlocksY++;
		break;
	case VK_SPACE:
	{
		while (!CheckCollision())
		{
			m_iCurBlocksY++;
			ClearCurBlocks(0, +1);
			PositionSave();
			//SetBlockToGameBoard();
		}

		m_iCurBlocksY--;
		SetBlockToGameBoard();

		LineFullCheck();
		CreateRandomBlocks();

	}
		
		break;
	}
}

void GameScene::LineFullCheck()
{
	int i, j, k, sum, deleteLine = 0;


	//26 16  24 14
	for (i = 0; i < HEIGHT; i++)
	{
		sum = 0;
		for (j = 1; j < WIDTH; j++)
			if (m_iGameBoard[i][j] > 0) sum += 1;

		if (sum == WIDTH-2)
		{
			for (k = i; k > 0; k--)
				for (j = 1; j < WIDTH; j++)
				{
					m_iGameBoard[k][j] = m_iGameBoard[k - 1][j];   //y 1감소
				}
		}
	}




}

void GameScene::MoveCollision()
{
	PositionSave();

}

void GameScene::DrawBackGround(HWND hWnd,HDC hdc)
{
	HBITMAP h01Bitmap;
	int bx, by;

	hBackGround = (HBITMAP)LoadImage(NULL, TEXT("IMG/background.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hBackGround, sizeof(BITMAP), &bitBackground);

	hBlocksDc = CreateCompatibleDC(hdc);
	h01Bitmap = (HBITMAP)SelectObject(hBlocksDc, hBackGround);

	bx = bitBackground.bmWidth;
	by = bitBackground.bmHeight;
	
	StretchBlt(hdc, 0,0, bx, by, hBlocksDc, 0, 0, bx, by, SRCCOPY);   //각 블럭의 색


	DeleteDC(hBlocksDc);
		

}

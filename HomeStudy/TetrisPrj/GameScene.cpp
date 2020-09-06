#include "stdafx.h"


extern SoundManager* g_theSoundManager;

void CALLBACK BlockUpdate(HWND, UINT, UINT_PTR, DWORD);

const int speed = 15;

GameScene::GameScene()
{

	
}

GameScene::~GameScene()
{
}

void GameScene::Init(void)
{
	m_iLevel = 1;
	SetTimer(GameCenter::GetInstance()->getHwnd(), 999, 10000/ (m_iLevel*speed), BlockUpdate);
	memset(m_iGameBoard, 0, sizeof(m_iGameBoard));
	m_GameStart = true;
	m_iBlockWidth = 30;
	m_iCurBlocksType = 0;
	m_iCurBlocksState = 0;
	m_iGostType = 0;
	m_iGostState = 0;
	m_iNextBlocksType = -1;
	m_iHoldBlocksType = -1;
	m_iTotalClearBlocks = 0;
	m_iStartClearBlocks = 5;
	m_iStepClearBlocks = 2;
	m_iGuideBlocksX = 0;
	m_iGuideBlocksY = 0;
	GameCenter::GetInstance()->InitMoveTime();
	GameCenter::GetInstance()->InitLocalLevel();
	GameCenter::GetInstance()->InitLocalScore();
	m_iAnimation = 0;
	

	m_YesBtn = { 495, 537, 595, 580 };
	m_NoBtn = { 650, 537, 750, 580 };

	//	m_rcLocal_borderLine = { m_rcclient.left + 400-1,m_rcclient.top + 85,m_rcclient.left + 820+1,m_rcclient.top + 835 };
	
	int i, j;
	for ( i = 0; i < HEIGHT-1; i++)
	{
		for (j = 0; j < WIDTH; j++)
		{
			BoardPoint[i][j] = { 370 + (m_iBlockWidth*j) ,85 + (m_iBlockWidth*i) };
		}
	}
	//	m_rcLocal_NextBlock = { m_rcclient.left + 880,m_rcclient.top + 85,m_rcclient.left + 1000 , m_rcclient.top + 205 };
	
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			NextBlockPosition[i][j] = { 920 + m_iBlockWidth *j ,140 + (m_iBlockWidth*i) };
		}
	}

	for (i = 0; i < HEIGHT; i++)
	{
		for (j = 0; j < WIDTH; j++)
		{
			m_iGameBoard[i][j] = (j == 0 || i == HEIGHT - 1 || j == WIDTH - 1) ? -1 : 0;
		}
	}
	
	for (i = 0; i < 4; i++)
	{
		GuidePosition[i].x = 0;
		GuidePosition[i].y = 0;
		Position[i].x = 0;
		Position[i].y = 0;

	}

	m_iNextBlocksType = rand() % 7;
	
	CreateRandomBlocks();

	
}

void GameScene::Update(UINT message, WPARAM wParam, LPARAM lParam)
{
	//ClickEvent(lParam);
	if (!m_GameStart)
	{
		if(message == WM_MOUSEMOVE)
			BtnAnimaition(lParam);
		else if (message == WM_LBUTTONDOWN)
		{
			ClickEvent(lParam);
		}
		return;
	}

	switch (message)
	{
	case WM_KEYDOWN:	
		Input();
		break;
	default:
		break;
	}

	GuidBlock();
	
}

void GameScene::Render(HWND hWnd, HDC hdc)
{
	UI(hdc);
}

void GameScene::Free(void)
{
	KillTimer(GameCenter::GetInstance()->getHwnd(), 999);
	DeleteObject(hBlocks);
	
}

void GameScene::UI(HDC hdc)
{
	switch (GameCenter::GetInstance()->getScene())
	{
	case GameCenter::Scene_enum::GAME_SCENE:
		break;
	case GameCenter::Scene_enum::LOCALGAME_SCENE:
		DrawBackGround(hdc);
		//GameCenter::GetInstance()->getUI()->UIRender(hdc);
		PrintScore(hdc);
		PrintLevel(hdc);
		DrawBlock(hdc);
		if (!m_GameStart)
		{
			DrawGameOver(hdc);
			

     			switch (m_iAnimation)
			{
			case 0:
				DrawContinue(hdc);
				break;
			case 1:
				DrawContinue2(hdc);
				break;
			case -1:
				DrawContinue3(hdc);
				break;
			}
				//Rectangle(hdc, m_YesBtn.left, m_YesBtn.top, m_YesBtn.right, m_YesBtn.bottom);
				//Rectangle(hdc, m_NoBtn.left, m_NoBtn.top, m_NoBtn.right, m_NoBtn.bottom);
			
		}

		break;
	}
}

void GameScene::ClickEvent(LPARAM lParam)
{
	int Clickx = LOWORD(lParam);
	int Clicky = HIWORD(lParam);

	if (Clickx >= m_YesBtn.left &&Clickx <= m_YesBtn.right
		&& Clicky >= m_YesBtn.top && Clicky <= m_YesBtn.bottom)
	{
		Init();
	}
	else if (Clickx >= m_NoBtn.left &&Clickx <= m_NoBtn.right
		&& Clicky >= m_NoBtn.top && Clicky <= m_NoBtn.bottom)
	{
		GameCenter::GetInstance()->SceneChange(GameCenter::Scene_enum::LOGIN_SCENE);
	}
	
}

void GameScene::PrintScore(HDC hdc)
{
	HFONT oldFont = (HFONT)SelectObject(hdc, GameCenter::GetInstance()->getUI()->GameFont);

	//TextOut(hdc, 100, 100,L"SCORE", strlen("SCORE"));

	TCHAR tcScore[30];
	_ltow(GameCenter::GetInstance()->getLocalScore(), tcScore, 10);
	TextOut(hdc, 600, 20, tcScore, lstrlen(tcScore));

	SelectObject(hdc, oldFont);
}

void GameScene::PrintLevel(HDC hdc)
{
	HFONT oldFont = (HFONT)SelectObject(hdc, GameCenter::GetInstance()->getUI()->GameFont);

	TextOut(hdc, 100, 100, L"LV", strlen("LV"));

	TCHAR tcLevel[30];
	_ltow(m_iLevel, tcLevel, 10);
	TextOut(hdc, 200, 140, tcLevel, lstrlen(tcLevel));

	SelectObject(hdc, oldFont);
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
	//움직이는 블럭
	for (i = 0; i < HEIGHT; i++)
		for (j = 0; j < WIDTH; j++)
		{
			if (m_iGameBoard[i][j] > 0)   //블럭이 존재할 때
				StretchBlt(hdc, BoardPoint[i][j].x, BoardPoint[i][j].y, m_iBlockWidth, m_iBlockWidth, hBlocksDc,16 * (m_iGameBoard[i][j] -1), 0,16,by, SRCCOPY);   //각 블럭의 색
			else if (m_iGameBoard[i][j] == -2)
			{
				//가이드 블럭
				TransparentBlt(hdc, BoardPoint[i][j].x, BoardPoint[i][j].y, m_iBlockWidth, m_iBlockWidth, hBlocksDc, 16 * 8, 0, 16, by, RGB(255, 0, 255));// bx*4 ,by*4 는 4배한것.
			}
		}

	//다음블럭
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
		{
			if (m_BlockList[m_iNextBlocksType][0][i][j] > 0)
			{
				StretchBlt(hdc, NextBlockPosition[i][j].x, NextBlockPosition[i][j].y, m_iBlockWidth, m_iBlockWidth, hBlocksDc, 16 * (8 - 1), 0, 16, by, SRCCOPY);   //각 블럭의 색
			}
		}
	DeleteDC(hBlocksDc);
	DeleteObject(hBlocks);
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

void GameScene::GuidePositionSave()
{
	int i, j;
	int cnt = 0;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (m_BlockList[m_iCurBlocksType][m_iCurBlocksState][i][j] > 0)
			{
				GuidePosition[cnt] = { m_iGuideBlocksX + j ,m_iGuideBlocksY + i };
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

void GameScene::SetGuideBlockToGameBoard()
{
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (m_BlockList[m_iCurBlocksType][m_iCurBlocksState][i][j] > 0)
			{
				m_iGameBoard[i + m_iGuideBlocksY][j + m_iGuideBlocksX] = -2;
	
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

bool GameScene::CheckGuideCollision()
{
	int i, j, temp;
	bool CheckFlag = false;

	for (i = 0; i < 4; i++)
	{
		CheckFlag = false;
		for (j = 0; j < 4; j++)
		{
			if (GuidePosition[i].x == GuidePosition[j].x)
			{

				if (GuidePosition[j].y > GuidePosition[i].y)
				{
					temp = j;
					CheckFlag = true;
				}

			}
		}
		if (!CheckFlag)
			temp = i;
		if (m_iGameBoard[GuidePosition[temp].y][GuidePosition[temp].x] == -1 || m_iGameBoard[GuidePosition[temp].y][GuidePosition[temp].x] > 0)
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
			if (m_iGameBoard[m_iCurBlocksY + i][m_iCurBlocksX + j] == -1 && m_BlockList[m_iCurBlocksType][m_iCurBlocksState][i][j] > 0)
			{             //정확한 위치를 위해 더해줌
				return true;
			}
			else if (m_iGameBoard[m_iCurBlocksY + i][m_iCurBlocksX + j] > 0 && m_BlockList[m_iCurBlocksType][m_iCurBlocksState][i][j] > 0)
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

	m_iGuideBlocksX = m_iCurBlocksX;
	m_iGuideBlocksY = m_iCurBlocksY;

	if (GameOver())
	{
		m_GameStart = false;
		return;
	}


	SetBlockToGameBoard();
	
}

bool GameScene::GameOver()
{
	for (int i = 1; i < WIDTH; i++)
	{
		if (m_iGameBoard[0][i] > 0 || m_iGameBoard[1][i] > 0)
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

void GameScene::ClearGuideBlocks()
{
	int i, j;
	for (i = 0; i < HEIGHT ; i++)
		for (j = 0; j < WIDTH; j++)
			if (m_iGameBoard[i][j] == -2)
				m_iGameBoard[i][j] = 0;
}

void GameScene::RotateBlocks()   //현재 블록 회전
{
	PositionSave();
	ClearCurBlocks(0,0);
	m_iCurBlocksState = (m_iCurBlocksState == 3) ? 0 : m_iCurBlocksState + 1;

	if (TurnCheckCollision())
	{
		m_iCurBlocksState = (m_iCurBlocksState == 0) ? 3 : m_iCurBlocksState - 1;   //회전 제한
	}
	else
	{
		if (CheckCollision())
		{
			m_iCurBlocksState = (m_iCurBlocksState == 0) ? 3 : m_iCurBlocksState - 1;
		}
	}
		
	

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

	else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
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
		g_theSoundManager->PlaySFX("BBam");
		InputProcess(VK_SPACE);

	}
	else
	{
		g_theSoundManager->PlaySFX("Melem");
	}

	SetBlockToGameBoard();

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
			//ClearCurBlocks(0, +1);
			PositionSave();
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
	int i, j, k, sum;


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

			GameCenter::GetInstance()->setLocalScore(GameCenter::GetInstance()->getLocalScore() + 100);
			if (m_iLevel != GameCenter::GetInstance()->getLocalLevel())
			{
				if (!(m_iLevel * speed >= 10000))
				{
					m_iLevel = GameCenter::GetInstance()->getLocalLevel();
				}
				SetTimer(GameCenter::GetInstance()->getHwnd(), 999, 10000 / (m_iLevel * speed), BlockUpdate);
			}


		}
	}
}

void GameScene::MoveCollision()
{
	PositionSave();

}

void GameScene::DrawBackGround(HDC hdc)
{
	HBITMAP h01Bitmap;
	int bx, by;

	hBackGround = (HBITMAP)LoadImage(NULL, TEXT("IMG/background.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hBackGround, sizeof(BITMAP), &bitBackground);

	hBlocksDc = CreateCompatibleDC(hdc);
	h01Bitmap = (HBITMAP)SelectObject(hBlocksDc, hBackGround);

	bx = bitBackground.bmWidth;
	by = bitBackground.bmHeight;
	
	StretchBlt(hdc, 0,0, bx+872, by+644, hBlocksDc, 0, 0, bx, by, SRCCOPY);   //각 블럭의 색

	DeleteDC(hBlocksDc);
		
	DeleteObject(hBackGround);
}

void GameScene::nonStaticUpdate()
{

	if (!m_GameStart)
		return;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
	switch (GameCenter::GetInstance()->getScene())
	{
	case GameCenter::Scene_enum::GAME_SCENE:

		break;
	case GameCenter::Scene_enum::LOCALGAME_SCENE:
		BlockMove();
		
		break;
	}

}

void GameScene::DrawGameOver(HDC hdc)
{

	HBITMAP h01Bitmap;
	int bx, by;

	hBackGround = (HBITMAP)LoadImage(NULL, TEXT("IMG/GameOver.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hBackGround, sizeof(BITMAP), &bitBackground);

	hBlocksDc = CreateCompatibleDC(hdc);
	h01Bitmap = (HBITMAP)SelectObject(hBlocksDc, hBackGround);

	bx = bitBackground.bmWidth;
	by = bitBackground.bmHeight;

	TransparentBlt(hdc,0,0, bx*4.7, by*5, hBlocksDc, 0, 0, bx, by, RGB(255, 0, 255));// bx*4 ,by*4 는 4배한것.


	DeleteDC(hBlocksDc);

	DeleteObject(hBackGround);
}

void GameScene::DrawContinue(HDC hdc)
{

	HBITMAP h01Bitmap;
	int bx, by;

	hBackGround = (HBITMAP)LoadImage(NULL, TEXT("IMG/Continue1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hBackGround, sizeof(BITMAP), &bitBackground);

	hBlocksDc = CreateCompatibleDC(hdc);
	h01Bitmap = (HBITMAP)SelectObject(hBlocksDc, hBackGround);

	bx = bitBackground.bmWidth;
	by = bitBackground.bmHeight;

	TransparentBlt(hdc,425, 400, bx*1.8, by* 1.5, hBlocksDc, 0, 0, bx, by, RGB(255, 0, 255));// bx*4 ,by*4 는 4배한것.


	DeleteDC(hBlocksDc);

	DeleteObject(hBackGround);
}

void GameScene::DrawContinue2(HDC hdc)
{
	HBITMAP h01Bitmap;
	int bx, by;

	hBackGround = (HBITMAP)LoadImage(NULL, TEXT("IMG/Continue2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hBackGround, sizeof(BITMAP), &bitBackground);

	hBlocksDc = CreateCompatibleDC(hdc);
	h01Bitmap = (HBITMAP)SelectObject(hBlocksDc, hBackGround);

	bx = bitBackground.bmWidth;
	by = bitBackground.bmHeight;

	TransparentBlt(hdc, 425, 400, bx*1.8, by* 1.5, hBlocksDc, 0, 0, bx, by, RGB(255, 0, 255));// bx*4 ,by*4 는 4배한것.


	DeleteDC(hBlocksDc);

	DeleteObject(hBackGround);
}

void GameScene::DrawContinue3(HDC hdc)
{
	HBITMAP h01Bitmap;
	int bx, by;

	hBackGround = (HBITMAP)LoadImage(NULL, TEXT("IMG/Continue3.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hBackGround, sizeof(BITMAP), &bitBackground);

	hBlocksDc = CreateCompatibleDC(hdc);
	h01Bitmap = (HBITMAP)SelectObject(hBlocksDc, hBackGround);

	bx = bitBackground.bmWidth;
	by = bitBackground.bmHeight;

	TransparentBlt(hdc, 425, 400, bx*1.8, by* 1.5, hBlocksDc, 0, 0, bx, by, RGB(255, 0, 255));// bx*4 ,by*4 는 4배한것.


	DeleteDC(hBlocksDc);

	DeleteObject(hBackGround);
}

void GameScene::BtnAnimaition(LPARAM lParam)
{
	int Clickx = LOWORD(lParam);
	int Clicky = HIWORD(lParam);

	if (Clickx >= m_YesBtn.left &&Clickx <= m_YesBtn.right
		&& Clicky >= m_YesBtn.top && Clicky <= m_YesBtn.bottom)
	{
		m_iAnimation = 1;
	}
	else if (Clickx >= m_NoBtn.left &&Clickx <= m_NoBtn.right
		&& Clicky >= m_NoBtn.top && Clicky <= m_NoBtn.bottom)
	{
		m_iAnimation = -1;
	}
	else
	{
		m_iAnimation = 0;
	}
}

void GameScene::GuidBlock()
{
	int i;
	m_iGuideBlocksY = m_iCurBlocksY + 4;
	m_iGuideBlocksX = m_iCurBlocksX;

	GuidePositionSave();

	if (CheckGuideCollision())
	{
		ClearGuideBlocks();
		m_iGuideBlocksY = m_iCurBlocksY - 4;
		GuidePositionSave();
		return;
	}
	
	while (!CheckGuideCollision())
	{
		for (i = 0; i < 4; i++)
		{
			GuidePosition[i].y++;
		}
		m_iGuideBlocksY++;
	
		GuidePositionSave();
		
	}
	ClearGuideBlocks();
	for (i = 0; i < 4; i++)
	{
		GuidePosition[i].y--;
	}
	m_iGuideBlocksY--;


	SetGuideBlockToGameBoard();

}



void CALLBACK BlockUpdate(HWND, UINT, UINT_PTR, DWORD)
{
	GameCenter::GetInstance()->getGameScene()->nonStaticUpdate();
}

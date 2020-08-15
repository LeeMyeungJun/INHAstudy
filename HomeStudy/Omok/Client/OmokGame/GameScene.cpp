#include "stdafx.h"


extern ServerManager *Servermanager;
extern char g_player;
extern char g_turn;
//a > 빈것 w> 하얀돌 b>검은돌 
GameScene::GameScene()
{
	Init();
	count = 0;
}


GameScene::~GameScene()
{

}

void GameScene::Init(void)
{
	memset(boardState, 'a', sizeof(boardState));

	for (int i = 0; i < OMOKLINE; i++)
	{
		for (int j = 0; j < OMOKLINE; j++)
		{
			board[i][j].x = SUBWIDTH + j*BLOCKSIZE;
			board[i][j].y = SUBWIDTH + i*BLOCKSIZE;
		}

	}
}

void GameScene::Update(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
		ClickEvent(wParam, lParam);
		break;
	case WM_CHAR:
		ChatLog(wParam);
		break;
	}

	if (g_turn == 'u')
	{
		if (Servermanager->server == INVALID_SOCKET)
			return;
		else
		{
			strcpy(tchturn, "(t");
			strcpy_s(Servermanager->buffer, tchturn);
			send(Servermanager->server, (LPSTR)Servermanager->buffer, strlen(Servermanager->buffer), 0);

			//send(Servermanager->server,"(t", _tcslen("(t"), 0);
			g_turn = '\0';
		}
	}
	


}

void GameScene::Render(HWND hWnd, HDC hdc)
{
	UI(hdc);
	StoneRender(hdc);
	//TextOut(hdc, 700, 30, tcharx, lstrlen(tcharx));
	//TextOut(hdc, 700, 50, tchary, lstrlen(tchary));
	DrawChat(hdc);
	

}

void GameScene::Free(void)
{
}

void GameScene::UI(HDC hdc)
{
	
	myBrush = (HBRUSH)CreateSolidBrush(RGB(250, 203, 125));
	oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

	Rectangle(hdc, SUBWIDTH, SUBWIDTH, BLOCKSIZE*(OMOKLINE-1) + SUBWIDTH, SUBWIDTH + BLOCKSIZE*(OMOKLINE - 1));

	SelectObject(hdc, oldBrush);
	DeleteObject(myBrush);

	for (int i = 1; i < OMOKLINE-1; i++)
	{
		MoveToEx(hdc, 0 + SUBWIDTH, BLOCKSIZE * i + SUBWIDTH, NULL);
		LineTo(hdc, BLOCKSIZE * (OMOKLINE-1) + SUBWIDTH, BLOCKSIZE * i + SUBWIDTH); //가로줄

		MoveToEx(hdc, BLOCKSIZE * i + SUBWIDTH, 0 + SUBWIDTH, NULL);
		LineTo(hdc, BLOCKSIZE * i + SUBWIDTH, SUBWIDTH + BLOCKSIZE*(OMOKLINE - 1)); //세로줄
	}
	

}

void GameScene::BlackStone(HDC hdc,POINT pt)
{
	myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

	Ellipse(hdc, pt.x - STONE_SIZE, pt.y - STONE_SIZE, pt.x + STONE_SIZE, pt.y + STONE_SIZE);
	SelectObject(hdc, oldBrush);
	DeleteObject(myBrush);

}

void GameScene::WhiteStone(HDC hdc, POINT pt)
{
	Ellipse(hdc, pt.x - STONE_SIZE, pt.y - STONE_SIZE, pt.x + STONE_SIZE, pt.y + STONE_SIZE);
}

void GameScene::DrawChat(HDC hdc)
{
	////채팅부분 밑 
	SetBkMode(hdc, TRANSPARENT);
	
	size_t chatLogSize = Servermanager->chatLog.size();

	SelectObject(hdc, charRectTitleBrush);
	Rectangle(hdc, BLOCKSIZE*(OMOKLINE - 1) + SUBWIDTH + 50, 0, BLOCKSIZE*(OMOKLINE - 1) + SUBWIDTH + 450, SUBWIDTH + BLOCKSIZE*(OMOKLINE - 1) + 50);

	SelectObject(hdc, charRectBrush);
	Rectangle(hdc, BLOCKSIZE*(OMOKLINE - 1) + SUBWIDTH + 50, SUBWIDTH + BLOCKSIZE*(OMOKLINE - 1), BLOCKSIZE*(OMOKLINE-1) + SUBWIDTH + 450, SUBWIDTH + BLOCKSIZE*(OMOKLINE - 1) + 50);
	RECT charRect = { 820, 750, 1100, 800 };

	for (size_t i = 0; i < chatLogSize; i++)
	{
		TextOut(hdc, 820, 720 - (i * 20), Servermanager->chatLog[chatLogSize - 1 - i], _tcslen(Servermanager->chatLog[chatLogSize - 1 - i]));
	}
	DrawText(hdc, str, _tcslen(str), &charRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

	

}

void GameScene::StoneRender(HDC hdc)
{
	for (int i = 0; i < OMOKLINE; i++)
	{
		for (int j = 0; j < OMOKLINE; j++)
		{
			if (boardState[i][j] == 'b')
			{
				BlackStone(hdc, { board[i][j].x , board[i][j].y });
			}
			else if (boardState[i][j] == 'w')
			{
				WhiteStone(hdc, { board[i][j].x , board[i][j].y });
			}

		}

	}
}

int GameScene::Distance(const POINT & p1, const POINT & p2)
{

	double distance;

	// 피타고라스의 정리
	// pow(x,2) x의 2승,  sqrt() 제곱근
	distance = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));

	return distance;
}

void GameScene::ChatLog(WPARAM wParam)
{

	if (wParam == VK_RETURN)
	{
		if (Servermanager->server == INVALID_SOCKET)
			return ;
		else
		{
			strcpy_s(Servermanager->buffer, str);
			send(Servermanager->server, (LPSTR)Servermanager->buffer, strlen(Servermanager->buffer), 0);
			count = 0;
			str[count] = str[1] = '\0';
		}
	}
	else if (wParam == VK_BACK)
	{
		if (Servermanager->server == INVALID_SOCKET)
			return ;
		if (count != 0)
			str[--count] = '\0';
	}
	else
	{
		if (count < 40)
		{
			str[count++] = (TCHAR)wParam;
			str[count] = '\0';
		}
	}
}

void GameScene::ClickEvent(UINT message  ,LPARAM lParam)
{
	Clickx = LOWORD(lParam);
	Clicky = HIWORD(lParam);

	_ltow(Clickx, tcharx, 10);
	_ltow(Clicky, tchary, 10);

	if (g_turn == 't')
	{
		POINT pt = { Clickx,Clicky };
		for (int i = 0; i < OMOKLINE; i++)
		{
			for (int j = 0; j < OMOKLINE; j++)
			{
				if (Distance(pt, { board[i][j].x , board[i][j].y }) < 5 && boardState[i][j] == 'a')
				{
					boardState[i][j] = g_player;
					g_turn = 'u';
					break;
				}

			}

		}


	}
}


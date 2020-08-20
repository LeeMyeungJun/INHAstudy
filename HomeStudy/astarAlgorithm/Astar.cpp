#include "stdafx.h"


extern char boardState[19][19];
static POINT pt;
//a: 빈벽 x:장애물 s:시작점  e:도착점 c:닫힌 o:열린 r:길
Astar::Astar()
{
	Init();
	ClickFlag = false;
	StartFlag = false;
	EndFlag = false;
//	player =new Player;
	CommonFont = CreateFont(12, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"빙그레체");
	TitleFont = CreateFont(12, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"1훈새마을운동 R");

}


Astar::~Astar()
{
}

void Astar::Init(void)
{
	
	for (int i = 0; i < OMOKLINE; i++)
	{
		for (int j = 0; j < OMOKLINE; j++)
		{
			board[i][j].x = SUBWIDTH + j*BLOCKSIZE;
			board[i][j].y = SUBWIDTH + i*BLOCKSIZE;
		}

	}
}

void Astar::Update(UINT message, WPARAM wParam, LPARAM lParam)
{
	if(StartFlag && EndFlag)
		Algorithm();
}

void Astar::Render(HWND hWnd, HDC hdc)
{
	UI(hdc);
	ObstacleStartEndRender(hdc);

}

void Astar::Free(void)
{
}

void Astar::UI(HDC hdc)
{
	Rectangle(hdc, SUBWIDTH, SUBWIDTH, BLOCKSIZE*(OMOKLINE - 1) + SUBWIDTH, SUBWIDTH + BLOCKSIZE*(OMOKLINE - 1));

	for (int i = 1; i < OMOKLINE - 1; i++)
	{
		MoveToEx(hdc, 0 + SUBWIDTH, BLOCKSIZE * i + SUBWIDTH, NULL);
		LineTo(hdc, BLOCKSIZE * (OMOKLINE - 1) + SUBWIDTH, BLOCKSIZE * i + SUBWIDTH); //가로줄

		MoveToEx(hdc, BLOCKSIZE * i + SUBWIDTH, 0 + SUBWIDTH, NULL);
		LineTo(hdc, BLOCKSIZE * i + SUBWIDTH, SUBWIDTH + BLOCKSIZE*(OMOKLINE - 1)); //세로줄
	}
}

void Astar::ObstacleCreate(LPARAM lParam)
{
	int Clickx = LOWORD(lParam);
	int Clicky = HIWORD(lParam);

	POINT pt = { Clickx,Clicky };
	for (int i = 0; i < OMOKLINE; i++)
	{
		for (int j = 0; j < OMOKLINE; j++)
		{
			if (Distance(pt, { board[i][j].x , board[i][j].y }) && boardState[i][j] == 'a' && boardState[i][j] != 'x'&& boardState[i][j] != 's' && boardState[i][j] != 'e')
			{
				boardState[i][j] = 'x';
				ClickFlag = true;
				break;
			}
			else if (Distance(pt, { board[i][j].x , board[i][j].y }) && boardState[i][j] == 'x' && boardState[i][j] != 'a'&& boardState[i][j] != 's' && boardState[i][j] != 'e')
			{
				boardState[i][j] = 'a';
				ClickFlag = true;
				break;
			}

		}

		if (ClickFlag)
		{
			ClickFlag = false;
			break;
		}
	}



}

//p1이 클릭한위치 p2가 점위치 
bool Astar::Distance(const POINT & p1, const POINT & p2)
{
	double distance;

	distance = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));

	if (p1.x > p2.x && p1.y > p2.y)
	{
		if (distance > BLOCKSIZE)
			return false;
		return true;
	}

	return false;
}

void Astar::ObstacleStartEndRender(HDC hdc)
{


	HFONT oldFont = (HFONT)SelectObject(hdc, TitleFont);




	for (int i = 0; i < OMOKLINE-1; i++)
	{
		for (int j = 0; j < OMOKLINE-1; j++)
		{
			if (boardState[i][j] == 'x')
			{
				myBrush = (HBRUSH)CreateSolidBrush(RGB(0,0, 0));
				oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
				Rectangle(hdc, board[i][j].x, board[i][j].y, board[i][j].x + BLOCKSIZE, board[i][j].y + BLOCKSIZE);
				SelectObject(hdc, oldBrush);
				DeleteObject(myBrush);			
			}
			else if (boardState[i][j] == 's')
			{
				myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 64, 0));
				oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
				Rectangle(hdc, board[i][j].x, board[i][j].y, board[i][j].x + BLOCKSIZE, board[i][j].y + BLOCKSIZE);
				SelectObject(hdc, oldBrush);
				DeleteObject(myBrush);
			}
			else if (boardState[i][j] == 'e')
			{
				myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
				oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
				Rectangle(hdc, board[i][j].x, board[i][j].y, board[i][j].x + BLOCKSIZE, board[i][j].y + BLOCKSIZE);
				SelectObject(hdc, oldBrush);
				DeleteObject(myBrush);
			}

			if (boardState[i][j] == 'o')
			{
				myBrush = (HBRUSH)CreateSolidBrush(RGB(128, 255, 128));
				oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
				Rectangle(hdc, board[i][j].x, board[i][j].y, board[i][j].x + BLOCKSIZE, board[i][j].y + BLOCKSIZE);
				SelectObject(hdc, oldBrush);
				DeleteObject(myBrush);
			}
			else if (boardState[i][j] == 'c')
			{
				myBrush = (HBRUSH)CreateSolidBrush(RGB(250, 100, 200));
				oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
				Rectangle(hdc, board[i][j].x, board[i][j].y, board[i][j].x + BLOCKSIZE, board[i][j].y + BLOCKSIZE);
				SelectObject(hdc, oldBrush);
				DeleteObject(myBrush);
			}

			if (boardState[i][j] == 'o' || boardState[i][j] == 'c')
			{
				_ltow(setting[i][j].st_f, tchText, 10);

				TextOut(hdc,board[i][j].x + 8, board[i][j].y+5, tchText, lstrlen(tchText));

				_ltow(setting[i][j].st_g, tchText, 10);

				TextOut(hdc, board[i][j].x, board[i][j].y+20, tchText, lstrlen(tchText));

				_ltow(setting[i][j].st_h, tchText, 10);

				TextOut(hdc, board[i][j].x+20, board[i][j].y+20, tchText, lstrlen(tchText));
			}


		}
	}

	
	
	SelectObject(hdc, oldFont);


}



void Astar::StartEndPointCreate(LPARAM lParam)
{
	int Clickx = LOWORD(lParam);
	int Clicky = HIWORD(lParam);

	POINT pt = { Clickx,Clicky };
	for (int i = 0; i < OMOKLINE; i++)
	{
		for (int j = 0; j < OMOKLINE; j++)
		{

			if (Distance(pt, { board[i][j].x , board[i][j].y }) && boardState[i][j] == 'e')
			{

				boardState[i][j] = 'a';
				StartEnd[1].x = 0;
				StartEnd[1].y = 0;
				ClickFlag = true;
				EndFlag = false;
				break;
			}
			else if (Distance(pt, { board[i][j].x , board[i][j].y }) && boardState[i][j] == 's')
			{
				boardState[i][j] = 'a'; //스타트를 해제함으로 엔드 지점도 해제되게끔
				boardState[StartEnd[1].y][StartEnd[1].x] = 'a';
				player.st_position = { 0,0 };

				StartEnd[0].x = 0;
				StartEnd[0].y = 0;
				StartEnd[1].x = 0;
				StartEnd[1].y = 0;
				ClickFlag = true;
				EndFlag = false;
				StartFlag = false;
				break;
			}


			if (Distance(pt, { board[i][j].x , board[i][j].y }) && boardState[i][j] == 'a' && boardState[i][j] != 'x'&& boardState[i][j] != 's' && boardState[i][j] != 'e'&& StartFlag && !EndFlag)
			{
				boardState[i][j] = 'e';
				StartEnd[1].x = j;
				StartEnd[1].y = i;
				ClickFlag = true;
				EndFlag = true;
				break;
			}


			if (Distance(pt, { board[i][j].x , board[i][j].y }) && boardState[i][j] == 'a' && boardState[i][j] != 'o'&& boardState[i][j] != 's' && boardState[i][j] != 'e' && !StartFlag)
			{
				boardState[i][j] = 's';
				player.st_position = { j,i };
				StartEnd[0].x = j;
				StartEnd[0].y = i;
				tempPt = { player.st_position.x, player.st_position.y };
				StartFlag = true;
				ClickFlag = true;
				break;
			}
			

		}

		if (ClickFlag)
		{
			ClickFlag = false;
			break;
		}
	}
}


//a: 빈벽 x:장애물 s:시작점  e:도착점 c:닫힌 o:열린 r:길

void Astar::Algorithm()
{
	if (!StartFlag || !EndFlag)
		return;

	int temp = 999;

		/*
		POINT
		0 1 2
		7   3
		6 5 4
		*/

		POINT ptCheck[8] =
		{
			{ tempPt.x - 1,tempPt.y - 1 },{ tempPt.x,tempPt.y - 1 },{ tempPt.x + 1,tempPt.y - 1 },{ tempPt.x + 1,tempPt.y },
			{ tempPt.x + 1,tempPt.y + 1 },{ tempPt.x,tempPt.y + 1 },{ tempPt.x - 1,tempPt.y + 1 },{ tempPt.x - 1,tempPt.y }
		};

		for (int i = 0; i < 8; i++)
		{
			if (boardState[ptCheck[i].y][ptCheck[i].x] == 'e')
			{
				return;
			}
		}
		for (int i = 0; i < 8; i++)
		{
			if (boardState[ptCheck[i].y][ptCheck[i].x] == 'x')
			{


		/*		if (temp > setting[ptCheck[i].y][ptCheck[i].x].st_g)
				{
					temp = setting[ptCheck[i].y][ptCheck[i].x].st_g;
					tempPt = ptCheck[i];
				}*/
			}
			else if (boardState[ptCheck[i].y][ptCheck[i].x] == 'a')
			{
				boardState[ptCheck[i].y][ptCheck[i].x] = 'o';
				switch (i)
				{
				case 0:
				case 2:
				case 4:
				case 6:
					setting[ptCheck[i].y][ptCheck[i].x].st_g += 14;
					break;
				default:
					setting[ptCheck[i].y][ptCheck[i].x].st_g += 10;
					break;
				}

				setting[ptCheck[i].y][ptCheck[i].x].st_h += (abs(StartEnd[1].x - ptCheck[i].x)) * 10;
				setting[ptCheck[i].y][ptCheck[i].x].st_h += (abs(StartEnd[1].y - ptCheck[i].y)) * 10;
				setting[ptCheck[i].y][ptCheck[i].x].st_f = setting[ptCheck[i].y][ptCheck[i].x].st_g + setting[ptCheck[i].y][ptCheck[i].x].st_h;

				if (temp > setting[ptCheck[i].y][ptCheck[i].x].st_f)
				{
					temp = setting[ptCheck[i].y][ptCheck[i].x].st_f;
					tempPt = ptCheck[i];
				}



			}
		
				


		}
		/*if (boardState[tempPt.y][tempPt.x] == 'e')
			return;*/
	
	
		boardState[tempPt.y][tempPt.x] = 'c';

		
		
		
	}

	

	

	




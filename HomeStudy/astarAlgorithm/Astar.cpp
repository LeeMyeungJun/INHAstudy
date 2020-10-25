#include "stdafx.h"

int LINE_COUNT = 20;

Astar::Astar()
	: myBrush(NULL)
	, oldBrush(NULL)
{
	

}


Astar::~Astar()
{
}

void Astar::Init(void)
{
	
}

void Astar::Update(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	

}

void Astar::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
		{
			if (GetAsyncKeyState('W') & 0x8000)
			{
				LINE_COUNT++;
			}
			else if (GetAsyncKeyState('Q') & 0x8000)
			{
				LINE_COUNT--;
				if (LINE_COUNT == 0)
					LINE_COUNT = 1;
			}
		}
		break;
	default:
		break;
	}
}


void Astar::Render(HWND hWnd, HDC hdc)
{
	/*myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

	float fSize = 20.0f;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			Rectangle(hdc, j*fSize, i*fSize, (j+1)*fSize, (i+1)*fSize);
		}
	}
	SelectObject(hdc, oldBrush);
	DeleteObject(myBrush);*/
	RECT rc;
	GetClientRect(hWnd, &rc);
	Render_Board(hdc,rc);



}

void Astar::Free(void)
{
}

//p1이 클릭한위치 p2가 점위치 
bool Astar::Distance(const POINT & p1, const POINT & p2)
{
	double distance;

	distance = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));

	if (p1.x > p2.x && p1.y > p2.y)
	{
		//if (distance > BLOCKSIZE)
			return false;
		return true;
	}

	return false;
}

void Astar::Render_Board(HDC hdc,RECT rc)
{
	
	for (int i = 1; i < LINE_COUNT; i++)
	{
		for (int j = 1; j < LINE_COUNT; j++)
		{
			/*가로줄*/
			MoveToEx(hdc, 0, (rc.bottom / LINE_COUNT)*i, NULL);
			LineTo(hdc, rc.right, (rc.bottom / LINE_COUNT)*i);

			/*세로줄*/
			MoveToEx(hdc, (rc.right / LINE_COUNT)*i, 0, NULL);
			LineTo(hdc, (rc.right / LINE_COUNT)*i, rc.bottom);
		}
	}


	//MoveToEx(hdc, x, y, lpPoint)            라인(선) 시작
	//LineTo(hdc, xEnd, yEnd)                  라인(선) 끝
}

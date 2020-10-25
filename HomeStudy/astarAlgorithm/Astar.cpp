#include "stdafx.h"



Astar::Astar()
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
	WndProc(hWnd,message,wParam,lParam);

}

void Astar::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}


void Astar::Render(HWND hWnd, HDC hdc)
{
	Rectangle(hdc,0, 0, 100, 100);


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
		if (distance > BLOCKSIZE)
			return false;
		return true;
	}

	return false;
}

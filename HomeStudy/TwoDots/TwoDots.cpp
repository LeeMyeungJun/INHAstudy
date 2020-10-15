// TwoDots.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include <windows.h>

using namespace std;


enum DIRECTION
{
	LEFT = 0, TOP = 1, RIGHT = 2, BOTTOM = 3, END = 4
};

struct ST_POINT
{
	int x , y;
	bool bCheck;
	ST_POINT()
		:x(0)
		,y(0)
		,bCheck(false)
	{
		
	}

	
};

//_g
ST_POINT g_Node[16];

int g_Board[4][4] = {
	{ 3,2,3,2 },
	{ 2,1,1,2 },
	{ 1,1,2,1 },
	{ 4,1,1,1 } };


ostream& operator<<(ostream& os, const ST_POINT& pos) {
	os << '[' << pos.x << " , " << pos.y << ']';
	return os;
}

void PrintBoard(int lentgth)
{

	cout << "Node : ";
	for (int i = lentgth; i >= 0; i--)
	{
		cout << g_Node[i] << "  ";
	}

	cout << endl << "Length : " << lentgth + 1 << endl;
}
//>>:Front Declare
void ExamineBoard(DIRECTION _Direction, int _Length, ST_POINT _Position);

bool ExamineDirection(DIRECTION _Direction, ST_POINT _Position);

DIRECTION ChangeDirection(DIRECTION _Direction);

void MovePosition(DIRECTION& _Direction ,ST_POINT _Position);
//<<:




int main()
{
	int iLength = 0;
	ST_POINT ptPosition;

	ExamineBoard(DIRECTION::LEFT,iLength, ptPosition);
	
	PrintBoard(iLength);
    return 0;
}


void ExamineBoard(DIRECTION _Direction, int _Length, ST_POINT _Position)
{
	if(!ExamineDirection(_Direction,_Position))
	{
		//조사할곳이없다면 .
		_Direction = ChangeDirection(_Direction);
		
		if (_Direction == DIRECTION::END)
			return;
		else
			ExamineBoard(_Direction, _Length, _Position);
	}
	else
	{
		MovePosition(_Direction, _Position);
	}

	int a = 0;
}

bool ExamineDirection(DIRECTION _Direction, ST_POINT _Position)
{
	//현재 숫자와 다른 숫자이거나, 조사했던 곳이거나 , 갈수가 없거나. false
	switch (_Direction)
	{
	case DIRECTION::LEFT:
		{
		if (_Position.x == 0)
			return false;


		}
		break;
	case DIRECTION::TOP:
		{
		if (_Position.y == 0)
			return false;
			
		}
		break;
	case DIRECTION::RIGHT:
		{
		if (_Position.x == 3)
			return false;
			
		}
		break;
	case DIRECTION::BOTTOM:
		{
		if (_Position.y == 3)
			return false;

			
		}
		break;
	}


	return true;
}

DIRECTION ChangeDirection(DIRECTION _Direction)
{
	switch (_Direction)
	{
	case DIRECTION::LEFT:
		return _Direction = DIRECTION::TOP;
	case DIRECTION::TOP:
		return _Direction = DIRECTION::RIGHT;
	case DIRECTION::RIGHT:
		return _Direction = DIRECTION::BOTTOM;
	case DIRECTION::BOTTOM:
		return _Direction = DIRECTION::END;
	}

}


void MovePosition(DIRECTION& _Direction, ST_POINT _Position)
{
	switch (_Direction)
	{
	case DIRECTION::LEFT:
	{
		_Position.x--;
	}
	break;
	case DIRECTION::TOP:
	{
		_Position.y--;
	}
	break;
	case DIRECTION::RIGHT:
	{
		_Position.x++;
	}
	break;
	case DIRECTION::BOTTOM:
	{
		_Position.y++;
	}
	break;
	}

	return;
}
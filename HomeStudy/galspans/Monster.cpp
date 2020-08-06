#include "stdafx.h"
#include "Monster.h"

Monster::Monster(int x, int y) :speed(SPEED_ONE), bDead(false), Direction(rand() % 8), ptMonster_Position({x,y}), ptTemp_Position({ x,y })
{
	
}
Monster::~Monster()
{
}

void Monster::setSpeed(int speed)
{
	this->speed = speed;
}

void Monster::setPosition(POINT pt)
{
	ptMonster_Position.x = pt.x;
	ptMonster_Position.y = pt.y;
}

void Monster::ChangeDirection()
{
	switch (this->Direction)
	{
	case DIR_LT:
	{
		this->Direction = 7;
	}
	break;
	case DIR_T:
	{
		this->Direction = 6;
	}
	break;
	case DIR_RT:
	{
		this->Direction = 5;
	}
	break;
	case DIR_L:
	{
		this->Direction = 4;
	}
	break;
	case DIR_R:
	{
		this->Direction = 3;
	}					  
	break;				  
	case DIR_LB:		  
	{					  
		this->Direction = 2;
	}					  
	break;				  
	case DIR_B:			  
	{					  
		this->Direction = 1;
	}					  
	break;				  
	case DIR_RB:		  
	{					  
		this->Direction = 0;
	}
	break;
	}
}

void Monster::setDirection(int dir)
{
	this->Direction = dir;
}

int Monster::getDirection()
{
	return Direction;
}

void Monster::setDead(bool bflag)
{
	this->bDead = bflag;
}

bool Monster::getDead()
{
	return bDead;
}

int Monster::getSpeed()
{
	return speed;
}

POINT Monster::getPosition()
{
	return ptMonster_Position;
}


void Monster::ObjectCollide(vector<Monster*> enemy)
{
	for (Monster *i : enemy)
	{
		if (Collide(this->getPosition(), i->getPosition()))
		{
			swap(this->Direction, i->Direction);
		}
	}
}

bool Monster::Collide(POINT Object,POINT OtherObject)
{
	double dLength = (double)sqrt(pow(Object.x - OtherObject.x, 2) + pow(Object.y - OtherObject.y, 2));

	if (MONSTER_SIZE*2 > dLength) //충돌
	{
		return true;
	}

	return false;
}

void Monster::Update()
{
	Move();
}

void Monster::Render(HDC hdc)
{
	Ellipse(hdc, ptMonster_Position.x - MONSTER_SIZE, ptMonster_Position.y - MONSTER_SIZE, ptMonster_Position.x + MONSTER_SIZE, ptMonster_Position.y + MONSTER_SIZE);
}

void Monster::reflection(POINT pt)
{
	
	if (pt.x <= 0 || pt.x >= 880 ||pt.y <= 0 || pt.y >= 760)
	{
		ChangeDirection();
	}

}

/*
가로 : 880  세로 :760
0  1  2
3  M  4
5  6  7
*/

void Monster::Move()
{
	POINT ptTemp;

	ptTemp = getPosition();
	//ptTemp.x += speed;
	//ptTemp.y += speed;
	//setPosition({ ptTemp.x ,ptTemp.y});


	switch (Direction)
	{
	case DIR_LT:
		{
			ptTemp.x -= speed;
			ptTemp.y -= speed;
		}
		break;
	case DIR_T:
		{
			ptTemp.y -= speed;
		}
		break;
	case DIR_RT:
		{
			ptTemp.x += speed;
			ptTemp.y -= speed;
		}
		break;
	case DIR_L:
		{
			ptTemp.x -= speed;
		}
		break;
	case DIR_R:
		{
			ptTemp.x += speed;
		}
		break;
	case DIR_LB:
		{
			ptTemp.x -= speed;
			ptTemp.y += speed;
		}
		break;
	case DIR_B:
		{
			ptTemp.y += speed;
		}
		break;
	case DIR_RB:
		{
			ptTemp.x += speed;
			ptTemp.y += speed;
		}
		break;
	}

	setPosition({ ptTemp.x ,ptTemp.y });

	reflection(ptTemp);
}

void Monster::Init()
{
	setPosition(ptTemp_Position);
}

void Monster::Free()
{
}

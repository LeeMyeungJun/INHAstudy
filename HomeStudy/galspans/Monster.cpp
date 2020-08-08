#include "stdafx.h"
#include "Monster.h"

Monster::Monster(int x, int y) :speed(10), bDead(false), Direction(rand() % 8), ptMonster_Position({x,y}), ptTemp_Position({ x,y }), iTimeCheck(0)
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


void Monster::PolygonCollide(int side)
{
	switch (side)
	{
	case SIDE_LEFT:
		switch (this->Direction)
		{
		case DIR_RT:
			this->Direction = DIR_LT;
			break;
		case DIR_R:
			this->Direction = DIR_L;
			break;
		case DIR_RB:
			this->Direction = DIR_LB;
			break;

		}
		break;
	case SIDE_RIGHT:
		switch (this->Direction)
		{
		case DIR_LT:
			this->Direction = DIR_RT;
			break;
		case DIR_L:
			this->Direction = DIR_R;
			break;
		case DIR_LB:
			this->Direction = DIR_RB;
			break;
		}
		break;
	case SIDE_TOP:
		switch (this->Direction)
		{
		case DIR_LB:
			this->Direction = DIR_LT;
			break;
		case DIR_B:
			this->Direction = DIR_T;
			break;
		case DIR_RB:
			this->Direction = DIR_RT;
			break;
		}
		break;
	case SIDE_BOTTOM:
		switch (this->Direction)
		{
		case DIR_LT:
			this->Direction = DIR_LB;
			break;
		case DIR_T:
			this->Direction = DIR_B;
			break;
		case DIR_RT:
			this->Direction = DIR_RB;
			break;
		}
		break;

	}
}

void Monster::TimeCheck()
{
	POINT pt = getPosition();

	if (pt.x > 440)
	{
		setPosition({ pt.x - 30,pt.y });
	}
	else if (pt.x < 440)
	{
		setPosition({ pt.x + 30,pt.y });
	}

	if (pt.y > 380)
	{
		setPosition({ pt.x,pt.y -30});
	}
	else if (pt.y < 380)
	{
		setPosition({ pt.x ,pt.y + 30 });
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
		iTimeCheck++;
		return true;
	}

	return false;
}

void Monster::Update()
{
	Move();

	if (iTimeCheck > 5)
	{
		TimeCheck();
	}

}

void Monster::Render(HDC hdc)
{
	Ellipse(hdc, ptMonster_Position.x - MONSTER_SIZE, ptMonster_Position.y - MONSTER_SIZE, ptMonster_Position.x + MONSTER_SIZE, ptMonster_Position.y + MONSTER_SIZE);
}

void Monster::reflection(POINT pt)
{
	
	if (pt.x <= 0 || pt.x >= 880 ||pt.y <= 0 || pt.y >= 760)
	{
		iTimeCheck++;
		POINT pt = getPosition();
		//if (pt.x <= 0 || pt.x >= 880 || pt.y <= 0 || pt.y >= 760)
		switch (this->Direction)
		{
		case DIR_LT:
		{
			if(pt.x <=0)
				this->Direction = DIR_RT;
			else if(pt.y<= 0)
				this->Direction = DIR_LB;
		}
		break;
		case DIR_T:
		{
			this->Direction = DIR_B;
		}
		break;
		case DIR_RT:
		{
			if (pt.x >= 880)
				this->Direction = DIR_LT;
			else if (pt.y <= 0)
				this->Direction = DIR_RB;
		}
		break;
		case DIR_L:
		{
			this->Direction = DIR_R;
		}
		break;
		case DIR_R:
		{
			this->Direction = DIR_L;
		}
		break;
		case DIR_LB:
		{
			if (pt.x <= 0)
				this->Direction = DIR_RB;
			else if (pt.y >= 760)
				this->Direction = DIR_LT;
		}
		break;
		case DIR_B:
		{
			this->Direction = DIR_T;
		}
		break;
		case DIR_RB:
		{
			if (pt.x >= 880)
				this->Direction = DIR_LB;
			else if (pt.y >= 760)
				this->Direction = DIR_RT;
		}
		break;
		}
	}
	else
	{
		iTimeCheck = 0;
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

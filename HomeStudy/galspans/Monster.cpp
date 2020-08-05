#include "stdafx.h"


Monster::Monster(int x,int y) :speed(SPEED_ONE) , bDead(false)
{
	setPosition({ x,y });
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

int Monster::getSpeed()
{
	return 0;
}

POINT Monster::getPosition()
{
	return ptMonster_Position;
}

void Monster::MonsterPatternUp()
{
	switch (speed)
	{
	case SPEED_ONE:
		speed = SPEED_TWO;
		break;
	case SPEED_TWO:
		speed = SPEED_THREE;
		break;
	default:
		break;
	}
}

void Monster::Update()
{
	reflection();
	Move();
}

void Monster::Render(HDC hdc)
{
	Ellipse(hdc, ptMonster_Position.x - MONSTER_SIZE, ptMonster_Position.y - MONSTER_SIZE, ptMonster_Position.x + MONSTER_SIZE, ptMonster_Position.y + MONSTER_SIZE);
}

void Monster::reflection()
{

}

void Monster::Move()
{
	POINT ptTemp;

	ptTemp = getPosition();
	ptTemp.x += speed;
	ptTemp.y += speed;
	setPosition({ ptTemp.x ,ptTemp.y});
}

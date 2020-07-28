#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "Rect.h"



class PlayerBullet;
class Rect;

const int downSpeed = 15;


class Monster :public GameAdmin
{

public:
	int		monster_id;
	double  monster_hp;
	int		PositionX;
	int		PositionY;
	bool	monster_Flag;
	RECT	rcMonster;
	int		spwanTime;

	virtual void update(vector<Rect*> rect);

	void setMonster_false_Flag() { monster_Flag = false; }

	virtual void Draw(HDC hdc)
	{
		if (monster_Flag) {
			Rectangle(hdc, PositionX * 100, PositionY, (1 + PositionX) * 100, PositionY + 100);
		}
	
	}


	Monster(int i, int rand) :PositionY(101), PositionX(rand), monster_id(i), spwanTime(0)
	{
		monster_hp = manager->monster_hp;
	}

};
#pragma once
#include "GameObject.h"
#include "stdafx.h"
#include "Monster.h"


//class PlayerBullet;


class Rect :public GameAdmin
{
	bool CollisionRect(RECT rectBullet, RECT rectMonster)
	{
		bool bVertical   = false;
		bool bHorizontal = false;

		if (rectBullet.left <rectMonster.right && rectBullet.right > rectMonster.left)
		{
			bHorizontal = true;
		}

		if (rectBullet.top < rectMonster.bottom && rectBullet.bottom > rectMonster.top)
		{
			bVertical = true;
		}

		if (bVertical && bHorizontal)
		{
			rectBullet.left = 0;
			rectBullet.right = 0;
			rectBullet.top = 0;
			rectBullet.bottom = 0;

			return true;
		}
		return false;
	}


public:
	int iRect_id;
	double rect_hp;
	RECT rcRect;
	bool FlagRect;

	
	virtual void update(vector<Monster*> monster);

	virtual void Draw(HDC hdc)
	{
		if (FlagRect)
		{
			Rectangle(hdc, iRect_id * 100, 850, (1 + iRect_id) * 100, 950);
			rcRect.left = iRect_id * 100;
			rcRect.top = 850;
			rcRect.right = (1 + iRect_id) * 100;
			rcRect.bottom = 950;
		}
		else
		{
			rcRect.left = 0;
			rcRect.top = 0;
			rcRect.right = 0;
			rcRect.bottom = 0;
		}
	}

	Rect(int i) :iRect_id(i), FlagRect(true)
	{
		rect_hp = manager->rect_hp;
	}
};





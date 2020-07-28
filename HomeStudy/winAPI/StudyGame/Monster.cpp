#include "stdafx.h"
#include "Monster.h"

void Monster::update(vector<Rect*> rect)
{
	if (!monster_Flag)
	{

		spwanTime++;
		if (spwanTime >= 300)
		{
	 		monster_Flag = true;
			PositionY = 101;

			vector<int> temp;
			for (Rect* i : rect)
			{
				if (i->FlagRect)
				{
					temp.push_back(i->iRect_id);
				}
			}

			PositionX = temp[rand() % temp.size()];
			temp.clear();

			spwanTime = 0;
			
		}

	}

	if(monster_Flag)
	{
		//내려가는속도
		if (PositionY >= 1000)
		{
			monster_Flag = false;

		}
		rcMonster.left = PositionX * 100;
		rcMonster.top = PositionY;
		rcMonster.right = (1 + PositionX) * 100;
		rcMonster.bottom = PositionY + 100;
		PositionY += downSpeed;
	}

		

	
	
	

}

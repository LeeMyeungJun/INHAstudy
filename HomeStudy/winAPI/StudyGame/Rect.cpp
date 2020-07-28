#include "stdafx.h"
#include "Rect.h"

void Rect::update(vector<Monster*> monster)
{
	for (Monster *i : monster)
	{

		if (CollisionRect(rcRect, i->rcMonster))
		{
			FlagRect = false;
			i->setMonster_false_Flag();
		}

	}
}

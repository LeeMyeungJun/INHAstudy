#include "stdafx.h"



PlayerManager::PlayerManager():slope(0)
{
	ptPosition = { 0 , 0 };
}


PlayerManager::~PlayerManager()
{
	
}

void PlayerManager::DrawPlayerCharacter(HDC hdc)
{
	Ellipse(hdc, ptPosition.x - CHARACTER_SIZE, ptPosition.y - CHARACTER_SIZE, ptPosition.x + CHARACTER_SIZE, ptPosition.y + CHARACTER_SIZE);
}



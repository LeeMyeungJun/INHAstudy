#include "stdafx.h"



PlayerManager::PlayerManager()
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



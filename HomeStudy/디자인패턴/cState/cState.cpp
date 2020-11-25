// cState.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Player.h"


int main() {
	Player* player = new Player;

	player->Setup();
	player->Update();

	
	
	return 0;
}

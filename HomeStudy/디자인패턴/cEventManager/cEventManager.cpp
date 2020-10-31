#include "stdafx.h"
#include "Audio.h"
#include "Achievements.h"

int main()
{
	Achievements* achievements = new Achievements; 
	Audio* audio = new Audio; 
	
	
	g_EventManager->Attach(achievements);
	g_EventManager->Attach(audio);

	g_EventManager->EventNumber(0);
	g_EventManager->EventNumber(2);

	delete achievements;
	delete audio;

	
    return 0;
}



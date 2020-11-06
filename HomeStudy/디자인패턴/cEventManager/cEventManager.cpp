#include "stdafx.h"
#include "Audio.h"
#include "Achievements.h"

int main()
{
	Achievements* achievements = new Achievements; 
	Audio* audio = new Audio; 
	
	
	g_EventManager->Attach(achievements, achievements);
	g_EventManager->Attach(audio, achievements);

	g_EventManager->EventNumber(achievements,0);
	g_EventManager->EventNumber(audio,2);

	delete achievements;
	delete audio;

	
    return 0;
}



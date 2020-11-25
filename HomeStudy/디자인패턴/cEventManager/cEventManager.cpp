#include "stdafx.h"
#include "Audio.h"
#include "Achievements.h"

int main()
{
	Achievements* achievements = new Achievements; 
	Audio* audio = new Audio; 
	
	
	g_EventManager->Attach(EEvent::E_ATTACK,audio);
	g_EventManager->Attach(EEvent::E_SLEEP, audio);
	g_EventManager->Attach(EEvent::E_ATTACK, achievements);
	ST_AttackEvent data;
	data.name = "asd";
	data.age = 20;
	g_EventManager->EventCall(EEvent::E_ATTACK, (void*)&data);
	
	g_EventManager->Detach(EEvent::E_ATTACK,achievements);
	g_EventManager->EventCall(EEvent::E_ATTACK, (void*)&data);


	
	delete achievements;
	delete audio;

	
    return 0;
}



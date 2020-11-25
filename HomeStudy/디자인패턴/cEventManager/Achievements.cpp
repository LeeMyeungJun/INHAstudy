#include "stdafx.h"
#include "Achievements.h"


Achievements::Achievements()
{
}


Achievements::~Achievements()
{
}

void Achievements::OnEvent(EEvent eEvent, void* _value)
{
	switch (eEvent)
	{
	case EEvent::E_ATTACK:
		std::cout << "공격 업적 달성" << std::endl;
		break;
	case EEvent::E_NONE:
		std::cout << "기본 업적 달성" << std::endl;
		break;
	case EEvent::E_SLEEP:
		std::cout << "수면 업적 달성" << std::endl;
		break;
	default:
		std::cout << "달성한 업적이 없습니다." << std::endl;
		break;
	}
}

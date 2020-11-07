#include "stdafx.h"
#include "Audio.h"


Audio::Audio()
{
}


Audio::~Audio()
{
}

void Audio::OnEvent(EEvent eEvent, void* _value)
{
	switch (eEvent)
	{
	case EEvent::E_ATTACK:
		{
		ST_AttackEvent *data = static_cast<ST_AttackEvent*>(_value);
		std::cout << "오디오:(공격 이벤트중)" << std::endl;
		}
		break;
	case EEvent::E_NONE:
		std::cout << "오디오:(기본값)" << std::endl;
		break;
	case EEvent::E_SLEEP:
		std::cout << "오디오:(수면중)" << std::endl;
		break;
	default:
		std::cout << "오디오:(달성한 업적이없습니다.)" << std::endl;
		break;
	}
}

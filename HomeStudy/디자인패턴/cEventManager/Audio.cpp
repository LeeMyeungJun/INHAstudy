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
		std::cout << "�����:(���� �̺�Ʈ��)" << std::endl;
		}
		break;
	case EEvent::E_NONE:
		std::cout << "�����:(�⺻��)" << std::endl;
		break;
	case EEvent::E_SLEEP:
		std::cout << "�����:(������)" << std::endl;
		break;
	default:
		std::cout << "�����:(�޼��� �����̾����ϴ�.)" << std::endl;
		break;
	}
}

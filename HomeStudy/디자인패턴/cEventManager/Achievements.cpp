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
		std::cout << "���� ���� �޼�" << std::endl;
		break;
	case EEvent::E_NONE:
		std::cout << "�⺻ ���� �޼�" << std::endl;
		break;
	case EEvent::E_SLEEP:
		std::cout << "���� ���� �޼�" << std::endl;
		break;
	default:
		std::cout << "�޼��� ������ �����ϴ�." << std::endl;
		break;
	}
}

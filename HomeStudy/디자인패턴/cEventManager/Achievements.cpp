#include "stdafx.h"
#include "Achievements.h"


Achievements::Achievements()
{
}


Achievements::~Achievements()
{
}

void Achievements::Update(Observer* _subTract, const int eventNumver)
{
	switch (eventNumver)
	{
	case 0:
		std::cout << "���� 100���� ��� ����"<<std::endl;
		break;
	case 1:
		std::cout << "���� ������ ���� ����" << std::endl;
		break;
	case 2:
		std::cout << "���� ������ �Ǹ� ����" << std::endl;
		break;
		default:
			std::cout << "�޼��� �����̾����ϴ�." << std::endl;
			break;
	}
}

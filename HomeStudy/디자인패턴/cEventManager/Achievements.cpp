#include "stdafx.h"
#include "Achievements.h"


Achievements::Achievements()
{
}


Achievements::~Achievements()
{
}

void Achievements::Update(const int EventNumver)
{
	switch (EventNumver)
	{
	case 0:
		std::cout << "몬스터 100마리 사냥 성공"<<std::endl;
		break;
	case 1:
		std::cout << "상점 아이템 구매 성공" << std::endl;
		break;
	case 2:
		std::cout << "상점 아이템 판매 성공" << std::endl;
		break;
		default:
			std::cout << "달성한 업적이없습니다." << std::endl;
			break;
	}
}

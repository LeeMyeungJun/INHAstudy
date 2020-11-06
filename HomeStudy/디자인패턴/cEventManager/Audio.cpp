#include "stdafx.h"
#include "Audio.h"


Audio::Audio()
{
}


Audio::~Audio()
{
}

void Audio::Update(Observer* _subTract, const int eventNumver)
{
	switch (eventNumver)
	{
	case 0:
		std::cout << "오디오:(몬스터 100마리 사냥 성공)" << std::endl;
		break;
	case 1:
		std::cout << "오디오:(상점 아이템 구매 성공)" << std::endl;
		break;
	case 2:
		std::cout << "오디오:상점 아이템 판매 성공)" << std::endl;
		break;
	default:
		std::cout << "오디오:(달성한 업적이없습니다.)" << std::endl;
		break;
	}
}

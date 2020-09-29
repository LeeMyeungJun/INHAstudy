#include "stdafx.h"
#include "cAnimation.h"


cAnimation::cAnimation()
{
}


cAnimation::~cAnimation()
{
}

void cAnimation::Setup(D3DXVECTOR3* player_body)
{
	//player_body_ = player_body;
}

void cAnimation::Setup(vector<D3DXVECTOR3*>& parts)
{
	parts_ = &parts;
}

void cAnimation::Update()
{
	AnimaitionWalk();
}

void cAnimation::AnimaitionWalk()
{
	(*parts_)[LEFT_LEG]->x = 40;
	(*parts_)[LEFT_HAND]->x = 40;

	//player_body_[1].x = 40;
	/*
	m_PlayerBody[RIGHT_LEG]  = D3DXVECTOR3(0, 0, 0);
	m_PlayerBody[LEFT_HAND]  = D3DXVECTOR3(40, 0, 0);
	m_PlayerBody[RIGHT_HAND] = D3DXVECTOR3(0, 0, 0);*/


}

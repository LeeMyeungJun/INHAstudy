#include "stdafx.h"
#include "Player.h"
#include "JumpState.h"
#include "AttackState.h"
#include "RunState.h"


Player::Player()
	: m_pState(NULL)
	, m_pJumpState(NULL)
	, m_pAttackState(NULL)
	, m_pRunState(NULL)
{
}


Player::~Player()
{
	delete m_pRunState;
	delete m_pAttackState;
	delete m_pJumpState;
}

void Player::Update()
{
	m_pState->Update();
	
	m_pState = m_pRunState;
	m_pState->Update();
	
	m_pState = m_pJumpState;
	m_pState->Update();
	
	m_pState = m_pAttackState;
	m_pState->Update();
}

void Player::Setup()
{
	m_pJumpState = new JumpState;
	m_pAttackState = new AttackState;
	m_pRunState = new RunState;
	
	m_pState = m_pRunState;
}

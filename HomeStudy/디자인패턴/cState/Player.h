#pragma once
class State;
class JumpState;
class AttackState;
class RunState;


class Player
{

private:
	State*			m_pState;
	JumpState*		m_pJumpState;
	AttackState*	m_pAttackState;
	RunState*		m_pRunState;
	
public:
	Player();
	~Player();

	void Update();
	void Setup();
};


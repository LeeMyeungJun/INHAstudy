#pragma once
#include "cAnimation.h"
class cCubePC;
class cAnimation;

class cPlayer
{
private:
	vector<cCubePC*>		m_vParts;

	FLOAT					m_fRotY;
	D3DXVECTOR3				m_vDirection;
	D3DXVECTOR3				m_vPosition;

	cAnimation				m_Animation;
	D3DXVECTOR3*			m_PlayerBody[6];
	vector<D3DXVECTOR3*>	m_partsAnimaiton;

public:
	cPlayer();
	~cPlayer();

	void Setup();
	void Update();
	void Render();
	D3DXVECTOR3&      GetPosition();

	void Input();
	void InputProcess(char In);

};


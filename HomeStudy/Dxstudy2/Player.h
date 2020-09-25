#pragma once
class cCubePC;


class Player
{
public:
	Player();
	~Player();

private:
	FLOAT				m_fRotY;
	D3DXVECTOR3			m_vPosition;
	D3DXVECTOR3			m_vDirection;
	vector<cCubePC*>	m_vCubeVertexStorage;


public:
	void Setup();
	void Update();
	void Render();
	void Input();
	D3DXVECTOR3 GetPosition();
	
};


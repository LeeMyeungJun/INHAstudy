#pragma once
class cCubePC;

class cPlayer
{
private:
	vector<cCubePC*> m_character;
	D3DXVECTOR3		m_vPosition;
	D3DXVECTOR3		m_vDirection;
	D3DXMATRIXA16	m_worldMat;

	float			m_fRotY;
	
public:
	cPlayer();
	~cPlayer();

	void Setup();
	void Update();
	void KeyInput();
	void Render();

	D3DXVECTOR3&	GetPlayerPosition() { return m_vPosition; }
};


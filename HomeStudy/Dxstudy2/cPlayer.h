#pragma once
class cCubePC;

class cPlayer
{
private:
	vector<cCubePC*>		m_vParts;

	FLOAT					m_fRotY;
	D3DXVECTOR3				m_vDirection;
	D3DXVECTOR3				m_vPosition;
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


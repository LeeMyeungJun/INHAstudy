#pragma once
class cCubePC;

class cPlayer
{
private:
	float             m_fRotY;
	D3DXVECTOR3       m_vDirection;
	D3DXVECTOR3       m_vPosition;
	D3DXMATRIXA16     m_matWorld;
	D3DXMATRIXA16     m_matS;
	D3DXMATRIXA16     m_matR;
	D3DXMATRIXA16     m_matT;

	vector<cCubePC*> playerBody;
public:
	cPlayer();
	~cPlayer();

	void Setup();
	void Update();
	void Render();

public:
	D3DXVECTOR3&      GetPosition();
	
};


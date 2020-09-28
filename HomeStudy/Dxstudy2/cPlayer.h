#pragma once
<<<<<<< HEAD
class cCubePC;
=======
#include "cAnimation.h"
class cCubePC;
class cAnimation;
>>>>>>> 3e1ee1aadc6623cb81b24a7f83d252cef31695d3

class cPlayer
{
private:
<<<<<<< HEAD
	float             m_fRotY;
	D3DXVECTOR3       m_vDirection;
	D3DXVECTOR3       m_vPosition;
	D3DXMATRIXA16     m_matWorld;
	D3DXMATRIXA16     m_matS;
	D3DXMATRIXA16     m_matR;
	D3DXMATRIXA16     m_matT;

	vector<cCubePC*> playerBody;
=======
	vector<cCubePC*>		m_vParts;

	FLOAT					m_fRotY;
	D3DXVECTOR3				m_vDirection;
	D3DXVECTOR3				m_vPosition;

	cAnimation				m_Animation;
	D3DXVECTOR3*			m_PlayerBody[6];
	vector<D3DXVECTOR3*>	m_partsAnimaiton;

>>>>>>> 3e1ee1aadc6623cb81b24a7f83d252cef31695d3
public:
	cPlayer();
	~cPlayer();

	void Setup();
	void Update();
	void Render();
<<<<<<< HEAD

public:
	D3DXVECTOR3&      GetPosition();
	
=======
	D3DXVECTOR3&      GetPosition();

	void Input();
	void InputProcess(char In);

>>>>>>> 3e1ee1aadc6623cb81b24a7f83d252cef31695d3
};


#include "stdafx.h"
#include "Player.h"
#include "cCubePC.h"


Player::Player()
{

}

Player::~Player()
{

}

void Player::Setup()
{
	D3DXVECTOR3 s;
	D3DXVECTOR3 p;

	s = D3DXVECTOR3(0.6f, 0.6f, 0.6f);
	p = D3DXVECTOR3(0, 0.6f, 0);
	cCubePC* head = new cCubePC;
	head->setScale(s);
	head->Setup(p);
	m_vPosition = D3DXVECTOR3(0, 0, 0);
	m_vDirection = D3DXVECTOR3(0, 0, 1);
	m_fRotY = 0.0f;



	m_vCubeVertexStorage.push_back(head);

}

void Player::Update()
{
	Input();

	for each(auto p in m_vCubeVertexStorage)
	{
		p->Update();
	}

}

void Player::Render()
{

	D3DXMATRIXA16 matR, matT, m_matWorld;
	D3DXMatrixRotationY(&matR, m_fRotY);

	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	m_matWorld = matR * matT;

	
	for each(auto p in m_vCubeVertexStorage)
	{
		p->Render(m_matWorld);
	}
}

void Player::Input()
{
	if (GetKeyState('A') & 0X8000)
	{
		m_fRotY -= 0.1f;
	}
	if (GetKeyState('D') & 0X8000)
	{
		m_fRotY += 0.1f;
	}
	if (GetKeyState('W') & 0X8000)
	{
		m_vPosition += (m_vDirection * 0.1f);
	}
	if (GetKeyState('S') & 0X8000)
	{
		m_vPosition -= (m_vDirection * 0.1f);
	}
}

D3DXVECTOR3& Player::GetPosition()
{
	return m_vPosition;
}
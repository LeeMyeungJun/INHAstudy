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
	m_vPosition = D3DXVECTOR3(0, 0, 0);
	m_vDirection = D3DXVECTOR3(0, 0, 1);
	m_fRotY = 0.0f;

	
	D3DXVECTOR3 s;
	D3DXVECTOR3 p;

	s = D3DXVECTOR3(0.6f, 0.6f, 0.6f);
	p = D3DXVECTOR3(0, 2.8f, 0);
	cCubePC* head = new cCubePC;
	head->setScale(s);
	head->Setup(p);

	m_vCubeVertexStorage.push_back(head);
	
	
	s = D3DXVECTOR3(0.6f, 0.7f, 0.3f);
	p = D3DXVECTOR3(0, 1.5f, 0);
	cCubePC* body = new cCubePC;
	body->setScale(s);
	body->Setup(p);

	m_vCubeVertexStorage.push_back(body);
	

	
	
	s = D3DXVECTOR3(0.3f, 0.7f, 0.3f);
	p = D3DXVECTOR3(0.7f, 1.5f, 0);
	cCubePC* rightArm = new cCubePC;
	rightArm->setScale(s);
	rightArm->Setup(p);

	m_vCubeVertexStorage.push_back(rightArm);

	s = D3DXVECTOR3(0.3f, 0.7f, 0.3f);
	p = D3DXVECTOR3(-0.7f, 1.5f, 0);
	cCubePC* leftArm = new cCubePC;
	leftArm->setScale(s);
	leftArm->Setup(p);

	m_vCubeVertexStorage.push_back(leftArm);
	

	s = D3DXVECTOR3(0.3f, 0.4f, 0.3f);
	p = D3DXVECTOR3(0.3f, 0.4f, 0);
	cCubePC* rightLeg = new cCubePC;
	rightLeg->setScale(s);
	rightLeg->Setup(p);

	m_vCubeVertexStorage.push_back(rightLeg);

	s = D3DXVECTOR3(0.3f, 0.4f, 0.3f);
	p = D3DXVECTOR3(-0.3f, 0.4f, 0);
	cCubePC* leftLeg = new cCubePC;
	leftLeg->setScale(s);
	leftLeg->Setup(p);

	m_vCubeVertexStorage.push_back(leftLeg);

}

void Player::Update()
{
	Input();
	D3DXMATRIXA16 matS ,matR, matT, m_matWorld;


	D3DXMatrixScaling(&matS, 0.5f, 0.5f, 0.5f);
	
	D3DXMatrixRotationY(&matR, m_fRotY);
	m_vDirection = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
	
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	m_matWorld = matS *matR * matT;
	

	
	for each(auto p in m_vCubeVertexStorage)
	{
		p->Update(m_matWorld, m_fRotY);
	}

}

void Player::Render()
{
	for each(auto p in m_vCubeVertexStorage)
	{
		p->Render();
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
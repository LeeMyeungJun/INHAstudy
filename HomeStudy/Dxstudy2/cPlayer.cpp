#include "stdafx.h"
#include "cPlayer.h"
#include "cCubePC.h"
#include "cAnimation.h"

cPlayer::cPlayer():m_fRotY(0)
{
	m_vPosition = D3DXVECTOR3(0, 0, 0);
	m_vDirection = D3DXVECTOR3(0, 0, 1);

}


cPlayer::~cPlayer()
{
}

void cPlayer::Setup()
{
	D3DXVECTOR3 p,s;

	cCubePC* body = new cCubePC;
	p = D3DXVECTOR3(0, 0.0f, 0);
	s = D3DXVECTOR3(0.6f, 0.7f, 0.3f);
	body->Setup(p, s);
	m_vParts.push_back(body);
	m_PlayerBody[0] = &(body->getRot());

	cCubePC* leftLeg = new cCubePC;
	p = D3DXVECTOR3(0.3f, -1.1f, 0);
	s = D3DXVECTOR3(0.3f, 0.4f, 0.3f);
	leftLeg->Setup(p, s);
	m_vParts.push_back(leftLeg);
	m_PlayerBody[1] = &(leftLeg->getRot());

	cCubePC* rightLeg = new cCubePC;
	p = D3DXVECTOR3(-0.3f, -1.1f, 0);
	s = D3DXVECTOR3(0.3f, 0.4f, 0.3f);
	rightLeg->Setup(p, s);
	m_vParts.push_back(rightLeg);
	m_PlayerBody[2] = &rightLeg->getRot();

	cCubePC* leftHand = new cCubePC;
	p = D3DXVECTOR3(-0.9f, 0, 0);
	s = D3DXVECTOR3(0.3f, 0.7f, 0.3f);
	leftHand->Setup(p, s);
	m_vParts.push_back(leftHand);
	m_PlayerBody[3] = &leftHand->getRot();

	cCubePC* rightHand = new cCubePC;
	p = D3DXVECTOR3(0.9f, 0, 0);
	s = D3DXVECTOR3(0.3f, 0.7f, 0.3f);
	rightHand->Setup(p, s);
	m_vParts.push_back(rightHand);
	m_PlayerBody[4] = &rightHand->getRot();

	cCubePC* head = new cCubePC;
	p = D3DXVECTOR3(0,1.3f,0);
	s = D3DXVECTOR3(0.6f, 0.6f, 0.6f);
	head->Setup(p,s);
	m_vParts.push_back(head);
	m_PlayerBody[5] = &(head->getRot());

	for (size_t i = 0; i < 6; i++)
	{
		m_partsAnimaiton.push_back(m_PlayerBody[i]);
	}

	m_Animation.Setup(m_partsAnimaiton);

	m_vPosition.y = 0.8f + 0.7f;
}

void cPlayer::Update()
{
	Input();
	D3DXMATRIXA16 matT ,matR, matWorld;
	D3DXQUATERNION quarRot;
	D3DXQuaternionIdentity(&quarRot);
	D3DXQuaternionRotationYawPitchRoll(&quarRot, m_fRotY, 0.0f, 0.0f);
	D3DXMatrixRotationQuaternion(&matR, &quarRot);

	/*D3DXMatrixRotationY(&matR, m_fRotY);*/

	m_vDirection = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	matWorld = matR *matT;

	m_Animation.Update();

	for each(auto p in m_vParts)
		p->Update(matWorld);

	
}

void cPlayer::Render()
{
	for each(auto p in m_vParts)
		p->Render();
}

D3DXVECTOR3 & cPlayer::GetPosition()
{
	return m_vPosition;
}

void cPlayer::Input()
{

	if (GetKeyState('A') & 0X8000)
	{
		InputProcess('A');
	}
	if (GetKeyState('D') & 0X8000)
	{
		InputProcess('D');
	}
	if (GetKeyState('W') & 0X8000)
	{
		InputProcess('W');
	}
	if (GetKeyState('S') & 0X8000)
	{
		InputProcess('S');
	}

}

void cPlayer::InputProcess(char In)
{
	switch (In)
	{
	case 'A':
		m_fRotY -= 0.1f;
		break;
	case 'D':
		m_fRotY += 0.1f;
		break;
	case 'W':
		m_vPosition += (m_vDirection * 0.1f);
		break;
	case 'S':
		m_vPosition -= (m_vDirection * 0.1f);
		break;
	}
}

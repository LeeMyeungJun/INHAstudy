#include "stdafx.h"
#include "cPlayer.h"
#include "cCubePC.h"

cPlayer::cPlayer()
{
	m_vPosition = D3DXVECTOR3(0, 0, 0);
	m_vDirection = D3DXVECTOR3(0, 0, 1);
	D3DXMatrixIdentity(&m_worldMat);
	m_fRotY = 0;
}

cPlayer::~cPlayer()
{
	
}

void cPlayer::Setup()
{
	cCubePC* body = new cCubePC;
	body = new cCubePC;	//몸통
	body->Setup();
	body->SetScale(0.2f, 0.3f, 0.1f);
	m_character.push_back(body);

	cCubePC* leftArm = new cCubePC;
	leftArm->Setup();
	leftArm->SetScale(0.1f, 0.3f, 0.1f);
	leftArm->SetPosition(D3DXVECTOR3(0.3f, 0, 0));
	m_character.push_back(leftArm);

	cCubePC* rightArm = new cCubePC;
	rightArm->Setup();
	rightArm->SetScale(0.1f, 0.3f, 0.1f);
	rightArm->SetPosition(D3DXVECTOR3(-0.3f, 0, 0));
	m_character.push_back(rightArm);

	cCubePC* leftLeg = new cCubePC;
	leftLeg->Setup();
	leftLeg->SetScale(0.1f, 0.3f, 0.1f);
	leftLeg->SetPosition(D3DXVECTOR3(-0.1f, -0.5f, 0));
	m_character.push_back(leftLeg);

	cCubePC* rightLeg = new cCubePC;
	rightLeg->Setup();
	rightLeg->SetScale(0.1f, 0.3f, 0.1f);
	rightLeg->SetPosition(D3DXVECTOR3(0.1f, -0.5f, 0));
	m_character.push_back(rightLeg);

	cCubePC* head = new cCubePC;
	head->Setup();
	head->SetScale(0.2f, 0.2f, 0.1f);
	head->SetPosition(D3DXVECTOR3(0, 0.5f, 0));
	m_character.push_back(head);
}

void cPlayer::Update()
{
	D3DXMATRIXA16	matR, matT;
	D3DXMatrixRotationY(&matR, m_fRotY);	//Y축으로 회전된 행렬 제작

	m_vDirection = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);	//벡터 라디안 회전
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);	//이동된 행렬 제작

	m_worldMat = matR * matT;
	
	D3DXMATRIXA16 parentMat = m_worldMat;
	for each(auto p in m_character)
		p->Update(parentMat);
}

void cPlayer::KeyInput()
{
	if (GetKeyState('A') & 0x8000)
		m_fRotY -= 0.1f;
	else if (GetKeyState('D') & 0x8000)
		m_fRotY += 0.1f;

	if (GetKeyState('W') & 0x8000)
		m_vPosition += (m_vDirection * 0.1f);	//회전된 방향따라 이동
	else if (GetKeyState('S') & 0x8000)
		m_vPosition -= (m_vDirection * 0.1f);
}

void cPlayer::Render()
{
	for each(auto p in m_character)
		p->Render();
}
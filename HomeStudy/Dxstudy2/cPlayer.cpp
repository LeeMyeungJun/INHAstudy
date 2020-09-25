#include "stdafx.h"
#include "cPlayer.h"
#include "cCubePC.h"


cPlayer::cPlayer():m_vDirection(0, 0, 1), m_vPosition(0, 0, 0), m_fRotY(0.0f)
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matS);
	D3DXMatrixIdentity(&m_matR);
	D3DXMatrixIdentity(&m_matT);
}


cPlayer::~cPlayer()
{
	
}

void cPlayer::Setup()
{

	
	D3DXVECTOR3 v;

	
	cCubePC* cHead = new cCubePC;
	cHead->Setup(0.6f, 0.6f, 0.6f);
	v = D3DXVECTOR3(0, 1.4f, 0);
	cHead->setPosition(v);
	playerBody.push_back(cHead);
	
	cCubePC* cBody = new cCubePC;
	cBody->Setup(0.6f, 0.7f, 0.3f);
	v = D3DXVECTOR3(0, 0.73f, 0);
	cBody->setPosition(v);
	playerBody.push_back(cBody);

	cCubePC* cRightArm = new cCubePC;
	cRightArm->Setup(0.3f, 0.7f, 0.3f);
	v = D3DXVECTOR3(0.48f, 0.73f, 0);
	cRightArm->setPosition(v);
	playerBody.push_back(cRightArm);

	cCubePC* cLeftArm = new cCubePC;
	cLeftArm->Setup(0.35f, 0.7f, 0.3f);
	v = D3DXVECTOR3(-0.48f, 0.73f, 0);
	cLeftArm->setPosition(v);
	playerBody.push_back(cLeftArm);

	cCubePC* cLeftLeg = new cCubePC;
	cLeftLeg->Setup(0.3f, 0.4f, 0.3f);
	v = D3DXVECTOR3(-0.15f, 0.2f, 0);
	cLeftLeg->setPosition(v);
	playerBody.push_back(cLeftLeg);

	cCubePC* cRightLeg = new cCubePC;
	cRightLeg->Setup(0.3f, 0.4f, 0.3f);
	v = D3DXVECTOR3(0.15f, 0.2f, 0);
	cRightLeg->setPosition(v);
	playerBody.push_back(cRightLeg);
	

	m_vPosition = cBody->GetPosition();
	
}

void cPlayer::Update()
{
		//m_Tmat = playerBody[1]->GetTmat();
		
		//D3DXMATRIXA16 rotYMat;
		//D3DXMatrixRotationY(&rotYMat, rotY);*/

		//for each(auto p in playerBody)
		//{
		//	//D3DXVECTOR3 newPos = p->GetPosition();
		//	//D3DXVec3TransformNormal(&newPos, &newPos, &rotYMat);
		//	//p->setPosition(newPos);

		//	p->setTmat(m_Tmat);
		//	p->Update();
		//}

	m_vPosition = playerBody[1]->GetPosition();
	float rotY = playerBody[1]->m_fRotY;
	
	D3DXMATRIXA16 matR, matT;
	D3DXMatrixRotationY(&matR, rotY);

	m_vDirection = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
	
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matR * matT;

	for each(auto p in playerBody)
	{
		p->Update(m_matWorld);
		//p->setTmat(m_Tmat);
	}
		
	
	
		
}

void cPlayer::Render()
{
	for each(auto p in playerBody)
		p->Render();
}

D3DXVECTOR3& cPlayer::GetPosition()
{
	return m_vPosition;
}


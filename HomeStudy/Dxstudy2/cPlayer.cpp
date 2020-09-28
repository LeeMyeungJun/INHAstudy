#include "stdafx.h"
#include "cPlayer.h"
#include "cCubePC.h"
<<<<<<< HEAD


cPlayer::cPlayer():m_vDirection(0, 0, 1), m_vPosition(0, 0, 0), m_fRotY(0.0f)
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matS);
	D3DXMatrixIdentity(&m_matR);
	D3DXMatrixIdentity(&m_matT);
=======
#include "cAnimation.h"

cPlayer::cPlayer():m_fRotY(0)
{
	m_vPosition = D3DXVECTOR3(0, 0, 0);
	m_vDirection = D3DXVECTOR3(0, 0, 1);

>>>>>>> 3e1ee1aadc6623cb81b24a7f83d252cef31695d3
}


cPlayer::~cPlayer()
{
<<<<<<< HEAD
	
=======
>>>>>>> 3e1ee1aadc6623cb81b24a7f83d252cef31695d3
}

void cPlayer::Setup()
{
<<<<<<< HEAD

	
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
	
=======
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
>>>>>>> 3e1ee1aadc6623cb81b24a7f83d252cef31695d3
}

void cPlayer::Update()
{
<<<<<<< HEAD
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
		
	
	
		
=======
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

	
>>>>>>> 3e1ee1aadc6623cb81b24a7f83d252cef31695d3
}

void cPlayer::Render()
{
<<<<<<< HEAD
	for each(auto p in playerBody)
		p->Render();
}

D3DXVECTOR3& cPlayer::GetPosition()
=======
	for each(auto p in m_vParts)
		p->Render();
}

D3DXVECTOR3 & cPlayer::GetPosition()
>>>>>>> 3e1ee1aadc6623cb81b24a7f83d252cef31695d3
{
	return m_vPosition;
}

<<<<<<< HEAD
=======
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
>>>>>>> 3e1ee1aadc6623cb81b24a7f83d252cef31695d3

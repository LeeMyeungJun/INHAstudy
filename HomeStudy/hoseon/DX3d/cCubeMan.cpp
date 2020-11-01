#include "stdafx.h"
#include "cCubeMan.h"

#include "cCubeNode.h"
#include "cBody.h"
#include "cLeftArm.h"
#include "cRightArm.h"
#include "cLeftLeg.h"
#include "cRightLeg.h"
#include "cHead.h"


cCubeMan::cCubeMan():m_pRoot(NULL)
{
	
}


cCubeMan::~cCubeMan()
{
	if(m_pRoot)
	{
		m_pRoot->Destroy();
	}
	SafeRelease(m_pPlayerTexture);
}

void cCubeMan::Setup()
{
	D3DXCreateTextureFromFile(g_pD3DDevice, L"images/jje.png", &m_pPlayerTexture);
	cCharacter::Setup();

	ZeroMemory(&m_stMt1, sizeof(D3DMATERIAL9));
	m_stMt1.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMt1.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMt1.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);

	cBody* pBody = new cBody;
	pBody->Setup();
	pBody->SetParentWorldTM(&m_matWorld);
	m_pRoot = pBody;

	cHead* pHead = new cHead;
	pHead->Setup();
	m_pRoot->AddChild(pHead);

	cLeftArm* pLArm = new cLeftArm;
	pLArm->Setup();
	pLArm->SetRotDeltaX(0.1f);
	m_pRoot->AddChild(pLArm);

	cRightArm* pRArm = new cRightArm;
	pRArm->Setup();
	pRArm->SetRotDeltaX(-0.1f);
	m_pRoot->AddChild(pRArm);

	cLeftLeg* pLLeg = new cLeftLeg;
	pLLeg->Setup();
	pLLeg->SetRotDeltaX(-0.1f);
	m_pRoot->AddChild(pLLeg);

	cRightLeg* pRLeg = new cRightLeg;
	pRLeg->Setup();
	pRLeg->SetRotDeltaX(0.1f);
	m_pRoot->AddChild(pRLeg);
}

void cCubeMan::Update(iMap* pMap)
{
	cCharacter::Update(pMap);
	if (m_pRoot)
		m_pRoot->Update();
}

void cCubeMan::Render()
{
	if(g_pD3DDevice)
	{
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
		g_pD3DDevice->SetMaterial(&m_stMt1);
		g_pD3DDevice->SetTexture(0, m_pPlayerTexture);

		D3DXMATRIXA16 matWorld;
		D3DXMatrixIdentity(&matWorld);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		if (m_pRoot)
			m_pRoot->Render();
		
		g_pD3DDevice->SetTexture(0, NULL);
	}
}

void cCubeMan::WalkHexa()
{
	m_vPosition += (m_vDirection * 0.05f);
	
	if(D3DXVec3Length(&(m_vPostPos - m_vPosition)) >= 5)
	{
		m_vPostPos = m_vPosition;
		SetRotY(m_fRotY - D3DXToRadian(60));
	}
}

void cCubeMan::WalkBezier()
{
	D3DXMATRIXA16	matR;
	m_vPosition += (m_vDirection * 0.05f);

	D3DXVECTOR3 vUp(0, 1, 0);
	D3DXVECTOR3 vAt(1, 0, 1);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixLookAtLH(&matR, &m_vPosition, &vAt, &vUp);
	D3DXMatrixTranspose(&matR, &matR);
}

void cCubeMan::SetPosition(D3DXVECTOR3 _vec)
{
	m_vPosition = _vec;
}

void cCubeMan::SetRotY(float _rot)
{
	m_fRotY = _rot;
}

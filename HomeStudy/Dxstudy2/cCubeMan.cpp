#include "stdafx.h"

#include "cBody.h"
#include "cLeftArm.h"
#include "cRightArm.h"
#include "cLeftLeg.h"
#include "cRightLeg.h"
#include "cHead.h"

#include "cCubeMan.h"



cCubeMan::cCubeMan()
	:m_pRoot(NULL)
{
}

cCubeMan::~cCubeMan()
{
	if (m_pRoot)
		m_pRoot->Destroy();

	SafeRelease(m_pTexture);
}

void cCubeMan::Setup()
{
	cCharacter::Setup();

	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
	D3DXCreateTextureFromFile(g_pD3DDvice, L"ddung.png", &m_pTexture);
	
	m_stMtl.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f,1.0f);
	m_stMtl.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtl.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);

	cBody*	pBody = new cBody;
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

void cCubeMan::Update()
{
	cCharacter::Update();
	if (m_pRoot)
		m_pRoot->Update();
}

void cCubeMan::Render()
{
	if(g_pD3DDvice)
	{
		g_pD3DDvice->SetRenderState(D3DRS_LIGHTING, true);
		g_pD3DDvice->SetMaterial(&m_stMtl);
		
		cCharacter::Render();

		D3DXMATRIXA16 matWorld;
		D3DXMatrixIdentity(&matWorld);

		g_pD3DDvice->SetTransform(D3DTS_WORLD, &matWorld); //월드에 텍스쳐를 적용
		g_pD3DDvice->SetTexture(0, m_pTexture);

		if(m_pRoot)
		{
			m_pRoot->Render();
		}
		g_pD3DDvice->SetTexture(0, NULL); //월드에 텍스쳐빼기
	}
}
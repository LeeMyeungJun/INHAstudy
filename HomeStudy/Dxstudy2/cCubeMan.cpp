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
	delete this;
}

void cCubeMan::Setup()
{
	cCharacter::Setup();

	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));

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
	m_pRoot->AddChild(pLArm);
	
	cRightArm* pRArm = new cRightArm;
	pRArm->Setup();
	m_pRoot->AddChild(pRArm);

	cLeftLeg* pLLeg = new cLeftLeg;
	pLLeg->Setup();
	m_pRoot->AddChild(pLLeg);

	cRightLeg* pRLeg = new cRightLeg;
	pRLeg->Setup();
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
		g_pD3DDvice->SetTransform(D3DTS_WORLD, &matWorld);
		if(m_pRoot)
		{
			m_pRoot->Render();
		}
	}
}


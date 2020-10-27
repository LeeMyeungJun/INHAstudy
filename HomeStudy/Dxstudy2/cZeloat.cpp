#include "stdafx.h"
#include "cZeloat.h"
#include "cSkinnedMesh.h"
#include "cOBB.h"


cZeloat::cZeloat()
	: m_pSkinnedMesh(NULL)
	, m_pCharacterController(NULL)
	, m_pOBB(NULL)
{
}


cZeloat::~cZeloat()
{
	SafeRelease(m_pCharacterController);
	SafeDelete(m_pSkinnedMesh);
	SafeDelete(m_pOBB);
	
}

void cZeloat::Setup()
{
	m_pSkinnedMesh = new cSkinnedMesh("Zealot", "zealot.x");
	m_pSkinnedMesh->SetRandomTrackPosition();

	m_pOBB = new cOBB;
	m_pOBB->Setup(m_pSkinnedMesh);
}

void cZeloat::Update(iMap* pMap)
{
	if (m_pCharacterController)
		m_pCharacterController->Update(pMap);

	if (m_pOBB)
		m_pOBB->Update(m_pCharacterController ? m_pCharacterController->GetTransform() : NULL); //없으면 버려

	
}

void cZeloat::Render(D3DCOLOR c)
{
	if (m_pCharacterController)
		m_pSkinnedMesh->SetTransform(m_pCharacterController->GetTransform());

	m_pSkinnedMesh->UpdateAndRender(); //별로구조가 안예쁜데? 너희들이 고쳐

	if (m_pOBB)
		m_pOBB->OBBBOX_Render(c);
}

cOBB* cZeloat::GetOBB()
{
	return m_pOBB;
}

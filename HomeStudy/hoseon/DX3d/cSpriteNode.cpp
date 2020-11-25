#include "stdafx.h"
#include "cSpriteNode.h"


cSpriteNode::cSpriteNode()
	:m_pParentWorldTM(NULL)
{
	D3DXMatrixIdentity(&m_matWorldTM);
}


cSpriteNode::~cSpriteNode()
{
}

void cSpriteNode::AddChild(cSpriteNode* pChild)
{
	pChild->m_pParentWorldTM = &m_matWorldTM;
	m_vecChild.push_back(pChild);
}

void cSpriteNode::Destroy()
{
}

void cSpriteNode::Setup()
{
	cSprite::Setup();
}

void cSpriteNode::Update()
{
	m_matWorldTM = matTranslation;
	
	if (m_pParentWorldTM)
	{
		m_matWorldTM *= *m_pParentWorldTM;
	}
	
	for each(auto p in m_vecChild)
	{
		p->Update();
	}
}

void cSpriteNode::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorldTM);
	cSprite::Render();
	for each(auto p in m_vecChild)
	{
		p->Render();
	}
}

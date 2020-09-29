#include "stdafx.h"
#include "cCubeNode.h"


cCubeNode::cCubeNode()
	:m_fRotDeltaX(0.0f)
	,m_pParentWorldTM(NULL)
	,m_vLocalPos(0,0,0)
{
	D3DXMatrixIdentity(&m_matLocalTM);
	D3DXMatrixIdentity(&m_matWorldTM);
	
}


cCubeNode::~cCubeNode()
{
}

void cCubeNode::AddChild(cCubeNode* pChild)
{
	pChild->m_pParentWorldTM = &m_matWorldTM;
	m_vecChild.push_back(pChild);
}

void cCubeNode::Destroy()
{
	for each(auto p in m_vecChild)
	{
		p->Destroy();
	}
	delete this;
}

void cCubeNode::Setup()
{
	cCubePNT::Setup();
}

void cCubeNode::Update()
{
	cCubePNT::Update();
	D3DXMATRIXA16 matR, matT;
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);

	D3DXMatrixTranslation(&matT, m_vLocalPos.x, m_vLocalPos.y, m_vLocalPos.z);
	m_matLocalTM = matR * matT;

	m_matWorldTM = m_matLocalTM;
	if(m_pParentWorldTM)
	{//몸통이아니라 팔이라면 
		m_matWorldTM *= *m_pParentWorldTM;
	}

	for each(auto p in m_vecChild)
	{
		p->Update();
	}
}

void cCubeNode::Render()
{
	g_pD3DDvice->SetTransform(D3DTS_WORLD, &m_matWorldTM);
	cCubePNT::Render();
	//자식들한테도 그리라해야함 몸통밖에없잖아
	for each(auto p in m_vecChild)
	{
		p->Render();
	}
}

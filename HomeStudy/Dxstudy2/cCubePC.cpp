#include "stdafx.h"
#include "cCubePC.h"


cCubePC::cCubePC() :m_fRotX(0.0f), m_vPosition(0,0,0)
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matS);
}


cCubePC::~cCubePC()
{
}

void cCubePC::Setup(D3DXVECTOR3 position)
{
	ST_PC_VERTEX v;
	//front
	v.c = D3DCOLOR_XRGB(120,125,0);
	v.p = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, 1.0f, -1.0f);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, 1.0f, -1.0f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, -1.0f, -1.0f);
	m_vecVertex.push_back(v);

	//back
	v.c = D3DCOLOR_XRGB(168, 130,180);
	v.p = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, -1.0f, 1.0f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_vecVertex.push_back(v);

	//left
	v.c = D3DCOLOR_XRGB(90, 111,17);
	v.p = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
	m_vecVertex.push_back(v);

	//right
	v.c = D3DCOLOR_XRGB(168,0, 170);
	v.p = D3DXVECTOR3(1.0f, -1.0f, -1.0f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, 1.0f, -1.0f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(1.0f, -1.0f, -1.0f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, -1.0f, 1.0f);
	m_vecVertex.push_back(v);

	//top
	v.c = D3DCOLOR_XRGB(166,166,0);
	v.p = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, 1.0f, -1.0f);
	m_vecVertex.push_back(v);

	//bottom
	v.c = D3DCOLOR_XRGB(60,30, 120);
	v.p = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, -1.0f, -1.0f);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, -1.0f, -1.0f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, -1.0f, 1.0f);
	m_vecVertex.push_back(v);


	m_vPosition = position;

}

void cCubePC::Update(D3DXMATRIXA16& matWrold)
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	D3DXMATRIXA16 matR,matT;
	D3DXMatrixRotationY(&matR, m_fRotX);

	D3DXVECTOR3 m_vDirection = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = m_matS *matR * matT;
}

void cCubePC::Render()
{
	g_pD3DDvice->SetRenderState(D3DRS_CULLMODE, false);
	g_pD3DDvice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDvice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDvice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex.size() / 3,
		&m_vecVertex[0],
		sizeof(ST_PC_VERTEX));
}

void cCubePC::setScale(D3DXVECTOR3 s)
{
	D3DXMatrixScaling(&m_matS, s.x, s.y,s.z);
}


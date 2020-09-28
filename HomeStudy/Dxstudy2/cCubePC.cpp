#include "stdafx.h"
#include "cCubePC.h"


cCubePC::cCubePC() : m_vPosition(0, 0, 0)
{

}


cCubePC::~cCubePC()
{
}

void cCubePC::Setup(D3DXVECTOR3 position, D3DXVECTOR3 scale)
{
	{


	ST_PC_VERTEX v;
	//front
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
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
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
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
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
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
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
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
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
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
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
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
	}

	m_vPosition = position;

	m_vScale = scale;

}

void cCubePC::Update(D3DXMATRIXA16& world)
{
	

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	
	D3DXMATRIXA16 matS,matT, matR;
	D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matS * matT * world;
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


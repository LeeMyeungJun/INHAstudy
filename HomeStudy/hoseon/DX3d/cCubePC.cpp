#include "stdafx.h"
#include "cCubePC.h"


cCubePC::cCubePC(): m_vDirection(0, 0, 1), m_vPosition(0, 0, 0), m_fRotY(0.0f)
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matS);
}

cCubePC::~cCubePC()
{
}

void cCubePC::Setup()
{
	ST_PC_VERTEX v;
	
	//front
	v.c = D3DCOLOR_XRGB(0, 254, 155);
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
	v.c = D3DCOLOR_XRGB(255, 80, 97);
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
	v.c = D3DCOLOR_XRGB(2, 196, 53);
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
	v.c = D3DCOLOR_XRGB(148, 97, 253);
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
	v.c = D3DCOLOR_XRGB(255, 219, 78);
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
	v.c = D3DCOLOR_XRGB(45, 217, 254);
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

void cCubePC::Update()
{
	//RECT rc;
	//GetClientRect(g_hWnd, &rc);
	D3DXMATRIXA16	matR, matT;
	D3DXMatrixRotationY(&matR, m_fRotY);	//Y축으로 회전된 행렬 제작

	m_vDirection = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);	//벡터 라디안 회전
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);	//이동된 행렬 제작

	m_matWorld = m_matS * matR * matT;
}

void cCubePC::Update(D3DXMATRIXA16 &_parentMat)
{
	Update();
	m_matWorld *= _parentMat;
}

void cCubePC::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, false);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0],
		sizeof(ST_PC_VERTEX));
}

D3DXVECTOR3& cCubePC::GetPosition()
{
	return m_vPosition;
}

void cCubePC::SetScale(float _x, float _y, float _z)
{
	D3DXMatrixScaling(&m_matS, _x, _y, _z);
}

void cCubePC::SetPosition(D3DXVECTOR3 _vec)
{
	m_vPosition = _vec;
}
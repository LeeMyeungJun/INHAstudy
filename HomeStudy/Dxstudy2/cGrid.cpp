#include "stdafx.h"
#include "cGrid.h"
#include "cPyramid.h"

cGrid::cGrid()
{
}


cGrid::~cGrid()
{
	for each(auto p in m_vecPyramid)
	{
		SafeDelete(p);
	}
	m_vecPyramid.clear();
}

void cGrid::Setup(int nNumHalfTile, float fInterval)
{
	float fMax = nNumHalfTile * fInterval;
	float fMin = -fMax;

	ST_PC_VERTEX v;
	for(int i = 1; i <= nNumHalfTile; i++)
	{
		if (i % 5 == 0)
			v.c = D3DCOLOR_XRGB(255, 255, 255);
		else
			v.c = D3DCOLOR_XRGB(128, 128, 128);

		v.p = D3DXVECTOR3(fMin, 0, i *fInterval);
		m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(fMax, 0, i*fInterval);
		m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(fMin, 0, -i *fInterval);
		m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(fMax, 0, -i*fInterval);
		m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(i *fInterval, 0,fMin );
		m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(i *fInterval, 0,fMax );
		m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3( -i *fInterval, 0, fMin);
		m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(-i *fInterval, 0, fMax);
		m_vecVertex.push_back(v);
	}
	v.c = D3DCOLOR_XRGB(255, 0, 0);
	v.p = D3DXVECTOR3(fMin, 0, 0);m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(fMax, 0, 0);m_vecVertex.push_back(v);

	v.c = D3DCOLOR_XRGB(0, 255, 0);
	v.p = D3DXVECTOR3(0, fMin, 0); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0, fMax, 0); m_vecVertex.push_back(v);

	v.c = D3DCOLOR_XRGB(0, 0, 255);
	v.p = D3DXVECTOR3(0, 0, fMin); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0, 0, fMax); m_vecVertex.push_back(v);
	//���� ���࿡���� ����

	//����𼱾�
	cPyramid* pPyramid = NULL;
	D3DXMATRIXA16 matR;
	//x��
	pPyramid = new cPyramid;
	D3DXMatrixRotationZ(&matR, D3DX_PI / 2.0f);
	pPyramid->Setup(D3DCOLOR_XRGB(255, 0, 0), matR);
	m_vecPyramid.push_back(pPyramid);

	//y��
	pPyramid = new cPyramid;
	D3DXMatrixRotationZ(&matR, D3DX_PI);
	pPyramid->Setup(D3DCOLOR_XRGB(0, 255, 0), matR);
	m_vecPyramid.push_back(pPyramid);

	//z��
	pPyramid = new cPyramid;
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0f);
	pPyramid->Setup(D3DCOLOR_XRGB(0, 0, 255), matR);
	m_vecPyramid.push_back(pPyramid);
	

}

void cGrid::Render()
{
	g_pD3DDvice->SetRenderState(D3DRS_LIGHTING, false);
	D3DXMATRIXA16 matI;
	D3DXMatrixIdentity(&matI);
	g_pD3DDvice->SetTransform(D3DTS_WORLD, &matI);
	g_pD3DDvice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDvice->DrawPrimitiveUP(D3DPT_LINELIST,
		m_vecVertex.size() / 2,
		&m_vecVertex[0],
		sizeof(ST_PC_VERTEX));

	for each(auto p in m_vecPyramid)
		p->Render();

	
}
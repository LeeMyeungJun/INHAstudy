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

	v.c = D3DCOLOR_XRGB(0, 255, 0);
	for (int i = 0; i < nNumHalfTile * 2; ++i)
	{
		for (int j = 0; j < nNumHalfTile * 2; ++j)
		{
			v.p = D3DXVECTOR3{ fMin + j * fInterval, 0, fMax - i * fInterval };
			m_vecVertex.push_back(v);
			v.p = D3DXVECTOR3{ fMin + j * fInterval + fInterval, 0, fMax - i * fInterval };
			m_vecVertex.push_back(v);
			v.p = D3DXVECTOR3{ fMin + j * fInterval, 0, fMax - i * fInterval - fInterval };
			m_vecVertex.push_back(v);

			v.p = D3DXVECTOR3{ fMin + j * fInterval, 0, fMax - i * fInterval - fInterval };
			m_vecVertex.push_back(v);
			v.p = D3DXVECTOR3{ fMin + j * fInterval + fInterval, 0, fMax - i * fInterval };
			m_vecVertex.push_back(v);
			v.p = D3DXVECTOR3{ fMin + j * fInterval + fInterval, 0, fMax - i * fInterval - fInterval };
			m_vecVertex.push_back(v);
		}
	}
	
	//위가 각축에대한 선언

	////기즈모선언
	cPyramid* pPyramid = NULL;
	D3DXMATRIXA16 matR;
	//x축
	pPyramid = new cPyramid;
	D3DXMatrixRotationZ(&matR, D3DX_PI / 2.0f);
	pPyramid->Setup(D3DCOLOR_XRGB(255, 0, 0), matR);
	m_vecPyramid.push_back(pPyramid);

	//y축
	pPyramid = new cPyramid;
	D3DXMatrixRotationZ(&matR, D3DX_PI);
	pPyramid->Setup(D3DCOLOR_XRGB(0, 255, 0), matR);
	m_vecPyramid.push_back(pPyramid);

	//z축
	pPyramid = new cPyramid;
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0f);
	pPyramid->Setup(D3DCOLOR_XRGB(0, 0, 255), matR);
	m_vecPyramid.push_back(pPyramid);

	nNumHalfTile = 20;
	fInterval = 1;

	float fMax2 = nNumHalfTile * fInterval;
	float fMin2 = -fMax2;

	ST_PC_VERTEX v2;
	for (int i = 1; i <= nNumHalfTile; i++)
	{
		if (i % 5 == 0)
			v2.c = D3DCOLOR_XRGB(255, 255, 255);
		else
			v2.c = D3DCOLOR_XRGB(128, 128, 128);

		v2.p = D3DXVECTOR3(fMin2, 0, i *fInterval);
		m_vecVertex2.push_back(v2);
		v2.p = D3DXVECTOR3(fMax2, 0, i*fInterval);
		m_vecVertex2.push_back(v2);

		v2.p = D3DXVECTOR3(fMin2, 0, -i *fInterval);
		m_vecVertex2.push_back(v2);
		v2.p = D3DXVECTOR3(fMax2, 0, -i*fInterval);
		m_vecVertex2.push_back(v2);

		v2.p = D3DXVECTOR3(i *fInterval, 0, fMin2);
		m_vecVertex2.push_back(v2);
		v2.p = D3DXVECTOR3(i *fInterval, 0, fMax2);
		m_vecVertex2.push_back(v2);

		v2.p = D3DXVECTOR3(-i *fInterval, 0, fMin2);
		m_vecVertex2.push_back(v2);
		v2.p = D3DXVECTOR3(-i *fInterval, 0, fMax2);
		m_vecVertex2.push_back(v2);
	}
	v2.c = D3DCOLOR_XRGB(255, 0, 0);
	v2.p = D3DXVECTOR3(fMin2, 0, 0); m_vecVertex2.push_back(v2);
	v2.p = D3DXVECTOR3(fMax2, 0, 0); m_vecVertex2.push_back(v2);

	v2.c = D3DCOLOR_XRGB(0, 255, 0);
	v2.p = D3DXVECTOR3(0, fMin2, 0); m_vecVertex2.push_back(v2);
	v2.p = D3DXVECTOR3(0, fMax2, 0); m_vecVertex2.push_back(v2);

	v2.c = D3DCOLOR_XRGB(0, 0, 255);
	v2.p = D3DXVECTOR3(0, 0, fMin2); m_vecVertex2.push_back(v2);
	v2.p = D3DXVECTOR3(0, 0, fMax2); m_vecVertex2.push_back(v2);
	//위가 각축에대한 선언



}

void cGrid::Render()
{
	g_pD3DDvice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDvice->SetTexture(NULL, 0); //잠깐 추가
	
	D3DXMATRIXA16 matI;
	D3DXMatrixIdentity(&matI);
	g_pD3DDvice->SetTransform(D3DTS_WORLD, &matI);
	g_pD3DDvice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDvice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex.size()/3,
		&m_vecVertex[0],
		sizeof(ST_PC_VERTEX));

	for each(auto p in m_vecPyramid)
		p->Render();

	Render_Line();
}

void cGrid::Render_Line()
{
	D3DXMATRIXA16 matI;
	D3DXMatrixIdentity(&matI);
	g_pD3DDvice->SetTransform(D3DTS_WORLD, &matI);
	g_pD3DDvice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDvice->DrawPrimitiveUP(D3DPT_LINELIST,
		m_vecVertex2.size()/2,
		&m_vecVertex2[0],
		sizeof(ST_PC_VERTEX));
}

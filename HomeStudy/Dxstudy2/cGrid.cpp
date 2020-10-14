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

	ST_PN_VERTEX v;
	v.n = D3DXVECTOR3(0, 1, 0);
	
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
	//cPyramid* pPyramid = NULL;
	//D3DXMATRIXA16 matR;
	////x축
	//pPyramid = new cPyramid;
	//D3DXMatrixRotationZ(&matR, D3DX_PI / 2.0f);
	//pPyramid->Setup(D3DCOLOR_XRGB(255, 0, 0), matR);
	//m_vecPyramid.push_back(pPyramid);

	////y축
	//pPyramid = new cPyramid;
	//D3DXMatrixRotationZ(&matR, D3DX_PI);
	//pPyramid->Setup(D3DCOLOR_XRGB(0, 255, 0), matR);
	//m_vecPyramid.push_back(pPyramid);

	////z축
	//pPyramid = new cPyramid;
	//D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0f);
	//pPyramid->Setup(D3DCOLOR_XRGB(0, 0, 255), matR);
	//m_vecPyramid.push_back(pPyramid);
	

}

void cGrid::Render()
{
	g_pD3DDvice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDvice->SetTexture(NULL, 0); //잠깐 추가
	D3DXMATRIXA16 matI;
	D3DXMatrixIdentity(&matI);
	g_pD3DDvice->SetTransform(D3DTS_WORLD, &matI);
	g_pD3DDvice->SetFVF(ST_PN_VERTEX::FVF);
	g_pD3DDvice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex.size()/3,
		&m_vecVertex[0],
		sizeof(ST_PN_VERTEX));

	//for each(auto p in m_vecPyramid)
	//	p->Render();

	
}

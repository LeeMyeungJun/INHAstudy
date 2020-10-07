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


}

void cGrid::Render()
{
	g_pD3DDvice->SetRenderState(D3DRS_LIGHTING, true);
	D3DXMATRIXA16 matI;
	D3DXMatrixIdentity(&matI);
	g_pD3DDvice->SetTransform(D3DTS_WORLD, &matI);
	g_pD3DDvice->SetFVF(ST_PN_VERTEX::FVF);
	g_pD3DDvice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex.size() / 3,
		&m_vecVertex[0],
		sizeof(ST_PN_VERTEX));
}

#include "stdafx.h"
#include "cHex.h"


cHex::cHex()
	:m_vHexagon(NULL)
	,m_vBezier(NULL)
{
	
}


cHex::~cHex()
{
}

void cHex::Render()
{
	g_pD3DDvice->SetRenderState(D3DRS_LIGHTING, true);
	D3DXMATRIXA16 matI;
	D3DXMatrixIdentity(&matI);
	g_pD3DDvice->SetTransform(D3DTS_WORLD, &matI);
	g_pD3DDvice->SetFVF(ST_PN_VERTEX::FVF);
	g_pD3DDvice->DrawPrimitiveUP(D3DPT_LINELIST,
		m_vecVertex.size() / 2,
		&m_vecVertex[0],
		sizeof(ST_PN_VERTEX));
}

void cHex::Setup()
{
	m_vHexagon = new D3DXVECTOR3[6];

	m_vHexagon[0] = D3DXVECTOR3(0, 0, 6);
	D3DXMATRIXA16 temp;
	D3DXMatrixRotationY(&temp, D3DXToRadian(60));

	
	for(int i = 1; i < 6; i++)
	{
		D3DXVec3TransformNormal(&m_vHexagon[i], &m_vHexagon[i-1], &temp);
	}

}

#include "stdafx.h"
#include "cHexagon.h"


cHexagon::cHexagon()
{
}

cHexagon::~cHexagon()
{
}

void cHexagon::Setup()
{
	ST_PC_VERTEX v;

	v.c = D3DCOLOR_XRGB(100, 240, 100);
	v.p = D3DXVECTOR3(5, 0, 0);
	m_vHexagon.push_back(v);
	
	for (int i = 0; i < 6; i++)
	{
		D3DXMATRIXA16 matRY;
		D3DXMatrixRotationY(&matRY, D3DXToRadian(60));
		D3DXVec3TransformNormal(&v.p, &v.p, &matRY);
		m_vHexagon.push_back(v);
	}

	v.c = D3DCOLOR_XRGB(240, 100, 100);

	for(int i = 0; i < m_vHexagon.size()-1; i += 2)
	{
		for(float f = 0.0f; f < 1.0f; f += 0.125f)
		{
			v.p = (pow(1 - f, 2) * m_vHexagon[i].p) + (2 * (1 - f) * f * m_vHexagon[i + 1].p)
				+ (pow(f, 2) * m_vHexagon[i + 2].p);

			m_vBezier.push_back(v);
		}
	}
}

void cHexagon::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	D3DXMATRIXA16 matI;
	D3DXMatrixIdentity(&matI);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matI);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, m_vHexagon.size()-1, &m_vHexagon[0],
		sizeof(ST_PC_VERTEX));

	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, m_vBezier.size() - 1, &m_vBezier[0],
		sizeof(ST_PC_VERTEX));
}

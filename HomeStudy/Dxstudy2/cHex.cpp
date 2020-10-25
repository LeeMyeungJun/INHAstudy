#include "stdafx.h"
#include "cHex.h"


cHex::cHex()
	:m_vHexagon(NULL)
	,m_vBezier(NULL)
{
	
}


cHex::~cHex()
{
	delete[] m_vHexagon;
	delete[] m_vBezier;
}

void cHex::Render()
{
	//Draw_Hexagon();
	//Draw_Bezier();
}

void cHex::Setup()
{
	m_vHexagon = new D3DXVECTOR3[6];

	m_vHexagon[0] = D3DXVECTOR3(0, 1, 6);

	D3DXMATRIXA16 temp;
	D3DXMatrixRotationY(&temp, D3DXToRadian(60)); 

	//60도 회전 행렬
	for(int i = 1; i < 6; i++)
	{
		D3DXVec3TransformNormal(&m_vHexagon[i], &m_vHexagon[i-1], &temp);
	}

	ST_PN_VERTEX v;
	//>> :hexagon Setup
	for (int i = 0; i < 6; i++)// 0 1 2 3 4 5 0 
	{
		v.p = m_vHexagon[i];
		m_vecVertex.push_back(v);
	}

	v.p = m_vHexagon[0];
	m_vecVertex.push_back(v);
	//<< : 

	//>>:m_vBezier
	float div = 16;
	float t = 1 / div;

	for (int i = 0; i < m_vecVertex.size() -1; i += 2)
	{
		for (int j = 0; j < div; j++)
		{
			v.p = pow(1 - (t*j), 2) * m_vecVertex[i].p + 2 * (t*j)*(1 - (t*j))*m_vecVertex[i + 1].p + pow((t*j), 2)*m_vecVertex[i + 2].p;
			m_vecBezierVertex.push_back(v);
		}
	}

	v.p = m_vecBezierVertex[0].p;
	m_vecBezierVertex.push_back(v);

	m_iSize = m_vecBezierVertex.size();

	

	//<<:


}

void cHex::Draw_Hexagon()
{
	g_pD3DDvice->SetRenderState(D3DRS_LIGHTING, true);
	D3DXMATRIXA16 matI;
	D3DXMatrixIdentity(&matI);
	g_pD3DDvice->SetTransform(D3DTS_WORLD, &matI);
	g_pD3DDvice->SetFVF(ST_PN_VERTEX::FVF);
	g_pD3DDvice->DrawPrimitiveUP(D3DPT_LINESTRIP,
		m_vecVertex.size() - 1,
		&m_vecVertex[0],
		sizeof(ST_PN_VERTEX));
}

void cHex::Draw_Bezier()
{
	g_pD3DDvice->SetRenderState(D3DRS_LIGHTING, true);
	D3DXMATRIXA16 matI;
	D3DXMatrixIdentity(&matI);
	g_pD3DDvice->SetTransform(D3DTS_WORLD, &matI);
	g_pD3DDvice->SetFVF(ST_PN_VERTEX::FVF);
	g_pD3DDvice->DrawPrimitiveUP(D3DPT_LINESTRIP,
		m_vecBezierVertex.size()-1,
		&m_vecBezierVertex[0],
		sizeof(ST_PN_VERTEX));

}

#include "stdafx.h"
#include "cGrid.h"
#include "cPyramid.h"
#include "cGroup.h"

cGrid::cGrid()
	:m_PlaneTexture(NULL)
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
	ZeroMemory(&m_stMt1, sizeof(D3DMATERIAL9));
	m_stMt1.Ambient = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
	m_stMt1.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMt1.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	
	float fMax = nNumHalfTile * fInterval;
	float fMin = -fMax;
	ST_PNT_VERTEX	v;
	ST_PC_VERTEX	vc;
	ST_Tile			t;
	//v.n = D3DXVECTOR3(0, 1, 0);

	//Grid
	for(int i = 1; i <= nNumHalfTile; ++i)
	{
		if (i % 5 == 0)
			vc.c = D3DCOLOR_XRGB(255, 255, 255);
		else
			vc.c = D3DCOLOR_XRGB(128, 128, 128);

		vc.p = D3DXVECTOR3(fMin, 0, i * fInterval);
		m_vecVertex.push_back(vc);
		vc.p = D3DXVECTOR3(fMax, 0, i * fInterval);
		m_vecVertex.push_back(vc);

		vc.p = D3DXVECTOR3(fMin, 0, -i * fInterval);
		m_vecVertex.push_back(vc);
		vc.p = D3DXVECTOR3(fMax, 0, -i * fInterval);
		m_vecVertex.push_back(vc);

		vc.p = D3DXVECTOR3(i * fInterval, 0, fMin);
		m_vecVertex.push_back(vc);
		vc.p = D3DXVECTOR3(i * fInterval, 0, fMax);
		m_vecVertex.push_back(vc);

		vc.p = D3DXVECTOR3(-i * fInterval, 0, fMin);
		m_vecVertex.push_back(vc);
		vc.p = D3DXVECTOR3(-i * fInterval, 0, fMax);
		m_vecVertex.push_back(vc);
	}

	vc.c = D3DCOLOR_XRGB(240, 100, 100);
	vc.p = D3DXVECTOR3(fMin, 0, 0); m_vecVertex.push_back(vc);
	vc.p = D3DXVECTOR3(fMax, 0, 0);	m_vecVertex.push_back(vc);

	vc.c = D3DCOLOR_XRGB(100, 240, 100);
	vc.p = D3DXVECTOR3(0, fMin, 0); m_vecVertex.push_back(vc);
	vc.p = D3DXVECTOR3(0, fMax, 0);	m_vecVertex.push_back(vc);

	vc.c = D3DCOLOR_XRGB(100, 100, 240);
	vc.p = D3DXVECTOR3(0, 0, fMin); m_vecVertex.push_back(vc);
	vc.p = D3DXVECTOR3(0, 0, fMax);	m_vecVertex.push_back(vc);

	m_PlaneTexture = g_pTextureManager->GetTexture("images/Albedo00.jpg");
	v.n = D3DXVECTOR3(0, 1, 0);
	//Plane
	for (int i = 0; i < nNumHalfTile * 2; ++i)
	{
		for (int j = 0; j < nNumHalfTile * 2; ++j)
		{
			v.p = D3DXVECTOR3{ fMin + j * fInterval, 0, fMax - i * fInterval }; v.t = D3DXVECTOR2(0, 0);
			m_vecVertexPlane.push_back(v);
			v.p = D3DXVECTOR3{ fMin + j * fInterval + fInterval, 0, fMax - i * fInterval }; v.t = D3DXVECTOR2(1, 0);
			m_vecVertexPlane.push_back(v);
			v.p = D3DXVECTOR3{ fMin + j * fInterval, 0, fMax - i * fInterval - fInterval }; v.t = D3DXVECTOR2(0, 1);
			m_vecVertexPlane.push_back(v);


			
			v.p = D3DXVECTOR3{ fMin + j * fInterval, 0, fMax - i * fInterval - fInterval };  v.t = D3DXVECTOR2(0, 1);
			m_vecVertexPlane.push_back(v);
			v.p = D3DXVECTOR3{ fMin + j * fInterval + fInterval, 0, fMax - i * fInterval }; v.t = D3DXVECTOR2(1, 0);
			m_vecVertexPlane.push_back(v);
			v.p = D3DXVECTOR3{ fMin + j * fInterval + fInterval, 0, fMax - i * fInterval - fInterval }; v.t = D3DXVECTOR2(1, 1);
			m_vecVertexPlane.push_back(v);

		}
	}

	cPyramid *pPyramid = NULL;
	D3DXMATRIXA16 matR;

	pPyramid = new cPyramid;
	D3DXMatrixRotationZ(&matR, D3DX_PI / 2.0f);
	pPyramid->Setup(D3DCOLOR_XRGB(240, 100, 100), matR);
	m_vecPyramid.push_back(pPyramid);

	pPyramid = new cPyramid;
	D3DXMatrixRotationZ(&matR, D3DX_PI);
	pPyramid->Setup(D3DCOLOR_XRGB(100, 240, 100), matR);
	m_vecPyramid.push_back(pPyramid);

	pPyramid = new cPyramid;
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0f);
	pPyramid->Setup(D3DCOLOR_XRGB(100, 100, 240), matR);
	m_vecPyramid.push_back(pPyramid);


}

void cGrid::Render()
{
	//Plane
	//g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	//g_pD3DDevice->SetTexture(NULL, m_PlaneTexture);
	//g_pD3DDevice->SetMaterial(&m_stMt1);
	//g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	//g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertexPlane.size() / 3, &m_vecVertexPlane[0],
	//	sizeof(ST_PNT_VERTEX));


	//Grid
	//g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	//g_pD3DDevice->SetTexture(NULL, 0);
	//D3DXMATRIXA16 matI2;
	//D3DXMatrixIdentity(&matI2);
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &matI2);
	//g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	//g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST, m_vecVertex.size() / 2, &m_vecVertex[0],
	//	sizeof(ST_PC_VERTEX));

	g_pD3DDevice->SetTexture(NULL, 0);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	for each(auto p in m_vecPyramid)
		p->Render();



	for each(auto p in m_vecGroup)
	{
		p->Render();
	}
}

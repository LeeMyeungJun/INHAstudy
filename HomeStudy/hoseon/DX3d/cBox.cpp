#include "stdafx.h"
#include "cBox.h"

cBox::cBox()
{
}

cBox::~cBox()
{
}

void cBox::Render()
{
	if (g_pD3DDevice)
	{
		D3DXMATRIXA16	matWorld, matS;
		D3DXMatrixScaling(&matS, 0.1f, 0.1f, 0.1f);

		matWorld = matS;

		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
		g_pD3DDevice->SetMaterial(&m_boxMtl);
		g_pD3DDevice->SetTexture(0, m_boxTexture); 

		cCubePNT::Render();
		
		g_pD3DDevice->SetTexture(0, NULL);
	}
}

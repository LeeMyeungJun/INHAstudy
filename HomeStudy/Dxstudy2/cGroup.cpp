#include "stdafx.h"
<<<<<<< HEAD
#include "cGroup.h"


cGroup::cGroup()
	:m_pMtlTex(NULL)
{
	
=======



cGroup::cGroup()
{
>>>>>>> 41302b6992cdd6e25a5b860ae2afd9f7e1656f1b
}


cGroup::~cGroup()
{
<<<<<<< HEAD
	SafeRelease(m_pMtlTex);
=======
>>>>>>> 41302b6992cdd6e25a5b860ae2afd9f7e1656f1b
}

void cGroup::Render()
{
<<<<<<< HEAD
	if(m_pMtlTex)
	{
		g_pD3DDvice->SetTexture(0, m_pMtlTex->GetTexture());
		g_pD3DDvice->SetMaterial(&m_pMtlTex->GetMaterial());
	}

	g_pD3DDvice->SetFVF(ST_PNT_VERTEX::FVF);
	g_pD3DDvice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex.size()/3,
		&m_vecVertex[0],
		sizeof(ST_PNT_VERTEX));
=======
>>>>>>> 41302b6992cdd6e25a5b860ae2afd9f7e1656f1b
}

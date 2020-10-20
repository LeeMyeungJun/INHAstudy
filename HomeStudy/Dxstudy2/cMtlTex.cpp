#include "stdafx.h"
<<<<<<< HEAD
#include "cMtlTex.h"


cMtlTex::cMtlTex()
	: m_pTexture(NULL)
	, m_nAttrID(0)
{
	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
=======


cMtlTex::cMtlTex()
{
>>>>>>> 41302b6992cdd6e25a5b860ae2afd9f7e1656f1b
}


cMtlTex::~cMtlTex()
{
<<<<<<< HEAD
	SafeRelease(m_pTexture);
=======
>>>>>>> 41302b6992cdd6e25a5b860ae2afd9f7e1656f1b
}

#pragma once
#include "cObject.h"
class cMtlTex :
	public cObject
{
public:
	cMtlTex();
	~cMtlTex();

private:
	Synthesize_Pass_by_Ref(D3DMATERIAL9, m_stMtl, Material);
	Synthesize_Add_Ref(LPDIRECT3DTEXTURE9, m_pTexture, Texture);
<<<<<<< HEAD

	Synthesize(int, m_nAttrID, AttrID);
=======
>>>>>>> 41302b6992cdd6e25a5b860ae2afd9f7e1656f1b
};


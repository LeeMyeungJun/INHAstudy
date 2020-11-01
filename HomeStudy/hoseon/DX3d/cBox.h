#pragma once
#include "cCubePNT.h"

class cBox : public cCubePNT
{
public:
	D3DMATERIAL9		m_boxMtl;
	LPDIRECT3DTEXTURE9	m_boxTexture;
public:
	cBox();
	~cBox();
	
	void Render();
};


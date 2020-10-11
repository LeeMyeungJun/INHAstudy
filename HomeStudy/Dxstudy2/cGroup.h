#pragma once
#include "cObject.h"
#include "cMtlTex.h"
class cGroup :
	public cObject
{
public:
	cGroup();
	~cGroup();
public:
	Synthesize_Pass_by_Ref(vector<ST_PNT_VERTEX>, m_vecVertex, Vertex);
	Synthesize_Add_Ref(cMtlTex*, m_pMtlTex, mtlTex);

public:
	void Render();
	
};


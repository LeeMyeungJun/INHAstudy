#pragma once
#include "cGroup.h"
#include "cMtlTex.h"

class cAseLoader
{
public:
	cAseLoader();
	~cAseLoader();
private:
	map<string, cMtlTex*> m_mapMtlTex;
public:
	void Load(OUT vector<cGroup*> &vecGroup, IN char* szFolder, IN char* szFile);
};


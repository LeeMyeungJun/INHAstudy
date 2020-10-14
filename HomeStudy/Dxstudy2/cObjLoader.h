#pragma once
class cGroup;
class cMtlTex;

class cObjLoader
{
public:
	cObjLoader();
	~cObjLoader();
private:
	map<string, cMtlTex*> m_mapMtlTex;
public:
	void Load(OUT vector<cGroup*> &vecGroup, IN char* szFolder, IN char* szFile);
	void LoadMtlLib(char* szFolder, char* szFile);

	void LoadSurface(OUT vector<D3DXVECTOR3>&vecSurface, IN char* szFolder, IN char* szFile, IN D3DXMATRIXA16* pmat = NULL);
};


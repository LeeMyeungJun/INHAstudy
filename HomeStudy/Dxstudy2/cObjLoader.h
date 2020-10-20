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
<<<<<<< HEAD

public:
	void Load(OUT vector<cGroup*> &vecGroup, IN char* szFolder, IN char* szFile);
	void LoadMtlLib(char* szFolder, char* szFile);

	void LoadSurface(OUT vector<D3DXVECTOR3>&vecSurface, IN char* szFolder, IN char* szFile, IN D3DXMATRIXA16* pmat = NULL);

	//>>:Mesh
	LPD3DXMESH	LoadMesh(OUT vector<cMtlTex*>& vecMtlTex, IN char* szFolder, IN char* szFile);
=======
public:
	void Load(OUT vector<cGroup*> &vecGroup, IN char* szFolder, IN char* szFile);
	void LoadMtlLib(char* szFolder, char* szFile);
>>>>>>> 41302b6992cdd6e25a5b860ae2afd9f7e1656f1b
};


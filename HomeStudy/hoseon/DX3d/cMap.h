#pragma once
class cObjLoader;
class cGroup;

class cMap
{
	//texture
	vector<cGroup*> m_vecGroup;
	vector<cGroup*> m_vecMapSurface;

public:
	cMap();
	~cMap();

	void Setup_Obj();
	void Obj_Render();

	vector<cGroup*> GetVecMapSurface();
};


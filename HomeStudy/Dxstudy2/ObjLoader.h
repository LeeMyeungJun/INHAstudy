#pragma once
class cCubePC;

class ObjLoader
{
public:
	vector<ST_PNT_VERTEX> v_Group;
	map<string, ST_PNT_VERTEX> m_MtlTex;
	vector<D3DXVECTOR3> v_FilePoint;
	vector<D3DXVECTOR3> v_FileNormal;
	vector<D3DXVECTOR2> v_FileTexture;

public:
	void FileLoad(char* FileName);
	void ProcessMtl(char* FileName);

	virtual void Setup();
	virtual void Render();
public:
	ObjLoader();
	virtual ~ObjLoader();
};


#pragma once
class cFrame;
class cMtlTex;

class cAseLoader
{
public:
	cAseLoader();
	~cAseLoader();
private:
	FILE* m_fp;
	char m_szToken[1024];
	vector<cMtlTex*> m_vecMtlTex;
	map<string, cFrame*> m_mapFrame;
	int MtlIndex;

public:
	cFrame* Load(IN char* szFullPath);

private: //���������� ������Լ����� �����غ���.
	char* GetToken();
	int GetInteger();
	float GetFloat();
	bool IsWhite(IN char c);
	bool IsEqual(IN char* str1, IN char* str2);
	void SkipBlock();
	void ProcessMATERIAL_LIST();
	void ProcessMATERIAL(OUT cMtlTex* pMtltex);
	void ProcessMAP_DIFFUSE(OUT cMtlTex* pMtltex);
	cFrame* ProcessGEOBJECT();
	void ProcessMESH(OUT cFrame* pFrame);
	void ProcessMESH_VERTEX_LIST(OUT vector<D3DXVECTOR3>& vecV);
	void ProcessMESH_FACE_LIST(OUT vector<ST_PNT_VERTEX>& vecVertex, IN vector<D3DXVECTOR3>& vecV);
	void ProcessMESH_TVERTLIST(OUT vector<D3DXVECTOR2>& vecVT);
	void ProcessMESH_TFACELIST(OUT vector<ST_PNT_VERTEX>& vecVertex, IN vector<D3DXVECTOR2>& vecVT);
	void ProcessMESH_NOMRALS(OUT vector<ST_PNT_VERTEX>& vecVertex);
	void ProcessNODE_TM(OUT cFrame* pFrame);

	//>>: Animaition

	void ProcessScene();	
	void Set_SceneFrame(OUT cFrame* pRoot);
	void ProcessTM_ANIMATION(OUT cFrame* pFrame);
	void ProcessCONTROL_POS_TRACK(OUT cFrame* pFrame);
	void ProcessCONTROL_ROT_TRACK(OUT cFrame* pFrame);

	////>>:Mesh
	LPD3DXMESH	LoadMesh(OUT vector<cMtlTex*>& vecMtlTex, IN char* szFullPath);


	
	DWORD		m_dwFirstFrame;
	DWORD		m_dwLastFrame;
	DWORD		m_dwFrameSpeed;
	DWORD		m_dwTicksPerFrame;

	//<<:

	vector<DWORD>		vecAttrBuf;//�Ӽ������� ����
};
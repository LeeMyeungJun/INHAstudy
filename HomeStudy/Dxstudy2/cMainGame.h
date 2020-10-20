#pragma once
#include "stdafx.h"

#include "cMtlTex.h"
class cFrame;
class cCubeMan;
class cCubePC;
class cCamera;
class cGrid;
class cLight;
class cGroup;

class cMainGame
{
public:
	cMainGame();
	~cMainGame();

private:
	vector<ST_PC_VERTEX> m_vecLineVertex;
	vector<ST_PC_VERTEX> m_vecTriangleVertex;
	

	//위에껀안씀

	cCubePC*		m_pCubePC;
	cCamera*		m_pCamera;
	cGrid*			m_pGrid;
	cCubeMan*		m_pCubeMan;
	cLight*			m_pLight;
	iMap*			m_pMap;

	//:>>AseLoader
	cFrame*			m_pRootFrame;
	//<:

	//::texture
	LPDIRECT3DTEXTURE9		m_pTexture;
	vector<ST_PT_VERTEX>	m_vecVertex;
	//<<:

	//>>:
	vector<cGroup*>			m_vecGroup;

	
public:
	void Setup();
	void Update();
	void Render();
	void wndProc(HWND hWnd,UINT message,WPARAM wParam, LPARAM lParam);

	void Setup_Line();
	void Draw_Line();


	void Setup_Triangle();
	void Draw_Triangle();

	void Set_Light();
	void Draw_Texture();

	void Setup_Obj();
	void Obj_Render();

	void Load_Surface();

	//>>:
	POINT					m_ptMousepick;
	vector<ST_PC_VERTEX>	m_gridVertex;

	void MousePicking(POINT ptCursor,UINT message);
	bool raySpherelntersectionTest(Ray* ray, BoundingSphere shpere);
	bool raGridlntersectionTest(Ray* ray, vector<ST_PN_VERTEX> Grid);

	

private:
	LPD3DXMESH		m_pMeshTeapot;
	LPD3DXMESH		m_pMeshSphere[10]; //그리기용
	BoundingSphere	m_stBoundShpere[10]; //판정용
	D3DMATERIAL9	m_stMtlTeapot;
	D3DMATERIAL9	m_stMtlSphere[10]; //색칠용 

	//OBJLoader통해서그리기
	LPD3DXMESH	m_pObjMesh;
	vector<cMtlTex*>	m_vecObjMtltex;

	//AseLoader통해서 그리기
	LPD3DXMESH	m_pAseObjMesh;
	vector<cMtlTex*>	m_vecAseObjMtltex;
	
public:
	void Setup_MeshObejct();
	void Mesh_Render();

	
	
};


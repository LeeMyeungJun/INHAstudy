#pragma once
class cCubePC;class cCamera;class cGrid;class cCubeMan;class cLight;class cHexagon;
class cObjLoader;class cGroup;class iMap;class cFrame;class cMtlTex;class cRawLoader;
class cXLoader;class cSkinnedMesh;class cFrustumCulling;class cFrustum;class cZealot;

class cMainGame
{
public:
	cMainGame();
	~cMainGame();

private:
	D3DXVECTOR3 vEye;
	D3DXVECTOR3 vLookAt;
	D3DXVECTOR3 vUp;
	
	vector<ST_PC_VERTEX>	m_vecLineVertex;
	vector<ST_PC_VERTEX>	m_vecTriangleVertex;

	vector<D3DXVECTOR3>		m_vecBoxVertex;
	vector<ST_PC_VERTEX>	m_vecBoxTrisVertex;
	
	vector<D3DXVECTOR3>		m_vecGridIndex;
	vector<ST_PC_VERTEX>	m_vecGridVertex;

	vector<D3DXVECTOR3>		m_vecPyramidVertex;
	vector<ST_PC_VERTEX>	m_vecPyramidTrisVertex;
	
	D3DXVECTOR3			m_vPosition;				//박스 위치
	POINT				m_ptPrevMouse;				//마우스 이전위치
	bool				m_isLButtonDown;			//마우스가 눌렸는지
	float				m_fCameraDist;				//카메라 거리

	D3DXVECTOR3			m_vCamRotAngle;				//카메라 회전
	float				m_fBoxRotY;					//박스 회전량
	D3DXVECTOR3			m_vBoxDirection;			//박스의 방향

private:
	cCamera*	m_pCamera;
	cGrid*		m_pGrid;
	
	cCubeMan*	m_pCubeMan;
	cCubeMan*	m_pCubeMans[2];
	cLight*		m_pLight;
	cCubePC*	m_pLightCube[2];

	cHexagon*	m_pHexagon;
	iMap*		m_pMap;

	cFrame*		m_pRootFrame;

	cRawLoader* m_pRawLoader;
	cXLoader*	m_pXLoader;

	cSkinnedMesh* m_pSkinnedMesh;
	cFrustumCulling*	m_pFrustumCulling;

	LPDIRECT3DTEXTURE9		m_pTexture;
	vector<ST_PT_VERTEX>	m_vecVertex;

	vector<cGroup*> m_vecGroup;
	vector<cGroup*> m_vecMapSurface;
	vector<cGroup*> m_vecAseGroup;

	LPD3DXFONT		m_pFont;

public:
	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void SetLight();
	void Draw_Texture();

	//texture
	void Setup_Obj();
	void Obj_Render();
	void Load_Surface();
	//

	void Setup_Line();
	void Draw_Line();
	void Setup_Triangle();
	void Draw_Triangle();
	
	void Setup_Box();
	void Draw_Box();
	void Setup_Grid();
	void Draw_Grid();

	void Setup_Pyramid();
	void Draw_Pyramid();
	
	void Update_Move();
	void Update_Rotation();

private:
	LPD3DXMESH			m_pMeshTeapot;
	LPD3DXMESH			m_pMeshSphere;
	D3DMATERIAL9		m_stMtlTeapot;
	D3DMATERIAL9		m_stMtlSphere;

	LPD3DXMESH			m_pObjMesh;
	vector<cMtlTex*>	m_vecObjMtlTex;

	//
	vector<ST_SPHERE>	m_vecSphere;
	D3DMATERIAL9		m_stMtlNone;
	D3DMATERIAL9		m_stMtlPicked;
	D3DMATERIAL9		m_stMtlPlane;
	vector<ST_PN_VERTEX>	m_vecPlaneVertex;
	D3DXVECTOR3			m_vPickedPosition;
	//

	//
	vector<ST_PNT_VERTEX>	m_meshPlaneVertex;
	vector<ST_PNT_VERTEX>	m_vecMtVertex;
	LPDIRECT3DTEXTURE9		m_pMtTexture;
	//

	//frustum
	LPD3DXMESH			m_pSphere;
	D3DMATERIAL9		m_stCullingMtl;
	vector<ST_SPHERE*>	m_vecCullingSphere;
	cFrustum*			m_pFrustum;
	//

	//obb
	cZealot*			m_pHoldZealot;
	cZealot*			m_pMoveZealot;
	//

public:
	void Setup_MeshObejct();
	void Mesh_Render();

	//
	void Setup_PickingObj();
	void PickingObj_Render();
	//

	void Setup_Raw();
	void Render_Raw();

	void SkinnedMesh_Render();

	//
	void Setup_Frustum();
	void Frustum_Render();
	//

	void Setup_OBB();
	void OBB_Render();
};


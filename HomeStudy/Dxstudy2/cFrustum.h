#pragma once
class cFrustum
{
public:
	vector<ST_PN_VERTEX> m_PlaneVertex; //면의 버텍스값 순서대로 
	D3DXVECTOR3			m_Pos; //카메라 위치 값
	D3DXPLANE			m_plnae[6]; //면의갯수
	vector<D3DXVECTOR3> m_vecFrustum;// 카메라 좌표 8개


public:
	vector<D3DXVECTOR3> m_vecVertex;

	
	vector<ST_SPHERE>	m_vecSphere;
	LPD3DXMESH			m_meshSpear;
	D3DMATERIAL9		m_stMtlNone;
	
	
public:
	cFrustum();
	~cFrustum();

	
	void Setup();
	void Update();
	void Render();
	
	bool InternalCheck(D3DXVECTOR3 vecPoint);

	void Setup_Mesh();

};


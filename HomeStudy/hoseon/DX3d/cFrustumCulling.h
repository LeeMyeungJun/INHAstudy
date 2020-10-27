#pragma once
class cFrustumCulling
{
private:
	vector<ST_PN_VERTEX> m_vecVertex;
	vector<ST_PN_VERTEX> m_vecProjVertex;

	vector<D3DXPLANE>	m_vecPlane;
	vector<ST_SPHERE>	m_vecSphere;

	LPD3DXMESH			m_pMeshSphere;
	D3DMATERIAL9		m_stMtlSphere;

public:
	cFrustumCulling();
	~cFrustumCulling();

	void Setup_Frustum();
	void Setup_Sphere();
	void Update();
	void Render_sphere();
	void FrustumCulling();
};


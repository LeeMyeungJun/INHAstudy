#pragma once
class cFrustum
{
public:
	vector<ST_PN_VERTEX> m_PlaneVertex; //���� ���ؽ��� ������� 
	D3DXVECTOR3			m_Pos; //ī�޶� ��ġ ��
	D3DXPLANE			m_plnae[6]; //���ǰ���
	vector<D3DXVECTOR3> m_vecFrustum;// ī�޶� ��ǥ 8��


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


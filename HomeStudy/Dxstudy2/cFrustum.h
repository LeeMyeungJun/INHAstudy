#pragma once
class cFrustum
{
public:
	vector<ST_PN_VERTEX> m_PlaneVertex; //���� ���ؽ��� ������� 
	D3DXVECTOR3			m_Pos; //ī�޶� ��ġ ��
	vector<D3DXPLANE>	m_plnae; //���ǰ���
	vector<D3DXVECTOR3> m_vecFrustum;// ī�޶� ��ǥ 8��


public:
	vector<D3DXVECTOR3> m_vecVertex;
	D3DMATERIAL9 m_stMtlSphere;
	vector<ST_SPHERE>	m_vecMeshSphere;
	
	
	
	
public:
	cFrustum();
	~cFrustum();

	
	void Setup();
	void Update();
	void Render();
	
	bool InternalCheck(D3DXVECTOR3* vecPoint);


};


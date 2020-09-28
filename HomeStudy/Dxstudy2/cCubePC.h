#pragma once
class cCubePC
{
public:
	cCubePC();
	~cCubePC();
private:
	vector<ST_PC_VERTEX> m_vecVertex;
	
	float				m_fRotX;
	D3DXVECTOR3         m_vPosition;
	D3DXVECTOR3			m_vScale;
	D3DXMATRIXA16       m_matWorld;

public:
	void Setup(D3DXVECTOR3 position , D3DXVECTOR3 scale);
	void Update(D3DXMATRIXA16& world);
	void Render();


};
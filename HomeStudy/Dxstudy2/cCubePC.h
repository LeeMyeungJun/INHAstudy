#pragma once
class cCubePC
{
public:
	cCubePC();
	~cCubePC();
private:
	vector<ST_PC_VERTEX> m_vecVertex;
	D3DXMATRIXA16       m_matWorld;
	D3DXMATRIXA16		m_matS;
	FLOAT				m_fRotX; //팔애니메이션 용
	D3DXVECTOR3			m_vPosition;
public:
	void Setup(D3DXVECTOR3 position);
	void Update(D3DXMATRIXA16& matWorld, FLOAT m_fRotY);
	void Render();


	void setScale(D3DXVECTOR3 s);




};
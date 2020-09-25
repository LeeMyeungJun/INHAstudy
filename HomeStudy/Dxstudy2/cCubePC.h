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
	FLOAT				m_fRotX;
	D3DXVECTOR3			m_vPosition;
public:
	void Setup(D3DXVECTOR3 position);
	void Update();
	void Render(D3DXMATRIXA16& matWrold);


	void setScale(D3DXVECTOR3 s);




};
#pragma once
class cCubePC
{
public:
	cCubePC();
	~cCubePC();
private:
	vector<ST_PC_VERTEX>	m_vecVertex;	//삼각형 꼭짓점 저장
	float					m_fRotY;		//큐브의 회전값

	D3DXVECTOR3				m_vDirection;	//큐브의 앞방향
	D3DXVECTOR3				m_vPosition;	//큐브의 위치
	D3DXMATRIXA16			m_matWorld;		//월드 행렬
	D3DXMATRIXA16			m_matS;			//큐브 크기행렬

public:
	void Setup();
	void Update();	//큐브의 점 갱신
	void Update(D3DXMATRIXA16 &_parentMat);
	void Render();
	D3DXVECTOR3 &GetPosition();

	float get_m_fRoty() const
	{
		return m_fRotY;
	}
	void set_m_fRoty(float m_f_rot_y)
	{
		m_fRotY = m_f_rot_y;
	}

	D3DXMATRIXA16 GetWMatrix() { return m_matWorld; }
	void SetScale(float _x, float _y, float _z);
	void SetPosition(D3DXVECTOR3 _vec);
};
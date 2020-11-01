#pragma once
class cCubePC
{
public:
	cCubePC();
	~cCubePC();
private:
	vector<ST_PC_VERTEX>	m_vecVertex;	//�ﰢ�� ������ ����
	float					m_fRotY;		//ť���� ȸ����

	D3DXVECTOR3				m_vDirection;	//ť���� �չ���
	D3DXVECTOR3				m_vPosition;	//ť���� ��ġ
	D3DXMATRIXA16			m_matWorld;		//���� ���
	D3DXMATRIXA16			m_matS;			//ť�� ũ�����

public:
	void Setup();
	void Update();	//ť���� �� ����
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
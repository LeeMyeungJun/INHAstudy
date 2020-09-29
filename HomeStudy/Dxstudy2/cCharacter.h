#pragma once
class cCharacter
{//ȸ���� �̵����� ��ġ �����Ʈ������
public:
	cCharacter();
	//~cCharacter();
protected:
	FLOAT			m_fRotY;
	D3DXVECTOR3		m_vDirection;
	D3DXVECTOR3		m_vPosition;
	D3DXMATRIXA16	m_matWorld;
public:
	virtual ~cCharacter(void);
	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual D3DXVECTOR3& GetPosition();
};


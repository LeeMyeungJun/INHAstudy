#pragma once
class cPath;

class cCharacter : public cObject
{//ȸ���� �̵����� ��ġ �����Ʈ������
public:
	cCharacter();
	//~cCharacter();
	int				m_iIndex;
	cPath*			m_pPath;
protected:
	FLOAT			m_fRotY;
	D3DXVECTOR3		m_vDirection;
	D3DXVECTOR3		m_vPosition;
	D3DXMATRIXA16	m_matWorld;

	iMap*			m_pMap;
public:
	virtual ~cCharacter(void);
	virtual void Setup();
	virtual void Update(iMap* pMap);
	virtual void Render();
	virtual D3DXVECTOR3& GetPosition();
	virtual D3DXVECTOR3& GetDirection();
	
	virtual D3DXMATRIXA16* GetTransform()
	{
		return &m_matWorld;
	}
};


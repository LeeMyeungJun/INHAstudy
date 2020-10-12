#pragma once
#include "cGroup.h"
class cPath;

class cCharacter
{//ȸ���� �̵����� ��ġ �����Ʈ������
private:
	vector<cGroup*>			m_vecGroup;

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

public:
	virtual ~cCharacter(void);
	virtual void Setup();
	virtual void Update();
	virtual void Render();


public:
	bool CollisionCheck();
	void PlayerMove();

	D3DXVECTOR3& GetPosition();
	D3DXVECTOR3& GetDirection();
};


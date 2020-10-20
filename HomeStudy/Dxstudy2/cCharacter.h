#pragma once
#include "cHex.h"
class cPath;

class cCharacter
{//ȸ���� �̵����� ��ġ �����Ʈ������
public:
	cCharacter();
	//~cCharacter();
	int				m_iIndex;
	int				m_iEndIndex;
	cPath*			m_pPath;
	//cHex*			m_pHex;



protected:
	FLOAT			m_fRotY;
	D3DXVECTOR3		m_vDirection;
	D3DXVECTOR3		m_vOldDirection;
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
public:
	void SetupMove(int size, vector<ST_PN_VERTEX> m_vecBezierVertex);
};


#pragma once
class cMap;

class cCharacter : public cObject
{
public:
	cCharacter();
	//~cCharacter();
protected:
	float			m_fRotY;
	D3DXVECTOR3		m_vDirection;
	D3DXVECTOR3		m_vPosition;
	D3DXVECTOR3		m_vPostPos;
	D3DXMATRIXA16	m_matWorld;

	D3DXVECTOR3		m_vPrevPos;
	D3DXVECTOR3		m_vRayPos;
	D3DXVECTOR3		m_vRayDir;

	LPDIRECT3DTEXTURE9	m_pPlayerTexture;

	iMap*         m_pMap;

public:
	virtual ~cCharacter(void);

	virtual void Setup();
	virtual void Update(iMap* pMap);
	virtual void Render();

	virtual void KeyInput();
	virtual D3DXVECTOR3& GetPosition();

	virtual D3DXMATRIXA16* GetTransform()
	{
		return &m_matWorld;
	}
};


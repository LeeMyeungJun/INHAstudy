#pragma once
class cSprite
{
public:
	cSprite();
	
protected:
	D3DXMATRIXA16		matTranslation;
	
	LPD3DXSPRITE		m_pSprite;
	D3DXIMAGE_INFO		m_stImageInfo;
	LPDIRECT3DTEXTURE9	m_pTextureUI;
	float				m_sizeX, m_sizeY;
	float				m_fX, m_fY;

	bool				m_bClickState;
	POINT				m_ptMouse;

public:
	virtual ~cSprite();
	virtual void Setup();
	virtual void Update();
	virtual void Render();

};
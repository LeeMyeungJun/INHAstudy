#pragma once
class cSprite
{
public:
	cSprite();
	
protected:
	D3DXMATRIXA16		matTranslation;
	D3DXMATRIXA16		m_matWorldTM;
	
	LPD3DXSPRITE		m_pSprite;
	D3DXIMAGE_INFO		m_stImageInfo;
	LPDIRECT3DTEXTURE9	m_pTextureUI;
public:
	virtual ~cSprite();
	virtual void Setup();
	virtual void Update();
	virtual void Render();

};
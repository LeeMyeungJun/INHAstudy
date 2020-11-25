#pragma once
class cSprite
{
public:
	cSprite();
	
protected:
	D3DXMATRIXA16		matTranslation;
	D3DXMATRIXA16		m_matWorldTM;
	
	LPD3DXSPRITE		m_pSprite;

	LPDIRECT3DTEXTURE9	m_pOffTextureUI;
	D3DXIMAGE_INFO		m_InfoOffImage;
	LPDIRECT3DTEXTURE9	m_pOnTextureUI;
	D3DXIMAGE_INFO		m_InfoOnImage;

	bool				m_btnCheck;

public:
	virtual ~cSprite();
	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual void BtnOnOff();

};
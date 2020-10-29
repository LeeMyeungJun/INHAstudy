#include "stdafx.h"
#include "cBtnSprite.h"

cBtnSprite::cBtnSprite(char* path, char* FileName)
{
	string sFullPath(path);
	sFullPath += (string("/") + string(FileName));

	m_pTextureUI = g_pUITextureManager->GetTexture(sFullPath);
	m_stImageInfo = g_pUITextureManager->GetTextureInfo(sFullPath);
}

cBtnSprite::~cBtnSprite()
{
}

void cBtnSprite::Setup(D3DXVECTOR2 vecTranslation)
{
	D3DXMatrixTranslation(&matTranslation, vecTranslation.x, vecTranslation.y, 0);
}

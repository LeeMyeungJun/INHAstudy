#include "stdafx.h"
#include "cBtnSprite.h"

cBtnSprite::cBtnSprite(char* OffBtnPath, char* OffFileName, char* OnBtnPath, char* OnFileName)
{
	string sFullPath(OffBtnPath);
	sFullPath += (string("/") + string(OffFileName));

	m_pOffTextureUI = g_pUITextureManager->GetTexture(sFullPath);
	m_InfoOffImage = g_pUITextureManager->GetTextureInfo(sFullPath);

	if (OnBtnPath == NULL)
		return;
	sFullPath = OnBtnPath;
	sFullPath += (string("/") + string(OnFileName));

	m_pOnTextureUI = g_pUITextureManager->GetTexture(sFullPath);
	m_InfoOnImage = g_pUITextureManager->GetTextureInfo(sFullPath);
	


	
}

cBtnSprite::~cBtnSprite()
{
}

void cBtnSprite::Setup(D3DXVECTOR2 vecTranslation)
{
	D3DXMatrixTranslation(&matTranslation, vecTranslation.x, vecTranslation.y, 0);
}

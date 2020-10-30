#pragma once
#include "cSpriteNode.h"
class cBtnSprite :
	public cSpriteNode
{

public:
	cBtnSprite(char* OffBtnPath, char* OffFileName , char* OnBtnPath, char* OnFileName);
	~cBtnSprite();

	virtual void Setup(D3DXVECTOR2 vecTranslation);

};


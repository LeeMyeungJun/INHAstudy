#pragma once
#include "cSpriteNode.h"
class cBtnSprite :
	public cSpriteNode
{

public:
	cBtnSprite(char* path, char* FileName);
	~cBtnSprite();

	virtual void Setup(D3DXVECTOR2 vecTranslation);

};


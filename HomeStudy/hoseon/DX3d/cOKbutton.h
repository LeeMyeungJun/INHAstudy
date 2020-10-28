#pragma once
#include "cSpriteNode.h"
class cOKbutton :
	public cSpriteNode
{
public:
	cOKbutton(char* path, char* FileName);
	~cOKbutton();

	virtual void Setup(D3DXVECTOR2 vecTranslation);

	
};


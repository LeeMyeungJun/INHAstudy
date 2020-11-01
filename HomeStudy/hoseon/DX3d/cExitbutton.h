#pragma once
#include "cSpriteNode.h"
class cExitbutton :
	public cSpriteNode
{
public:
	cExitbutton(char* path,char* FileName);
	~cExitbutton();

	virtual void Setup(D3DXVECTOR2 vecTranslation);

};


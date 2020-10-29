#pragma once
#include "cSprite.h"
class cSpriteNode:
	public cSprite
{
public:
	cSpriteNode();

protected:
	vector<cSpriteNode*>	m_vecChild;
	Synthesize(D3DXMATRIXA16*, m_pParentWorldTM, ParentWorldTM);

public:
	virtual ~cSpriteNode();
	virtual void AddChild(cSpriteNode* pChild);
	virtual void Destroy();

	virtual void Setup();
	virtual void Update();
	virtual void Render();

};


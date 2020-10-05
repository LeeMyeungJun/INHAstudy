#pragma once
#include "cCharacter.h"
class cCubeNode;

class cCubeMan :
	public cCharacter
{
public:
	cCubeMan();
	//~cCubeMan();
protected:
	cCubeNode*		m_pRoot;

	Synthesize(D3DXMATRIXA16*, m_pParentWorldTM, ParentWorldTM);
	Synthesize(float, m_fRotDeltaX, RotDeltaX);

public:
	virtual ~cCubeMan();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
};


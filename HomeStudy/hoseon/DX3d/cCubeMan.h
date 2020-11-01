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
	D3DMATERIAL9	m_stMt1;
public:
	virtual ~cCubeMan();

	virtual void Setup() override;
	virtual void Update(iMap* pMap) override;
	virtual void Render() override;

	void WalkHexa();
	void WalkBezier();
	void SetPosition(D3DXVECTOR3 _vec);
	void SetRotY(float _rot);
};


#pragma once

#include "cCubePNT.h"
class cCubeNode :
	public cCubePNT
{
public:
	cCubeNode();


public:
	virtual ~cCubeNode(void);
	virtual void AddChild(cCubeNode* pChild);
	virtual void Destroy();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
};


#include "stdafx.h"
#include "cCubeMan.h"

#include "cBody.h"
#include "cLeftArm.h"
#include "cRightArm.h"
#include "cLeftLeg.h"
#include "cRightLeg.h"
#include "cHead.h"


cCubeMan::cCubeMan()
{
}


cCubeMan::~cCubeMan()
{
	delete this;
}

void cCubeMan::Setup()
{
	cCharacter::Setup();

	cBody* pBody = new cBody;
	

}

void cCubeMan::Update()
{
}

void cCubeMan::Render()
{
}

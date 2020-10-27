#include "stdafx.h"

cObject::cObject()
	:m_ulRefCount(1) //자기자신들어왔으므로 1이다.
{
	g_pObjectManager->AddObject(this);
}


cObject::~cObject()
{
	g_pObjectManager->RemoveObject(this); //자기자신을 remove해주기 .
}

void cObject::AddRef()
{
	++m_ulRefCount;
}

void cObject::Release()
{
	--m_ulRefCount;
	
	if (m_ulRefCount == 0)//0이되면 실질적으로 안쓰는거아니야 
		delete this;
}

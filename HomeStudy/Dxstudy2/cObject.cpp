#include "stdafx.h"
<<<<<<< HEAD
#include "cObject.h"


cObject::cObject()
	:m_ulRefCount(1) //자기자신들어왔으므로 1이다.
=======


cObject::cObject()
	:m_ulRefCount(1)
>>>>>>> 41302b6992cdd6e25a5b860ae2afd9f7e1656f1b
{
	g_pObjectManager->AddObject(this);
}


cObject::~cObject()
{
<<<<<<< HEAD
	g_pObjectManager->RemoveObject(this); //자기자신을 remove해주기 .
}

void cObject::AddRef()
{
	++m_ulRefCount;
=======
	g_pObjectManager->RemoveObject(this);
}


void cObject::AddRef()
{
	m_ulRefCount++;
>>>>>>> 41302b6992cdd6e25a5b860ae2afd9f7e1656f1b
}

void cObject::Release()
{
<<<<<<< HEAD
	--m_ulRefCount;
	
	if (m_ulRefCount == 0)//0이되면 실질적으로 안쓰는거아니야 
		delete this;
=======
	m_ulRefCount--;

	if (m_ulRefCount == 0)
	{
		delete this;
	}
>>>>>>> 41302b6992cdd6e25a5b860ae2afd9f7e1656f1b
}

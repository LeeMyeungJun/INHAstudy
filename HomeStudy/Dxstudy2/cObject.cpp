#include "stdafx.h"
<<<<<<< HEAD
#include "cObject.h"


cObject::cObject()
	:m_ulRefCount(1) //�ڱ��ڽŵ������Ƿ� 1�̴�.
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
	g_pObjectManager->RemoveObject(this); //�ڱ��ڽ��� remove���ֱ� .
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
	
	if (m_ulRefCount == 0)//0�̵Ǹ� ���������� �Ⱦ��°žƴϾ� 
		delete this;
=======
	m_ulRefCount--;

	if (m_ulRefCount == 0)
	{
		delete this;
	}
>>>>>>> 41302b6992cdd6e25a5b860ae2afd9f7e1656f1b
}

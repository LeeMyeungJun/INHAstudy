#include "stdafx.h"

cObject::cObject()
	:m_ulRefCount(1) //�ڱ��ڽŵ������Ƿ� 1�̴�.
{
	g_pObjectManager->AddObject(this);
}


cObject::~cObject()
{
	g_pObjectManager->RemoveObject(this); //�ڱ��ڽ��� remove���ֱ� .
}

void cObject::AddRef()
{
	++m_ulRefCount;
}

void cObject::Release()
{
	--m_ulRefCount;
	
	if (m_ulRefCount == 0)//0�̵Ǹ� ���������� �Ⱦ��°žƴϾ� 
		delete this;
}

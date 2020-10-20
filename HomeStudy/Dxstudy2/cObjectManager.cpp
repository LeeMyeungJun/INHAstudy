#include "stdafx.h"
<<<<<<< HEAD
#include "cObjectManager.h"
=======
>>>>>>> 41302b6992cdd6e25a5b860ae2afd9f7e1656f1b


cObjectManager::cObjectManager()
{
}


cObjectManager::~cObjectManager()
{
}

<<<<<<< HEAD
void cObjectManager::AddObject(cObject* pObject)
=======
void cObjectManager::AddObject(cObject * pObject)
>>>>>>> 41302b6992cdd6e25a5b860ae2afd9f7e1656f1b
{
	m_setObject.insert(pObject);
}

<<<<<<< HEAD
void cObjectManager::RemoveObject(cObject* pObject)
=======
void cObjectManager::RemoveObject(cObject * pObject)
>>>>>>> 41302b6992cdd6e25a5b860ae2afd9f7e1656f1b
{
	m_setObject.erase(pObject);
}

void cObjectManager::Destroy()
{
	m_setObject.clear();
}

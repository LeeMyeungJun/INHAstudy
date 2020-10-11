#pragma once

#define g_pObjectManager cObjectManager::GetInstance()

class cObjectManager //ΩÃ±€≈Ê¿∏∑Œ∏∏µÈøπ¡§ 
{
//public:
//	cObjectManager();
//	~cObjectManager();

private:
	Singletone(cObjectManager);
	set<cObject*> m_setObject;

public:
	void AddObject(cObject* pObject);
	void RemoveObject(cObject* pObject);
	void Destroy();
	
};


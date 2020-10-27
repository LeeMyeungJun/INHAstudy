#pragma once

class cObjectManager //ΩÃ±€≈Ê¿∏∑Œ∏∏µÈøπ¡§ 
{

private:
	Singleton(cObjectManager);
	set<cObject*> m_setObject;

public:
	void AddObject(cObject* pObject);
	void RemoveObject(cObject* pObject);
	void Destroy();
	
};

#define g_pObjectManager cObjectManager::GetInstance()

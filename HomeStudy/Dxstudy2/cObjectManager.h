#pragma once
class cObject;
#define g_pObjectManager cObjectManager::GetInstance()


class cObjectManager
{
//public:
//	cObjectManager();
//	~cObjectManager();
private:
	set<cObject*> m_setObject;

public:
	void AddObject(cObject* pObject);
	void RemoveObject(cObject* pObject);
	void Destroy();


private:
	Singletone(cObjectManager);
};


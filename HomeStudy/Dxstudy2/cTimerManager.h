#pragma once

#define g_pTimeManager cTimerManager::GetInstance();

class cTimerManager
{
//public:
//	cTimerManager();
//	~cTimerManager();

private:
	Singletone(cTimerManager);

private:
	DWORD		m_dwLastUpdateTime;
	float		m_fElapsedTime;

public:
	void Update();
	float GetElapsedTime();
	float GetLastUpdateTime();
};


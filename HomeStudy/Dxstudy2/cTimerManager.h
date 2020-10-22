#pragma once


class cTimerManager
{
//public:
//	cTimerManager();
//	~cTimerManager();

private:
	Singleton(cTimerManager);

private:
	DWORD		m_dwLastUpdateTime;
	float		m_fElapsedTime;

public:
	void Update();
	float GetElapsedTime();
	float GetLastUpdateTime();
};

#define g_pTimeManager cTimerManager::GetInstance()
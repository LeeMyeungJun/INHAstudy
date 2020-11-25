#include "stdafx.h"


EventManager::EventManager()
	:m_eEvent(EEvent::E_NONE)
{
}

EventManager::~EventManager()
{
}

void EventManager::Attach(EEvent eEvent, Observer* observer)
{
	for(int i = 0 ; i < m_mapEventMap[eEvent].size(); i++)
	{
		if(m_mapEventMap[eEvent][i] == observer)
			return;
	}
	
	m_mapEventMap[eEvent].push_back(observer);
}

bool EventManager::Detach(EEvent eEvent, Observer* observer)
{
	std::vector<Observer*>::iterator it = std::find(m_mapEventMap[eEvent].begin(), m_mapEventMap[eEvent].end(), observer);

	if (it != m_mapEventMap[eEvent].end())
	{
		m_mapEventMap[eEvent].erase(it);
		return true;
	}
	return false;
}


void EventManager::Notify(void* value)
{
	std::vector<Observer *>::iterator iterator = m_mapEventMap[m_eEvent].begin();

	while (iterator != m_mapEventMap[m_eEvent].end())
	{
		(*iterator)->OnEvent(m_eEvent, value);
		++iterator;
	}
}

void EventManager::EventCall(EEvent eEvent, void* value)
{	
	m_eEvent = eEvent;
	Notify(value);
}

void EventManager::ErrorSend()
{
	std::cout << "publisher또는 subscriber 가 없습니다." << std::endl;
}

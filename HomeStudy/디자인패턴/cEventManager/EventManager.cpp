#include "stdafx.h"


EventManager::EventManager()
		: m_evnet_num_(0)
		, m_subtract(NULL)
{
}

EventManager::~EventManager()
{
}

void EventManager::Attach(Publisher* publisher, Observer* observer)
{
	if(m_map_EventList.find(publisher) == m_map_EventList.end())
	{
		std::vector<Observer*> vecTemp;
		vecTemp.push_back(observer);
		m_map_EventList[publisher] = vecTemp;

		return;
	}
	m_map_EventList[publisher].push_back(observer);
}

void EventManager::Detach(Observer* observer)
{

	for each(auto it in m_map_EventList)
	{

		for(int i = 0 ; i <it.second.size(); i++)
		{
			if(it.second[i] == observer)
			{
				SafeDelete(observer);
			}
		}
	
	}

	
	m_list_observer_.remove(observer);
}

void EventManager::Detach(Publisher* publisher)
{
}

void EventManager::Notify()
{
	std::list<Observer *>::iterator iterator = m_list_observer_.begin();

	while (iterator != m_list_observer_.end())
	{
		(*iterator)->Update(m_subtract,m_evnet_num_);
		++iterator;
	}
}

void EventManager::EventNumber(Observer* _subtract, size_t event_num)
{
	m_subtract = _subtract;
	m_evnet_num_ = event_num;
	Notify();

}


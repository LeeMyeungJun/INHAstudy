#include "stdafx.h"


EventManager::EventManager()
		:evnet_num_(0)
{
}

EventManager::~EventManager()
{
}

void EventManager::Attach(Observer* observer)
{
	list_observer_.push_back(observer);
}

void EventManager::Detach(Observer* observer)
{
	list_observer_.remove(observer);
}

void EventManager::Notify()
{
	std::list<Observer *>::iterator iterator = list_observer_.begin();

	while (iterator != list_observer_.end()) 
	{
		(*iterator)->Update(evnet_num_);
		++iterator;
	}
}

void EventManager::EventNumber(size_t event_num)
{
	evnet_num_ = event_num;
	Notify();
}


#pragma once

#define g_EventManager EventManager::GetInstance()

class Observer;

class EventManager
{
private:
	EventManager();
	~EventManager();


public:
	void Attach(Observer *observer);
	void Detach(Observer *observer);
	void Notify();
	void EventNumber(size_t event_num);

private:
	std::list<Observer *> list_observer_;
	size_t evnet_num_;

public:
	static EventManager* GetInstance()
	{
		static EventManager instance;
		return &instance;
	}

};



#pragma once

#define g_EventManager EventManager::GetInstance()


class Observer;
class Publisher;

class EventManager
{
private:
	EventManager();
	~EventManager();


public:
	void Attach(Publisher* publisher,Observer* observer);
	void Detach(Observer* observer);
	void Detach(Publisher* publisher);
	void Notify();
	void EventNumber(Observer* _subtract,size_t event_num);

private:
	std::map<Publisher*, std::vector<Observer*>> m_map_EventList;

	
	std::list<Observer *> m_list_observer_;
	
	size_t m_evnet_num_;
	Observer* m_subtract;

public:
	static EventManager* GetInstance()
	{
		static EventManager instance;
		return &instance;
	}

};



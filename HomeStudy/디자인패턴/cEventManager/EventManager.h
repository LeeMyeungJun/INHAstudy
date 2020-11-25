#pragma once

#define g_EventManager EventManager::GetInstance()

class Observer;


enum class EEvent
{
	E_DEFAULT,
	E_ATTACK,
	E_SLEEP,
	E_NONE
};

struct ST_AttackEvent
{
	std::string name;
	int age;
	ST_AttackEvent():age(0){}
};

class EventManager
{
private:
	EventManager();
	~EventManager();

public:
	void Attach(EEvent eEvent,Observer* observer);
	bool Detach(EEvent eEvent, Observer* observer);
	void Notify(void* value);
	void EventCall(EEvent eEvent, void* value);
	void ErrorSend();

private:
	std::map<EEvent, std::vector<Observer*>> m_mapEventMap;
	EEvent m_eEvent;

public:
	static EventManager* GetInstance()
	{
		static EventManager instance;
		return &instance;
	}

};



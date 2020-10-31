#pragma once


#include "ISubject.h"
class Subject :
	public ISubject
{
public:
	Subject();
	virtual ~Subject();

	/**
	* The subscription management methods.
	*/
	void Attach(IObserver *observer) override;
	void Detach(IObserver *observer) override;
	void Notify() override;

	void CreateMessage(std::string message = "Empty");
	void HowManyObserver();
	void SomeBusinessLogic();

private:
	std::list<IObserver *> list_observer_;
	std::string message_;
};


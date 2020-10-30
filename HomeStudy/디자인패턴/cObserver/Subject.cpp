#include "stdafx.h"
#include "Subject.h"




Subject::Subject()
{
}


Subject::~Subject()
{
}

void Subject::Attach(IObserver* observer)
{
	list_observer_.push_back(observer);
}

void Subject::Detach(IObserver* observer)
{
	list_observer_.remove(observer);
}

void Subject::Notify()
{
	std::list<IObserver *>::iterator iterator = list_observer_.begin();
	HowManyObserver();
	while (iterator != list_observer_.end()) {
		(*iterator)->Update(message_);
		++iterator;
	}
}

void Subject::CreateMessage(std::string message)
{
	this->message_ = message;
	Notify();
}

void Subject::HowManyObserver()
{
	std::cout << "There are " << list_observer_.size() << " observers in the list.\n";
}

void Subject::SomeBusinessLogic()
{
	this->message_ = "change message message";
	Notify();
	std::cout << "I'm about to do some thing important\n";
}

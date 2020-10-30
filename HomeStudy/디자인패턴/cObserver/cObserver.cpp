// cObserver.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"



int Observer::static_number_ = 0;

int main()
{
	Subject *subject = new Subject;//�Ѱ�ü�� 
	Observer *observer1 = new Observer(*subject);
	Observer *observer2 = new Observer(*subject);
	Observer *observer3 = new Observer(*subject);
	Observer *observer4;
	Observer *observer5;
	
	subject->CreateMessage("Hello World! :D");
	observer3->RemoveMeFromTheList();

	subject->CreateMessage("The weather is hot today! :p");
	observer4 = new Observer(*subject);

	observer2->RemoveMeFromTheList();
	observer5 = new Observer(*subject);

	subject->CreateMessage("My new car is great! ;)");
	observer5->RemoveMeFromTheList();

	observer4->RemoveMeFromTheList();
	observer1->RemoveMeFromTheList();

	delete observer5;
	delete observer4;
	delete observer3;
	delete observer2;
	delete observer1;
	delete subject;

    return 0;
}


#pragma once
#include "BaseComponent.h"
class Component1 :
	public BaseComponent
{
public:
	Component1();
	~Component1();

	void DoA() {
		std::cout << "Component 1 does A.\n";
		this->mediator_->Notify(this, "A");
	}
	void DoB() {
		std::cout << "Component 1 does B.\n";
		this->mediator_->Notify(this, "B");
	}
	
};


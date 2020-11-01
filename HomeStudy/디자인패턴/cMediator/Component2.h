#pragma once
#include "BaseComponent.h"
class Component2 :
	public BaseComponent
{
public:
	Component2();
	~Component2();

	void DoC() {
		std::cout << "Component 2 does C.\n";
		this->mediator_->Notify(this, "C");
	}
	void DoD() {
		std::cout << "Component 2 does D.\n";
		this->mediator_->Notify(this, "D");
	}
};



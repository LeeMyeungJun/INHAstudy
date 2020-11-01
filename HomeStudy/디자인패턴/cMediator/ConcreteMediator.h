#pragma once
#include "Mediator.h"
class BaseComponent;
class Component1;
class Component2;

class ConcreteMediator :
	public Mediator
{

private:
	Component1 *component1_;
	Component2 *component2_;
	
public:
	ConcreteMediator(Component1 *c1, Component2 *c2);
	~ConcreteMediator();

	void Notify(BaseComponent *sender, std::string event) const override;
};


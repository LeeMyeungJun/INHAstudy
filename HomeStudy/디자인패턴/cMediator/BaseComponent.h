#pragma once
class BaseComponent
{
protected:
	Mediator *mediator_;
	
public:
	BaseComponent(Mediator *mediator = nullptr);
	~BaseComponent();

	void set_mediator(Mediator *mediator);
};


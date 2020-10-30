#include "stdafx.h"


BaseComponent::BaseComponent(Mediator *mediator) : mediator_(mediator)
{
}


BaseComponent::~BaseComponent()
{
}

void BaseComponent::set_mediator(Mediator* mediator)
{
	this->mediator_ = mediator;
}

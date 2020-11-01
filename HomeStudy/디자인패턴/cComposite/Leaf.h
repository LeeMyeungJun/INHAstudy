#pragma once
#include "Component.h"
class Leaf :
	public Component
{
public:
	std::string Operation() const override;
};


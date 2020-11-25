#pragma once
#include "State.h"
class RunState :
	public State
{
public:
	RunState();
	~RunState();
	void Update();
};


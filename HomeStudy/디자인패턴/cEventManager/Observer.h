#pragma once
class Observer
{
public:
	virtual ~Observer(){};
	virtual void OnEvent(EEvent eEvent,void* _value) = 0;
};


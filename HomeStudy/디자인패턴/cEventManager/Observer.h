#pragma once
class Observer
{
public:
	virtual ~Observer(){};
	virtual void Update(const int EventNumver) = 0;
};


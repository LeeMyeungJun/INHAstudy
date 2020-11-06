#pragma once
class Observer
{
public:
	virtual ~Observer(){};
	virtual void Update(Observer* _subTract,const int eventNumver) = 0;
};


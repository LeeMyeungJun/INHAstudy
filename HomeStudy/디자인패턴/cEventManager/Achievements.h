#pragma once

class Achievements :
	public Observer
{
public:
	Achievements();
	virtual ~Achievements();
	virtual void OnEvent(EEvent eEvent, void* _value)override;

};


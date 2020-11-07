#pragma once

class Audio :
	public Observer
{
public:
	Audio();
	virtual~Audio();
	virtual void OnEvent(EEvent eEvent, void* _value)override;

};


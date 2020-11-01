#pragma once

class Audio :
	public Observer
{
public:
	Audio();
	virtual~Audio();
	virtual void Update(const int EventNumver)override;

};


#pragma once

class Audio :
	public Observer, public Publisher
{
public:
	Audio();
	virtual~Audio();
	virtual void Update(Observer* _subTract, const int eventNumver)override;

};


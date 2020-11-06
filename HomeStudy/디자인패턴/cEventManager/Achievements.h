#pragma once

class Achievements :
	public Observer, public Publisher
{
public:
	Achievements();
	virtual ~Achievements();
	virtual void Update(Observer* _subTract, const int eventNumver)override;

};


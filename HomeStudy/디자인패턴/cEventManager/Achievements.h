#pragma once

class Achievements :
	public Observer
{
public:
	Achievements();
	virtual ~Achievements();
	virtual void Update(const int EventNumver)override;

};


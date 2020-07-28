#pragma once

using namespace std;

class stopwatch
{
private:
	long		startTime;
	long		endTime;
public:

	double getStartTime() { return startTime; }
	double getendTime() { return endTime; }
	void setStartTime();
	void setEndTime();
	double getElapsesedTime();

	stopwatch();
	~stopwatch();
};


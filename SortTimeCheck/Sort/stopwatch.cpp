#include "stopwatch.h"
#include <sys/timeb.h>
#include <time.h>
#include <iostream>



stopwatch::stopwatch()
{
	startTime = 0;
	endTime = 0;
}


stopwatch::~stopwatch()
{

}

void stopwatch::setStartTime()
{
	clock_t start = clock();

	startTime = start;
}

void stopwatch::setEndTime()
{
	clock_t end = clock();
	endTime = end;
}

double stopwatch::getElapsesedTime()
{
	if (startTime == 0 || endTime == 0)
		cout << "시작시간 혹은 종료시간을 선언을 안했습니다.";


	return (double)(endTime - startTime) / 1000;
}


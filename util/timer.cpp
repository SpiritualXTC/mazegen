/********************************************************************
File: timer.cpp
Author: s3435406
********************************************************************/
#include "timer.h"

using namespace util;

/*

*/
Timer::Timer()
{
	_previousTime = CHRONO::now();
}

/*

*/
Timer::~Timer()
{

}


/*

*/
float Timer::time()
{
	CHRONO::time_point currentTime = CHRONO::now();
	
	// Calculate Time
	float ms = (currentTime - _previousTime).count() 
		/ (float)CHRONO::period::den;

	// Set Current Time
	_previousTime = currentTime;

	return ms * Timer::MILLISECONDS;
}
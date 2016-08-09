/********************************************************************
File: random.cpp
Author: s3435406
********************************************************************/
#include "random.h"

#include <chrono>


using namespace util;


// Keep the compiler happy ><
std::mt19937 Random::_twister;


/*
	Seed the Random Number Generator using the Current Time
*/
uint32_t Random::seed()
{
	int32_t time = (int32_t)std::chrono::system_clock::now()
		.time_since_epoch().count();

	return seed(time);
}

/*
	Seed the Random Number Generator using the Passed Value
*/
uint32_t Random::seed(uint32_t seed_no)
{
	_twister.seed(seed_no);

	return seed_no;
}



/*
	Generate A Random Number!
*/
uint32_t Random::generate()
{
	return _twister();
}

/*
	Generate a Random Number with a Maximum
*/
uint32_t Random::generate(uint32_t max)
{
	return generate() % max;
}

/*
	Generate a Random Number between min / max
*/
uint32_t Random::generate(uint32_t min, uint32_t max)
{
	return generate() % (max - min) + min;
}



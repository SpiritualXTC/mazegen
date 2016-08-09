#pragma once
/********************************************************************
File: random.h
Author: s3435406
Desc: Interface for handling numerous random number generators.

Has been simplified down a bit to only allowing access to the 
same RNG via a static class. May update it for Singleton...
without all the fancy template stuff that was originally planned

Originally was a singleton pattern for any implementation of 
IRandom.
********************************************************************/


#include <cstdint>
#include <random>

namespace util
{
	/*
		Simple Static Access to a Random Number Generator.
		
		TODO:
		Could make this so it could be any type of Random 
		Number Generator, using an interface / templates
	*/
	class Random
	{
	public:

		static uint32_t seed();
		static uint32_t seed(uint32_t seed);

		static uint32_t generate();
		static uint32_t generate(uint32_t max);
		static uint32_t generate(uint32_t min, uint32_t max);
		 

	private:
		static std::mt19937 _twister;
		//std::unique_ptr<IRandom> _rng = nullptr;


	private:
		Random() {}
		virtual ~Random() {}
	};

}

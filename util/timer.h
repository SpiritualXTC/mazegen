#pragma once
/********************************************************************
File: timer.h
Author: s3435406
Desc: Timer class for benchmarking
********************************************************************/


#include <chrono>

namespace util
{
	/*
	
	*/
	class Timer
	{
	public:
		static const int MILLISECONDS = 1000;

	private:
		typedef std::chrono::system_clock CHRONO;

	public:
		Timer();
		virtual ~Timer();

		float time();

	private:


		CHRONO::time_point _previousTime;
	};
}
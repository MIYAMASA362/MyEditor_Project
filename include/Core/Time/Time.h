#pragma once
#ifndef CORE_TIME_H
#define CORE_TIME_H

#include<chrono>

namespace Core
{
	/**
	* @class    Time
	* @brief    
	*/
	class Time
	{
	public:
		using NanoSeconds = std::chrono::nanoseconds;
		using MicroSeconds = std::chrono::microseconds;
		using MilliSeconds = std::chrono::milliseconds;
		using Seconds = std::chrono::seconds;
		using Hours = std::chrono::hours;

	protected:

	private:

	};// class Time

}// namespace Core

#endif // ifndef CORE_TIME_H
#include "stdafx.h"
#include "Timer.h"
#include "TimerManager.h"
#include <iostream>

Timer::Timer(std::string function, TimerFlags flags)
{
	_flags = flags;
	_function = function;
	_start = std::chrono::high_resolution_clock::now();
}

Timer::Timer(std::string function, std::string classname, TimerFlags flags)
{
	_flags = flags;
	_function = function;
	_class = classname;
	_start = std::chrono::high_resolution_clock::now();
}

Timer::~Timer()
{
	_end = std::chrono::high_resolution_clock::now();
	_duration = _end - _start;

	float ms = _duration.count() * 1000.0f;
	std::string prefix;
	
	if (!_class.empty())
		prefix.append(_class);
	
	if (!_function.empty())
	{
		if (!prefix.empty())
			prefix.append("::");

		prefix.append(_function);
	}
	if (!(_flags & kTimerNoOutput))
		std::cout << prefix << " : " << ms << " ms" << std::endl;

	TimerManager::Instance().AddData(prefix, ms);
}

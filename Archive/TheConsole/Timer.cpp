#include "stdafx.h"
#include "Timer.h"
#include "TimerManager.h"
#include <iostream>

Timer::Timer(std::string key, TimerFlags flags)
{
	if (key.empty())
		throw "Timer key is empty";

	_key = key;
	_flags = flags;

	_start = std::chrono::high_resolution_clock::now();
}

Timer::~Timer()
{
	_end = std::chrono::high_resolution_clock::now();
	_duration = _end - _start;

	float ms = _duration.count() * 1000.0f;
		
	if (!(_flags & kTimerNoOutput))
		std::cout << _key << " : " << ms << " ms" << std::endl;

	TimerManager::Instance().AddData(_key, ms);
}

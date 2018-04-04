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

	_start = std::chrono::steady_clock::now();
}

Timer::~Timer()
{
	_end = std::chrono::steady_clock::now();
	auto microseconds_duration = std::chrono::duration_cast<std::chrono::microseconds>(_end - _start);
	auto milliseconds_duration = std::chrono::duration_cast<std::chrono::milliseconds>(_end - _start);
	auto seconds_duration = std::chrono::duration_cast<std::chrono::seconds>(_end - _start);

	if (!(_flags & kTimerNoOutput))
		std::cout << _key << " : duration = " << microseconds_duration.count() << " microseconds " << milliseconds_duration.count() << " milliseconds " << seconds_duration.count() << " seconds" << std::endl;

	if (!(_flags & kTimerNoLog))
		TimerManager::Instance().AddData(_key, microseconds_duration.count(), milliseconds_duration.count(), seconds_duration.count());
}

bool Timer::operator==(const Timer &other)
{
	if (this->_end != other._end)
		return false;
	if (this->_flags != other._flags)
		return false;
	if (this->_key != other._key)
		return false;
	if (this->_start != other._start)
		return false;
	return true;
}

bool Timer::operator!=(const Timer &other)
{
	return !(*this == other);
}

Timer& Timer::operator=(const Timer & other)
{
	if (*this != other)
	{
		this->_end = other._end;
		this->_flags = other._flags;
		this->_key = other._key;
		this->_start = other._start;
	}

	return *this;
}
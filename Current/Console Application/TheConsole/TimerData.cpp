#include "stdafx.h"
#include "TimerData.h"
#include "TimerManager.h"
#include <iostream>

TimerData::TimerData()
{
}


TimerData::~TimerData()
{
}

void TimerData::PrintReport()
{
	TimerManager::Instance().PrintLine( std::string( _info + " took " + std::to_string(_time_microseconds) + " microseconds " + std::to_string(_time_milliseconds) + " milliseconds " + std::to_string(_time_seconds) + " seconds"  ));
}

void TimerData::SetInfo(std::string info)
{
	_info = info;
}

void TimerData::SetTime(long long time_microseconds, long long time_milliseconds, long long time_seconds)
{
	_time_microseconds = time_microseconds;
	_time_milliseconds = time_milliseconds;
	_time_seconds = time_seconds;
}

std::string TimerData::GetInfo()
{
	return _info;
}

long long TimerData::GetTime(TimeOptions timeOption)
{
	if (timeOption == kTimeOptionMicroseconds)
		return _time_microseconds;
	else if (timeOption == kTimeOptionMilliseconds)
		return _time_milliseconds;
	else
		return _time_seconds;
}
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
	TimerManager::Instance().PrintLine( std::string( _info + " took " + std::to_string(_time) + " ms" ));
}

void TimerData::SetInfo(std::string info)
{
	_info = info;
}

void TimerData::SetTime(float time)
{
	_time = time;
}

std::string TimerData::GetInfo()
{
	return _info;
}

float TimerData::GetTime()
{
	return _time;
}
#include "stdafx.h"
#include "TimerManager.h"
#include "TimerData.h"
#include <iostream>
#include <string>

TimerManager::TimerManager()
{
	_indent = 0;
}


TimerManager::~TimerManager()
{
}

void TimerManager::AddData(std::string info, long long time_microseconds, long long time_milliseconds, long long time_seconds)
{
	TimerData data;
	data.SetInfo(info);
	data.SetTime(time_microseconds, time_milliseconds, time_seconds);

	_data.push_back(data);
}

void TimerManager::PushIndent()
{
	_indent++;
}

void TimerManager::PopIndent()
{
	_indent--;
}

void TimerManager::PrintReport()
{
	using namespace std;

	cout << endl << string(80, '=') << endl << "Timer Manager Report" << endl << endl;

	PushIndent();
	{
		PrintLine(std::string("Data Count = " + std::to_string(_data.size())));
		PrintLine("");

		PushIndent();
		{
			for (size_t i = 0; i < _data.size(); i++)
			{
				_data[i].PrintReport();
			}
		}
		PopIndent();
	}
	PopIndent();

	cout << endl << "End of Timer Manager Report" << endl << string(80, '=') << endl << endl;
}

void TimerManager::PrintLine(std::string line)
{
	std::cout << std::string(_indent, '\t') << line << std::endl;
}

void TimerManager::Average(std::string info)
{
	std::vector<TimerData> common;
	for (size_t i = 0; i < _data.size(); i++)
	{
		if (!_data[i].GetInfo().compare(0, info.size(), info))
			common.push_back(_data[i]);
	}

	TimerData timerdata;
	timerdata.SetInfo("AVERAGE:  " + info);
	auto count = common.size();
	if (count == 0)
	{
		_data.push_back(timerdata);
		return;
	}

	long long microseconds = 0;
	long long milliseconds = 0;
	long long seconds = 0;
	for (size_t i = 0; i < count; i++)
	{
		microseconds += common[i].GetTime(kTimeOptionMicroseconds);
		milliseconds += common[i].GetTime(kTimeOptionMilliseconds);
		seconds += common[i].GetTime(kTimeOptionSeconds);
	}

	timerdata.SetTime(microseconds / count, milliseconds / count, seconds / count);
	_data.push_back(timerdata);
}
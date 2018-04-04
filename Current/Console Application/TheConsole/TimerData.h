#pragma once
#include <string>

enum TimeOptions
{
	kTimeOptionMicroseconds,
	kTimeOptionMilliseconds,
	kTimeOptionSeconds
};
class TimerData
{
public:
	TimerData();
	~TimerData();
	
	void PrintReport();

	void SetInfo(std::string);
	void SetTime(long long time_microseconds, long long time_milliseconds, long long time_seconds);

	std::string GetInfo();
	long long GetTime(TimeOptions timeOption);

private:
	std::string _info;
	long long _time_microseconds;
	long long _time_milliseconds;
	long long _time_seconds;
};


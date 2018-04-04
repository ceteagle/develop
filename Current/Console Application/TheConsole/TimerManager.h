#pragma once
#include <string>
#include <vector>

class TimerData;

class TimerManager
{
public:
	TimerManager();
	~TimerManager();

	static TimerManager & Instance()
	{
		static TimerManager manager;
		return manager;
	}

	void AddData(std::string info, long long time_microseconds, long long time_milliseconds, long long time_seconds);
	void PrintReport();
	void PushIndent();
	void PopIndent();
	
	void PrintLine(std::string line);

private:
	static TimerManager * _manager;
	std::vector<TimerData> _data;
	unsigned int _indent;
};


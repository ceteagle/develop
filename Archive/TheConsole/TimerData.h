#pragma once
#include <string>

class TimerData
{
public:
	TimerData();
	~TimerData();
	
	void PrintReport();

	void SetInfo(std::string);
	void SetTime(float time);

	std::string GetInfo();
	float GetTime();

private:
	std::string _info;
	float _time;
};


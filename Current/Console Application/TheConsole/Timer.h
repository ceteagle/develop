#pragma once
#include <chrono>
#include <string>

enum TimerFlags
{
	kTimerNone = 0,
	kTimerNoOutput = 0x00000001,
	kTimerNoLog = 0x00000002
};

class Timer
{
public:
	Timer(std::string key, TimerFlags flags=kTimerNone);
	~Timer();

	bool operator==(const Timer &other);
	bool operator!=(const Timer &other);
	Timer& operator=(const Timer & other);

private:
	std::chrono::time_point<std::chrono::steady_clock> _start, _end;
	std::string _key;
	TimerFlags _flags;
};


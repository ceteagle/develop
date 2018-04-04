#pragma once
#include <chrono>
#include <string>

enum TimerFlags
{
	kTimerNone = 0,
	kTimerNoOutput = 0x00000001
};

class Timer
{
public:
	Timer(std::string key, TimerFlags flags=kTimerNone);
	~Timer();

private:
	std::chrono::time_point<std::chrono::steady_clock> _start, _end;
	std::chrono::duration<float> _duration;
	std::string _key;
	TimerFlags _flags;
};


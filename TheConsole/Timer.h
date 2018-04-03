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
	Timer(std::string function, TimerFlags flags=kTimerNone);
	Timer(std::string function, std::string classname, TimerFlags flags = kTimerNone);
	~Timer();

private:
	std::chrono::time_point<std::chrono::steady_clock> _start, _end;
	std::chrono::duration<float> _duration;
	std::string _function;
	std::string _class;
	
	TimerFlags _flags;
};


// TheConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ConsoleOutput.h"
#include "Timer.h"
#include "TimerManager.h"

void TestFunc(int test)
{
	Timer t("TestFunc", kTimerNoOutput);
	int count = 0;
	while (true)
	{
		if (count >= test)
			break;
		count++;
	}
}

int main()
{
	ConsoleOutput * out = new ConsoleOutput();

	TestFunc(100);
	TestFunc(1000);
	TestFunc(10);
	TestFunc(599);

	out->ClearScreen();

	delete out;

	TimerManager::Instance().PrintReport();

    return 0;
}


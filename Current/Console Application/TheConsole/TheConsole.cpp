// TheConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "CodeControlTest.h"
#include "ConsoleOutput.h"
#include "MapSearchTest.h"
#include "StackManager.h"
#include "Timer.h"
#include "TimerManager.h"

#include <iostream>
#include <thread>
#include <time.h>

void TestFunc(int test)
{
	Timer t(std::string("TestFunc(int " + std::to_string(test) + ")"), kTimerNoOutput);
	std::this_thread::sleep_for(std::chrono::microseconds(test));
}

// Function to calculate
// Fibonacci series
unsigned int fibonacci(unsigned int n)
{
	if (n < 2)
	{
		return n;
	}
	return fibonacci(n - 1) + fibonacci(n - 2);
}

void doFib(unsigned n)
{
	Timer t(std::string("fibonacci(int " + std::to_string(n) + ")"), kTimerNoOutput);

	auto num = fibonacci(n);
	std::cout << "fib of " << n << " is " << num << std::endl;
}

void ObjectConstructorTest()
{
	{
		for (size_t i = 0; i < 5; i++)
		{
			Timer t("MapSearchTest Object Creation");
			MapSearchTest mst;
		}

		for (size_t i = 0; i < 5; i++)
		{
			Timer t("MapSearchTest Object Creation and Deletion");
			MapSearchTest* mst = new MapSearchTest();;
			if (mst != NULL)
				delete mst;
		}
		
	}
}

int main()
{
	//ConsoleOutput * out = new ConsoleOutput();

	//for (size_t i = 0; i < 100; i++)
	//{
	//	TestFunc(1000);
	//}
	//TestFunc(1000000);
	//TestFunc(10);
	//TestFunc(599);

	//out->ClearScreen();
	//delete out;

	//doFib(42);

	//iterObjectConstructorTest();

	MapSearchTest maptest;
	maptest.DoMapLookupTest();

	maptest.DoMultiMapLookupTest();

	CodeControlTest controltest;
	controltest.SwitchControlTest();

	TimerManager::Instance().PrintReport();

	return 0;
}


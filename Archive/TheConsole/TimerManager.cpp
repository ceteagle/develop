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

void TimerManager::AddData(std::string info, float time)
{
	TimerData data;
	data.SetInfo(info);
	data.SetTime(time);

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

	cout <<endl << "End of Timer Manager Report" << endl << string(80, '=') << endl << endl;
}

void TimerManager::PrintLine(std::string line)
{
	std::cout << std::string(_indent, '\t') << line << std::endl;
}
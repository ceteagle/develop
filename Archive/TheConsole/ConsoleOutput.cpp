#include "stdafx.h"
#include "ConsoleOutput.h"
#include <iostream>
#include "Timer.h"

using namespace std;

ConsoleOutput::ConsoleOutput()
{
	cout << "Console" << endl;
	system("cls");

}

ConsoleOutput::~ConsoleOutput()
{
}

void ConsoleOutput::ClearScreen()
{
	Timer t("ConsoleOutput::ClearScreen()");
}

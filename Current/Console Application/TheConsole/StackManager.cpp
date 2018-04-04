#include "stdafx.h"
#include "StackManager.h"
#include <iostream>

StackManager::StackManager()
{
	_stack = 0;
}

StackManager::~StackManager()
{
}

void StackManager::Push()
{
	_stack++;
	std::cout << "Stack Manager Position " << _stack << std::endl;
}

void StackManager::Pop()
{
	_stack--;
}

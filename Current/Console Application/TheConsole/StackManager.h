#pragma once
class StackManager
{
public:
	StackManager();
	~StackManager();

	static StackManager & Instance()
	{
		static StackManager manager;
		return manager;
	}

	void Push();
	void Pop();

private:
	unsigned int _stack;
};


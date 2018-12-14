#pragma once

#include <vector>
#include <fstream>

class Day14
{
public:
	Day14();
	~Day14();

	void Run();
	bool CheckForRecipe(int target, int numdigits);
	void PrintScores();
	void WriteToFile();

	std::vector<int> _recipes;
	int _elf1idx;
	int _elf2idx;
	std::ofstream _myfile;
};


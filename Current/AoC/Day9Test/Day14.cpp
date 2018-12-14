#include "Day14.h"
#include <iostream>
#include <fstream>

using namespace std;

Day14::Day14()
{
	_recipes.push_back(3);
	_recipes.push_back(7);
	_elf1idx = 0;
	_elf2idx = 1;
}


Day14::~Day14()
{
}

void Day14::Run()
{
	//int targetnum = 503761;	// Actual
	int targetnum = 503761;
	
	vector<int> target = { 5,0,3,7,6,1 };	// Actual
	//vector<int> target = { 5,1,5,8,9 };	// Test
	//vector<int> target = { 0,1,2,4,5 };	// Test
	//vector<int> target = { 9,2,5,1,0 };	// Test
	//vector<int> target = { 5,9,4,1,4 };	// Test

	const int numdigits = target.size();;
	
	int nummatches = 0;

	//while (_recipes.size() < (target + 10))		// Part 1
	while(true)
	{
		if (_recipes.size() == (targetnum + 10))
		{
			cout << "Part 1 ";
			int start = _recipes.size() - 10;
			for (int i = start; i < _recipes.size(); i++)
			{
				std::cout << _recipes[i];
			}
			cout << endl;
		}
		//PrintScores();
		int score = _recipes[_elf1idx] + _recipes[_elf2idx];
		int newscore1 = 0;
		int newscore2 = 0;
		
		if (score >= 10)
		{
			score -= 10;
			newscore1 = 1;
			newscore2 = score;
			_recipes.push_back(newscore1);


			if (target[nummatches] == newscore1)
				nummatches++;
			else
				nummatches = 0;
			
			if (nummatches != numdigits)
			{
				_recipes.push_back(newscore2);
				if (target[nummatches] == newscore2)
					nummatches++;
				else if (nummatches > 0)
				{
					nummatches = 0;
					if (target[nummatches] == newscore2)
						nummatches++;
				}
				else
					nummatches = 0;
			}
		}
		else
		{
			newscore1 = score;
			_recipes.push_back(newscore1);

			if (target[nummatches] == newscore1)
				nummatches++;
			else
				nummatches = 0;
		}

		if (nummatches == numdigits)
			break;

		int elf1idx = (_elf1idx + 1 + _recipes[_elf1idx]) % _recipes.size();
		int elf2idx = (_elf2idx + 1 + _recipes[_elf2idx]) % _recipes.size();

		_elf1idx = elf1idx;
		_elf2idx = elf2idx;
	}

	/*cout << "Write to file" << endl;
	_myfile.open("day14debug.txt");
	WriteToFile();
	_myfile.close();*/

	/*int start = _recipes.size() - 10;
	for (int i = start; i < _recipes.size(); i++)
	{
		std::cout << _recipes[i];
	}
	cout << endl;*/

	//PrintScores();
	cout << "Part 2:  Number of recipes to left of target = " << _recipes.size() - numdigits << endl;

}

bool Day14::CheckForRecipe(int target, int numdigits)
{
	int count = _recipes.size();

	if (count < numdigits)
		return false;

	int check = 0;
	int multiplier = 1;
	int lastidx = _recipes.size() - 1;
	int firstidx  = _recipes.size() - numdigits;

	for (int i = lastidx; i >= firstidx; i--)
	{
		check += _recipes[i] * multiplier;
		multiplier *= 10;
	}	

	bool same = (check == target);
	if (same)
	{
		cout << "Found same at size " << _recipes.size() << endl;
		//PrintScores();
	}
	return same;
}

void Day14::PrintScores()
{
	for (int i = 0; i < _recipes.size(); i++)
	{
		if (i == _elf1idx)
			cout << "(" << _recipes[i] << ") ";
		else if (i == _elf2idx)
			cout << "[" << _recipes[i] << "] ";
		else
			cout << " " << _recipes[i] << "  ";
		//cout << _recipes[i];
	}
	cout << endl;
}

void Day14::WriteToFile()
{
	for (int i = 0; i < _recipes.size(); i++)
	{
		/*if (i == _elf1idx)
			_myfile << "(" << _recipes[i] << ") ";
		else if (i == _elf2idx)
			_myfile << "[" << _recipes[i] << "] ";
		else
			_myfile << " " << _recipes[i] << "  ";*/
		_myfile << _recipes[i];
	}
	_myfile << endl;
}
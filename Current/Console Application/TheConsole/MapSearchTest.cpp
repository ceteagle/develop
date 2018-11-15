#include "stdafx.h"
#include <random>

#include "MapSearchTest.h"
#include "Timer.h"
#include "TimerManager.h"

MapSearchTest::MapSearchTest()
{
}


MapSearchTest::~MapSearchTest()
{
}

void MapSearchTest::DoMapLookupTest()
{
	int mapsize = 50000;
	{
		Timer t("MAP FILL TIME ==> MapSearchTest::DoMapLookupTest()", kTimerNoOutput);
		for (int i = 0; i < mapsize; i++)
		{
			_map[mapsize - i] = i;
		}
	}

	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0, mapsize);
	int dice_roll = distribution(generator);  // generates number in the range 1..6 

	::std::map<int, int>::iterator iter;
	::std::string info = "MapSearchTest::DoMapLookupTest";
	for (int i = 0; i < 10; i++)
	{
		dice_roll = distribution(generator);
		Timer timer(info + " " + std::to_string(dice_roll), kTimerNoOutput);
		iter = _map.find(dice_roll);
		if (iter == _map.end())
		{
			Timer timer("NOT FOUND ==> " + info + " " + std::to_string(dice_roll), kTimerNoOutput);
		}
	}

	TimerManager::Instance().Average(info);
}

void MapSearchTest::DoMultiMapLookupTest()
{
	int mapsize = 50000;
	{
		Timer t("MULTI MAP FILL TIME ==> MapSearchTest::DoMultiMapLookupTest()", kTimerNoOutput);
		for (int i = 0; i < mapsize; i++)
		{
			_mmap.insert(std::pair<int, int>(mapsize - i, i));
		}
	}

	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0, mapsize);
	int dice_roll = distribution(generator);  // generates number in the range 1..6 

	::std::map<int, int>::iterator iter;
	::std::string info = "MapSearchTest::DoMultiMapLookupTest";
	for (int i = 0; i < 10; i++)
	{
		dice_roll = distribution(generator);
		Timer timer(info + " " + std::to_string(dice_roll), kTimerNoOutput);
		iter = _mmap.find(dice_roll);
		if (iter == _mmap.end())
		{
			Timer timer("NOT FOUND ==> " + info + " " + std::to_string(dice_roll), kTimerNoOutput);
		}
	}

	TimerManager::Instance().Average(info);
}

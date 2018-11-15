#pragma once
#include <map>

class MapSearchTest
{
public:
	MapSearchTest();
	~MapSearchTest();

	void DoMapLookupTest();
	void DoMultiMapLookupTest();

private:
	std::map<int,int> _map;
	std::multimap<int, int> _mmap;

};


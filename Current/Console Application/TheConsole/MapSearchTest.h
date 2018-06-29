#pragma once
#include <map>

class MapSearchTest
{
public:
	MapSearchTest();
	~MapSearchTest();

	void DoMapLookupTest();

private:
	std::map<int,int> _map;

};


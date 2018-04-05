#pragma once
#include <fstream>
#include <iostream>
#include <list>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

class Parser {
public:
	// constructors

	/// default
	Parser();

	/// copy
	Parser(const Parser &p);

	/// custom
	Parser(string filename);

	// destructor
	~Parser();

	// public members
	string getFilename();
	list<string> getContent();

	// operators
	Parser& operator=(const Parser &p);
	Parser& operator-=(const Parser &p);
	Parser& operator+=(const Parser &p);

	bool operator==(const Parser &p) const;
	bool operator!=(const Parser &p) const;

	bool operator<(const Parser &p) const;
	bool operator>(const Parser &p) const;
	bool operator<=(const Parser &p) const;
	bool operator>=(const Parser &p) const;

	friend Parser operator+(const Parser &p1, const Parser &p2);
	friend Parser operator-(const Parser &p1, const Parser &p2);

	friend ostream& operator<<(ostream &outstream, const Parser &p);
	//friend istream& operator>>(istream &instream, const Parser &p);
protected:
	// shared members
	void allocFilename(string filename, bool freeMemory = false);
private:
	// attributes
	char* filename;
	list<string> content;
};

#include "stdafx.h"
#include "Parser.h"
#include <iostream>  
#include <string>

void panic(string msg) {
	cout << "ERROR: " << msg << endl;
	exit(EXIT_FAILURE);
}

void Parser::allocFilename(string Filename, bool freeMemory) {
	if (freeMemory) {
		delete[] filename;
	}

	filename = new char[Filename.size()];
	strcpy(filename, Filename.c_str());
}

Parser::Parser() {
	allocFilename("");
}

Parser::Parser(string Filename) {
	allocFilename(Filename);

	ifstream file(Filename);

	if (file) {
		// we have one
		string line;
		while (getline(file, line)) {
			content.push_back(line);
		}
	}
	else {
		// we don't have one
		panic("Could not find the file " + Filename + "!");
	}
}

Parser::Parser(const Parser &p) {
	// set the filename
	allocFilename(p.filename, true);

	// clear the destination for the text
	content.clear();

	// copy p's content over
	for (auto it = p.content.begin(); it != p.content.end(); it++) {
		content.push_back(*it);
	}
}

Parser::~Parser() {
	delete[] filename;
	content.clear();
}

string Parser::getFilename() {
	return filename;
}

list<string> Parser::getContent() {
	return content;
}

Parser& Parser::operator=(const Parser &p) {
	if (this == &p) {
		return *this;
	}

	// set the new filename
	allocFilename(p.filename);

	// make room for the new content
	content.clear();

	// add in p's content
	for (auto it = p.content.begin(); it != p.content.end(); it++) {
		content.push_back(*it);
	}

	return *this;
}

Parser& Parser::operator-=(const Parser &p) {
	for (auto it = p.content.begin(); it != p.content.end(); it++) {
		content.remove(*it);
	}

	return *this;
}

Parser& Parser::operator+=(const Parser &p) {
	for (auto it = p.content.begin(); it != p.content.end(); it++) {
		content.push_back(*it);
	}

	return *this;
}

bool Parser::operator==(const Parser &p) const {
	return content == p.content;
}

bool Parser::operator!=(const Parser &p) const {
	return content != p.content;
}

bool Parser::operator<(const Parser &p) const {
	return content < p.content;
}

bool Parser::operator>(const Parser &p) const {
	return content > p.content;
}

bool Parser::operator<=(const Parser &p) const {
	return content <= p.content;
}

bool Parser::operator>=(const Parser &p) const {
	return content >= p.content;
}

Parser operator+(const Parser &p1, const Parser &p2) {
	Parser sum(p1);

	for (auto it = p2.content.begin(); it != p2.content.end(); it++) {
		sum.content.push_back(*it);
	}

	return sum;
}

Parser operator-(const Parser &p1, const Parser &p2) {
	Parser diff(p1);

	for (auto it = p2.content.begin(); it != p2.content.end(); it++) {
		diff.content.remove(*it);
	}

	return diff;
}

ostream& operator<<(ostream &outstream, const Parser &p) {
	for (auto it = p.content.begin(); it != p.content.end(); it++) {
		outstream << *it << endl;
	}

	return outstream;
}
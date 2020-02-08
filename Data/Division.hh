// File Division.hh

#ifndef DIVISION_HH
#define DIVISION_HH

#include <iostream>

using namespace std;

class Division {

	friend istream& operator>>(istream& is, Division& d);
	friend ostream& operator<<(ostream& os, const Division& d);

public:
	Division() {}
	int Code() const { return code; }
	int MinReferees() const { return minReferees; }
	int MaxReferees() const { return maxReferees; }
	int Level() const { return level; }
	int Teams() const { return teams; }

private:
	int code;
	int minReferees;
	int maxReferees;
	int level;
	int teams;

};

#endif

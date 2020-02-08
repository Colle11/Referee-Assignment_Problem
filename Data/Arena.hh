// File Arena.hh

#ifndef ARENA_HH
#define ARENA_HH

#include <iostream>
#include "Coordinates2D.hh"

using namespace std;

class Arena {

	friend istream& operator>>(istream& is, Arena& a);
	friend ostream& operator<<(ostream& os, const Arena& a);

public:
	Arena() {}
	int Code() const { return code; }
	Coordinates2D Address() const { return address; }

private:
	int code;
	Coordinates2D address;

};

#endif

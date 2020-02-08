// File Team.hh

#ifndef TEAM_HH
#define TEAM_HH

#include <iostream>

using namespace std;

class Team {

	friend istream& operator>>(istream& is, Team& t);
	friend ostream& operator<<(ostream& os, const Team& t);

public:
	Team() {}
	int Code() const { return code; }
	int Division() const { return division; }

private:
	int code;
	int division;

};

#endif

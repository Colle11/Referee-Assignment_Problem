// File Referee.hh

#ifndef REFEREE_HH
#define REFEREE_HH

#include <iostream>
#include <vector>
#include "Coordinates2D.hh"
#include "Event.hh"

using namespace std;

class Referee {

	friend istream& operator>>(istream& is, Referee& r);
	friend ostream& operator<<(ostream& os, const Referee& r);

public:
	Referee() {}
	int Code() const { return code; }
	int Level() const { return level; }
	Coordinates2D Address() const { return address; }
	int Experience() const { return experience; }
	bool IncompatibleReferee(int r) const;
	bool IncompatibleTeam(int t) const;
	bool Unavailable(const Event& e) const;

private:
	int code;
	int level;
	Coordinates2D address;
	int experience;
	vector<int> incompatibleReferees;
	vector<int> incompatibleTeams;
	vector<Event> unavailabilities;

};

#endif

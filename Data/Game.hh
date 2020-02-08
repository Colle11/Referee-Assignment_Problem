// File Game.hh

#ifndef GAME_HH
#define GAME_HH

#include <iostream>
#include "Event.hh"

using namespace std;

class Game {

	friend bool operator<=(const Game& g1, const Game& g2);
	friend istream& operator>>(istream& is, Game& g);
	friend ostream& operator<<(ostream& os, const Game& g);

public:
	Game() {}
	int HomeTeam() const { return homeTeam; }
	int AwayTeam() const { return awayTeam; }
	int Division() const { return division; }
	Event Match() const { return match; }
	int Arena() const { return arena; }
	int Experience() const { return experience; }

private:
	int homeTeam;
	int awayTeam;
	int division;
	Event match;
	int arena;
	int experience;

};

#endif

// File Game.cc

#include <iostream>
#include "Game.hh"

bool operator<=(const Game& g1, const Game& g2) {
	return g1.match <= g2.match;
}

istream& operator>>(istream& is, Game& g) {
	char ch;

	is >> ch >> g.homeTeam >> ch >> g.awayTeam >> ch >> g.division >> g.match >> ch >> g.arena >> g.experience;

	return is;
}

ostream& operator<<(ostream& os, const Game& g) {
	os << "T" << g.homeTeam << " T" << g.awayTeam << " D" << g.division << " " << g.match << " A" << g.arena << " " << g.experience;

	return os;
}

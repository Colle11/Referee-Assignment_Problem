// File Team.cc

#include <iostream>
#include "Team.hh"

istream& operator>>(istream& is, Team& t) {
	char ch;

	is >> ch >> t.code >> ch >> t.division;

	return is;
}

ostream& operator<<(ostream& os, const Team& t) {
	os << "T" << t.code << " D" << t.division;

	return os;
}

// File Division.cc

#include <iostream>
#include "Division.hh"

istream& operator>>(istream& is, Division& d) {
	char ch;

	is >> ch >> d.code >> ch >> d.minReferees >> ch >> d.maxReferees >> ch >> d.level >> ch >> d.teams;

	return is;
}

ostream& operator<<(ostream& os, const Division& d) {
	os << "D" << d.code << ": " << d.minReferees << ", " << d.maxReferees << ", " << d.level << ", " << d.teams;

	return os;
}

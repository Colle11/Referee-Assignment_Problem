// File Arena.cc

#include <iostream>
#include "Arena.hh"

istream& operator>>(istream& is, Arena& a) {
	char ch;

	is >> ch >> a.code >> a.address;

	return is;
}

ostream& operator<<(ostream& os, const Arena& a) {
	os << "A" << a.code << " " << a.address;

	return os;
}

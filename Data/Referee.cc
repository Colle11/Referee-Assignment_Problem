// File Referee.cc

#include <iostream>
#include <ctype.h>
#include <algorithm>
#include "Referee.hh"

bool Referee::IncompatibleReferee(int r) const {
	return binary_search(incompatibleReferees.begin(), incompatibleReferees.end(), r);
}

bool Referee::IncompatibleTeam(int t) const {
	return binary_search(incompatibleTeams.begin(), incompatibleTeams.end(), t);
}

bool Referee::Unavailable(const Event& e) const {
	return binary_search(unavailabilities.begin(), unavailabilities.end(), e);
}

istream& operator>>(istream& is, Referee& r) {
	char ch;
	int c;
	Event u;

	is >> ch >> r.code >> ch >> r.level >> ch >> r.address >> ch >> r.experience >> ch;

	// incompatible referees
	is >> ch;
	ch = is.peek();

	if (ch == ']')
		is >> ch;

	while (ch != ']') {
		is >> ch >> c >> ch;
		r.incompatibleReferees.push_back(c);
	}
	is >> ch;

	sort(r.incompatibleReferees.begin(), r.incompatibleReferees.end());

	// incompatible teams
	is >> ch;
	ch = is.peek();

	if (ch == ']')
		is >> ch;

	while (ch != ']') {
		is >> ch >> c >> ch;
		r.incompatibleTeams.push_back(c);
	}
	is >> ch;

	sort(r.incompatibleTeams.begin(), r.incompatibleTeams.end());

	// unavailabilities
	is >> ch;
	ch = is.peek();

	if (ch == ']')
		is >> ch;

	while (ch != ']') {
		is >> u >> ch;
		r.unavailabilities.push_back(u);
	}

	sort(r.unavailabilities.begin(), r.unavailabilities.end(), less_equal<Event>());

	return is;
}

ostream& operator<<(ostream& os, const Referee& r) {
	os << "R" << r.code << ", " << r.level << ", " << r.address << ", " << r.experience << ", ";

	// incompatible referees
	os << "[";
	if (!r.incompatibleReferees.empty()) {
		for (long unsigned int i = 0; i < r.incompatibleReferees.size() - 1; i++)
			os << "R" << r.incompatibleReferees[i] << ", ";

		os << "R" << r.incompatibleReferees.back();
	}
	os << "], ";

	// incompatible teams
	os << "[";
	if (!r.incompatibleTeams.empty()) {
		for (long unsigned int i = 0; i < r.incompatibleTeams.size() - 1; i++)
			os << "T" << r.incompatibleTeams[i] << ", ";

		os << "T" << r.incompatibleTeams.back();
	}
	os << "], ";

	// unavailabilities
	os << "[";
	if (!r.unavailabilities.empty()) {
		for (long unsigned int i = 0; i < r.unavailabilities.size() - 1; i++)
			os << r.unavailabilities[i] << ", ";

		os << r.unavailabilities.back();
	}
	os << "]";

	return os;
}

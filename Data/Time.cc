// File Time.cc

#include <iostream>
#include <iomanip>
#include "Time.hh"

Time::Time(int h, int m) {
	hours = h;
	minutes = m;

	if (!Valid()) {
		hours = 0;
		minutes = 0;
	}
}

Time::Time(const Time& t) {
	hours = t.hours;
	minutes = t.minutes;
}

Time& Time::operator=(const Time& t) {
	hours = t.hours;
	minutes = t.minutes;

	return *this;
}

Time Time::operator+(int d) {
	if (d > 0) {
		int t = (TimeInMinutes() + d) % (24 * 60);
		int h = t / 60;
		int m = t % 60;
		return Time(h, m);
	} else
		return *this;
}

int Time::NumberOfMidnights(int d) const {
	if (d > 0)
		return (TimeInMinutes() + d) / (24 * 60);
	else
		return 0;
}

bool Time::Valid() const {
	return hours >= 0 && hours <= 23
		&& minutes >= 0 && minutes <= 59;
}

bool operator<(const Time& t1, const Time& t2) {
	return t1.hours < t2.hours
		|| (t1.hours == t2.hours && t1.minutes < t2.minutes);
}

bool operator<=(const Time& t1, const Time& t2) {
	return t1.hours < t2.hours
		|| (t1.hours == t2.hours && t1.minutes <= t2.minutes);
}

istream& operator>>(istream& is, Time& t) {
	char ch;

	is >> t.hours >> ch >> t.minutes;

	if (!t.Valid()) {
		t.hours = 0;
		t.minutes = 0;
	}

	return is;
}

ostream& operator<<(ostream& os, const Time& t) {
	os << setfill('0') << setw(2) << t.hours << ':';
	os << setfill('0') << setw(2) << t.minutes;
	return os;
}

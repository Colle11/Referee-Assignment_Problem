// File Date.cc

#include <iostream>
#include "Date.hh"

Date::Date(int d, int m, int y) {
	day = d;
	month = m;
	year = y;

	if (!Valid()) {
		day = 1;
		month = 1;
		year = 1;
	}
}

Date::Date(const Date& d) {
	day = d.day;
	month = d.month;
	year = d.year;
}

Date& Date::operator=(const Date& d) {
	day = d.day;
	month = d.month;
	year = d.year;

	return *this;
}

void Date::operator++() {
	if (day != DaysOfTheMonth())
		day++;
	else
		if (month != 12) {
			day = 1;
			month++;
		} else {
			day = 1;
			month = 1;
			year++;
		}
}

Date Date::operator+(int n) {
	Date d = *this;

	if (n > 0) {
		int i;
		for (i = 0; i < n; i++)
			++d;
	}

	return d;
}

bool Date::Valid() const {
	return year >= 1 && year < 10000
		&& month >= 1 && month <= 12
		&& day >= 1 && day <= DaysOfTheMonth();
}

int Date::DaysOfTheMonth() const {
	if (month == 4 || month == 6 || month == 9 || month == 11)
		return 30;
	else if (month == 2)
		if (Bissextile())
			return 29;
		else
			return 28;
	else
		return 31;
}

bool Date::Bissextile() const {
	if (year % 4 != 0)
		return false;
	else if (year % 100 != 0)
		return true;
	else if (year % 400 != 0)
		return false;
	else
		return true;
}

bool operator==(const Date& d1, const Date& d2) {
	return d1.day == d2.day && d1.month == d2.month && d1.year == d2.year;
}

bool operator!=(const Date& d1, const Date& d2) {
	return d1.day != d2.day || d1.month != d2.month || d1.year != d2.year;
}

bool operator<(const Date& d1, const Date& d2) {
	return d1.year < d2.year
		|| (d1.year == d2.year && d1.month < d2.month)
		|| (d1.year == d2.year && d1.month == d2.month && d1.day < d2.day);
}

istream& operator>>(istream& is, Date& d) {
	char ch;

	is >> d.day >> ch >> d.month >> ch >> d.year;

	if (!d.Valid()) {
		d.day = 1;
		d.month = 1;
		d.year = 1;
	}

	return is;
}

ostream& operator<<(ostream& os, const Date& d) {
	os << d.day << '/' << d.month << '/' << d.year;
	return os;
}

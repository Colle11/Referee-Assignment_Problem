// File Date.hh

#ifndef DATE_HH
#define DATE_HH

#include <iostream>

using namespace std;

class Date {

	friend bool operator==(const Date& d1, const Date& d2);
	friend bool operator!=(const Date& d1, const Date& d2);
	friend bool operator<(const Date& d1, const Date& d2);
	friend istream& operator>>(istream& is, Date& d);
	friend ostream& operator<<(ostream& os, const Date& d);

public:
	Date() {}
	Date(int d, int m, int y);
	Date(const Date& d);

	Date& operator=(const Date& d);
	void operator++();
	Date operator+(int n);		// n: duration in days

	int Day() const { return day; }
	int Month() const { return month; }
	int Year() const { return year; }

private:
	int day;
	int month;
	int year;
	bool Valid() const;
	bool Bissextile() const;
	int DaysOfTheMonth() const;

};

#endif

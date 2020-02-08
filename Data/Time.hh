// File Time.hh

#ifndef TIME_HH
#define TIME_HH

#include <iostream>

using namespace std;

class Time {

	friend bool operator<(const Time& t1, const Time& t2);
	friend bool operator<=(const Time& t1, const Time& t2);
	friend istream& operator>>(istream& is, Time& t);
	friend ostream& operator<<(ostream& os, const Time& t);

public:
	Time() {}
	Time(int h, int m);
	Time(const Time& t);

	Time& operator=(const Time& t);
	Time operator+(int d);		// d: duration in minutes

	int Hours() const { return hours; }
	int HoursInMinutes() const { return hours * 60; }
	int Minutes() const { return minutes; }
	int TimeInMinutes() const { return HoursInMinutes() + minutes; }
	int NumberOfMidnights(int d) const;		// d: duration in minutes

private:
	int hours;
	int minutes;
	bool Valid() const;

};

#endif

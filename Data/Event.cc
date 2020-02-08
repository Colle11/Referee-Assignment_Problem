// File Event.cc

#include <iostream>
#include <ctype.h>
#include "Event.hh"

Event::Event(Date sD, Time sT, Date eD, Time eT)
	: startDate(sD), startTime(sT), endDate(eD), endTime(eT)
{
	if (!Valid()) {
		startDate = Date(1, 1, 1);
		startTime = Time(0, 0);
		endDate = Date(1, 1, 1);
		endTime = Time(0, 1);
	}
}

Event::Event(Date sD, Time sT, int d)
	: startDate(sD), startTime(sT)
{
	endDate = startDate + startTime.NumberOfMidnights(d);
	endTime = startTime + d;

	if (!Valid()) {
		startDate = Date(1, 1, 1);
		startTime = Time(0, 0);
		endDate = Date(1, 1, 1);
		endTime = Time(0, 1);
	}
}

Event::Event(const Event& e)
	: startDate(e.startDate), startTime(e.startTime), endDate(e.endDate), endTime(e.endTime)
{
	// do nothing
}

bool OverlappingEvents(const Event& e1, const Event& e2) {
	return !(e1.endDate < e2.startDate
		||   e2.endDate < e1.startDate
		||  (e1.endDate == e2.startDate && e1.endTime <= e2.startTime)
		||  (e2.endDate == e1.startDate && e2.endTime <= e1.startTime));
}

Event& Event::operator=(const Event& e) {
	startDate = e.startDate;
	startTime = e.startTime;
	endDate = e.endDate;
	endTime = e.endTime;

	return *this;
}

bool Event::Valid() const {
	return startDate < endDate
		|| (startDate == endDate && startTime <  endTime);
}

bool operator<=(const Event& e1, const Event& e2) {
	return e1.startDate < e2.startDate
		|| (e1.startDate == e2.startDate && e1.startTime < e2.startTime);
}

bool operator<(const Event& e1, const Event& e2) {
	return !OverlappingEvents(e1, e2)
		&& e1 <= e2;
}

istream& operator>>(istream& is, Event& e) {
	char ch;

	is >> e.startDate >> e.startTime;
	ch = is.peek();

	if (ch == '-') {
		is >> ch;
		e.endDate = e.startDate;
		is >> e.endTime;
	} else if (ch == '~') {
		is >> ch;
		is >> e.endDate >> e.endTime;
	} else {
		e = Event(e.startDate, e.startTime);
	}

	if (!e.Valid()) {
		e.startDate = Date(1, 1, 1);
		e.startTime = Time(0, 0);
		e.endDate = Date(1, 1, 1);
		e.endTime = Time(0, 1);
	}

	return is;
}

ostream& operator<<(ostream& os, const Event& e) {
	if (e.startDate == e.endDate)
		os << e.startDate << " " << e.startTime << "-" << e.endTime;
	else
		os << e.startDate << " " << e.startTime << "~" << e.endDate << " " << e.endTime;

	return os;
}

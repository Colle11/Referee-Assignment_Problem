// File Event.hh

#ifndef EVENT_HH
#define EVENT_HH

#include <iostream>
#include "Date.hh"
#include "Time.hh"

using namespace std;

class Event {

	friend bool operator<=(const Event& e1, const Event& e2);
	friend bool operator<(const Event& e1, const Event& e2);
	friend istream& operator>>(istream& is, Event& e);
	friend ostream& operator<<(ostream& os, const Event& e);
	friend bool OverlappingEvents(const Event& e1, const Event& e2);

public:
	Event() {}
	Event(Date sD, Time sT, Date eD, Time eT);
	Event(Date sD, Time sT, int d = 120);	// d: duration in minutes of the event (the duration of a game is fixed and assumed to be equal to 2 hours)
	Event(const Event& e);

	Event& operator=(const Event& e);

	Date StartDate() const { return startDate; }
	Time StartTime() const { return startTime; }
	Date EndDate() const { return endDate; }
	Time EndTime() const { return endTime; }

private:
	Date startDate;
	Time startTime;

	Date endDate;
	Time endTime;

	bool Valid() const;

};

#endif

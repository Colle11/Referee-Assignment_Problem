// File Coordinates2D.hh

#ifndef COORDINATES2D_HH
#define COORDINATES2D_HH

#include <iostream>

using namespace std;

class Coordinates2D {

	friend istream& operator>>(istream& is, Coordinates2D& coords);
	friend ostream& operator<<(ostream& os, const Coordinates2D& coords);
	friend int EuclideanDistance(const Coordinates2D& coordsA, const Coordinates2D& coordsB);

public:
	Coordinates2D() {}
	Coordinates2D(double cx, double cy);
	double X() const { return x; }
	double Y() const { return y; }

private:
	double x;	// x coordinate
	double y;	// y coordinate

};

#endif

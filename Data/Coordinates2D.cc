// File Coordinates2D.cc

#include <cmath>
#include "Coordinates2D.hh"

Coordinates2D::Coordinates2D(double cx, double cy) {
	x = cx;
	y = cy;
}

istream& operator>>(istream& is, Coordinates2D& coords) {
	char ch;

	is >> ch >> coords.x >> ch >> coords.y >> ch;
	return is;
}

ostream& operator<<(ostream& os, const Coordinates2D& coords) {
	os << "(" << coords.x << ", " << coords.y << ")";
	return os;
}

int EuclideanDistance(const Coordinates2D& coordsA, const Coordinates2D& coordsB) {
	double deltaX = coordsB.x - coordsA.x;
	double deltaY = coordsB.y - coordsA.y;
	return static_cast<int>(ceil(sqrt(deltaX * deltaX + deltaY * deltaY)));
}

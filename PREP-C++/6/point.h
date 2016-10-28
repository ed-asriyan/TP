#ifndef POINT_H
#define POINT_H

#include <string>
#include <iostream>
#include <math.h>

#define GET_COORDINATE_ERROR -854875

class Point
{
private:
	double x;
	double y;

public:
	// Constructors & Destructors
	Point();
	Point(double x, double y);
	Point(const Point&);

	// Operators Overloading
	bool operator==(const Point&) const;
	const Point& operator=(const Point&);
	friend std::ostream& operator<<(std::ostream&, const Point&);


	// Getters & Setters
	double GetX() const;
	void SetX(double);

	double GetY() const;
	void SetY(double);

};

double distance(const Point& p1, const Point& p2);
bool isOnOneLine(const Point& p1, const Point& p2, const Point& p3);

#endif
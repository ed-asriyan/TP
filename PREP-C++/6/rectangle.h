#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "point.h"
#include "polygone.h"

#define ERR_DIAGONAL -1


class Rectangle: public Polygone{
private:
	void setDefault();
public:
	// Constructors & Destructors
	Rectangle();
	Rectangle(const Point& p1, const Point& p3);

	~Rectangle();

	// Public Methods
	double Square() const;
	const char* Type() const;

	double GetDiagonal(int index) const;
};

#endif
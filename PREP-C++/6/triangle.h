#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <math.h>
#include "point.h"
#include "polygone.h"

#define ERR_MEDIAN -1
#define ERR_BISECTOR -1
#define ERR_HEIGHT -1

class Triangle : public Polygone
{
private:
	void setDefault();
public:
	// Constructors & Destructors
	Triangle();
	Triangle(const Point& p1, const Point& p2, const Point& p3);

	~Triangle();

	// Public Methods
	double Square() const;
	const char* Type() const;
	
	Point GetMedianIntersection() const;
	double GetMedian(int index) const;

	Point GetBisectorsIntersection() const;
	double GetBisector(int index) const;

	double GetHeight(int index) const;
};

#endif
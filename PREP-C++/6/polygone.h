#ifndef POLYGONE_H
#define POLYGONE_H

#include <vector>
#include "point.h"

#define ERR_SQUARE -1
#define ERR_SIDE -2

class Polygone
{
private:
	std::vector<Point> points;

protected:
	bool addPoint(const Point& point);
	bool setPoint(int index, const Point& point);
	void clearPoints();

	virtual void setDefault() = 0;
public:
	Polygone();
	Polygone(const Polygone&);
	
	~Polygone();
	
	// Public Methods
	double Perimeter() const;
	virtual double Square() const = 0;
	virtual const char* Type() const = 0;

	// Getters & Setters
	Point GetPoint(int index) const;
	double GetSide(int index) const;
	int PointCount() const;

	// Operators Overloading
	bool operator==(const Polygone&) const;
	bool operator!=(const Polygone&) const;
	const Polygone& operator=(const Polygone&);
	friend std::ostream& operator<<(std::ostream&, const Polygone&);
};

#endif
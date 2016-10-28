#include "triangle.h"
#include "point.h"

// Private Methods
void Triangle::setDefault(){
	clearPoints();
	for (int i = 0; i < 3; i++){
		addPoint(Point(i == 2, i == 1));
	}
}

// Constructors
Triangle::Triangle()
 : Polygone() {
 	addPoint(Point());
	setDefault();
}

Triangle::Triangle(const Point& p1, const Point& p2, const Point& p3)
 : Polygone() {
	if (!addPoint(p1) || !addPoint(p2) || !addPoint(p3)){
		setDefault();
	}
}

Triangle::~Triangle(){
	
}

// Public Methods
double Triangle::Square() const{
	double side1 = GetSide(0);
	double side2 = GetSide(1);
	double side3 = GetSide(2);

	double p = (side1 + side2 + side3) / 2;

	return sqrt(p * (p - side1) * (p - side2) * (p - side3));
}

Point Triangle::GetMedianIntersection() const {
	Point p1 = GetPoint(0);
	Point p2 = GetPoint(1);
	Point p3 = GetPoint(2);

	return Point((p1.GetX() + p2.GetX() + p3.GetX()) / 3, (p1.GetY() + p2.GetY() + p3.GetY()) / 3);
}

double Triangle::GetMedian(int index) const{
	if (index < 0 || index >= 3) {
		return ERR_MEDIAN;
	}

	double side0 = GetSide((index + 1) % 3);
	double sideA = GetSide(index);
	double sideB = GetSide((index - 1) % 3);

	return 0.5 * sqrt(2 * sideA * sideA + 2 * sideB * sideB - side0 * side0);
}

Point Triangle::GetBisectorsIntersection() const{
	Point p1 = GetPoint(0);
	Point p2 = GetPoint(1);
	Point p3 = GetPoint(2);

	double side1 = GetSide(0);
	double side2 = GetSide(1);
	double side3 = GetSide(2);

	double per = Perimeter();

	double x0 = (side1 * p1.GetX() + side2 * p2.GetX() + side3 * p3.GetX()) / per;
	double y0 = (side1 * p1.GetY() + side2 * p2.GetY() + side3 * p3.GetY()) / per;

	return Point(x0, y0);
}

double Triangle::GetBisector(int index) const{
	if (index < 0 || index >= 3) {
		return ERR_BISECTOR;
	}

	double side0 = GetSide((index + 1) % 3);
	double sideA = GetSide(index);
	double sideB = GetSide((index + 2) % 3);

	return sqrt(sideA * sideB * (sideA + sideB + side0) * (sideA + sideB - side0)) / (sideA + sideB);
}

double Triangle::GetHeight(int index) const{
	if (index < 0 || index >= 3) {
		return ERR_HEIGHT;
	}	

	return 2 * Square() / GetSide((index + 1) % 3);
}

const char* Triangle::Type() const{
	return "Triangle";
}
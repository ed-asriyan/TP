#include "rectangle.h"

// Private Methods

void Rectangle::setDefault(){
	clearPoints();
	for (int i = 0; i < 4; i++){
		addPoint(Point(i >= 2, i == 1 || i == 2));
	}
}

// Constructors & Destructors
Rectangle::Rectangle(){
	setDefault();
}

Rectangle::Rectangle(const Point& p1, const Point& p3)
 : Polygone(){
 	addPoint(p1);
 	addPoint(Point(p1.GetX(), p3.GetY()));
 	addPoint(p3);
 	addPoint(Point(p3.GetX(), p1.GetY()));
 	

 	if (PointCount() != 4){
 		setDefault();
 	}
}

Rectangle::~Rectangle(){

}

// Public Methods
double Rectangle::Square() const{
	return GetSide(0) * GetSide(1);
}

const char* Rectangle::Type() const{
	return "Rectangle";
}

double Rectangle::GetDiagonal(int index) const{
	if (index < 0 || index >= 4){
		return ERR_DIAGONAL;
	}

	return distance(GetPoint(index), GetPoint((index + 2) % 4));
}
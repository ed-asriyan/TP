#include "point.h"

#define abs(a) (a) < 0 ? -(a) : (a)
#define min(a, b) (a) < (b) ? (a) : (b)
#define max(a, b) (a) > (b) ? (a) : (b)

// Local functions
template<typename T> void arrCopy(T* dist, const T* source, int count){
	for (int i = 0; i < count; i++){
		dist[i] = source[i];
	}
}


// Constructors & Destructors
Point::Point()
 : Point(0, 0){
}

Point::Point(double X, double Y){
	x = X;
	y = Y;
}

Point::Point(const Point& point){
	x = point.x;
	y = point.y;
}

// Getters & Setters
double Point::GetX() const{
	return x;
}

void Point::SetX(double value){
	x = value;
}

double Point::GetY() const{
	return y;
}

void Point::SetY(double value){
	y = value;
}

// Operators Overloading
bool Point::operator==(const Point& point) const{
	return x == point.x && y == point.y;
}

const Point& Point::operator=(const Point& point){
	x = point.x;
	y = point.y;
}


std::ostream& operator<<(std::ostream& stream, const Point& point){
	stream << '(' << point.x << ", " << point.y << ')';
	return stream;
}

// Other functions
double distance(const Point& p1, const Point& p2){
	return sqrt(pow(p1.GetX() - p2.GetX(), 2) + pow(p1.GetY() - p2.GetY(), 2));
}

bool isOnOneLine(const Point& p1, const Point& p2, const Point& p3){
	return (p1.GetX() - p3.GetX()) * (p2.GetY() - p3.GetY()) == (p2.GetX() - p3.GetX()) * (p1.GetY() - p3.GetY());
}
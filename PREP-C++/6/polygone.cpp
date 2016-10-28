#include "polygone.h"

// Constructors & Destructors
Polygone::Polygone(){

}

Polygone::Polygone(const Polygone& p){
	points = p.points;
}

Polygone::~Polygone(){

}

// Protected Methods
bool Polygone::addPoint(const Point& p){
	int pCount = PointCount();
	if (points.size() > 1 && 
	   (isOnOneLine(points[pCount - 2], points[pCount - 1], p) || 
		isOnOneLine(p, points[pCount - 1], points[0]) ||
		isOnOneLine(p, points[0], points[1]))) {
		return false;
	}

	points.push_back(p);
	return true;
}

bool Polygone::setPoint(int i, const Point& p){
	if (i < 0 || i >= points.size() ||
		(i > 1 && isOnOneLine(points[i - 2], points[i - 1], p)) ||
		(i < points.size() - 1 && isOnOneLine(p, points[i + 1], points[i + 2])) ||
		((i > 0 && i < points.size()) && isOnOneLine(points[i - 1], p, points[i + 1]))){
		return false;
	}

	points[i] = p;
	return true;
}

void Polygone::clearPoints(){
	points.clear();
}

// Public Methods
double Polygone::Perimeter() const{
	double result = 0;

	for (int i = 0; i < points.size(); i++){
		result += GetSide(i);
	}
	
	return result;
}

Point Polygone::GetPoint(int index) const{
	if (!points.size()){
		Point po;
		return po;
	}

	if (index < 0 || index >= points.size()) {
		index = points.size() - 1;
	}

	return points[index];
}

double Polygone::GetSide(int index) const{
	if (index < 0 || index >= points.size() || points.size() <= 1){
		return ERR_SIDE;
	}

	return distance(points[index], points[(index + 1) % points.size()]);
}

int Polygone::PointCount() const{
	return points.size();
}

// Operators Overloading
bool Polygone::operator==(const Polygone& p) const{
	return points == p.points;
}

bool Polygone::operator!=(const Polygone& p) const{
	return points != p.points;
}

const Polygone& Polygone::operator=(const Polygone& p){
	if (*this != p){
		points = p.points;
	}
}

std::ostream& operator<<(std::ostream& stream, const Polygone& p){
	stream << p.Type() << ": ";
	if (p.points.size()){
		std::vector<Point>::const_iterator lastElem = p.points.end() - 1; 
		for (std::vector<Point>::const_iterator i = p.points.begin(); i != lastElem; ++i){
			stream << *i << ", ";
		}

		stream << *lastElem;
	}

	return stream;
}
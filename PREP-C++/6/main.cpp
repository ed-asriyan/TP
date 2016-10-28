#include <iostream>
#include <fstream>

#include "point.h"
#include "polygone.h"
#include "triangle.h"
#include "rectangle.h"

using namespace std;

Point readPoint(istream& stream){
	double x = 0;
	double y = 0;
	stream >> x >> y;

	return Point(x, y);
}

void readTriangle(istream& stream, Triangle* t){
	*t = Triangle(readPoint(stream), readPoint(stream), readPoint(stream));
}

void readRectangle(istream& stream, Rectangle* r){
	*r = Rectangle(readPoint(stream), readPoint(stream));
}

// ----------------------------------------------

void triangleTest(const Triangle& t){
	cout << "\n- Medians: ";
	for (int i = 0; i < 3; i++){
		cout << t.GetMedian(i) << ' ';
	}
	cout << '\n';

	cout << "- Medians intersection: " << t.GetMedianIntersection() << '\n';

	cout << "\n- Bisectors: ";
	for (int i = 0; i < 3; i++){
		cout << t.GetBisector(i) << ' ';
	}
	cout << '\n';

	cout << "- Bisectors intersection: " << t.GetBisectorsIntersection() << '\n';

	cout << "\n- Heights: ";
	for (int i = 0; i < 3; i++){
		cout << t.GetHeight(i) << ' ';
	}
	cout << '\n';
}

void rectangleTest(const Rectangle& r){
	cout << "\nDiagonales: " << r.GetDiagonal(0) << ' ' << r.GetDiagonal(1) << '\n';
}

void polygoneTest(const Polygone& p){	
	cout << "\n- Sides: ";
	for (int i = 0; i < p.PointCount(); i++){
		cout << p.GetSide(i) << ' ';
	}
	cout << '\n';

	cout << "- Perimeter: " << p.Perimeter() << '\n';
	cout << "- Square:    " << p.Square()    << '\n';
}

// ----------------------------------------------

int main(int argc, char const *argv[])
{
	if (argc != 2){
		cout << "Invalid args.\n";
		return 0;
	}

	ifstream file;
	file.open(argv[1]);
	if (file.fail()){
		cout << "Error opening file.\n";
		return 0;
	}

	int triangleCount  = 0;
	int rectangleCount = 0;
	int polygoneCount  = 0;

	file >> triangleCount;
	file >> rectangleCount;

	polygoneCount = triangleCount + rectangleCount;

	Polygone** polygoneBase = new Polygone*[polygoneCount];

	// Copies
	Triangle** triangleBase = new Triangle*[triangleCount];
	Rectangle** rectangleBase = new Rectangle*[rectangleCount];


	// --- Reading file -------------------------

	for (int i = 0; i < triangleCount; i++){
		Triangle* t = new Triangle();
		
		polygoneBase[i] = t;
		triangleBase[i] = t;

		readTriangle(file, t);
	}

	for (int i = 0; i < rectangleCount; i++){
		Rectangle* r = new Rectangle();

		polygoneBase[i + triangleCount] = r;
		rectangleBase[i] = r;

		readRectangle(file, r);
	}

	file.close();

	// --- Tests --------------------------------

	cout << "\nTriangle count:  " << triangleCount  << '\n';
	cout << "Rectangle count: " << rectangleCount << '\n';

	cout << "\n         *** All Polygones ***\n";
	for (int i = 0; i < polygoneCount; i++){
		cout << *polygoneBase[i];
		polygoneTest(*polygoneBase[i]);
		cout << "\n";
	}

	cout << "\n         *** Triangles ***\n";
	for (int i = 0; i < triangleCount; i++){
		cout << *triangleBase[i];
		triangleTest(*triangleBase[i]);
		cout << '\n';
	}

	cout << "\n         *** Rectangles ***\n";
	for (int i = 0; i < rectangleCount; i++){
		cout << *rectangleBase[i];
		rectangleTest(*rectangleBase[i]);
		cout << '\n';
	}

	// ------------------------------------------

	for (int i = 0; i < polygoneCount; i++){
		delete polygoneBase[i];
	}

	delete[] rectangleBase;
	delete[] triangleBase;
	delete[] polygoneBase;

	return 0;
}
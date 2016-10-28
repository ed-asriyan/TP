#ifndef DOUBLEOBJECT_H
#define DOUBLEOBJECT_H

#include "iObject.h"

class DoubleObject: public IObject{
private:
	double value;

	void writeToStream(std::ostream&) const;
public:
	// Constructors & Destructors
	DoubleObject();
	DoubleObject(double);

	// Public Methods
	bool equal(const IObject*) const throw(std::invalid_argument);
	IObject* clone() const;

	// Getters & Setters
	double GetValue() const;
	void SetValue(double);

	// Operators
	operator double();
	DoubleObject& operator=(double);
};

#endif
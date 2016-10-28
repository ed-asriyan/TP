#ifndef INTOBJECT_H
#define INTOBJECT_H

#include "iObject.h"

class IntObject: public IObject
{
private:
	int value;

	void writeToStream(std::ostream&) const;
public:
	// Constructors & Destructors
	IntObject();
	IntObject(int);


 	// Public Methods
	bool equal(const IObject*) const throw(std::invalid_argument);
	IObject* clone() const;

	// Getters & Setters
	int GetValue() const;
	void SetValue(int value);

	// // Operators
	operator int();
	IntObject& operator=(int);
};

#endif
#ifndef STRINGOBJECT_H
#define STRINGOBJECT_H

#include <string>
#include "iObject.h"

class StringObject: public IObject{
private:
	std::string value;

	void writeToStream(std::ostream&) const;
public:
	// Constructors & Destructors
	StringObject();
	StringObject(std::string);

	// Public Methods
	bool equal(const IObject*) const throw(std::invalid_argument);
	IObject* clone() const;

	// Getters && Setters
	std::string GetValue() const;
	void SetValue(const std::string&);

	// Operators
	operator std::string();
	StringObject& operator=(const std::string&);
};

#endif
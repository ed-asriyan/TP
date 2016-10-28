#ifndef IOBJECT_H
#define IOBJECT_H

#include <iostream>
#include <exception>

class IObject{
protected:
	virtual void writeToStream(std::ostream&) const = 0;
public:
	// Public Methods
	virtual bool equal(const IObject*) const throw(std::invalid_argument) = 0;
	virtual IObject* clone() const = 0;

	friend std::ostream& operator<<(std::ostream&, const IObject*) throw(std::invalid_argument);
};

std::ostream& operator<<(std::ostream&, const IObject*) throw(std::invalid_argument);

#endif
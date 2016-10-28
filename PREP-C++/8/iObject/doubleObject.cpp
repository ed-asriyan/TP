#include "doubleObject.h"

// Constructor & Destructors
DoubleObject::DoubleObject()
	: DoubleObject(0){

}

DoubleObject::DoubleObject(double v){
	*this = v;
}

// Private Methods
void DoubleObject::writeToStream(std::ostream& stream) const{
	stream << value;
}

// Public Methods
bool DoubleObject::equal(const IObject* obj) const throw(std::invalid_argument) {
	const DoubleObject* doubleObj = dynamic_cast<const DoubleObject*>(obj);
	if (!doubleObj) throw std::invalid_argument("obj");

	return doubleObj->value == value;
}

IObject* DoubleObject::clone() const{
	DoubleObject* result = new DoubleObject();
	result->value = value;
	return result;
}

// Setters & Getters
double DoubleObject::GetValue() const{
	return value;
}

void DoubleObject::SetValue(double val){
	value = val;
}

// Operators
DoubleObject::operator double(){
	return value;
}

DoubleObject& DoubleObject::operator=(double val){
	value = val;
}
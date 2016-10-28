#include "intObject.h"

// Constructors & Destructors
IntObject::IntObject()
	: IntObject(0){ 

}

IntObject::IntObject(int v){
	*this = v;
}

//Private Methods
void IntObject::writeToStream(std::ostream& stream) const{
	stream << value;
}

// Public Methods 
bool IntObject::equal(const IObject* obj) const throw(std::invalid_argument) {
	const IntObject* intObj = dynamic_cast<const IntObject*>(obj);
	if (!intObj) throw std::invalid_argument("obj");

	return intObj->value == value;
}

IObject* IntObject::clone() const{
	IntObject* result = new IntObject();
	result->value = value;
	return result;
}

// Setters & Getters
int IntObject::GetValue() const{
	return value;
}

void IntObject::SetValue(int val){
	value = val;
}

// Operators
IntObject::operator int(){
	return value;
}

IntObject& IntObject::operator=(int val){
	value = val;
	return *this;
}
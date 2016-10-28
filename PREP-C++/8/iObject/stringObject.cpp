#include "stringObject.h"

// Constructors & Destructors
StringObject::StringObject()
	: StringObject(""){

}

StringObject::StringObject(std::string v){
	*this = v;
}
// Private Methods
void StringObject::writeToStream(std::ostream& stream) const{
	stream << value;
}

// Public Methods
bool StringObject::equal(const IObject* obj) const throw(std::invalid_argument){
	const StringObject* strObj = dynamic_cast<const StringObject*>(obj);
	if (!strObj) throw std::invalid_argument("obj");

	return strObj->value == value;
}

IObject* StringObject::clone() const{
	StringObject* result = new StringObject();
	result->value = value;
	return result;
}

// Setters & Getters
std::string StringObject::GetValue() const{
	return value;
}

void StringObject::SetValue(const std::string& val){
	value = val;
}

// Operators
StringObject::operator std::string(){
	return value;
}

StringObject& StringObject::operator=(const std::string& val){
	value = val;
	return *this;
}
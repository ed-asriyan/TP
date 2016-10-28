#include "iObject.h"

// Operators
std::ostream& operator<<(std::ostream& stream, const IObject* obj) throw(std::invalid_argument){
	if (!obj) throw std::invalid_argument("obj");

	if (obj){
		obj->writeToStream(stream);
	}
}
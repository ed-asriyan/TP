#include "foo.hpp"

// Local functions
template<class T>
bool isEmpty(const T& container){
	return std::begin(container) == std::end(container);
}


// Exceptions
ContainerIsEmptyException::ContainerIsEmptyException(const char* what_arg)
: std::logic_error(what_arg) {

}

ContainerIsEmptyException::ContainerIsEmptyException(const std::string& what_arg)
: std::logic_error(what_arg) {

}


// Foooooo
int foo(const std::vector<double>& v, std::list<double>& l, int step){
	if (isEmpty(v)) throw ContainerIsEmptyException("Vector is empty.");
	if (isEmpty(l)) throw ContainerIsEmptyException("List is empty.");
	if (step < 0)  throw std::out_of_range("Step must be non-negative.");

	int result = 0;

	auto vIt = v.cbegin();
	auto lIt = l.cbegin();

	while(vIt != v.cend() && lIt != l.cend()){
		if (*vIt != *lIt){
			lIt = l.insert(lIt, *vIt);
			result++;
		}

		vIt += step;
		lIt++;
	}

	std::cout << "Modified reversed list: " << constainerToString(l.crbegin(), l.crend()) << '\n';

	return result;
}
#ifndef HM11_FOO_HPP	
#define HM11_FOO_HPP

#include <iostream>
#include <ostream>

#include <stdexcept>
#include <functional>
#include <algorithm>
#include <vector>
#include <list>

#include "containerReader.hpp"

// Ecxeption types
class ContainerIsEmptyException: public std::logic_error{
private:
	ContainerIsEmptyException(const char* what_arg);
	ContainerIsEmptyException(const std::string& what_arg);

	friend int foo(const std::vector<double>&, std::list<double>&, int);
};

// Functions
int foo(const std::vector<double>&, std::list<double>&, int);

#endif // HM11_FOO_HPP
#ifndef HM11_CONTAINER_READER_HPP
#define HM11_CONTAINER_READER_HPP

#include <string>
#include <algorithm>
#include <sstream>
#include <ostream>

template<class ITERATOR>
std::ostream& printContainer(std::ostream& s, ITERATOR begin, ITERATOR end){
	s << "{ ";

	std::for_each(begin, end , [ &s, &end ] (auto obj) {
		s << obj << ' ';
	});

	s << "}";

	return s;
}

template<class ITERATOR>
std::string constainerToString(ITERATOR begin, ITERATOR end){
	std::stringstream s;
	printContainer(s, begin, end);
	return s.str();
}

#endif // HM11_CONTAINER_READER_HPP
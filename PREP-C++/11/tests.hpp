#ifndef HM11_TESTS_HPP
#define HM11_TESTS_HPP

#include <ctime>
#include <algorithm>
#include <ostream>
#include <vector>
#include <list>
#include <exception>
#include <typeinfo>

#include "foo.hpp"
#include "containerReader.hpp"

namespace Generator{
	const int MIN_INT_VALUE = 0;
	const int MAX_INT_VALUE = 10;

	const int MIN_SIZE = 0;
	const int MAX_SIZE = 10;

	const int MIN_STEP = 1;
	const int MAX_STEP = 2;

	void initRand(){
		srand(time(NULL));
	}

	int getRandSize(){
		return rand() % (MAX_SIZE - MIN_SIZE) + MIN_SIZE;
	}

	double getRandomDouble(){
		return rand() % (MAX_INT_VALUE - MIN_INT_VALUE) + MIN_INT_VALUE;
	}

	int getRandomStep(){
		return rand() % (MAX_STEP - MIN_STEP) + MIN_STEP;
	}

	template<class ITERATOR>
	void fill(ITERATOR begin, ITERATOR end){
		while(begin != end){
			*begin = getRandomDouble();
			begin++;
		}
	}

	template<class CONTAINER>
	void fillContainer(CONTAINER& container){
		fill(begin(container), end(container));
	}
}

namespace FooTest{
	void doRandomTest(std::ostream& stream){
		std::vector<double> v(Generator::getRandSize());
		std::list<double>   l(Generator::getRandSize());
		int step = Generator::getRandomStep();

		Generator::fillContainer(v);
		Generator::fillContainer(l);

		stream << "Source vector: " << constainerToString(v.cbegin(), v.cend()) << '\n';
		stream << "Source list  : " << constainerToString(l.cbegin(), l.cend()) << '\n';
		stream << "Step: " << step << '\n';

		stream << '\n';

		try {
			auto result = foo(v, l, step);
			stream << "Result: " << result << '\n';
		} catch (std::exception& ex){
			stream << "Exception was throwed (" /*<< typeid(ex).name()*/ << "): " << ex.what() << '\n';
		} catch (...){
			stream << "Exception was throwed (" /*<< typeid(ex).name()*/ << ")." << '\n';
		}
	}
}

#endif // HM11_TESTS_HPP
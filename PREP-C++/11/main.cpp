#include <vector>
#include <list>

#include "tests.hpp"
#include "foo.hpp"


// как создать свой тип с поддержкой конструкции { ... }
// like std::list<int> a { 0, 0, 1 }

int main(int argc, char* argv[]){
	Generator::initRand();

	FooTest::doRandomTest(std::cout);

	return 0;
}
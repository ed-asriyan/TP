#include <iostream>

#include "complex.hpp"
#include "tests.hpp"

#define N 5

class A{ };

int main(int argc, const char *argv[])
{
	Generator::initRand();

	Tests::DoTest<int, double>(std::cout, N);
	Tests::DoTest<bool, int>(std::cout, N);
	Tests::DoTest<double>(std::cout, N);
	
	return 0;
}
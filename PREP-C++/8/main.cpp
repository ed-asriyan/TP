#include <iostream>
#include <typeinfo>

#include "multiset.h"

#include "iObject/iObject.h"
#include "iObject/intObject.h"
#include "iObject/doubleObject.h"
#include "iObject/stringObject.h"

#include "test.h"

using namespace MultisetTest;

int main(int argc, char* argv[]){
	Generator::initRand();

	std::cout << " ----- MULTISET METHODS -----\n";
	std::cout << " *** INT ***\n";
	testMultiset(Generator::GenerateMultiset<IntObject>());

	std::cout << "\n\n *** DOUBLE ***\n";
	testMultiset(Generator::GenerateMultiset<DoubleObject>());

	std::cout << "\n\n *** STRING ***\n";
	testMultiset(Generator::GenerateMultiset<StringObject>());

	std::cout << "\n\n";
	std::cout << " ----- FUNCTIONS -----\n";
	testMultiset(Generator::GenerateMultiset<IntObject>(), Generator::GenerateMultiset<IntObject>());


	return 0;
}
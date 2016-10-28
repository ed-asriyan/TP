#include <exception>
#include <iostream>

#include "debug.hpp"
#include "set.hpp"
#include "test.hpp"

int main(int argc, char* argv[]){
	LOG_FUNC_ENTRY(argc, argv);
	try{

		Generator::initRand();

		auto s = Generator::GenerateSet<int>();
		SetTest::testSet(s);
	
	} catch (std::exception& ex){
		LOG_CATCH(ex);
	} catch (...){
		LOG_CATCH("exception");
	}
	LOG_FUNC_EXIT(0);
	return 0;
}
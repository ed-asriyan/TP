#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <exception>
#include <functional>

#include <random>
#include <time.h>

#include "set.hpp"

#define output std::cout

namespace Generator{
	const int MIN_RAND_INT = 1;
	const int MAX_RAND_INT = 5;

	const int MIN_RAND_SET_SIZE = 1;
	const int MAX_RAND_SET_SIZE = 7;

	const int STRING_LENGTH = 5;


	void initRand(){
		srand(time(NULL));
	}

	int getRandomInt(int min, int max){
		return rand() % (max - min) + min;
	}

	std::string getRandomString(const int len) {
	    const char alphanum[] =
	        "0123456789"
	        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	        "abcdefghijklmnopqrstuvwxyz"
	        "=-+_";

	    std::string r;

	    for (int i = 0; i < len; ++i) {
	        r.push_back(alphanum[rand() % (sizeof(alphanum) - 1)]);
	    }

	    return r;
	}

	int getRandomInt(){
		return getRandomInt(MIN_RAND_INT, MAX_RAND_INT);
	}

	template<class T>
	T Generate(){
		return static_cast<T>(getRandomInt());
	}

	template<class T>
	Set<T> GenerateSet(){
		Set<T> result;
		for (int i = getRandomInt(MIN_RAND_SET_SIZE, MAX_RAND_SET_SIZE); i > 0; i--){
			result.add(Generate<T>());
		}
		return result;
	}
}

namespace SetTest{
	// Util funcs

	template<class T>
	void doTest(const std::function<void(T)>& func){		
		output << '\n';
		// func(testItem);
		func(Generator::Generate<T>());

	}

	template<class T>
	void showSet(const Set<T>& m){
		output << "Set: " << m << " (" << m.getSize() << ")\n";
	}

	// Adding tests
	template<class T>
	void testAdd(Set<T>& m){
		T obj = Generator::Generate<T>();
		output << "Adding " << obj << ": ";
		m.add(obj);
		output << "Success.";
		
		output << '\n';
	
	}

	// Removing test
	template<class T>
	void testRemove(Set<T>& m) {
		T obj = Generator::Generate<T>();
		output << "Removing " << obj << ": ";
		
		m.remove(obj);
		
		output << "Success.";
		output << '\n';
	
	}

	//Count test
	template<class T>
	void testCount(Set<T>& m) {
		T obj = Generator::Generate<T>();
		output << "Count " << obj << ": ";
		output << m.count(obj);
		output << '\n';
	}

	// 

	// Full test
	template<class T>
	void testSet(Set<T> m){
		showSet(m);

		output << '\n';

		testAdd(m);
		showSet(m);

		testRemove(m);
		showSet(m);

		testCount(m);


		output << "\nTest all complete.\n";
	}
	template<class T>
	void testSet(const Set<T>& m1, const Set<T>& m2){
		output << "A = " << m1 << '\n';
		output << "B = " << m2 << '\n';

		output << "A^B = " <<  Intersection(m1, m2) << '\n';
		output << "AvB = " <<  Union(m1, m2) << '\n';
		output << "A\\B = " << Subtraction(m1, m2) << '\n';
		output << "B\\A = " << Subtraction(m2, m1) << '\n';
	}
}

#undef output

#endif
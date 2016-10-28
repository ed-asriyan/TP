#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <exception>
#include <functional>
#include <string>

#include <random>
#include <time.h>

#include "multiset.h"

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


	IntObject GenerateInt(){
		return IntObject(getRandomInt());
	}

	DoubleObject GenerateDouble(){
		return DoubleObject((double)getRandomInt() / getRandomInt());
	}

	StringObject GenerateString(){
		return StringObject(getRandomString(STRING_LENGTH));
	}

	template<class OBJ> Multiset GenerateMultiset() throw(MultisetInvalidType){
		Multiset result;
		for (int i = getRandomInt(MIN_RAND_SET_SIZE, MAX_RAND_SET_SIZE); i > 0; i--){
			IObject* o = nullptr;

			if (typeid(OBJ) == typeid(IntObject)){
				o = GenerateInt().clone();
			} else if (typeid(OBJ) == typeid(DoubleObject)){
				o = GenerateDouble().clone();
			} else if (typeid(OBJ) == typeid(StringObject)){
				o = GenerateString().clone();
			}

			result.Add(o);

			if (!o) throw MultisetInvalidType();
			delete o;
		}
		return result;
	}
}

namespace MultisetTest{
	// Util methods
	void safelyInvoke(const std::function<void()>& func) noexcept{
		try{
			func();
		} catch (std::exception& e) {
			output << e.what() << '.';
		} catch (...) {
			output << "Unknown exception was throwed.";
		}
	}

	void doWithThreeTypes(const std::function<void(IObject*)>& func) noexcept{
		IntObject    iObj = Generator::GenerateInt();
		DoubleObject dObj = Generator::GenerateDouble();
		StringObject sObj = Generator::GenerateString();

		func(&iObj);
		func(&dObj);
		func(&sObj);
	}

	void doTest(const std::function<void(IObject*)>& func, Multiset& m) noexcept{
		auto testItem = *(m.cbegin() + Generator::getRandomInt(0, m.GetSize()));

		IntObject    iObj = Generator::GenerateInt();
		DoubleObject dObj = Generator::GenerateDouble();
		StringObject sObj = Generator::GenerateString();
		
		output << '\n';
		func(testItem);
		func(&iObj);
		func(&dObj);
		func(&sObj);

	}

	void showSet(Multiset& m){
		output << "Set: " << m << " (" << m.GetSize() << ")\n";
	}

	// Adding tests
	void testAdd(Multiset& m) noexcept{
		doTest([ &m ] (IObject* obj){
			output << "Adding " << obj << ": ";
			safelyInvoke([ &m, &obj ] () {
				m.Add(obj);
				output << "Success.";
			});
			output << '\n';
		}, m);
	}

	// Removing test
	void testRemove(Multiset& m) noexcept{
		doTest([ &m ] (IObject* obj){
			output << "Removing " << obj << ": ";
			safelyInvoke([ &m, &obj ] () {
				m.Remove(obj);
				output << "Success.";
			});
			output << '\n';
		}, m);
	}

	//Count test
	void testCount(Multiset& m) noexcept{
		doTest([ &m ] (IObject* obj){
			output << "Count " << obj << ": ";
			safelyInvoke([ &m, &obj ] () {
				output << m.Count(obj);
			});
			output << '\n';
		}, m);
	}

	// 

	// Full test
	void testMultiset(Multiset m) noexcept{
		showSet(m);

		output << '\n';

		testAdd(m);
		showSet(m);

		testRemove(m);
		showSet(m);

		testCount(m);


		output << "\nTest all complete.\n";
	}

	void testMultiset(const Multiset& m1, const Multiset& m2){
		output << "A = " << m1 << '\n';
		output << "B = " << m2 << '\n';

		output << "A^B = " << Intersection(m1, m2) << '\n';
		output << "AvB = " << Union(m1, m2) << '\n';
		output << "A\\B = " << Subtraction(m1, m2) << '\n';
		output << "B\\A = " << Subtraction(m2, m1) << '\n';
	}
}

#endif
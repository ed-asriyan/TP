#ifndef TESTS_HPP
#define TESTS_HPP

#include <time.h>
#include <vector>
#include <ostream>
#include <algorithm>
#include <typeinfo>

#include "complex.h"

#define MIN_REAL_VALUE 0
#define MAX_REAL_VALUE 10

#define MIN_IMAG_VALUE 0
#define MAX_IMAG_VALUE 10

namespace Generator{
	void initRand(){
		srand(time(NULL));
	}

	int randInt(int min = 0, int max = 100){
		return rand() % (max - min) + min;
	}

	template<class T> T getRand(){
		return (T)randInt();
	}

	template<class REAL, class IMAG> Complex<REAL, IMAG> GenerateComplex(){
		return Complex<REAL, IMAG>((REAL)randInt(MIN_REAL_VALUE, MAX_REAL_VALUE), (IMAG)randInt(MIN_IMAG_VALUE, MAX_IMAG_VALUE));
	}

	template<class REAL, class IMAG> void AppendByGenerated(std::vector<Complex<REAL, IMAG>>& v, int count){
		for (int i = 0; i < count; i++){
			v.push_back(GenerateComplex<REAL, IMAG>());
		}
	}

	template<class REAL, class IMAG> std::vector<Complex<REAL, IMAG>> GenerateVector(int count){
		std::vector<Complex<REAL, IMAG>> result;
		AppendByGenerated(result, count);
		return result;
	}
}

namespace Tests{
	// template<class REAL, class IMAG, class OPERATION_FUNC> auto doOperations(const std::vector<Complex<REAL, IMAG>>& v, OPERATION_FUNC f){
	// 	if (!v.size()) throw std::invalid_argument("Vector is empty");
	// 	if (v.size() == 1) return (decltype(v[0] + v[1]))v[0];
		
	// 	decltype(f(v[0], v[1])) result(v[0])

	// 	std::for_each(v.cbegin() + 1, v.cend(), [ &result ] (const Complex<REAL, IMAG>& it) {
	// 		f(result)
	// 	});

	// 	return result;
	// }

	template<class REAL, class IMAG> auto sum(const std::vector<Complex<REAL, IMAG>>& v){
		if (!v.size()) throw std::invalid_argument("Vector is empty");
		// if (v.size() == 1) return (decltype(v[0] + v[1]))v[0];
		
		decltype(v[0] + v[1]) result(v[0]);
		// result = (v[0]);

		std::for_each(v.cbegin() + 1, v.cend(), [ &result ] (const Complex<REAL, IMAG>& it) {
			result += it;
		});

		return result;
	}

	template<class REAL, class IMAG = REAL> void DoTest(std::ostream& stream, int count){
		auto l = Generator::GenerateVector<REAL, IMAG>(count);

		stream << "List (real is " << typeid(REAL).name() << ", imaginary is " << typeid(IMAG).name() << "):\n";
		stream << l;
		stream << "Sum: " << Tests::sum(l) << '\n';
	}
}

template<class REAL, class IMAG> void printVector(std::ostream& stream, const std::vector<Complex<REAL, IMAG>>& v){
	for (int i = 0; i < v.size(); i++){
		stream << " " << v[i] << '\n';
	}
}

template<class REAL, class IMAG> std::ostream& operator<<(std::ostream& stream, const std::vector<Complex<REAL, IMAG>>& v){
	printVector(stream, v);
	return stream;
}

#endif
#ifndef OPERATOR_CHECKER_HPP
#define OPERATOR_CHECKER_HPP

#include <utility>

namespace OperatorChecker{
	class UNIQ_TYPE { };
	template<class T, class Arg = T> UNIQ_TYPE operator==(const T&, const Arg&);

	template<class T, class Arg = T> bool HaveEqualTo(){
		return !std::is_same<decltype(*((T*)(0)) == *((Arg*)(0))), UNIQ_TYPE>::value;
	}
}

#endif
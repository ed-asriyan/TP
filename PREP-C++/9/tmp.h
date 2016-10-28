#ifndef TMP_H
#define TMP_H

#include <utility>

#define CHECK_TEMPLATE(_OPERATOR_) template<class T, class Arg> UNIQ_TYPE operator _OPERATOR_ (const T&, const Arg&);
#define CHECK_FUNCTION(_OPERATOR_, _NAME_) template<class T, class Arg = T> bool _NAME_ (){return !std::is_same<decltype(*((T*)(nullptr)) _OPERATOR_ *((Arg*)(nullptr))), UNIQ_TYPE>::value;}
#define CHECK_COMPLETE(_OPERATOR_, _NAME_) CHECK_TEMPLATE(_OPERATOR_); CHECK_FUNCTION(_OPERATOR_, _NAME_)

namespace TYPE_CHECK{
	struct UNIQ_TYPE { };

	CHECK_COMPLETE(=, HaveAssignment);

	CHECK_COMPLETE(+, HaveAddition);
	CHECK_COMPLETE(-, HaveSubtraction);
	
	CHECK_COMPLETE(*, HaveMultiplication);
	CHECK_COMPLETE(/, HaveDivision);

	CHECK_COMPLETE(==, HaveEqualTo);
	CHECK_COMPLETE(!=, HaveNoEqualTo);

}

#undef CHECK_COMPLETE
#undef CHECK_FUNCTION
#undef CHECK_TEMPLATE

#endif
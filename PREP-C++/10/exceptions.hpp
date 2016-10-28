#include <exception>
#include <string>

#include "debug.hpp"

class ArgumentException: public std::exception
{
public:
	// Constructors & Destructors
	ArgumentException(const char* name)
		: std::exception() {
			LOG_FUNC_ENTRY(name);
			argName = name;
			LOG_FUNC_EXIT(NO_RETURN);
		};

	virtual ~ArgumentException() {
		LOG_FUNC_ENTRY(NO_ARGS);
		LOG_FUNC_EXIT(NO_RETURN);
	}

	protected:
		std::string argName;
};

class NullArgumentException: public ArgumentException{
	public:
		NullArgumentException(const char* name)
		: ArgumentException(name){ 
			LOG_FUNC_ENTRY(name);
			LOG_FUNC_EXIT(NO_RETURN);
		}

		virtual ~NullArgumentException(){
			LOG_FUNC_ENTRY(NO_ARGS);
			LOG_FUNC_EXIT(NO_RETURN);
		}

		virtual const char* what(){
			LOG_FUNC_ENTRY(NO_ARGS);
			auto result = ("Argument '" + argName + "' is NULL").c_str();
			LOG_FUNC_EXIT(result);
			return result;
		}
};

class ArgumentOutOfRangeException: public ArgumentException{
	public:
		ArgumentOutOfRangeException(const char* name)
		: ArgumentException(name){ 
			LOG_FUNC_ENTRY(name);
			LOG_FUNC_EXIT(NO_RETURN);
		}

		virtual ~ArgumentOutOfRangeException() {
			LOG_FUNC_ENTRY(NO_ARGS);
			LOG_FUNC_EXIT(NO_RETURN);
		}

		virtual const char* what(){
			LOG_FUNC_ENTRY(NO_ARGS);
			auto result = ("Argument '" + argName + "' is out of range.").c_str();
			LOG_FUNC_EXIT(result);
			return result;
		}
};
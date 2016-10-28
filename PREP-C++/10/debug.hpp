#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <ostream>
#include <iostream>
#include <fstream>
#include <utility>
#include <exception>
#include <typeinfo>


#define DEBUG 0


#define LOG(...)
#define LOG_FUNC_ENTRY(...)
#define LOG_FUNC_EXIT(val)
#define LOG_THROW()
#define LOG_CATCH(exc)

#define NO_ARGS ' '
#define NO_RETURN "void"

#ifdef DEBUG

#undef LOG
#undef LOG_FUNC_ENTRY
#undef LOG_FUNC_EXIT
#undef LOG_THROW
#undef LOG_CATCH

#define LOG(...)            Log::log(Log::currentFuncLevel, "", '\n', "//", __VA_ARGS__)
#define LOG_FUNC_ENTRY(...) Log::logFuncEntry(__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define LOG_FUNC_EXIT(val)  Log::logFuncExit(__FILE__, __FUNCTION__, __LINE__, val)
#define LOG_THROW()         Log::logThrow(__FILE__, __FUNCTION__, __LINE__)
#define LOG_CATCH(exc)      Log::logCatch(__FILE__, __FUNCTION__, __LINE__, exc)

#define output std::cerr
// object injection
// design patterns gof
// современное проектирование 
namespace Log{
	// std::fstream output("./lol.log", std::fstream::out);

	// General logging
	template<class SEP, class T>
	void _log(const SEP& sep, const T & t){
		output << t;
	}

	template<class SEPATATOR, class First, class ...Rest>
	void _log(const SEPATATOR& sep, const First & first, const Rest & ...rest)
	{
	 	output << std::forward<const First>(first) << sep;
		_log(sep, std::forward<const Rest>(rest)...);
	}

	template<class SEPATATOR, class END, class ...Rest>
	void log(int level, const SEPATATOR& sep, const END& end, const Rest & ...rest){
		for (int _i = 0; _i < level; _i++) {
			output << "  ";
		}

		_log(sep, rest...);
		output << end;
	}


	// Func logging
	int currentFuncLevel = -1;

	template<class ...Rest>
	void logFuncEntry(const char* file, const char* func, int line, const Rest&  ...rest){
		currentFuncLevel++;

		log(currentFuncLevel, "", "", '+', func, "(");
		log(0, ", ", "", rest...);
		log(0, "", "\n", ')'/*, "-", file, ':', line*/);
	}

	template<class RET>
	void logFuncExit(const char* file, const char* func, int line, const RET& r){
		log(currentFuncLevel, "", "\n", '-', func, " -> ", r/*, "-", file, ':', line*/);
		currentFuncLevel--;
	}

	// Exception logging
	template<class ...Rest>
	void logThrow(const char* file, const char* func, int line, const Rest& ...rest){
		log(currentFuncLevel, "", "", "Exception was throwed: ");
	}

	template<class ...Rest>
	void logCatch(const char* file, const char* func, int line, const Rest& ...rest){
		log(0, "", "\n", rest...);
		currentFuncLevel--;
	}

	void logCatch(const char* file, const char* func, int line, const std::exception& e){
		logCatch(file, func, line, '(', typeid(e).name(), "): ", e.what());
	}
}

#undef output

#endif // DEBUG

#endif // DEBUG_HPP
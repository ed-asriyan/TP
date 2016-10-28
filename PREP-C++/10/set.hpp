#ifndef SET_HPP
#define SET_HPP

#include <functional>
#include <iterator>
#include <sstream>

#include "exceptions.hpp"
#include "debug.hpp"

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

// Local functions
template<class T> void copyArray(T* destination, const T* source, int count);
template<class T> void copyPointersArray(T** destination, const T** source, int count);

template<class T>
class SetItemException: public std::exception{
	public:
		SetItemException(const T& _item)
		: std::exception(),
		  item(_item){
			LOG_FUNC_ENTRY(_item);

			LOG_FUNC_EXIT(NO_RETURN);
		}

		virtual ~SetItemException(){
			LOG_FUNC_ENTRY(NO_ARGS);
			LOG_FUNC_EXIT(NO_RETURN);
		}

	protected:
		const T item;
};

template<class T>
class SetItemAlreadyExistsException: public SetItemException<T>{
	public:
		SetItemAlreadyExistsException(const T& item)
		: SetItemException<T>(item){
			LOG_FUNC_ENTRY(item);
			LOG_FUNC_EXIT(NO_RETURN);
		}

		virtual ~SetItemAlreadyExistsException(){
			LOG_FUNC_ENTRY(NO_ARGS);
			LOG_FUNC_EXIT(NO_RETURN);
		}

		virtual const char* what(){
			LOG_FUNC_ENTRY(NO_ARGS);
			std::stringstream ss;
			ss << "Item " << item << " already exists in set";
			auto result = ss.str().c_str();
			LOG_FUNC_EXIT(result);
			return result;
		}
	private:
		T item;
};

template<class T>
class SetItemNotExistsException: public SetItemException<T>{
	public:
		SetItemNotExistsException(const T& item)
		: SetItemException<T>(item){
			LOG_FUNC_ENTRY(item);
			LOG_FUNC_EXIT(NO_RETURN);
		}

		virtual ~SetItemNotExistsException(){
			LOG_FUNC_ENTRY(NO_ARGS);
			LOG_FUNC_EXIT(NO_RETURN);
		}

		virtual const char* what(){
			LOG_FUNC_ENTRY(NO_ARGS);
			std::stringstream ss;
			ss << "Item " << item << " already exists in set";
			auto result = ss.str().c_str();
			LOG_FUNC_EXIT(result);
			return result;
		}
	private:
		T item;
};

template<class T>
class Set{
	public:
		// Types
		typedef T* iterator;


		// Constructors && Destructors
		Set(){
			LOG_FUNC_ENTRY(NO_ARGS);
			
			base     = nullptr;
			setEnd   = nullptr;
			baseSize = 0;
			setSize  = 0;

			setBaseSize(0);

			LOG_FUNC_EXIT(NO_RETURN);
		}

		Set(const Set<T>& set)
		: Set(){
			LOG_FUNC_ENTRY("'set&'");
			
			*this = set;

			LOG_FUNC_EXIT(NO_RETURN);
		}

		~Set(){
			LOG_FUNC_ENTRY(NO_ARGS);
			setBaseSize(0);
			LOG_FUNC_EXIT(NO_RETURN);
		};

		// Iterators
		iterator begin(){
			LOG_FUNC_ENTRY(NO_ARGS);
			LOG_FUNC_EXIT(base);
			return base;
		}

		iterator end(){
			LOG_FUNC_ENTRY(NO_ARGS);

			LOG_FUNC_EXIT(setEnd);
			return setEnd;
		}

		const iterator cbegin() const{
			LOG_FUNC_ENTRY(NO_ARGS);

			LOG_FUNC_EXIT(base);
			return base;
		}

		const iterator cend() const{
			LOG_FUNC_ENTRY(NO_ARGS);

			LOG_FUNC_EXIT(setEnd);
			return setEnd;
		}


		// Items methods
		void add(const T& obj){
			LOG_FUNC_ENTRY(obj);
			if (contains(obj)) {
				LOG_THROW();
				throw SetItemAlreadyExistsException<T>(obj);
			}

			if (setSize + 2 >= baseSize){
				setBaseSize((setSize + 1) * BASE_DIFF_RATIO);
			}

			setSize++;
			setEnd++;

			*(setEnd - 1) = obj;

			LOG_FUNC_EXIT(NO_RETURN);
		}

		void remove(const T& obj){
			int index = findItemIndex(obj);
			if (index < 0) {
				LOG_THROW();
				throw SetItemNotExistsException<T>(obj);
			}

			copyArray(base + index, base + index + 1, setSize - index - 1);
			
			setSize--;
			setEnd--;
		}

		bool contains(const T& obj) const{
			LOG_FUNC_ENTRY(obj);
			bool result = findItemIndex(obj) >= 0;
			
			LOG_FUNC_EXIT(result);
			return result;
		}

		void clear(){
			LOG_FUNC_ENTRY(NO_ARGS);

			setSize = 0;
			setEnd = base;

			LOG_FUNC_EXIT(NO_RETURN);
		}

		int count() const{
			LOG_FUNC_ENTRY(NO_ARGS);
			LOG_FUNC_EXIT(setSize);
			return setSize;
		}

		int getSize() const{
			LOG_FUNC_ENTRY(NO_ARGS);
			LOG_FUNC_EXIT(setSize);
			return setSize;
		}

		int count(const T& obj1) const{
			LOG_FUNC_ENTRY(obj1);

			int result = 0;
			foreach([ &result, &obj1 ] (const T& obj2) {
				result += obj2 == obj1;
			});

			LOG_FUNC_EXIT(result);
			return result;	
		}

		// Operators
		Set<T>& operator=(const Set<T>& set){
			LOG_FUNC_ENTRY("'set&'");

			clear();

			if (setSize + 2 >= baseSize){
				setBaseSize(set.setSize + 3);
			}

			int i = 0;
			set.foreach([ &i, this ] (const T& obj){
				this->base[i++] = obj;
			});

			setSize = set.setSize;
			setEnd = base + setSize;

			LOG_FUNC_EXIT("'set&");
			return *this;
		}

		// Friend functions
		// template<class U>
		friend std::ostream& operator<<(std::ostream&, const Set<T>&);

		template<class U>
		friend Set<U> Intersection(const Set<U>&, const Set<U>&);
		
		template<class U>
		friend Set<U> Union(const Set<U>&, const Set<U>&);

		template<class U>
		friend Set<U> Subtraction(const Set<U>&, const Set<U>&);


	private:
		const int BASE_DIFF_RATIO = 3;

		T* base;
		T* setEnd;
		
		int baseSize;
		int setSize;

		// Foreach's
		void foreach(const std::function<void(T*&)>& func){
			LOG_FUNC_ENTRY("'func'");
			for (auto i = begin(); i != end(); i++){
				func(*i);
			}
			LOG_FUNC_EXIT(NO_RETURN);
		}

		void foreach(const std::function<void(const T&)>& func) const{
			LOG_FUNC_ENTRY("'func'");
			for (auto i = cbegin(); i != cend(); i++){
				func(*i);
			}
			LOG_FUNC_EXIT(NO_RETURN);
		}

		// Base management methods
		void setBaseSize(int newBaseSize){
			LOG_FUNC_ENTRY(newBaseSize);

			if (newBaseSize < 0) throw ArgumentOutOfRangeException("newBaseSize");

			T* newBase = newBaseSize ? new T[newBaseSize] : nullptr;
			int newSetSize = min(newBaseSize, setSize);

			// copying data
			if (newSetSize){
				copyArray(newBase, base, newSetSize);
			}

			// deleting excess data
			// for (int i = newBaseSize; i < setSize; i++){
			// 	delete base[i];
			// 	base[i] = nullptr;
			// }

			delete[] base;

			baseSize = newBaseSize;
			setSize  = newSetSize;
			base     = newBase;
			setEnd   = newBase + newSetSize;

			LOG_FUNC_EXIT(NO_RETURN);
		}

		int findItemIndex(const T& obj) const{
			LOG_FUNC_ENTRY(obj);

			for (int i = 0; i < setSize; i++){
				if (base[i] && base[i] == obj){
					LOG_FUNC_EXIT(i);
					return i;
				}
			}

			LOG_FUNC_EXIT(-1);
			return -1;
		}
};

// F
// template<class U>
std::ostream& operator<<(std::ostream& s, const Set<int>& m){
	LOG_FUNC_ENTRY("'s&'", "'set&'");
	s << "{ ";

	auto lastElem = m.cend() - 1;
	m.foreach([ &s, &lastElem ] (const int& obj) {
		s << obj;
		if (obj != *lastElem){
			s << ", ";
		}
	});

	s << " }";

	LOG_FUNC_EXIT("'s'");
	return s;
}

template<class U>
Set<U> Intersection(const Set<U>& m1, const Set<U>& m2){
	LOG_FUNC_ENTRY("'m1&", "'m2&'");
	Set<U> result;

	m1.foreach([ &result, &m2, &m1 ] (const U& obj) {
		if (result.contains(obj)) return;
		int addCount = min(m1.count(obj), m2.count(obj));

		for (int i = 0; i < addCount; i++){
			result.add(obj);
		}
	});

	LOG_FUNC_EXIT("'s'");
	return result;
}

template<class U>
Set<U> Union(const Set<U>& m1, const Set<U>& m2){
	LOG_FUNC_ENTRY("'m1&'", "'m2&'");
	Set<U> result;

	m1.foreach([ &result ] (const U& obj) {
		result.add(obj);
	});
	m2.foreach([ &result ] (const U& obj) {
		result.add(obj);
	});

	LOG_FUNC_EXIT("'set'");
	return result;
}

template<class U>
Set<U> Subtraction(const Set<U>& m1, const Set<U>& m2){
	Set<U> result;

	m1.foreach([ &result, &m1, &m2 ] (const U& obj){
		if (result.contains(obj)) return;

		int addCount = m1.count(obj) - m2.count(obj);
		for (int i = 0; i < addCount; i++){
			result.add(obj);
		}
	});

	LOG_FUNC_EXIT("'set'");
	return result;
}

// Local functions
template<class T>
void copyArray(T* destination, const T* source, int count){
	LOG_FUNC_ENTRY(destination, source, count);
	for (int i = 0; i < count; i++){
		destination[i] = source[i];
	}
	LOG_FUNC_EXIT(NO_RETURN);
}

template<class T>
void copyPointersArray(T** destination, const T** source, int count){
	LOG_FUNC_ENTRY(destination, source, count);
	for (int i = 0; i < count; i++){
		*(destination[i]) = *(source[i]);
	}
	LOG_FUNC_EXIT(NO_RETURN);
}

#undef max
#undef min

#endif // SET_HPP
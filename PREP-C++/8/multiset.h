#ifndef MULTISET_H
#define MULTISET_H

#include "iObject/iObject.h"
#include "iObject/intObject.h"
#include "iObject/doubleObject.h"
#include "iObject/stringObject.h"

#include <exception>
#include <typeinfo>
#include <ostream>
#include <functional>

// Exception types
class MultisetItemNotFound: public std::exception{
public:
	const char* what() const throw(){ return "Item not found."; }
};

class MultisetInvalidType: public std::exception{
public:
	const char* what() const throw(){ return "Invalid item type."; }
};


class Multiset{
private:
	const int BASE_DIFF_RATIO = 3;

	IObject** base;
	IObject** setEnd;
	int baseSize;
	int setSize;

	void setBaseSize(int newBaseSize) throw(std::invalid_argument);
	int findItemIndex(const IObject*) const;

	void foreach(const std::function<void(IObject*&)>& func);
	void foreach(const std::function<void(const IObject*)>& func) const;

	void throwIfInvalidType(const IObject*) const throw(std::invalid_argument, MultisetInvalidType);
public:
	// Types
	typedef IObject** iterator;

	// Constructors && Destructors
	Multiset();
	Multiset(const Multiset&);
	~Multiset();


	// Public Methods
	bool IsValidType(const IObject*) const;
	void Add(const IObject*) throw(std::invalid_argument, MultisetInvalidType);
	void Remove(const IObject*) throw(std::invalid_argument, MultisetItemNotFound, MultisetInvalidType);
	bool Contains(const IObject*) const throw(std::invalid_argument, MultisetInvalidType);
	Multiset::iterator Find(const IObject*) const throw(std::invalid_argument, MultisetItemNotFound, MultisetInvalidType);
	int Count(const IObject*) const throw(std::invalid_argument, MultisetInvalidType);

	void Clear() noexcept;

	Multiset::iterator begin();
	Multiset::iterator end();

	const Multiset::iterator cbegin() const;
	const Multiset::iterator cend() const;

	// Getters && Setters
	int GetSize() const noexcept;

	// Operators overloading
 	Multiset& operator=(const Multiset&);

	// Friend functions
	friend std::ostream& operator<<(std::ostream&, const Multiset&);

	friend Multiset Intersection(const Multiset&, const Multiset&);
	friend Multiset Union(const Multiset&, const Multiset&);
	friend Multiset Subtraction(const Multiset&, const Multiset&);
};

std::ostream& operator<<(std::ostream&, const Multiset&);
Multiset Intersection(const Multiset&, const Multiset&);
Multiset Union(const Multiset&, const Multiset&);
Multiset Subtraction(const Multiset&, const Multiset&);

#endif

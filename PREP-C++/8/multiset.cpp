#include "multiset.h"

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

// Local functions
template<class T> void copyArray(T* destination, const T* source, int count){
	for (int i = 0; i < count; i++){
		destination[i] = source[i];
	}
}

template<class T> void copyPointersArray(T** destination, const T** source, int count){
	for (int i = 0; i < count; i++){
		*(destination[i]) = *(source[i]);
	}
}

// Constructors & Destructors
Multiset::Multiset(){
	base     = nullptr;
	setEnd   = nullptr;
	baseSize = 0;
	setSize  = 0;

}

Multiset::Multiset(const Multiset& source)
	: Multiset(){
	*this = source;
}

Multiset::~Multiset(){
	setBaseSize(0);
}


// Private Methods
void Multiset::throwIfInvalidType(const IObject* obj) const throw(std::invalid_argument, MultisetInvalidType){
	if (!obj) throw std::invalid_argument("");
	if (!IsValidType(obj)) throw MultisetInvalidType();
}

void Multiset::setBaseSize(int newBaseSize) throw(std::invalid_argument){
	if (newBaseSize < 0) throw std::invalid_argument("newBaseSize");

	IObject** newBase = newBaseSize ? new IObject*[newBaseSize] : nullptr;
	int newSetSize = min(newBaseSize, setSize);

	// copying data
	if (newSetSize){
		copyArray(newBase, base, newSetSize);
	}

	// deleting excess data
	for (int i = newBaseSize; i < setSize; i++){
		delete base[i];
		base[i] = nullptr;
	}

	delete[] base;

	baseSize = newBaseSize;
	setSize  = newSetSize;
	base     = newBase;
	setEnd   = newBase + newSetSize;
}

int Multiset::findItemIndex(const IObject* obj) const{
	if (IsValidType(obj)){
		for (int i = 0; i < setSize; i++){
			if (base[i] && base[i]->equal(obj)){
				return i;
			}
		}
	}

	return -1;
}

void Multiset::foreach(const std::function<void(IObject*&)>& func){
	for (auto i = begin(); i != end(); i++){
		func(*i);
	}
}


void Multiset::foreach(const std::function<void(const IObject*)>& func) const{
	for (auto i = cbegin(); i != cend(); i++){
		func(*i);
	}
}


// Public Methods
bool Multiset::IsValidType(const IObject* obj) const{
	// return true;
	return obj && (!setSize || typeid(*obj) == typeid(*base[0]));
}

void Multiset::Add(const IObject* obj) throw(std::invalid_argument, MultisetInvalidType){
	throwIfInvalidType(obj);

	if (setSize + 2 >= baseSize){
		setBaseSize((setSize + 1) * Multiset::BASE_DIFF_RATIO);
	}

	setSize++;
	setEnd++;

	*(setEnd - 1) = obj->clone();
}

void Multiset::Remove(const IObject* obj) throw(std::invalid_argument, MultisetItemNotFound, MultisetInvalidType){
	throwIfInvalidType(obj);

	int index = findItemIndex(obj);
	if (index < 0) throw MultisetItemNotFound();

	copyArray(base + index, base + index + 1, setSize - index - 1);
	
	setSize--;
	setEnd--;
}

bool Multiset::Contains(const IObject* obj) const throw(std::invalid_argument, MultisetInvalidType){
	throwIfInvalidType(obj);
	return findItemIndex(obj) >= 0;
}

Multiset::iterator Multiset::Find(const IObject* obj) const throw(std::invalid_argument, MultisetItemNotFound, MultisetInvalidType){
	throwIfInvalidType(obj);

	int index = findItemIndex(obj);
	if (index < 0) throw MultisetItemNotFound();

	return &base[index];
}

int Multiset::Count(const IObject* obj1) const throw(std::invalid_argument, MultisetInvalidType){
	throwIfInvalidType(obj1);

	int result = 0;
	foreach([ &result, &obj1 ] (const IObject* obj2) {
		result += obj2->equal(obj1);
	});
	return result;	
}

void Multiset::Clear() noexcept{
	foreach([ ] (IObject*& obj) {
		delete obj;
		obj = nullptr;
	});

	setSize = 0;
	setEnd = base;
}

Multiset::iterator Multiset::begin(){
	return base;
}

Multiset::iterator Multiset::end(){
	return setEnd;
}

const Multiset::iterator Multiset::cbegin() const{
	return base;
}

const Multiset::iterator Multiset::cend() const{
	return setEnd;
}

// Getters & Setters
int Multiset::GetSize() const noexcept{
	return setSize;
}


// Operators overloading
Multiset& Multiset::operator=(const Multiset& source){
	Clear();

	if (setSize + 2 >= baseSize){
		setBaseSize(source.setSize + 3);
	}

	int i = 0;
	source.foreach([ &i, this ] (const IObject* obj){
		this->base[i++] = obj->clone();
	});

	setSize = source.setSize;
	setEnd = base + setSize;


	return *this;
}


// Friend functions
std::ostream& operator<<(std::ostream& s, const Multiset& m){
	s << "{ ";

	auto lastElem = m.cend() - 1;
	m.foreach([ &s, &lastElem ] (const IObject* obj) {
		s << obj;
		if (obj != *lastElem){
			s << ", ";
		}
	});

	s << " }";
	return s;
}

Multiset Intersection(const Multiset& m1, const Multiset& m2){
	Multiset result;

	m1.foreach([ &result, &m2, &m1 ] (const IObject* obj) {
		if (result.Contains(obj)) return;
		int addCount = min(m1.Count(obj), m2.Count(obj));

		for (int i = 0; i < addCount; i++){
			result.Add(obj);
		}
	});

	return result;
}

Multiset Union(const Multiset& m1, const Multiset& m2){
	Multiset result;

	m1.foreach([ &result ] (const IObject* obj) {
		result.Add(obj);
	});
	m2.foreach([ &result ] (const IObject* obj) {
		result.Add(obj);
	});

	return result;
}

Multiset Subtraction(const Multiset& m1, const Multiset& m2){
	Multiset result;

	m1.foreach([ &result, &m1, &m2 ] (const IObject* obj){
		if (result.Contains(obj)) return;

		int addCount = m1.Count(obj) - m2.Count(obj);
		for (int i = 0; i < addCount; i++){
			result.Add(obj);
		}
	});

	return result;
}
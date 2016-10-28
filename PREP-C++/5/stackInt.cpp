#include "stackInt.h"

#define min(a, b) ((a) < (b)) ? (a) : (b)
#define abs(a) (a) > 0 ? (a) : -(a)

// Local Fuctions
void arrCpy(int* to, const int* from, int count){
	int* tPtr = to;
	const int* fPtr = from;
	for (int i = 0; i < count; i++){
		*tPtr = *fPtr;

		tPtr++;
		fPtr++;
	}
}

// Constructors & Destructors
StackInt::StackInt(){
	base = NULL;
	nextItem = NULL;

	prepairBase(0);
}

StackInt::StackInt(const int* values, int count)
	: StackInt(){
	if (!values || !count) return;

	prepairBase(count);
	arrCpy(base, values, count);
}

StackInt::StackInt(const StackInt& stack) 
	: StackInt(stack.base, stack.stackSize) {
}

StackInt::~StackInt(){
	delete[] base;

	base =  NULL;
	nextItem = NULL;
	baseSize = 0;
	stackSize = 0;
}

// Private Methods
void StackInt::resizeBase(int newSize){
	if (newSize < 0 || newSize == baseSize - 1) return;

	int* newBase = newSize ? new int[newSize] : NULL;
	if (base && newBase){
		arrCpy(newBase, base, stackSize);
	}
	
	delete[] base;

	base = newBase;
	baseSize = newSize;
}

void StackInt::prepairBase(int size){
	if (size < 0){
		return;
	}

	int diff = baseSize - size;

	if (diff > SIZE_DIV || diff <= 0){
		resizeBase(size + SIZE_DIV);
		nextItem = base + size;
	} else {
		nextItem += size - stackSize;
	}

	stackSize = size;
}

// General StackMethods
void StackInt::Push(int value){
	prepairBase(stackSize + 1);
	*(nextItem - 1) = value;
}


int StackInt::Pop(){
	if (!stackSize){
		return EMPTY_STACK;
	}

	int result = *(nextItem - 1);
	prepairBase(stackSize - 1);

	return result;
}


// Operator Overloading
bool StackInt::operator==(const StackInt& stack) const{
	return this == &stack;
}

bool StackInt::operator!=(const StackInt& stack) const{
	return this != &stack;
}

StackInt& StackInt::operator=(const StackInt& stack){
	if (stack != *this) {
		prepairBase(stack.stackSize);
		arrCpy(base, stack.base, stackSize);
	}

	return *this;
}

// Getters & Setters
int StackInt::GetSize() const{
	return stackSize;
}
#ifndef STACK_INT
#define STACK_INT

#include <stdlib.h>

#define EMPTY_STACK -189653168

class StackInt
{
private:
	static const int SIZE_DIV = 8;

	int* base;
	int baseSize;

	int* nextItem;
	int stackSize;

	void resizeBase(int newSize);
	void prepairBase(int size);

public:
	// Constructors & Destructors
	StackInt();
	StackInt(const int* values, int count);
	StackInt(const StackInt& stackInt);

	~StackInt();

	// Operators Overloading
	bool operator==(const StackInt& stack) const;
	bool operator!=(const StackInt& stack) const;
	StackInt& operator=(const StackInt& stack);
	
	int Pop();
	void Push(int value);

	int GetSize() const;
};

#endif
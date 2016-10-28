#include <iostream>
#include <fstream>

#include "stackInt.h"

#define ERROR_INVALID_ARGS -1
#define ERROR_READING_FILE -5

void ShowStack(StackInt stack){
	while (stack.GetSize()){
		std::cout << stack.Pop() << ' ';
	}
}

bool addFromFile(const char* filePath, StackInt& stack){
	if (!filePath) return false;

	std::ifstream stream;
	stream.open(filePath);
	if (stream.fail()){
		return false;
	}

	while (!stream.eof()){
		int buff = 0;
		stream >> buff;
		stack.Push(buff);
	}

	stream.close();

	return true;
}

void addFromConsole(StackInt& stack){
	int addCount = 0;
	std::cout << "Enter integers count: ";
	std::cin >> addCount;

	std::cout << "Enter " << addCount << " integer(s): ";
	for (int i = 0; i < addCount; i++){
		int buff = 0;
		std::cin >> buff;
		stack.Push(buff);
	}
}

void removeOddIndex(StackInt& stack){
	StackInt tmp;
	
	bool isOdd = true;
	while (stack.GetSize()){
		int val = stack.Pop();
		if (!isOdd){
			tmp.Push(val);
		}

		isOdd = !isOdd;
	}	

	// stack = tmp   нельзя
	while (tmp.GetSize()){
		stack.Push(tmp.Pop());
	}
}

int main(int argc, char* argv[]){
	StackInt mainStack;

	if (argc > 2){
		std::cout << "\tError: invalid arguments (code " << ERROR_INVALID_ARGS << ").\n";
		return ERROR_INVALID_ARGS;
	}

	if (argc == 2 && !addFromFile(argv[1], mainStack)){
		std::cout << "\tError: error reading file (code " << ERROR_READING_FILE << ").\n";
		return ERROR_READING_FILE;
	} 
	if (argc == 1){
		addFromConsole(mainStack);
	}

	std::cout << "Source stack:\n";
	ShowStack(mainStack);
	std::cout << '\n';

	removeOddIndex(mainStack);
	std::cout << "Stack without odd indexes: \n";
	ShowStack(mainStack);
	std::cout << '\n';

	return 0;
}
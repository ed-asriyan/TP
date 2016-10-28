#include <stdlib.h>
#include <string>
#include <iostream>
#include <cstring>

#include "fileWords.h"

#define ERROR_INVALID_ARGS -1
#define ERROR_CAN_NOT_OPEN -2

void printFileWords(FileWords fileWords){
	for (int i = 0; i < fileWords.count(); i++){
		std::cout << fileWords[i] << '\n';
	}
}

void fill(FileWords& f1, FileWords& f2){
	if (!f1.count()) return;

	f2.words.clear();
	std::string last = f1[0];
	f2.words.push_back(last.c_str());

	for (int i = 1; i < f1.count(); i++){
		std::string word = f1[i];
		if (strcmp(last.c_str(), word.c_str()) > 0){
			f2.words.push_back(word.c_str());
			last = word;
		}
	}
}

int main(int argc, char* argv[]){
	if (argc < 3){
		return ERROR_INVALID_ARGS;
	}

	FileWords f1(argv[1]);
	FileWords f2(argv[2]);

	fill(f1, f2);

	return 0;
}
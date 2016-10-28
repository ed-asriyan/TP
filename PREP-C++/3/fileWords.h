#ifndef FILE_WORDS_H
#define FILE_WORDS_H

#include <stdlib.h>	
#include <string>
#include <vector>
#include <stdio.h>

class FileWords
{
private:
	std::string fileName;

	bool canRead;
	bool canWrite;
public:
	FileWords(std::string filePath);
	~FileWords();
	
	int count();

	std::vector<std::string> words;
	
	void load();
	void upload();

	std::string operator[] (const int index);
};

#endif
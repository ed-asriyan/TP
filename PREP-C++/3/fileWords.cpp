#include "fileWords.h"

typedef std::vector<std::string> StringList;

FileWords::FileWords(std::string filePath){
	FileWords::fileName = filePath;

	FileWords::load();
}

FileWords::~FileWords(){
	FileWords::upload();
}


void FileWords::load(){

	FILE* f = fopen(this->fileName.c_str(), "r");

	FileWords::canRead = (bool)f;
	if (!canRead){
		printf("ss\n");
		return;
	}

	FileWords::words.clear();
	int index = 0;
	int lastIndex = 0;
	int isWord = 0;
	int isEOF = 0;
	while (!isEOF) {
		char c = getc(f);
		isEOF = feof(f);
		
		int isCurrWord = !isspace(c);
		if ((isWord != isCurrWord) || isEOF){
			if (isWord){
				int wordLength = index - lastIndex;
				fseek(f, lastIndex, SEEK_SET);
				
				//char* word = (char*)malloc((wordLength + 1) * sizeof(char));
				std::string word;

				for (int i = 0; i < wordLength; i++){
					word.push_back(fgetc(f));
				}
				fgetc(f);
				//word[wordLength] = '\0';
				
				FileWords::words.push_back(word);
			} else {
				lastIndex = index;
			}
			
			isWord = isCurrWord;
		}
		
		index++;
	}	
	
	fclose(f);
}

void FileWords::upload(){
	FILE* f = fopen(FileWords::fileName.c_str(), "w");

	FileWords::canWrite = (bool)f;
	if (!canWrite){
		return;
	}

	for (int i = 0; i < FileWords::count(); i++){
		fprintf(f, "%s ", words[i].c_str());
	}

	fclose(f);
}

std::string FileWords::operator[] (const int index){
	return FileWords::words[index];
}

int FileWords::count(){
	return FileWords::words.size();
}

#include <stdlib.h>
#include <stdio.h>
#include "wordDictionary.h"

#define ERROR_NO_ARGUMENT -1
#define ERROR_CAN_NOT_READ -2

int isSeparator(char c){
	return isspace(c) || ispunct(c);
}

struct WordDictionary getWords(FILE* f){
	struct WordDictionary result;
	result.First = result.Last = NULL;
	result.count = result.totalCount = 0;
	
	int index = 0;
	int lastIndex = 0;
	int isWord = 0;
	int isEOF = 0;
	while (!isEOF) {
		char c = getc(f);
		isEOF = feof(f);
		
		int isCurrWord = !isSeparator(c);
		if ((isWord != isCurrWord) || isEOF){
			if (isWord){
				int wordLength = index - lastIndex;
				fseek(f, lastIndex, SEEK_SET);
				
				char* word = malloc((wordLength + 1) * sizeof(char));
				
				for (int i = 0; i < wordLength; i++){
					word[i] = fgetc(f);
				}
				fgetc(f);
				word[wordLength] = '\0';
				
				AddWordToDictionary(&result, word);
			} else {
				lastIndex = index;
			}
			
			isWord = isCurrWord;
		}
		
		index++;
	}	
	
	return result;
}

void bubbleSort(struct WordDictionary dict){
	PWordNode p = dict.First;
	for (int i = 0; i < dict.count - 1; i++){
		PWordNode w = dict.First; // было PWordNode w = p;
		for (int j = 0; j < dict.count - i - 1; j++){
			if (CompareWordNodes(*w, *w->Next) < 0){
				SwapWordNodes(w, w->Next);
			}
			w = w->Next;
		}
		
		p = p->Next;
	}
}

void print(struct WordDictionary dict){
	PWordNode p = dict.First;
	for (PWordNode p = dict.First; p; p = p->Next){
		printf("%s %f\n", p->word, (double)p->count / dict.totalCount);
	}
}

int main(int argc, char* argv[]){
	if (argc < 2){
		return ERROR_NO_ARGUMENT;
	}
	
	FILE* f = fopen(argv[1], "r");
	if (f == NULL){
		return ERROR_CAN_NOT_READ;
	}
	
	struct WordDictionary dict = getWords(f);
	bubbleSort(dict);
	print(dict);
	
	freeNodes(dict);
	fclose(f);

	return 0;
}

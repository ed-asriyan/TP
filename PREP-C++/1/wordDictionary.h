#ifndef WORD_DICTIONARY_H_
#define WORD_DICTIONARY_H_

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct WordNode{
	char* word;
	int count;
	
	struct WordNode* Next;
	struct WordNode* Prev;
};

struct WordDictionary{
	struct WordNode* First;
	struct WordNode* Last;
	
	int count;
	int totalCount;
};

typedef struct WordNode* PWordNode;
typedef struct WordDictionary* PWordDictionary;

int CompareWordNodes(struct WordNode, struct WordNode);
void freeNodes(struct WordDictionary);
void SwapWordNodes(PWordNode, PWordNode);
PWordNode AddWordToDictionary(PWordDictionary dict, char* word);

#endif // WORD_DICTIONARY_H_

#include "wordDictionary.h"

int CompareWordNodes(struct WordNode a, struct WordNode b){
	if (a.count < b.count) return -1;
	if (a.count > b.count) return 1;
	return strcmp(a.word, b.word);
}

PWordNode FindWordNode(PWordDictionary dict, char* word){
	PWordNode currNode = dict->First;
	
	while (currNode && strcmp(word, currNode->word)){
		currNode = currNode->Next;
	}
	
	return currNode;
}

PWordNode AddWordToDictionary(PWordDictionary dict, char* word){
	PWordNode node = FindWordNode(dict, word);
	
	if (node){
		node->count++;
	} else {
		node = malloc(sizeof(struct WordNode));
		node->word = word;
		node->count = 1;
		
		if (dict->Last) {
			dict->Last->Next = node;
		}
		node->Next = NULL;
		node->Prev = dict->Last;
		dict->Last = node;

		if (dict->First == NULL) {
			dict->First = node;
		}
		dict->count++;
	}	
	
	dict->totalCount++;
	
	return node;
}

void SwapWordNodes(PWordNode a, PWordNode b){
	char* tWord = a->word;
	int tCount = a->count;
	
	a->word = b->word;
	a->count = b->count;
	b->word = tWord;
	b->count = tCount;
}

void freeNodes(struct WordDictionary dict){
	PWordNode p = dict.First;
	
	while (p){
		PWordNode next = p->Next;
		free(p->word);
		free(p);
		p = next;
	}
	
	dict.First = dict.Last = NULL;
}
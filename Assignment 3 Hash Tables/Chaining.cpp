#ifndef CHAINING_CPP
#define CHAINING_CPP
#include "Chaining.h"
#include "hashfunctions.cpp"
#include <cmath>

HashC::HashC(int size){
    tableSize = size;
    hashTable = new LinkedList<string>[size];
}
HashC::~HashC(){

}

unsigned long HashC :: hash(string input){
	unsigned long finalHash = 0;
	int len = input.length();
	for (int i = 0; i < len ; ++i)
	{
		finalHash ^= (finalHash<<5) + (finalHash>>2) + (unsigned long )(input[i]);
	}
  return (finalHash) % (tableSize);  
}

void HashC::insert(string word){
	hashTable[hash(word)].insertAtTail(word);
  return;
}

ListItem<string>* HashC :: lookup(string word){

	return hashTable[hash(word)].searchFor(word);
  	
}

void HashC :: deleteWord(string word){
	hashTable[hash(word)].deleteElement(word);
	hashTable[hash(word)].deleteElement(word);
}

#endif
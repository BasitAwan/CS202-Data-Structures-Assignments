#ifndef DOUBLEHASH_CPP
#define DOUBLEHASH_CPP
#include "doubleHash.h"
#include "hashfunctions.cpp"
HashD::HashD(){
    tableSize = 10000; // you cant change this
    hashTable = new block*[10000]();
    for (int i = 0; i < 10000; ++i)
    {
    	hashTable[i] = new block(-1,"@");
    }
    count = 0;
}

HashD::~HashD(){

}

unsigned long HashD :: hash1(string value){
    return polyHash(value);
}

unsigned long HashD :: hash2(string value){
    return bitHash(value);
}

void HashD::resizeTable(){
	if (tableSize*0.44 < count)
	{
		block **temp = hashTable;
		int size = tableSize;
		tableSize = 15*tableSize;
    	hashTable = new block*[tableSize]();
    	for (int i = 0; i < tableSize; ++i)
		{
		hashTable[i] = new block(-1,"@");
		}
		for (int i = 0; i < size; ++i)
    	{
    		if (temp[i]->key!=-1 && temp[i]->key!=-2)
    		{
    			string val = temp[i]->value;
    			insert(val);
    		}
    	}

	}
	else if (tableSize*0.02 > count && count >1000)
	{
		cout << "lol" << endl;
		block **temp = hashTable;
		int size = tableSize;
		if (tableSize/15 < 10000)
		{
			tableSize=10000;
		}
		else
		{
			tableSize = tableSize/15;

		}
		
    	hashTable = new block*[tableSize]();
    	for (int i = 0; i < tableSize; ++i)
		{
		hashTable[i] = new block(-1,"@");
		}
		for (int i = 0; i < size; ++i)
    	{
    		if (temp[i]->key!=-1 && temp[i]->key!=-2)
    		{
    			string val = temp[i]->value;
    			insert(val);
    		}
    	}

	}
	
    
    return;
}

void HashD::insert(string value){
	resizeTable();
	int collisions= 0;
	int hash = hash2(value);
	hash = abs(hash);
	int hashfir = hash;
	int hashsec = hash2(value);
	if (hash>= tableSize)
	{
		hash = hash % tableSize;
	}
	while(hashTable[hash]->key != -1)
	{
		if (hashTable[hash]->key==-2)
		{
			hashTable[hash] = new block(hash, value);
			count++;
			return;
		}
		collisions++;
		hash = hashfir + (collisions*hashsec);
		hash = abs(hash);
		if (hash >= tableSize)
		{
			hash = hash %tableSize;
	
		}



	}
	hashTable[hash] = new block(hash, value);
	count++;
    return;
}

void HashD::deleteWord(string value){
	block * temp = lookup(value);
	if (temp==NULL)
	{
		return;
	}
	hashTable[temp->key] = new block(-2,"!");
	count--;
	resizeTable();
	return;
}

block* HashD::lookup(string value){
	int collisions= 0;
	int hash = hash2(value);
	hash = abs(hash);
	int hashfir = hash;
	int hashsec = hash2(value);
	if (hash>= tableSize)
	{
		hash = hash % tableSize;
	}
	while(hashTable[hash]->value != value)
	{
		if (hashTable[hash] -> key == -1)
		{
			return NULL;
		}
		else
		{
			collisions++;
			hash = hashfir + (collisions*hashsec);
			hash = abs(hash);
			if (hash >= tableSize)
			{
				hash = hash%tableSize;
		
			}
		}



	}
	return hashTable[hash];
}

#endif
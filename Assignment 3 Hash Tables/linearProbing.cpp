#ifndef LINEARPROBING_CPP
#define LINEARPROBING_CPP

#include "linearProbing.h"
#include "hashfunctions.cpp"


HashL::HashL(){
    tableSize = 1000; // you cant change this
    hashTable = new block*[1000]();
    for (int i = 0; i < 1000; ++i)
    {
    	hashTable[i] = new block(-1,"@");
    }
    count = 0;
}

HashL::~HashL(){
    
}

unsigned long HashL :: hash(string value){
	unsigned long finalHash = 0;
	int len = value.length();
	for (int i = 0; i < len ; ++i)
	{
		finalHash ^= (finalHash<<5) + (finalHash>>2) + (unsigned long )(value[i]);
	}
  return (finalHash) % (tableSize);  
}


void HashL::resizeTable(){
	if (tableSize*0.70 < count)
	{
		block **temp = hashTable;
		int size = tableSize;
		tableSize = 2*tableSize;
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
	else if (tableSize*0.20 > count && count >300)
	{
		block **temp = hashTable;
		int size = tableSize;
		if (tableSize/2 < 1000)
		{
			tableSize=1000;
		}
		else
		{
			tableSize = tableSize/2;

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

void HashL::insert(string value){
	resizeTable();
	int index = hash(value);
	if (hashTable[index]->key==-1)
	{
		hashTable[index] = new block(index, value);
		count++;
	}
	else 
	{
		while(hashTable[index]->key!=-1)
		{
			if (hashTable[index]->key==-2)
			{
				hashTable[index] = new block(index, value);
				count++;
				return;
			}
			if (index == tableSize-1)
			{
				index = 0;
			}
			else
			{
				index++;
			}
		}
		hashTable[index] = new block(index, value);
		count++;
	}
    return;
}

void HashL::deleteWord(string value){
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
block* HashL::lookup(string value){
	int index = hash(value);
	while(hashTable[index]->value!=value)
	{
		if (index == tableSize-1)
		{
			index = 0;
		}
		else if(hashTable[index]->key==-1)
		{
			return NULL;
		}
		else
		{
			index++;
		}

	}
	return hashTable[index];
}
#endif

#ifndef HASHFUNCTIONS_CPP
#define HASHFUNCTIONS_CPP
#include <string>
#include <cmath>
// this takes in a string and returns a 64bit hash.
unsigned long polyHash(std::string value,int a = 5){
	unsigned long finalHash = 0;
	int size = value.length();
	for (int i = 0; i < size; ++i)
	{
		finalHash+= pow(a, size-i-1) * (int)(value[i]);
	}
	return finalHash;
}
//does some bitwise operation and generates a 64bit hash.
unsigned long bitHash(std::string value){
	unsigned long finalHash = 0;
	int len = value.length();
	for (int i = 0; i < len ; ++i)
	{
		finalHash ^= (finalHash<<5) + (finalHash>>2) + (int)(value[i]);
	}
	return finalHash;
}
// Size is the size of array maintained by the hashtable.
unsigned long divCompression(unsigned long hash,long size){
    return hash % size;
}
// multiplication addition and division compression. 
unsigned long madCompression(unsigned long hash,long size,int m = 1993,int a = 1637){
    return ((m*hash) + a) % size;
}
// 'm' and 'a' can take any value
#endif
// you may write your own program to test these functions.
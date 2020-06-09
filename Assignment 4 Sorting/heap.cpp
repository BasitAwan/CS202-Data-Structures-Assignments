#ifndef __HEAP_CPP
#define __HEAP_CPP
#include "heap.h"


MinHeap::MinHeap(int cap)
{
	capacity = cap;
	harr = new int[cap];
	for (int i = 0; i < cap; ++i)
	{
		harr[i]=-1;
	}
	heap_size = 0;
}

void MinHeap::MinHeapify(int i)
{
	if (i>heap_size-1)
	{
		return;
	}
	int lower = i;
	if (right(i)<heap_size)
	{
		if (harr[right(i)] < harr[lower])
		{
			lower = right(i);
		}
	}
	if (left(i) < heap_size)
	{
		if (harr[left(i)] < harr[lower])
		{
			lower = left(i);
		}
		
	}
	
	if (lower!=i)
	{
		int temp = harr[lower];
		harr[lower] = harr[i];
		harr[i]= temp;
		MinHeapify(lower);
	}

	
}
 
int MinHeap::parent(int i)
{
	return (i-1)/2;
}
 
int MinHeap::left(int i)
{
	return (2*i)+1;
}
 
int MinHeap::right(int i)
{
	return (2*i)+2;
}
 
int MinHeap::extractMin()
{
	int min = harr[0];
	deleteKey(0);
	return min;
}
 
void MinHeap::decreaseKey(int i, int new_val)
{
	harr[i] = new_val;
	int index = i;
	while(index>-1)
	{
		if (index%2==0)
		{
			if (harr[index]> harr[index-1])
			{
				index = index-1;
			}
		}
		if (harr[index] < harr[parent(index)])
		{
			int temp = harr[parent(index)];
			harr[parent(index)] = harr[index];
			harr[index] = temp;
			index= parent(index);
		}
		else
		{
			break;
		}
	}
}
 
int MinHeap::getMin()
{
	harr[0];
}
 
void MinHeap::deleteKey(int i)
{
	if (i>heap_size-1)
	{
		return;
	}
	harr[i] = harr[heap_size-1];
	harr[heap_size-1]= -1;
	heap_size--;
	MinHeapify(i);
}
 
void MinHeap::insertKey(int k)
{
	harr[heap_size] = k;
	heap_size++;
	int index = heap_size-1;
	while(index>-1)
	{
		if (index%2==0)
		{
			if (harr[index]> harr[index-1])
			{
				index = index-1;
			}
		}
		if (harr[index] < harr[parent(index)])
		{
			int temp = harr[parent(index)];
			harr[parent(index)] = harr[index];
			harr[index] = temp;
			index= parent(index);
		}
		else
		{
			break;
		}
	}
}

int* MinHeap::getHeap()
{
	return harr;
}

#endif
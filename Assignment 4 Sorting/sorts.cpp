#ifndef __SORTS_CPP
#define __SORTS_CPP
#include "sorts.h"
#include "heap.cpp"
#include "list.cpp"
//=====================================================================================
vector<long> InsertionSort(vector<long> nums)
{
	long * buff = new long[nums.size()];
	for (int i = 0; i < nums.size(); ++i)
	{
		buff[i] = nums[i];
	}
	for (int i = 0; i < nums.size(); ++i)
	{
		int x=i;
		while (x!=0)
		{
			if (buff[x] < buff[x-1])
			{
				int temp = buff[x];
				buff[x] = buff[x-1];
				buff[x-1] = temp;
			}
			else if(buff[x] > buff[x-1])
			{
				break;
			}
			x--;
		}
	}
	std::vector<long> v;
	for (int i = 0; i < nums.size(); ++i)
	{
		v.push_back(buff[i]);
	}
	return v;
}

//=====================================================================================

ListItem  <long> *mergehelper(ListItem <long> *leftList, ListItem <long> *rightList)
{
	ListItem <long> * merged;
	if (leftList==NULL)
	{
		return rightList;
	}
	else if(rightList==NULL)
	{
		return leftList;
	}

	if (rightList->value < leftList->value)
	{
		merged= rightList;
		merged->next = mergehelper(rightList->next, leftList);

	}
	else
	{
		merged = leftList;
		merged->next = mergehelper(rightList, leftList->next);
	}
	return merged;
}
List<long> helper(List<long> list)
{
	List <long> final;
	if (list.length() < 2)
	{
		return list;
	}
	List<long> leftList;
	ListItem<long> *head = list.getHead();
	leftList.insertAtTail(head->value);
	list.deleteHead();	
	ListItem<long> *Lhead = leftList.getHead();
	int size = list.length();
	for (int i = 0; i < (size)/2; ++i)
	{
		head = list.getHead();
		Lhead->next = new ListItem<long>(head->value);
		list.deleteHead();
		Lhead = Lhead->next;

	}
	ListItem<long> *leftHead = helper(leftList).getHead();
	ListItem<long> *rightHead = helper(list).getHead();
	ListItem <long> *merged = mergehelper(leftHead, rightHead);
	final.insertAtTail(merged->value);
	merged = merged->next;
	ListItem<long> *temp = final.getHead();
	while (merged!=NULL)
	{
		temp->next = new ListItem<long>(merged->value);
		merged = merged->next;
		temp = temp->next;
	}
	return final;
	
}
vector<long> MergeSort(vector<long> nums)
{
	vector<long> final;
	List <long> list;
	list.insertAtTail(nums[0]);
	ListItem<long> *temp = list.getHead();
	int size = nums.size();
	for (int i = 1; i < size; ++i)
	{
		temp->next = new ListItem<long>(nums[i]);
		temp= temp->next;
	}
	List <long> sorted = helper(list);
	ListItem<long> *head = sorted.getHead();
	while (head!=NULL)
	{
		final.push_back(head->value);
		head= head->next;
	}

	return final;
}
//=====================================================================================


void quicksort(int array[], int start, int pivot)
{
	if (start >= pivot)
	{
		return;
	}
	int smaller = start-1;
	for (int i = start; i < pivot; ++i)
	{
		if (array[i]<=array[pivot])
		{
			smaller++;
			int temp = array[smaller];
			array[smaller]= array[i];
			array[i] = temp; 
		}
	}
	int temp = array[smaller+1];
	array[smaller+1] = array[pivot];
	array[pivot] = temp;
	quicksort(array, start, smaller);
	quicksort(array,smaller+2,pivot);

}
vector<long> QuickSortArray(vector<long> nums)
{
	int * array = new int[nums.size()];
	int size = nums.size();
	for (int i = 0; i < size; ++i)
	{
		array[i]= nums[i];
	}
	quicksort(array,0,size-1);
	nums.clear();
	for (int i = 0; i < size; ++i)
	{
		nums.push_back(array[i]);
	}
	return nums;
}

//=====================================================================================
void quickList(ListItem<long> *start, ListItem<long> *pivot)
{
	if (start==NULL || pivot == NULL)
	{
		return;
	}
	if (start==pivot)
	{
		return;
	}
	if (start==pivot->next)
	{
		return;
	}

	ListItem<long> *first = start;
	ListItem<long> *smaller= start->prev;
	while(start!=pivot)
	{

		if (start->value <= pivot->value)
		{
			if (smaller==NULL)
			{
				smaller=first;
				int temp = smaller->value;
				smaller->value = start->value;
				start->value = temp;
			}
			else
			{
				smaller= smaller->next;
				int temp = smaller->value;
				smaller->value = start->value;
				start->value = temp;
			}
			
		}
		start= start->next;
	}
	if (smaller==NULL)
	{
		smaller=first;
		int temp = smaller->value;
		smaller->value = pivot->value;
		pivot->value= temp;
	}
	else
	{
		smaller = smaller->next;
		int temp = smaller->value;
		smaller->value = pivot->value;
		pivot->value= temp;
	}
	quickList(first,smaller->prev);
	quickList(smaller->next,pivot);
	
	
}

vector<long> QuickSortList(vector<long> nums)
{
	vector<long> final;
	List <long> list;
	list.insertAtTail(nums[0]);
	ListItem<long> *temp = list.getHead();
	int size = nums.size();
	for (int i = 1; i < size; ++i)
	{
		temp->next = new ListItem<long> (nums[i]);
		temp->next->prev=temp;
		temp= temp->next;
	}
	quickList(list.getHead(),list.getTail());
	ListItem<long> *head = list.getHead();
	while (head!=NULL)
	{
		final.push_back(head->value);
		head= head->next;
	}
	return final;



}

//=====================================================================================
vector<long> HeapSort(vector<long> nums)
{
	MinHeap * heap = new MinHeap(nums.size());
	int size = nums.size();
	for (int i = 0; i < size; ++i)
	{
		heap->insertKey(nums[i]);
	}
	nums.clear();
	for (int i = 0; i < size ; ++i)
	{
		nums.push_back(heap->extractMin());
	}
	return nums;
}

#endif
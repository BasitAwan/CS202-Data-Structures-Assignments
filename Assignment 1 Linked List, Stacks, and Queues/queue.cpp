#ifndef __QUEUE_CPP
#define __QUEUE_CPP
#include "queue.h"

template <class T>
Queue<T>::Queue()
{

}
    
template <class T>
Queue<T>::Queue(const Queue<T>& otherQueue)
{
	LinkedList<T>buff(otherQueue.list);
	if ((buff.getHead())==NULL)
	{
	
	}
	else
	{
		ListItem<T>* temp = (buff.getHead()); 
		list.insertAtHead(temp->value);
		ListItem<T>*ctemp= list.getHead();
		while(temp->next!=NULL)
		{
			ctemp->next= new ListItem<T>(temp->next->value);
			temp=temp->next;
			ctemp=ctemp->next;

		}
	}
}

template <class T>
Queue<T>::~Queue()
{
	list.~LinkedList();
}

template <class T>
void Queue<T>::enqueue(T item)
{
	list.insertAtTail(item);
}

template <class T>
T Queue<T>::front()
{
	return list.getHead()->value;
}

template <class T>
T Queue<T>::dequeue()
{
	int x= (list.getHead())->value;
	list.deleteHead();
	return x;
}

template <class T>
int Queue<T>::length()
{
	return list.length();
}

template <class T>
bool Queue<T>::isEmpty()
{
	if(list.getHead()==NULL)
	{
		return true;
	}
}


#endif

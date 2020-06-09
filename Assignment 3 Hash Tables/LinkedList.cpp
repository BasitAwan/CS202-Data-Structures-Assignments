#ifndef __LIST_CPP
#define __LIST_CPP

#include <cstdlib>
#include "LinkedList.h"

template <class T>
LinkedList<T>::LinkedList()
{
	head= NULL;
	tail=NULL;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& otherLinkedList)
{

	if ((otherLinkedList.head)==NULL)
	{
		head=NULL;
		tail=NULL;
	}
	else
	{
		head= new ListItem<T>(otherLinkedList.head->value);
		tail= new ListItem<T>(otherLinkedList.tail->value);
		ListItem<T>* temp = (otherLinkedList.head); 
		ListItem<T>* ctemp= head;
		while(temp->next!=NULL)
		{
			ctemp->next= new ListItem<T>(temp->next->value);
			temp=temp->next;
			ctemp->next->prev= ctemp;
			ctemp=ctemp->next;

		}
	}
	
	


}

template <class T>
LinkedList<T>::~LinkedList()
{
	ListItem <T> *temp = head;
	while(temp !=NULL)
	{
		ListItem <T> *ctemp= temp->next;
		delete temp;
		temp = ctemp;
	}
}

template <class T>
void LinkedList<T>::insertAtHead(T item)
{
	if(head==NULL)
	{
		ListItem<T>* temp = new ListItem<T>(item);
		head = temp;
		tail =temp;
		return;

	}
	ListItem <T> *temp = new ListItem <T>(item);
	head->prev= temp;
	temp->next = head;
	head = temp;

}

template <class T>
void LinkedList<T>::insertAtTail(T item)
{
	
	if (head==NULL)
	{
		ListItem<T>* temp = new ListItem<T>(item);
		head = temp;
		tail=temp;
		return;
	}
	ListItem<T>*temp= new ListItem<T>(item);
	tail->next= temp;
	temp->prev = tail;
	tail=temp;
	
}

template <class T>
void LinkedList<T>::insertAfter(T toInsert, T afterWhat)
{
	ListItem<T>*temp = head;
	while(temp!=NULL)
	{
		if(temp->value== afterWhat)
		{
			ListItem<T> *ctemp = new ListItem<T>(toInsert);
			ctemp->next= temp->next;
			ctemp->prev= temp;
			temp->next= ctemp;
			return;
		}
		temp= temp->next;
	}
	

}

template <class T>
void LinkedList<T>::insertSorted(T item)
{
	ListItem<T> *temp = new ListItem<T> (item);
	ListItem<T> *ctemp = head;
	if (head==NULL)
	{
		head = temp;
		return;
	}
	
	while(ctemp->value<= item && ctemp->next!=NULL)
	{
		ctemp= ctemp->next;
	}
	if (ctemp->value <= item)
	{
		ctemp->next =temp;
		temp->prev = ctemp;
		return;
	}
	temp->prev= ctemp->prev;
	ctemp->prev->next = temp;
	temp->next= ctemp;
	ctemp->prev=temp;


	
	
}

template <class T>
ListItem<T>* LinkedList<T>::getHead()
{
	return head;
}

template <class T>
ListItem<T>* LinkedList<T>::getTail()
{
	return tail;
}

template <class T>
ListItem<T> *LinkedList<T>::searchFor(T item)
{
	if (head==NULL)
	{
		return NULL;
	}

	ListItem<T>*temp = head;
	while(temp!=NULL)
	{
		if(temp->value== item)
		{
			return temp;
		}
		temp= temp->next;
	}
	return NULL;
}

template <class T>
void LinkedList<T>::deleteElement(T item)
{
	ListItem<T> *temp = searchFor(item);
	if (temp==NULL)
	{
		return;
	}
	if (temp->next==NULL && temp->prev==NULL)
	{
		head = NULL;
		tail = NULL;
	}
	if (temp->next==NULL)
	{
		this->deleteTail();
		return;
	}
	if (temp->prev==NULL)
	{
		this->deleteHead();
		return;
	}
	temp->prev->next= temp->next;
	temp->next->prev= temp->prev;
}

template <class T>
void LinkedList<T>::deleteHead()
{
	if (head==NULL)
	{
		return;
	}
	if (head==tail)
	{
		head=NULL;
		tail=NULL;
		return;
	}
	ListItem<T>*temp = head;
	head = head->next;
	head->prev=NULL;
	if (head->next==NULL)
	{
		tail=head;
	}
	delete temp;
}

template <class T>
void LinkedList<T>::deleteTail()
{
	if (head==NULL)
	{
		return;
	}
	if (head==tail)
	{
		head=NULL;
		tail=NULL;
		return;
	}
	ListItem<T> *temp = tail;
	tail = tail->prev;
	tail->next=NULL;
	if (tail->prev==NULL)
	{
		head=tail;
	}
	delete temp;
}

template <class T>
int LinkedList<T>::length()
{
	if (head==NULL)
	{
		return 0;
	}
	int x=0;
	ListItem <T> *temp = head;
	while(temp !=NULL)
	{
		x++;
		temp= temp->next;
	}
	return x;

}

template <class T>
void LinkedList<T>::reverse()
{
	ListItem<T> *temp =head;
	ListItem<T> *ctemp;
	tail = temp;
	ctemp = temp->next;
	temp->prev= ctemp;
	temp->next= NULL;
	temp=ctemp;
	while(temp->next!=NULL)
	{
		ctemp= temp->next;
		temp->next= temp->prev;
		temp->prev= ctemp;
		temp=ctemp; 
	}
	temp->next= temp->prev;
	temp->prev=NULL;
	head=temp;


}

template <class T>
void LinkedList<T>::parityArrangement()
{
	ListItem<T>*second= head->next;
	ListItem<T>*temp=head;
	ListItem<T> *ctemp;
	ListItem<T> *altnext;
	while(temp->next->next!=NULL)
	{
		ctemp=temp->next;
		altnext= temp->next->next;
		temp->next= altnext;
		altnext->prev= altnext->prev->prev;
		temp= ctemp;

	}
	temp->next= second;
	second->prev= temp;
}
template <class T>
bool LinkedList<T>::isPalindrome()
{
	if (head==NULL)
	{
		return 0;
	}
	ListItem<T> *temp = head;
	ListItem<T> *ctemp= tail;
	while(temp!=ctemp && temp->next==ctemp)
	{
		if (temp->value!=ctemp->value)
		{
			return 0;
		}
		temp=temp->next;
		ctemp= ctemp->prev;
	}
	if (ctemp->value != temp->value)
	{
		return 0;
	}
	return 1;
}

#endif

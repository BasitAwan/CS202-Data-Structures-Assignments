#include "MySortedSet.h"
#include "LinkedList.cpp"

template <class T>
MySortedSet<T>::MySortedSet()
{
	
}

template <class T>
MySortedSet<T>::~MySortedSet()
{
	list.~LinkedList();
}

template <class T>
ListItem<T>* MySortedSet<T>::getListHead()
{
	return list.getHead();
}

template <class T>
int MySortedSet<T>::insert(T ele)
{
	if (list.getHead()==NULL)
	{
		list.insertAtHead(ele);
	}
	if (list.searchFor(ele)==NULL)
	{
		list.insertSorted(ele);
		return 1;
	}
	return 0;

}

template <class T>
int MySortedSet<T>::deleteEle(T ele)
{
	list.deleteElement(ele);
}

template <class T>
int MySortedSet<T>::isEmpty()
{
	if (list.getHead()==NULL)
	{
		return 1;
	}
	return 0;
}

template <class T>
int MySortedSet<T>::isMember(T ele)
{
	if (list.searchFor(ele)==NULL)
	{
		return 0;
	}
	return 1;
}

template <class T>
int MySortedSet<T>::isEqual(MySortedSet<T>* anotherset)
{
	ListItem<T> *temp = anotherset->getListHead();
	while(temp!=NULL)
	{
		if (this->isMember(temp->value)==0)
		{
			return 0;
		}
		temp=temp->next;
	}
	temp = this->getListHead();
	while(temp!=NULL)
	{
		if (anotherset->isMember(temp->value)==0)
		{
			return 0;
		}
		temp=temp->next;
	}
	return 1;
}

template <class T>
int MySortedSet<T>::isSubset(MySortedSet<T>* anotherset)
{
	ListItem<T> *temp = anotherset->getListHead();
	while(temp!=NULL)
	{
		if (this->isMember(temp->value)==0)
		{
			return 0;
		}
		temp=temp->next;
	}
	return 1;
}

template <class T>
MySortedSet<T>* MySortedSet<T>::setUnion(MySortedSet<T>* anotherset)
{
	ListItem<T> *temp = this->getListHead();
	MySortedSet<T> *buffer = new MySortedSet<T>();
	while(temp!=NULL)
	{
		buffer->insert(temp->value);
		temp=temp->next;
	}
	temp = anotherset->getListHead();
	while(temp!=NULL)
	{
		buffer->insert(temp->value);
		temp=temp->next;
	}
	return buffer;
}

template <class T>
MySortedSet<T>* MySortedSet<T>::setIntersection(MySortedSet<T>* anotherset)
{
	ListItem<T> *temp = this->getListHead();
	MySortedSet<T> *buffer = new MySortedSet<T>();
	while(temp!=NULL)
	{
		if (anotherset->isMember(temp->value)==1)
		{
			buffer->insert(temp->value);
		}
		temp=temp->next;
	}
	
	return buffer;
}

template <class T>
MySortedSet<T>* MySortedSet<T>::setDifference(MySortedSet<T>* anotherset)
{
	ListItem<T> *temp = this->getListHead();
	MySortedSet<T> *buffer = new MySortedSet<T>();
	while(temp!=NULL)
	{
		if (anotherset->isMember(temp->value)==1)
		{
		}
		else
		{
			buffer->insert(temp->value);
		}
		temp=temp->next;
	}
	
	return buffer;
}
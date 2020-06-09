#ifndef __STACK_CPP
#define __STACK_CPP
#include "stack.h"
#include "LinkedList.cpp"

template <class T>
Stack<T>::Stack()
{

}
    
template <class T>
Stack<T>::Stack(const Stack<T>& otherStack)
{
	LinkedList<T>buff(otherStack.list);
	list.head= buff.getHead();


}

template <class T>
Stack<T>::~Stack()
{
	list.~LinkedList();
}

template <class T>
void Stack<T>::push(T item)
{
	list.insertAtHead(item);
}

template <class T>
T Stack<T>::top()
{
	return (list.getHead())->value;
}

template <class T>
T Stack<T>::pop()
{
	int x= (list.getHead())->value;
	list.deleteHead();
	return x;
}

template <class T>
int Stack<T>::length()
{
	return list.length();
}

template <class T>
bool Stack<T>::isEmpty()
{
	if(list.getHead()==NULL)
	{
		return true;
	}
}

#endif

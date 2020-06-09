#ifndef __BST_CPP
#define __BST_CPP
#include "bst.h"
#include <iostream>
#include <queue>
#include<iomanip>


// HELPER FUNCTIONS HERE...
template <class T>
BST<T>::BST()
{
	root = NULL;
}

template <class T>
BST<T>:: ~BST(){
    while(root)
    {
        delete_node(root->key);
    }
}

template <class T>
int BST<T> :: height (node<T>* p){
   // your find height code goes here
   return p->height;
}

template <class T>
int BST<T> :: balanceFactor(node<T>* p){
    // you can use this to find balance factor.
    if (!p)
    {
    	return 0;
    }
	else if (p->left && p->right)
   	{
   		int left_height=(p->left)->height;
    	int right_height=(p->right)->height;
   		return left_height-right_height;
    }
    else if (p->left)
    {
    	return (p->left)->height;
    }
    else if (p->right)
    {
    	return -((p->right)->height);
    }
    else
    {
    	return 0;
    }
}

template <class T>
void BST<T> :: fixHeight(node<T>* p){
    // use this function to fix height of a node after insertion or deletion.
    if (!p)
    {
        return;
    }
    else if (!p->left || !p->right)
    {
        if (p->left)
        {
            p->height=(p->left)->height+1;
        }
        else if (p->right)
        {
             p->height=(p->right)->height+1;
        }
        else
        {
            p->height=1;
        }
    }
    else if (((p->left)->height) >((p->right)->height))
    {
        p->height=(p->left)->height+1;
    }
    else
    {
        p->height=(p->right)->height+1;
    }
    return;
}

// ROTATING HELPERS 
template <class T>
node<T>* BST<T> :: rotateleft(node<T>* p){
    // Rotate left code goes here.
    node<T> *pRight=p->right;
    node<T> *temp=pRight->left;
    pRight->left=p;
    p->right=temp;
    fixHeight(p);
    fixHeight(pRight);
    return pRight;
}

template <class T>
node<T>* BST<T> :: rotateright(node<T>* p){
    // Rotate right code goes here
    //return p;
     node<T> *pLeft=p->left;
    node<T> *temp=pLeft->right;
    pLeft->right=p;
    p->left=temp;
    //fixHeightRec(p);
    fixHeight(p);
    fixHeight(pLeft);

    return pLeft;
}

template<class T>
void BST<T>::fixHeightRec(node<T> * p)
{
    if(p)
    {
        fixHeightRec(p->left);
        fixHeightRec(p->right);
        fixHeight(p);
       
    }
    else
    {
        fixHeight(p);
    }
}

template <class T>
node<T>* BST<T> :: balance(node<T>* p){    
    fixHeight(p);
  //  cout << "Here" << endl;
    if (balanceFactor(p)>1 && balanceFactor(p->left)>0) //left heavy
    {
    	//cout << "Left Left" << endl;
    	p=rotateright(p);

    }
    else if (balanceFactor(p)<-1 && balanceFactor(p->right)<0)
    {
        //cout << "Right Right" << endl;
        p=rotateleft(p);
    }
    else if (balanceFactor(p)>1 && balanceFactor(p->left)<0)
    {
    	//cout << "Left Right" << endl;
    	p->left=rotateleft(p->left);
    	
    	p=rotateright(p);
    }
    else if (balanceFactor(p)<-1 && balanceFactor(p->right)>0)
    {
    	//cout << "Right Left" << endl;
    	p->right=rotateright(p->right);
    	
    	p=rotateleft(p);
    }	
   
    	//fixHeight(p);
    	return p;
    
    // Balancing code goes here. You might need to find balance factor and call appropriate rotations.
}
// CLASS FUNCTIONS HERE
template <class T>
void BST<T> :: insert(string value,T k){
    root = insertHelper(value,k,root);
}
// insertion helpe  r
template <class T>
node<T>* BST<T> :: insertHelper(string value,T k, node<T> *p) { // note we need a helper because we need recursive calls
    // Insertion code goes here.
     if (p==NULL)
    {
        p = new node<T>(k, value);
    }
    else if (k >= p->key)
    {
        p->right = insertHelper(value,k,p->right);
    }
    else
    {
        p->left = insertHelper(value,k,p->left);
    }
    return balance(p);
}
template<class T>
node<T>* BST<T> :: search(T key)
{
    return searchHelper(key,root);
    // Search code goes here.
}

template<class T>
node<T>* BST<T> :: searchHelper(T k, node<T>* node)
{
    if(!node)
    {
        return NULL;
    }
    else
    {
        if (node->key==k)
        {
            return node;
        }
        else if (node->key>k)
        {
            return searchHelper(k,node->left);
        }
        else
        {
            return searchHelper(k,node->right);
        }
    }
}
// DELETE HELPER FUNCTIONS
template<class T>
node<T>* BST<T> :: findmin(node<T> *p){
    if(!p)
    {
        return NULL;
    }
    else if (!p->left)
    {
        return p;
    }
    else if (p->left)
    {
        return findmin(p->left);
    }
    else
    {
         return NULL;
    }
   
}

template<class T>
node<T>* BST<T> :: findParent(node<T> *p,T k){
  
   if (((p->left)->key==k) || ((p->right)->key==k))
    {
        return p;
    }
    else if (k<p->key)
    {
        return findParent(p->left,k);
    }
    else if (k>p->key)
    {
        return findParent(p->right,k);
    }
    else
    {
        return NULL;
    }

   
}

template<class T>
node<T>* BST<T>::removemin(node<T>* p) {
    if(!p)
    {
        return NULL;
    }
    else if (!p->left)
    {
        node<T> * temp = p->right;
        delete p;
        return temp;
    }
    else if (p->left)
    {
        p->left=removemin(p->left);
    }
    else
    {
         return NULL;
    }
    return balance(p);
    // This function recursively finds the min node and deletes it.
}

template<class T>
void BST<T>::delete_node(T k){
    root = remove(root, k);
}

template<class T>
node<T>*  BST<T>::remove(node<T>* p, T k) // k key deletion from p tree
{
    if (!p)
    {
        return NULL;
    }
    else if (p->key==k)
    {
        if (!p->right && !p->left)
        {
            delete p;
            p=NULL;
        }
        else if (!p->left)
        {
            node<T>* temp = p->right;
            delete p;
            p=temp;
            temp=NULL;
        }
        else if (!p->right)
        {
            node<T>* temp = p->left;
            delete p;
            p=temp;
            temp=NULL;
        }
        else
        {
            node<T>* temp = findmin(p->right); //sucessor found
            cout << "temp: " <<" " << temp->key << "  " << temp->value << endl;
            p->key=temp->key;
            p->value=temp->value;
            p->right=removemin(p->right);
        }
    }
    else if (k<p->key)
    {
        p->left=remove(p->left,k);
    }
    else
    {
        p->right=remove(p->right,k);
    }

    return balance(p);
    // This function uses findmin and deletemin to delete arbitrary node in the tree.
}
template<class T>
node<T>* BST<T>::getRoot(){
    return root;
}


template<class T>
void BST<T>::printTree(){
    printTreeHelper(root,0);
}

template<class T>
void BST<T>::printTreeHelper(node<T> * p, int indent)
{
     if(p != NULL) {
        if(p->right) {
            printTreeHelper(p->right, indent+4);
        }
        if (indent) {
            std::cout << std::setw(indent) << ' ';
        }
        if (p->right) std::cout<<" /\n" << std::setw(indent) << ' ';
        std::cout << p->key  << "\n ";
        if(p->left) {
            std::cout << std::setw(indent) << ' ' <<" \\\n";
            printTreeHelper(p->left, indent+4);
        }
    }    
}
/*
int main()
{
    
    BST<int> temp;

    temp.insert("Ten",10);
    cout << "Working" << endl;
    temp.insert("Thirteen",13);
    temp.insert("Eight",8);
    temp.insert("Twelve",12);
    temp.insert("Fifteen",15);
    temp.insert("Eleven",11);
    temp.insert("Sixteen",16);
    cout << "Height: " <<temp.search(10)->height << endl;
    //temp.delete_node(12);
    temp.printTree();
    temp.delete_node(13);

    cout << "Yo" << endl;
    temp.printTree();
    return 0;
}
*/
#endif



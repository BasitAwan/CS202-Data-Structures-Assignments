#include <iostream>
#include "bst.h"
#include <vector>


using namespace std;

template <class T>
BST<T>* bst_Union(BST<T>* tree1,BST<T>* tree2){
	
	helper(tree1->getRoot(), tree2->getRoot());
}
template <class T>
BST<T>* helper1(node<T> *root1, node<T>* root2)
{
	root2=helper2(root1->key, root1->value, root2);
	if(root1->left)
	{
		root2=helper1(root1->right,root2);
	}
	if(root2->right)
	{
		root2=helper1(root1->right,root2);
	}
	return root2;

}
template <class T>
BST<T>* helper2(string value,T k, node<T> *p)
{
	if (p==NULL)
    {
    	p = new node<T>(k, value);
    }
    else if (k > p->key)
    {
    	p->right = insertHelper(value,k,p->right);
    }
    else
    {
    	p->left = insertHelper(value,k,p->left);
    }
    return p;
}
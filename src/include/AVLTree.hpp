#ifndef AVLTREE_H
#define AVLTREE_H
#pragma once
#include "vector"
/*
Adelson-Velskii-Landis tree
*/

template<class T> 
struct __tree_node{
	T data;
	int height;
	typedef __tree_node<T>* pointer;
	pointer right,left, prev;

	__tree_node<T>(){};
	
	explicit __tree_node<T>(T v):data(v), right(nullptr), left(nullptr), prev(nullptr), height(0){};
	explicit __tree_node<T>(T v, pointer r, pointer l, pointer p):data(v), right(r), left(l), prev(p),height(0) {};
};


template<class T>
class AVLTree  
{	
	public:
		typedef __tree_node<T> TreeValue;
		typedef __tree_node<T>* TreePointer;

	private:
		TreePointer  root;
		// void __make_avltree(const vector<T> & v);
		bool __check_avl_constrain();
		AVLTree<T>::TreePointer __update_height(TreePointer newNode);
		TreePointer __insert_axu(TreePointer startNode, T& v);
		TreePointer __find_axu(TreePointer startNode, T& v);
		void __adjust_tree(TreePointer startNode);

		void __single_rotate(TreePointer startNode, bool isLL);
		void __double_rotate(TreePointer startNode, bool isLR);


	public:
		AVLTree():root(nullptr){};
		~AVLTree(){};
		explicit AVLTree(const std::vector<T> & v);
		void Insert(T v);
		TreePointer find(T v);
		void Erase(T v);
		void Display();
};
#endif

template<class T>
AVLTree<T>::AVLTree(const std::vector<T> & v){
	for(int i = 0; i < v.size(); i++){
		Insert(v.at(i));
	}
}

template<class T>
void AVLTree<T>::Insert(T v){
	if(root == nullptr){
		root = new TreeValue(v)
		return
	}
	TreePointer newNode = __insert_axu(root, v);
	TreePointer questionNode = __update_height(newNode);
	if(questionNode == nullptr) return;
	// it update to root node, no need to rotate sub tree.
	__adjust_tree(questionNode);
}

template<class T>
void AVLTree<T>::Erase(T v){
	TreePointer eraseNode = __find_axu(root, v);
	if(eraseNode == nullptr) {
		//Print msg
		return;
	}
	// delete it
	TreePointer eraseParentNode = eraseNode->prev;
	TreePointer questionNode = __update_height(eraseNode);
	if(questionNode == nullptr) return;
	__adjust_tree(questionNode);
}

template<class T>
AVLTree<T>::TreePointer AVLTree<T>::find(T v){
	return __find_axu(root, v);
}

template<class T>
void AVLTree<T>::Display(){

}

/* --------------------------- Private Helper Function -------------------------------*/


// return the new inserted node
// the startNode can not be nullptr
// the tree is not balanced
template<class T>
AVLTree<T>::TreePointer AVLTree<T>::__insert_axu(TreePointer startNode,T& v){
	assert(startNode != nullptr);
	bool isLeft = startNode->data > v;
	TreePointer next = isLeft ? startNode->left : startNode->right;
	if(next != nullptr){
		return __insert_axu(next, v);
	} else {
		// construct a new node
		TreePointer node = new TreeValue(v, nullptr, nullptr, startNode);
		if(isLeft) startNode->left = node;
		else startNode->right = node;
	}
}

template<class T>
AVLTree<T>::TreePointer AVLTree<T>::__find_axu(TreePointer startNode, T& v){
	if(startNode == nullptr) return nullptr;

	if(startNode->data == v) 
		return startNode;
	else if(startNode->data > v) 
		return __find_axu(startNode->left, v);
	else 
		return __find_axu(startNode->right, v); 
}


template<class T>
AVLTree<T>::TreePointer AVLTree<T>::__update_height(TreePointer startNode){
	if(startNode == nullptr) return nullptr;
	int leftTreeHeight = startNode->left == nullptr ? -1 : startNode->left->height;
	int rightTreeHeight = startNode->right == nullptr ? -1 : startNode->right->height;
	if(abs(leftTreeHeight - rightTreeHeight) > 1){
		return startNode;
	}
	startNode->height = leftTreeHeight > rightTreeHeight ? leftTreeHeight + 1 : rightTreeHeight + 1;
	return startNode->prev;
}

template<class T>
void AVLTree<T>::__adjust_tree(TreePointer startNode){
	// have to judge single rotate or double rotate
	if(startNode->right->height > startNode->left->height){
		TreePointer subNode = startNode->right;
		if(subNode->right->height > startNode->left->height) 
			__single_rotate(startNode, false);  // RL
		else
			__double_rotate(startNode, false)   // RL
	} else {
		TreePointer subNode = startNode->left;
		if(subNode->right->height > startNode->left->height)
			__double_rotate(startNode, true) // LR
		else
			__single_rotate(startNode, true) // LL
	}

}


template<class T>
void AVLTree<T>::__double_rotate(TreePointer startNode, bool isLR){
	TreePointer ParentNode = startNode->prev;
	if(isLR){
		/*
			    18
		      /	   \	     							   18
			14		20			 RR						 /    \	
		  /    \			 ===========>				16	  20
		12		16									    /
			   /									  14
			15										/   \
												   12   15
		*/
		__single_rotate(startNode->left, false);
		startNode->left->height++;
		/*
			LL
		*/
		__single_rotate(startNode, true);
	} else {
		/*
			LL
		*/
		__single_rotate(startNode->right, true);
		startNode->right->height++;
		/*
			RR
		*/
		__single_rotate(startNode,false);
	}

}


template<class T>
void AVLTree<T>::__single_rotate(TreePointer startNode, bool isLL){
	TreePointer subRootNode;
	TreePointer ParentNode = startNode->prev;
	if(isLL){
		/*
			a->	 18                 		b->		14
				/  \							   /   \
		b->	   14  20							 12	     18	  <-a
			  /  \			==========>			/  	    /  \	
			 12  16	 <-c					   11      16   20
			/  										c->  
		   11                                          
		*/
		subRootNode = startNode->left;
		TreePointer a = startNode, b = startNode->left, c = startNode->left->right;
		b->prev = ParentNode;
		b->right = a;
		a->prev = b;
		a->left = c;
		
		if(c != nullptr){
			c->prev = a;
		}

	} else {
		// RR
		/*
			a->	 18                 	       	b->		20
				/  \						     	   /   \
		  	  10    20	<- b			  a->		 18	    30 	  
			  	   /  \			=======>         	/  \	  \
			c->   19  30	     		    	   10  19      33		  
			   		    \						    	  <-c
		   			    33                                         
		*/
		subRootNode = startNode->right;
		TreePointer a = startNode, b = startNode->right, c = startNode->right->left;
		b->prev = ParentNode;
		b->left = a;
		
		a->prev = b;
		a->right = c;
		
		if(c != nullptr){
			c->prev = a;
		}
	}
	// adjust the height of startnode a
	startNode->height--;
	// adjust the parent tree's sub pointer
	if(ParentNode->right == startNode) ParentNode->right = b;
	else ParentNode->left = b;
	return;
}
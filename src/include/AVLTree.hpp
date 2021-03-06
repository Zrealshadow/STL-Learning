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
		
		//DEBUG
		void __find_path_axu(TreePointer startNode ,T& v, std::vector<T> & p);
		void __in_order_traversal(TreePointer startNode, std::vector<T> & p);
		void __pre_order_traversal(TreePointer startNode, std::vector<T> & p);
		void __clear_axu(TreePointer* startNodeAdd);
	public:
		AVLTree():root(nullptr){};
		~AVLTree(){};
		explicit AVLTree(const std::vector<T> & v);
		void Insert(T v);
		void Insert(std::vector<T> &p);

		TreePointer find(T v);
		void Erase(T v);
		void Display();
		int getHeight();
		int getSize();
		void Clear();

		

		// DEBUG
		TreePointer getRoot();
		std::vector<T> findPath(T v);

		std::vector<T> in_order_traversal();
		std::vector<T> pre_order_traversal();

};
#endif

template<class T>
AVLTree<T>::AVLTree(const std::vector<T> & v){
	root = nullptr;
	// initialize root is very important
	for(int i = 0; i < v.size(); i++){
		Insert(v.at(i));
	}
}

template<class T>
void AVLTree<T>::Insert(T v){
	if(root == nullptr){
		root = new TreeValue(v);
		return;
	}
	TreePointer newNode = __insert_axu(root, v);
	TreePointer questionNode = __update_height(newNode);
	if(questionNode == nullptr) return;
	// it update to root node, no need to rotate sub tree.
	__adjust_tree(questionNode);
}

template<class T>
void AVLTree<T>::Insert(std::vector<T> &p){
	for(unsigned int i = 0; i < p.size(); i++){
		Insert(p.at(i));
	}
}

template<class T>
void AVLTree<T>::Clear(){
	if(root == nullptr) return;
	__clear_axu(&root);
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
	
	if(eraseParentNode->left == eraseNode) eraseParentNode->left = nullptr;
	else eraseNode->right = nullptr;
	delete eraseNode;
	TreePointer questionNode = __update_height(eraseParentNode);
	if(questionNode == nullptr) return;
	__adjust_tree(questionNode);
}

template<class T>
typename AVLTree<T>::TreePointer AVLTree<T>::find(T v){
	return __find_axu(root, v);
}

template<class T>
void AVLTree<T>::Display(){

}


template<class T>
int AVLTree<T>::getHeight(){
	return root->height;
}

template<class T>
typename AVLTree<T>::TreePointer AVLTree<T>::getRoot(){
	return root;
}

template<class T>
std::vector<T> AVLTree<T>::findPath(T v){
	std::vector<T> p;
	__find_path_axu(root, v, p);
	return p;
}


/* --------------------------- Private Helper Function -------------------------------*/

template<class T>
void AVLTree<T>::__find_path_axu(TreePointer startNode, T& v, std::vector<T>&p){
	if(startNode == nullptr) {
		p.clear();
		return;
	}
	p.push_back(startNode->data);
	TreePointer next = startNode->data > v ? startNode->left : startNode->right;
	if(startNode->data == v) return;
	return __find_path_axu(next, v, p);
}

template<class T>
void AVLTree<T>::__clear_axu(TreePointer* startNodeAdd){
	assert((*startNodeAdd) != nullptr);
	TreePointer startNode = (*startNodeAdd);
	if(startNode->left != nullptr) __clear_axu(&(startNode->left));
	if(startNode->right != nullptr) __clear_axu(&(startNode->right));
	// leaf node
	delete startNode;
	(*startNodeAdd) = nullptr;
}

// return the new inserted node
// the startNode can not be nullptr
// the tree is not balanced
template<class T>
typename AVLTree<T>::TreePointer AVLTree<T>::__insert_axu(TreePointer startNode,T& v){
	assert(startNode != nullptr);
	bool isLeft = startNode->data > v;
	TreePointer next = isLeft ? startNode->left : startNode->right;
	if(next != nullptr){
		TreePointer f = __insert_axu(next, v); // return __insert_axu(next, v);
		return f;
	}

	TreePointer node = new TreeValue(v, nullptr, nullptr, startNode); // construct a new node
	if(isLeft) {
		// std::cout <<"left"<< std::endl;
		startNode->left = node;
	} else {
		// std::cout << "right" << std::endl;
		startNode->right = node;
	}
	return node;

}

template<class T>
typename AVLTree<T>::TreePointer AVLTree<T>::__find_axu(TreePointer startNode, T& v){
	if(startNode == nullptr) return nullptr;

	if(startNode->data == v) 
		return startNode;
	else if(startNode->data > v) 
		return __find_axu(startNode->left, v);
	else 
		return __find_axu(startNode->right, v); 
}


template<class T>
typename AVLTree<T>::TreePointer AVLTree<T>::__update_height(TreePointer startNode){
	if(startNode == nullptr) return nullptr;
	int leftTreeHeight = startNode->left == nullptr ? -1 : startNode->left->height;
	int rightTreeHeight = startNode->right == nullptr ? -1 : startNode->right->height;
	if(abs(leftTreeHeight - rightTreeHeight) > 1){
		return startNode;
	}
	startNode->height = leftTreeHeight > rightTreeHeight ? leftTreeHeight + 1 : rightTreeHeight + 1;
	// return startNode->prev;
	return __update_height(startNode->prev);
}

template<class T>
void AVLTree<T>::__adjust_tree(TreePointer startNode){
	// have to judge single rotate or double rotate
	int rightheight = startNode->right == nullptr ? -1 : startNode->right->height;
	int leftheight = startNode->left == nullptr ? -1 : startNode->left->height;
	if(rightheight > leftheight){
		TreePointer subNode = startNode->right;
		rightheight = subNode->right == nullptr ? -1 : subNode->right->height;
		leftheight = subNode->left == nullptr ? -1 : subNode->left->height;
		if(rightheight > leftheight) 
			__single_rotate(startNode, false);  // RR
		else
			__double_rotate(startNode, false);   // RL
	} else {
		TreePointer subNode = startNode->left;
		rightheight = subNode->right == nullptr ? -1 : subNode->right->height;
		leftheight = subNode->left == nullptr ? -1 : subNode->left->height;
		if(rightheight > leftheight)
			__double_rotate(startNode, true); // LR
		else
			__single_rotate(startNode, true); // LL
		
			
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
	TreePointer a,b,c;
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
		a = startNode, b = startNode->left, c = startNode->left->right;
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
		a = startNode, b = startNode->right, c = startNode->right->left;
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
	if(ParentNode == nullptr) {
		root = b;
		return;
	}
	if(ParentNode->right == startNode) ParentNode->right = b;
	else ParentNode->left = b;
	return;
}


/* ----------- TRAVERSAL --------------*/

template<typename T>
std::vector<T> AVLTree<T>::in_order_traversal(){
	std::vector<T> p;
	__in_order_traversal(root, p);
	return p;
}

template<typename T>
std::vector<T> AVLTree<T>::pre_order_traversal(){
	std::vector<T> p;
	__pre_order_traversal(root, p);
	return p;
}

template<typename T>
void AVLTree<T>:: __in_order_traversal(TreePointer startNode, std::vector<T> & p){
	if(startNode == nullptr) return;
	p.push_back(startNode->data);
	__in_order_traversal(startNode->left, p);
	__in_order_traversal(startNode->right, p);
}

template<typename T>
void AVLTree<T>:: __pre_order_traversal(TreePointer startNode, std::vector<T> & p){
	if(startNode == nullptr) return;
	__pre_order_traversal(startNode->left, p);
	p.push_back(startNode->data);
	__pre_order_traversal(startNode->right, p);
}
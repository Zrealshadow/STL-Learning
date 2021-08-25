#ifndef OWNHEAP_H
#define OWNHEAP_H
#pragma once
#include<vector>

template<class T>
class Ownheap  
{	

	public:
		typedef typename std::vector<T>::iterator iterator;
		void display();
		bool empty() const {return c.empty();};
		size_t capacity() const {return c.capacity();};
		size_t size() const { return c.size();};

		Ownheap(std::vector<T> &);
		
		T pop();
		void push(const T &);
		
		Ownheap();
		~Ownheap();
	
	private:
		std::vector<T> c;
		void __pop_heap(iterator first, iterator last);
		void __init_heap(iterator first, iterator last);
		void __push_heap(iterator first, iterator last);

};


#endif
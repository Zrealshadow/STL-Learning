// #include "Ownheap.hpp" 
// #include "math.h"
// #include "iostream"
// template<typename T>
// Ownheap<T>::Ownheap()
// {
	
// }

// template<typename T>	
// Ownheap<T>::~Ownheap()
// {
// 	c.clear();
// }

// template<typename T>
// Ownheap<T>::Ownheap(std::vector<T> &cc){
//     c = cc;
//     if(c.size() > 1) {
//         __init_heap(c.begin(), c.end());
//     }
// }

// template<typename T>
// T Ownheap<T>::pop(){
//     if(empty()) throw std::exception();
//     if(size() == 1) {

//     } else {
//         __pop_heap(c.begin(), c.end());
//     }

//     T ans = c.at(c.size() - 1);
//     c.pop_back();
//     return ans;    
// }


// template<typename T>
// void Ownheap<T>::push(const T & v){
//     c.push_back(v);
//     if(empty()) return;
    
//     __push_heap(c.begin(), c.end());
//     return;
// }


// template<typename T>
// void Ownheap<T>::__pop_heap(iterator first, iterator last){
//     T result = *(first);
//     T value = *(last - 1);
//     *last = *(first);

//     size_t len = std::distance(first, last) - 1;
//     size_t topIndex = 0;
//     size_t secondChild = topIndex * 2 + 2;
//     while(secondChild < len){
//         // 该节点不再拥有两个子节点
//         if( *(first + secondChild) < *(first + secondChild - 1)){
//             // 右节点 < 左节点
//             secondChild--;
//         }
//         if(*(first + secondChild) < value){
//             break;
//         }
//         *(first + topIndex) = *(first + secondChild);
//         topIndex = secondChild;
//         secondChild = topIndex * 2 + 2;
//     }

//     if(secondChild == len and *(first + secondChild - 1) > value){
//         //有左节点,没有右节点
//         *(first + topIndex) = *(first + secondChild - 1);
//         topIndex = secondChild - 1;
//     }

//     *(first + topIndex) = value;
//     return;
// }

// template<typename T>
// void Ownheap<T>::__init_heap(iterator first, iterator last){
//     size_t lastRange = std::distance(first, last);
//     for(size_t i = 2; i <= lastRange; i++){
//         iterator l = first + i;
//         __push_heap(first, l);
//     }
// }



// // last element is the new pushed value 
// template<typename T>
// void Ownheap<T>::__push_heap(iterator first, iterator last){
//     T value = *(last - 1);
//     size_t holeIndex = std::distance(first, last) - 1;
//     size_t parentIndex = (holeIndex - 1) / 2;
//     while(holeIndex > 0 && *(first + parentIndex) < value){
//         *(first + holeIndex) = *(first + parentIndex);
//         holeIndex = parentIndex;
//         parentIndex = (holeIndex - 1) / 2;
//     }
//     *(first + holeIndex) = value;
// }


// template<typename T>
// void Ownheap<T>::display(){
//     size_t level = ceil(log(size()) / log(2));
//     for(size_t i = 0, j = 0; j < size(); j++){
//         std::cout << c.at(j) << " ";
//         if(j == pow(2, i + 1) - 2){
//             std::cout << std::endl;
//             i++;
//         }
//     }
//     std::cout << std::endl;
// }

// template class Ownheap<int>;
// template class Ownheap<float>;
#include <iostream>
#include <vector>
#include <new>
#include <string>
// #include "jjalloc.hpp"
#include "Ownheap.hpp"
#include "math.h"
using namespace std;







int main(){

    std::vector<int> v1 = {20, 30, 40, 25, 15, 100, 50};
    Ownheap<int> f = Ownheap<int>(v1);
    
    std::cout << f.size() << endl;
    std::cout << f.capacity() << endl;
    f.display();
}
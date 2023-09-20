#include <list>
#include <iostream> 
//std::cout<<&r<<"\n";

int main() {
    std::list<int> list4{ 1, 2, 4, 5 };   // список list4 состоит из чисел 1, 2, 4, 5
std::list<int> list5 = { 1, 2, 3, 5 }; // список list5 состоит из чисел 1, 2, 4, 5
std::list<int> list6(list4);          // список list6 - копия списка list4
std::list<int> list7 = list4;
std::cout<<list4.max_size()<<"\n";
}
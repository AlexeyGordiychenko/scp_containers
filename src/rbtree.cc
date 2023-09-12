#include "rbtree.h"

#include <iostream>
int main() {
  {
    RbTree<int, int, std::less<int>, std::allocator<int>> tree;
    int a = 9;
    tree.insert(a);
    tree.insert(7);
    tree.insert(15);
    tree.insert(6);
    tree.insert(5);
    tree.insert(2);
    tree.insert(2);
    a = 1;
    tree.print();
  }
  std::cout << "finish" << std::endl;
  return 0;
}
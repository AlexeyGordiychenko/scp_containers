#include "rbtree.h"

#include <iostream>
int main() {
  RbTree<int, int, std::less<int>, std::allocator<int>> tree;
  tree.insert(9);
  tree.insert(7);
  tree.insert(15);
  tree.insert(6);
  tree.insert(5);
  tree.insert(2);
  tree.print();
  return 0;
}
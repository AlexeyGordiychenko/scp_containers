#include "rbtree.h"

#include <iostream>

struct GetKeySet {
  int operator()(const int& value) const { return value; }
};

struct GetKeyMap {
  template <typename K, typename V>
  const K& operator()(const std::pair<K, V>& value) const {
    return value.first;
  }
};

int main() {
  {
    RbTree<int, GetKeySet, std::less<int>, std::allocator<int>> tree;
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

  {
    RbTree<std::pair<int, std::string>, GetKeyMap, std::less<int>,
           std::allocator<int>>
        tree;
    tree.insert(std::make_pair(9, "nine"));
    tree.insert(std::make_pair(7, "seven"));
    tree.insert(std::make_pair(15, "fifteen"));
    tree.insert(std::make_pair(6, "six"));
    tree.insert(std::make_pair(5, "five"));
    tree.insert(std::make_pair(2, "two"));
    tree.insert(std::make_pair(2, "two"));
    tree.print();
  }

  std::cout << "finish" << std::endl;
  return 0;
}
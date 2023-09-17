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
  std::cout << "SET TEST" << std::endl;
  {
    RbTree<int, GetKeySet, std::less<int>> tree;
    int a = 9;
    tree.insert(a);
    tree.insert(7);
    tree.insert(15);
    tree.insert(6);
    tree.insert(5);
    tree.insert(2);
    tree.insert(2);
    tree.insert(22);
    tree.insert(18);
    tree.insert(25);
    a = 1;
    tree.print();
    std::cout << "SET FORWARD ITERATOR" << std::endl;
    for (auto i = tree.begin(); i != tree.end(); i++) {
      std::cout << *i << " ";
    }
    std::cout << std::endl;
    std::cout << "SET BACKWARD ITERATOR" << std::endl;
    for (auto i = tree.rbegin(); i != tree.rend(); i++) {
      std::cout << *i << " ";
    }
    std::cout << std::endl;
  }

  {
    std::cout << "MAP TEST" << std::endl;
    RbTree<std::pair<int, std::string>, GetKeyMap, std::less<int>> tree;
    tree.insert(std::make_pair(9, "nine"));
    tree.insert(std::make_pair(7, "seven"));
    tree.insert(std::make_pair(15, "fifteen"));
    tree.insert(std::make_pair(6, "six"));
    tree.insert(std::make_pair(5, "five"));
    tree.insert(std::make_pair(2, "two"));
    tree.insert(std::make_pair(2, "two"));
    tree.insert(std::make_pair(22, "twenty-two"));
    tree.insert(std::make_pair(18, "eighteen"));
    tree.insert(std::make_pair(25, "twenty-five"));

    tree.print();
    std::cout << "MAP FORWARD ITERATOR" << std::endl;
    for (auto i = tree.begin(); i != tree.end(); ++i) {
      std::cout << i->second << " ";
    }
    std::cout << std::endl;
    std::cout << "MAP BACKWARD ITERATOR" << std::endl;
    for (auto i = tree.rbegin(); i != tree.rend(); ++i) {
      std::cout << i->second << " ";
    }
    std::cout << std::endl;
  }

  {
    std::cout << "MAP EMPTY TEST" << std::endl;
    RbTree<std::pair<int, std::string>, GetKeyMap, std::less<int>> tree;
    for (auto i = tree.begin(); i != tree.end(); ++i) {
      std::cout << (*i).second << " ";
    }
    std::cout << std::endl;
    for (auto i = tree.rbegin(); i != tree.rend(); ++i) {
      std::cout << (*i).second << " ";
    }
    std::cout << std::endl;
  }

  {
    std::cout << "MAP SINGLE ELEMENT TEST" << std::endl;
    RbTree<std::pair<int, std::string>, GetKeyMap, std::less<int>> tree;
    tree.insert(std::make_pair(2, "two"));
    std::cout << "MAP SINGLE ELEMENT FORWARD ITERATOR" << std::endl;
    for (auto i = tree.begin(); i != tree.end(); ++i) {
      std::cout << (*i).second << " ";
    }
    std::cout << std::endl;
    std::cout << "MAP SINGLE ELEMENT BACKWARD ITERATOR" << std::endl;
    for (auto i = tree.begin(); i != tree.end(); ++i) {
      std::cout << (*i).second << " ";
    }
    std::cout << std::endl;
  }

  std::cout << "finish" << std::endl;
  return 0;
}
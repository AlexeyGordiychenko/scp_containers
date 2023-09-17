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
    for (auto i = tree.cbegin(); i != tree.cend(); i++) {
      std::cout << *i << " ";
    }
    std::cout << std::endl;
    std::cout << "SET BACKWARD ITERATOR" << std::endl;
    for (auto i = tree.crbegin(); i != tree.crend(); i++) {
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
      std::cout << i->second << " ";
    }
    std::cout << std::endl;
    std::cout << "MAP SINGLE ELEMENT BACKWARD ITERATOR" << std::endl;
    for (auto i = tree.begin(); i != tree.end(); ++i) {
      std::cout << i->second << " ";
    }
    std::cout << std::endl;
  }

  {
    std::cout << "SET TEST2" << std::endl;
    RbTree<int, GetKeySet, std::less<int>> tree;
    tree.insert(30);
    tree.insert(20);
    tree.insert(10);
    tree.insert(40);
    tree.insert(50);
    std::cout << "SET TEST2 FORWARD ITERATOR" << std::endl;
    for (auto i = tree.begin(); i != tree.end(); ++i) {
      std::cout << *i << " ";
    }
    std::cout << std::endl;
    std::cout << "SET TEST2 BACKWARD ITERATOR" << std::endl;
    for (auto i = tree.rbegin(); i != tree.rend(); ++i) {
      std::cout << *i << " ";
    }
    std::cout << std::endl;
  }

  {
    std::cout << "SET CHANGE NON-CONST ITERATOR" << std::endl;
    RbTree<int, GetKeySet, std::less<int>> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(8);
    for (auto i = tree.begin(); i != tree.end(); ++i) {
      *i = 1;
      std::cout << *i << " ";
    }
    std::cout << std::endl;
    for (auto i = tree.rbegin(); i != tree.rend(); ++i) {
      *i = 2;
      std::cout << *i << " ";
    }
    std::cout << std::endl;
  }

  {
    std::cout << "MAP CHANGE NON-CONST ITERATOR" << std::endl;
    RbTree<std::pair<int, std::string>, GetKeyMap, std::less<int>> tree;
    tree.insert(std::make_pair(5, "five"));
    tree.insert(std::make_pair(3, "three"));
    tree.insert(std::make_pair(8, "eight"));
    for (auto i = tree.begin(); i != tree.end(); ++i) {
      i->second = "one";
      std::cout << i->second << " ";
    }
    std::cout << std::endl;
    for (auto i = tree.rbegin(); i != tree.rend(); ++i) {
      i->second = "two";
      std::cout << i->second << " ";
    }
    std::cout << std::endl;
  }

  std::cout << "finish" << std::endl;
  return 0;
}
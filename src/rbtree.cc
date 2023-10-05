#include <array>
#include <iostream>

#include "s21_rb_tree.h"

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
    s21::RbTree<int, int, GetKeySet, std::less<int>> tree;
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
    s21::RbTree<int, std::pair<int, std::string>, GetKeyMap, std::less<int>>
        tree;
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
    s21::RbTree<int, std::pair<int, std::string>, GetKeyMap, std::less<int>>
        tree;
    for (auto i = tree.begin(); i != tree.end(); ++i) {
      std::cout << (*i).second << " ";
    }
    for (auto i = tree.rbegin(); i != tree.rend(); ++i) {
      std::cout << (*i).second << " ";
    }
  }

  {
    std::cout << "MAP SINGLE ELEMENT TEST" << std::endl;
    s21::RbTree<int, std::pair<int, std::string>, GetKeyMap, std::less<int>>
        tree;
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
    s21::RbTree<int, int, GetKeySet, std::less<int>> tree;
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
    s21::RbTree<int, int, GetKeySet, std::less<int>> tree;
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
    s21::RbTree<int, std::pair<int, std::string>, GetKeyMap, std::less<int>>
        tree;
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

  {
    std::cout << "MAP FIND TEST" << std::endl;
    s21::RbTree<int, std::pair<int, std::string>, GetKeyMap, std::less<int>>
        tree;
    tree.insert(std::make_pair(9, "nine"));
    tree.insert(std::make_pair(7, "seven"));
    tree.insert(std::make_pair(15, "fifteen"));
    tree.insert(std::make_pair(6, "six"));
    tree.insert(std::make_pair(5, "five"));
    tree.insert(std::make_pair(2, "two"));
    auto test = tree.insert(std::make_pair(2, "two"));
    std::cout << test.second << std::endl;
    std::cout << test.first->first << std::endl;
    std::cout << test.first->second << std::endl;
    auto test2 = tree.insert(std::make_pair(22, "twenty-two"));
    std::cout << test2.second << std::endl;
    std::cout << test2.first->first << std::endl;
    std::cout << test2.first->second << std::endl;
    tree.insert(std::make_pair(18, "eighteen"));
    tree.insert(std::make_pair(25, "twenty-five"));

    std::array a = {16, 6, 25, 30};
    for (auto i = a.begin(); i != a.end(); ++i) {
      auto pos = tree.find(*i);
      if (pos != tree.end()) {
        std::cout << "  " << pos->second << std::endl;
      } else {
        std::cout << "  Not found" << std::endl;
      }
    }
  }

  {
    std::cout << "MAX SIZE" << std::endl;
    s21::RbTree<int, std::pair<int, std::string>, GetKeyMap, std::less<int>>
        tree;
    std::cout << tree.max_size() << std::endl;
  }

  {
    std::cout << "COPY CONSTRUCTOR" << std::endl;
    s21::RbTree<int, std::pair<int, std::string>, GetKeyMap, std::less<int>>
        tree1;
    tree1.insert(std::make_pair(1, "one"));
    tree1.insert(std::make_pair(2, "two"));
    s21::RbTree<int, std::pair<int, std::string>, GetKeyMap, std::less<int>>
        tree2(tree1);
    for (auto i = tree1.begin(); i != tree1.end(); ++i) {
      std::cout << i->second << " ";
    }
    std::cout << std::endl;
    for (auto i = tree2.begin(); i != tree2.end(); ++i) {
      std::cout << i->second << " ";
    }
    std::cout << std::endl;
  }

  {
    std::cout << "MOVE CONSTRUCTOR" << std::endl;
    s21::RbTree<int, std::pair<int, std::string>, GetKeyMap, std::less<int>>
        tree1;
    tree1.insert(std::make_pair(1, "one"));
    tree1.insert(std::make_pair(2, "two"));
    s21::RbTree<int, std::pair<int, std::string>, GetKeyMap, std::less<int>>
        tree2 = std::move(tree1);
    for (auto i = tree2.begin(); i != tree2.end(); ++i) {
      std::cout << i->second << " ";
    }
    std::cout << std::endl;
  }

  {
    std::cout << "COPY OPERATOR" << std::endl;
    s21::RbTree<int, std::pair<int, std::string>, GetKeyMap, std::less<int>>
        tree1;
    tree1.insert(std::make_pair(1, "one"));
    tree1.insert(std::make_pair(2, "two"));
    s21::RbTree<int, std::pair<int, std::string>, GetKeyMap, std::less<int>>
        tree2;
    tree2 = tree1;
    for (auto i = tree2.begin(); i != tree2.end(); ++i) {
      std::cout << i->second << " ";
    }
    std::cout << std::endl;
  }

  {
    std::cout << "MOVE OPERATOR" << std::endl;
    s21::RbTree<int, std::pair<int, std::string>, GetKeyMap, std::less<int>>
        tree1;
    tree1.insert(std::make_pair(1, "one"));
    tree1.insert(std::make_pair(2, "two"));
    s21::RbTree<int, std::pair<int, std::string>, GetKeyMap, std::less<int>>
        tree2;
    tree2 = std::move(tree1);
    for (auto i = tree2.begin(); i != tree2.end(); ++i) {
      std::cout << i->second << " ";
    }
    std::cout << std::endl;
  }

  {
    std::cout << "SWAP" << std::endl;
    s21::RbTree<int, std::pair<int, std::string>, GetKeyMap, std::less<int>>
        tree1;
    tree1.insert(std::make_pair(1, "one"));
    tree1.insert(std::make_pair(2, "two"));
    s21::RbTree<int, std::pair<int, std::string>, GetKeyMap, std::less<int>>
        tree2;
    tree2.insert(std::make_pair(3, "three"));
    tree2.insert(std::make_pair(4, "four"));
    tree1.swap(tree2);
    for (auto i = tree1.begin(); i != tree1.end(); ++i) {
      std::cout << i->second << " ";
    }
    std::cout << std::endl;
    for (auto i = tree2.begin(); i != tree2.end(); ++i) {
      std::cout << i->second << " ";
    }
    std::cout << std::endl;
  }

  std::cout << "finish" << std::endl;
  return 0;
}
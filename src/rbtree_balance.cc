#include <array>
#include <iostream>
#include <random>

#include "rbtree.h"

struct GetKeySet {
  int operator()(const int& value) const { return value; }
};

struct GetKeyMap {
  template <typename K, typename V>
  const K& operator()(const std::pair<K, V>& value) const {
    return value.first;
  }
};

// Function to generate random number
// Function to generate random number
int GenerateRandomNumber(std::mt19937& gen, int a, int b) {
  // Uniform distribution
  std::uniform_int_distribution<> dis(a, b);

  // Generate and return random number
  return dis(gen);
}

void FillTree(std::vector<int>& values_to_insert,
              std::vector<int>& values_to_delete,
              RbTree<int, int, GetKeySet, std::less<int>>& tree) {
  std::cout << "Inserted values: " << std::endl;
  for (auto value : values_to_insert) {
    tree.insert(value);
    std::cout << value << ",";
  }
  // std::cout << std::endl << "Deleted values: " << std::endl;
  // for (auto value : values_to_delete) {
  //   tree.erase(tree.find(value));
  //   std::cout << value << ",";
  // }
  std::cout << std::endl;
  int count = 0, size = tree.size();
  for (auto it = tree.begin(); it != tree.end(); it++, count++) {
  }
  // tree.print();
  std::string color = (count == size) ? "\033[0;32m" : "\033[0;31m";
  std::string color_off = "\033[0m";
  std::cout << "Inserted: " << color << count << color_off
            << "; Tree size: " << color << size << color_off << "; Tree is "
            << (tree.is_valid_tree() ? "\033[0;32m" : "\033[0;31mnot ")
            << "correct" << color_off << std::endl;
}
void Test1() {
  std::cout << "SET TEST" << std::endl;
  RbTree<int, int, GetKeySet, std::less<int>> tree;
  int a = 9;
  std::cout << "insert " << a << std::endl;
  tree.insert(a);
  tree.print();
  std::cout << "insert 7" << std::endl;
  tree.insert(7);
  tree.print();
  std::cout << "insert 15" << std::endl;
  tree.insert(15);
  tree.print();
  std::cout << "insert 6" << std::endl;
  tree.insert(6);
  tree.print();
  std::cout << "insert 5" << std::endl;
  tree.insert(5);
  tree.print();
  std::cout << "insert 2" << std::endl;
  tree.insert(2);
  tree.print();
  std::cout << "insert 2" << std::endl;
  tree.insert(2);
  tree.print();
  std::cout << "insert 22" << std::endl;
  tree.insert(22);
  tree.print();
  std::cout << "insert 18" << std::endl;
  tree.insert(18);
  tree.print();
  std::cout << "insert 25" << std::endl;
  tree.insert(25);
  tree.print();
  std::cout << "insert 8" << std::endl;
  tree.insert(8);
  tree.print();
  std::cout << "insert 16" << std::endl;
  tree.insert(16);
  tree.print();
  std::cout << "insert 17" << std::endl;
  tree.insert(17);
  tree.print();
  std::cout << "insert 19" << std::endl;
  tree.insert(19);
  tree.print();
  std::cout << "insert 20" << std::endl;
  tree.insert(20);
  tree.print();
  std::cout << "insert 23" << std::endl;
  tree.insert(23);
  tree.print();
  std::cout << "insert 24" << std::endl;
  tree.insert(24);
  a = 1;
  tree.print();
  std::cout << "delete 18" << std::endl;
  tree.erase(tree.find(18));
  tree.print();
  std::cout << "delete 9" << std::endl;
  tree.erase(tree.find(9));
  tree.print();
  std::cout << tree.is_valid_tree() << std::endl;
}

void Test2() {
  std::cout << "SET TEST2" << std::endl;
  RbTree<int, int, GetKeySet, std::less<int>> tree;
  auto it9 = tree.insert(9);
  auto it8 = tree.insert(8);
  tree.erase(it8.first);
  tree.erase(it9.first);
  tree.print();
}

void Test3(int n, int from, int to) {
  // Create a random device
  std::random_device rd;
  // Initialize Mersenne Twister pseudo-random number generator
  std::mt19937 gen(rd());

  std::cout << "SET TEST3" << std::endl;
  RbTree<int, int, GetKeySet, std::less<int>> tree;
  std::vector<int> values_to_insert;
  std::vector<int> values_to_delete;
  for (int i = 0; i < n; ++i) {
    int value = GenerateRandomNumber(gen, from, to);
    values_to_insert.push_back(value);
    // if (GenerateRandomNumber(gen, 0, 3) == 0) {
    // values_to_delete.push_back(value);
    // }
  }
  FillTree(values_to_insert, values_to_delete, tree);
}

void Test4() {
  RbTree<int, int, GetKeySet, std::less<int>> tree;
  std::vector<int> values_to_insert = {789, 188, 12,  454, 82,  474, 203,
                                       418, 330, 279, 282, 996, 676, 252,
                                       43,  131, 851, 971, 270, 266};
  std::vector<int> values_to_delete = {188};  //, 474, 131};
  FillTree(values_to_insert, values_to_delete, tree);
}

int main() {
  // Test1();
  // Test2();
  Test3(1000, 1, 10000);
  // Test4();
}

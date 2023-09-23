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
int GenerateRandomNumber(std::mt19937& gen, int a, int b) {
  // Uniform distribution
  std::uniform_int_distribution<> dis(a, b);

  // Generate and return random number
  return dis(gen);
}

void FillTree(std::vector<int>& values_to_insert,
              std::vector<int>& values_to_delete,
              RbTree<int, int, GetKeySet, std::less<int>>& tree) {
  // std::cout << "Inserted values: " << std::endl;
  for (auto value : values_to_insert) {
    tree.insert(value);
    // std::cout << value << ",";
  }
  // std::cout << std::endl << "Deleted values: " << std::endl;
  // for (auto value : values_to_delete) {
  //   tree.erase(tree.find(value));
  //   std::cout << value << ",";
  // }
  // std::cout << std::endl;
}

void OutputTree(RbTree<int, int, GetKeySet, std::less<int>>& tree,
                bool colored = true) {
  tree.print(colored);
  int count = 0, size = tree.size();
  for (auto it = tree.begin(); it != tree.end(); it++, count++) {
  }
  bool is_valid = tree.is_valid_tree();
  std::string color_size =
      (colored) ? ((count == size) ? "\033[0;32m" : "\033[0;31m") : "";
  std::string color_valid =
      (colored) ? (is_valid ? "\033[0;32m" : "\033[0;31m") : "";
  std::string color_off = (colored) ? "\033[0m" : "";
  std::cout << "Inserted: " << color_size << count << color_off
            << "; Tree size: " << color_size << size << color_off
            << "; Tree is " << color_valid << (is_valid ? "" : "not ")
            << "correct" << color_off << std::endl;
}
void Test1() {
  std::cout << "SET TEST1" << std::endl;
  RbTree<int, int, GetKeySet, std::less<int>> tree;
  std::vector<int> values_to_insert = {9,  7, 15, 6,  5,  2,  22, 18,
                                       25, 8, 16, 17, 19, 20, 23, 24};
  std::vector<int> values_to_delete = {18, 9};
  FillTree(values_to_insert, values_to_delete, tree);
  OutputTree(tree, false);
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
  OutputTree(tree, false);
}

void Test4() {
  RbTree<int, int, GetKeySet, std::less<int>> tree;
  std::vector<int> values_to_insert = {789, 188, 12,  454, 82,  474, 203,
                                       418, 330, 279, 282, 996, 676, 252,
                                       43,  131, 851, 971, 270, 266};
  std::vector<int> values_to_delete = {188};  //, 474, 131};
  FillTree(values_to_insert, values_to_delete, tree);
  OutputTree(tree, false);
}

int main() {
  // Test1();
  // Test2();
  for (int i = 0; i < 10; i++) Test3(1000, 1, 10000);
  // Test4();
}

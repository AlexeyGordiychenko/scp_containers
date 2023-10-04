#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <set>

#include "rbtree.h"

#define DEBUG 0

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
              s21::RbTree<int, int, GetKeySet, std::less<int>>& tree,
              bool duplicates = false) {
  if (DEBUG) std::cout << "Inserted values: " << std::endl;
  for (auto value : values_to_insert) {
    tree.insert(value, duplicates);
    if (DEBUG) std::cout << value << ",";
  }
  if (DEBUG) std::cout << std::endl << "Deleted values: " << std::endl;
  for (auto value : values_to_delete) {
    tree.erase(tree.find(value));
    if (DEBUG) std::cout << value << ",";
  }
  if (DEBUG) std::cout << std::endl;
}

void OutputTree(s21::RbTree<int, int, GetKeySet, std::less<int>>& tree,
                int expected_size, int expected_min, int expected_max,
                bool colored = true) {
  // tree.print(colored);
  int count = 0, size = tree.size();
  for (auto it = tree.begin(); it != tree.end(); it++, count++) {
  }
  bool is_valid = tree.is_valid_tree();
  auto start = tree.begin();
  auto end = tree.rbegin();

  if (!is_valid || count != expected_size || size != expected_size ||
      *start != expected_min || *end != expected_max) {
    throw std::runtime_error("Invalid tree");
  }

  std::string color_size =
      (colored)
          ? ((expected_size == count && expected_size == size) ? "\033[0;32m"
                                                               : "\033[0;31m")
          : "";
  std::string color_valid =
      (colored) ? (is_valid ? "\033[0;32m" : "\033[0;31m") : "";
  std::string color_start =
      (colored) ? ((expected_min == *start) ? "\033[0;32m" : "\033[0;31m") : "";
  std::string color_end =
      (colored) ? ((expected_max == *end) ? "\033[0;32m" : "\033[0;31m") : "";
  std::string color_off = (colored) ? "\033[0m" : "";

  std::cout << "Size: " << color_size << expected_size << color_off
            << "; Min: " << color_start << expected_min << color_off
            << " Max: " << color_end << expected_max << color_off
            << "; Tree is " << color_valid << (is_valid ? "" : "not ")
            << "correct" << color_off << std::endl;
}

void Test1() {
  std::cout << "SET TEST1" << std::endl;
  s21::RbTree<int, int, GetKeySet, std::less<int>> tree;
  std::vector<int> values_to_insert = {9,  7, 15, 6,  5,  2,  22, 18,
                                       25, 8, 16, 17, 19, 20, 23, 24};
  std::vector<int> values_to_delete = {18, 9};
  FillTree(values_to_insert, values_to_delete, tree);
  OutputTree(tree, 14, 2, 25, true);
}
void Test2() {
  std::cout << "SET TEST2" << std::endl;
  s21::RbTree<int, int, GetKeySet, std::less<int>> tree;
  auto it9 = tree.insert(9);
  auto it8 = tree.insert(8);
  tree.erase(it8.first);
  tree.erase(it9.first);
  // tree.print();
  for (auto it = tree.begin(); it != tree.end(); it++) {
    std::cout << *it << std::endl;
  }
}

void GenerateTree(int n, int from, int to, size_t& size, int& min, int& max,
                  s21::RbTree<int, int, GetKeySet, std::less<int>>& tree,
                  bool duplicates = false) {
  // Create a random device
  std::random_device rd;
  // Initialize Mersenne Twister pseudo-random number generator
  std::mt19937 gen(rd());

  // std::cout << "SET TEST3" << std::endl;
  // s21::RbTree<int, int, GetKeySet, std::less<int>> tree;
  std::vector<int> values_to_insert;
  std::vector<int> values_to_delete;
  for (int i = 0; i < n; ++i) {
    int value = GenerateRandomNumber(gen, from, to);
    if (GenerateRandomNumber(gen, 0, 3) == 0) {
      values_to_delete.push_back(value);
    }
    values_to_insert.push_back(value);
  }

  FillTree(values_to_insert, values_to_delete, tree, duplicates);

  if (!duplicates) {
    std::sort(values_to_insert.begin(), values_to_insert.end());
    auto last = std::unique(values_to_insert.begin(), values_to_insert.end());
    values_to_insert.erase(last, values_to_insert.end());
  }
  for (int element : values_to_delete) {
    auto it =
        std::find(values_to_insert.begin(), values_to_insert.end(), element);
    if (it != values_to_insert.end()) {
      values_to_insert.erase(it);
    }
  }

  auto min_max_pair =
      std::minmax_element(values_to_insert.begin(), values_to_insert.end());

  size = values_to_insert.size();
  min = *min_max_pair.first;
  max = *min_max_pair.second;
}
void Test3(int n, int from, int to, bool duplicates = false,
           bool colored = true) {
  // // Create a random device
  // std::random_device rd;
  // // Initialize Mersenne Twister pseudo-random number generator
  // std::mt19937 gen(rd());

  // std::cout << "SET TEST3" << std::endl;
  // s21::RbTree<int, int, GetKeySet, std::less<int>> tree;
  // std::vector<int> values_to_insert;
  // std::vector<int> values_to_delete;
  // for (int i = 0; i < n; ++i) {
  //   int value = GenerateRandomNumber(gen, from, to);
  //   if (GenerateRandomNumber(gen, 0, 3) == 0) {
  //     values_to_delete.push_back(value);
  //   }
  //   values_to_insert.push_back(value);
  // }

  // FillTree(values_to_insert, values_to_delete, tree, duplicates);

  // if (!duplicates) {
  //   std::sort(values_to_insert.begin(), values_to_insert.end());
  //   auto last = std::unique(values_to_insert.begin(),
  //   values_to_insert.end()); values_to_insert.erase(last,
  //   values_to_insert.end());
  // }
  // for (int element : values_to_delete) {
  //   auto it =
  //       std::find(values_to_insert.begin(), values_to_insert.end(), element);
  //   if (it != values_to_insert.end()) {
  //     values_to_insert.erase(it);
  //   }
  // }

  // auto min_max_pair =
  //     std::minmax_element(values_to_insert.begin(), values_to_insert.end());
  std::cout << "SET TEST3" << std::endl;
  size_t size;
  int min, max;
  s21::RbTree<int, int, GetKeySet, std::less<int>> tree;

  GenerateTree(n, from, to, size, min, max, tree, duplicates);
  OutputTree(tree, size, min, max, colored);
}

void Test4() {
  std::cout << "SET TEST4" << std::endl;
  s21::RbTree<int, int, GetKeySet, std::less<int>> tree;
  std::vector<int> values_to_insert = {789, 188, 12,  454, 82,  474, 203,
                                       418, 330, 279, 282, 996, 676, 252,
                                       43,  131, 851, 971, 270, 266};
  std::vector<int> values_to_delete = {188};  //, 474, 131};
  FillTree(values_to_insert, values_to_delete, tree);
  OutputTree(tree, 19, 12, 996, true);
}

void Test5() {
  std::cout << "SET TEST5" << std::endl;
  s21::RbTree<int, int, GetKeySet, std::less<int>> tree;
  std::vector<int> values_to_insert = {789, 188, 12,  454, 82,  474, 203,
                                       418, 330, 279, 282, 996, 676, 252,
                                       43,  131, 851, 971, 270, 266};
  std::vector<int> values_to_delete = {188};
  FillTree(values_to_insert, values_to_delete, tree);
  std::cout << tree.empty() << std::endl;
  tree.clear();
  std::cout << tree.empty() << std::endl;
}

void Test6() {
  std::cout << "SET TEST6" << std::endl;
  s21::RbTree<int, int, GetKeySet, std::less<int>> tree;
  std::vector<int> values_to_insert = {54, 85, 47, 15, 64, 53, 56, 32, 87, 14,
                                       49, 64, 17, 43, 48, 3,  66, 80, 21, 100};
  std::vector<int> values_to_delete = {85, 56, 87, 3, 21};
  FillTree(values_to_insert, values_to_delete, tree);
  OutputTree(tree, 14, 14, 100, true);
}
void Test7() {
  std::cout << "SET TEST7" << std::endl;
  s21::RbTree<int, int, GetKeySet, std::less<int>> tree;
  std::vector<int> values_to_insert = {18, 73, 53, 71, 61, 2, 8, 11, 87, 65};
  std::vector<int> values_to_delete = {8, 11};
  FillTree(values_to_insert, values_to_delete, tree);
  OutputTree(tree, 8, 2, 87, true);
}

void Test8() {
  std::cout << "SET TEST8" << std::endl;
  s21::RbTree<int, int, GetKeySet, std::less<int>> tree;
  std::vector<int> values_to_insert = {31, 42, 85, 84, 39, 72, 11, 89, 71, 13};
  std::vector<int> values_to_delete = {85, 89};
  FillTree(values_to_insert, values_to_delete, tree);
  OutputTree(tree, 8, 11, 84, true);
}

void Test9() {
  std::cout << "SET TEST9" << std::endl;
  s21::RbTree<int, int, GetKeySet, std::less<int>> tree;
  std::vector<int> values_to_insert = {29, 35, 87, 62, 91, 32, 66, 98, 38, 5,
                                       23, 9,  85, 91, 39, 48, 70, 87, 79, 76};
  std::vector<int> values_to_delete = {62, 91, 66, 23, 9, 48, 87, 79};
  FillTree(values_to_insert, values_to_delete, tree);
  OutputTree(tree, 10, 5, 98, true);
}

void Test10() {
  std::cout << "SET TEST10" << std::endl;
  s21::RbTree<int, int, GetKeySet, std::less<int>> tree;
  std::vector<int> values_to_insert = {29, 35, 87, 62, 91, 32, 66, 98, 38, 5,
                                       23, 9,  85, 91, 39, 48, 70, 87, 79, 76};
  std::vector<int> values_to_delete = {62, 91, 66, 23, 9, 48, 87, 79};
  FillTree(values_to_insert, values_to_delete, tree);
  OutputTree(tree, 10, 5, 98, true);
  for (auto it = tree.begin(); it != tree.end(); it++) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
  for (auto it = tree.rbegin(); it != tree.rend(); it++) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}

void Test11() {
  std::cout << "SET TEST11" << std::endl;
  s21::RbTree<int, int, GetKeySet, std::less<int>> tree;
  for (auto it = tree.begin(); it != tree.end(); it++) {
    std::cout << *it << " ";
  }
  for (auto it = tree.rbegin(); it != tree.rend(); it++) {
    std::cout << *it << " ";
  }
}

void Test12() {
  std::cout << "SET TEST12" << std::endl;
  s21::RbTree<int, int, GetKeySet, std::less<int>> tree;
  tree.insert(1);
  for (auto it = tree.begin(); it != tree.end(); it++) {
    std::cout << *it << " ";
  }
  for (auto it = tree.rbegin(); it != tree.rend(); it++) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}

void Test13() {
  std::cout << "SET TEST13" << std::endl;
  s21::RbTree<int, int, GetKeySet, std::less<int>> tree;
  tree.insert(1);
  tree.insert(2);
  for (auto it = tree.begin(); it != tree.end(); it++) {
    std::cout << *it << " ";
  }
  for (auto it = tree.rbegin(); it != tree.rend(); it++) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}

void TestMerge(int n, int from, int to, bool duplicates = false,
               bool colored = true) {
  // std::cout << "MERGE" << std::endl;
  size_t size1, size2;
  int min1, max1, min2, max2;
  s21::RbTree<int, int, GetKeySet, std::less<int>> tree1;
  GenerateTree(n, from, to, size1, min1, max1, tree1, duplicates);
  // OutputTree(tree1, size1, min1, max1, colored);
  s21::RbTree<int, int, GetKeySet, std::less<int>> tree2;
  GenerateTree(n, from, to, size2, min2, max2, tree2, duplicates);
  // OutputTree(tree2, size2, min2, max2, colored);
  tree1.merge(tree2, duplicates);
  // std::cout << "merged tree" << std::endl;
  // tree1.print(colored);
  // std::cout << "other tree" << std::endl;
  // tree2.print(colored);
  bool correct_size = (tree1.size() + tree2.size()) == (size1 + size2);
  auto it1 = tree1.begin();
  auto it2 = tree1.rbegin();
  bool correct_min = *it1 == std::min(min1, min2);
  bool correct_max = *it2 == std::max(max1, max2);

  bool correct_merge = tree1.is_valid_tree() && tree2.is_valid_tree() &&
                       correct_size && correct_min && correct_max;
  std::string color_valid =
      (colored) ? (correct_merge ? "\033[0;32m" : "\033[0;31m") : "";
  std::string color_off = (colored) ? "\033[0m" : "";
  std::cout << "Merge is " << color_valid << (correct_merge ? "" : "not ")
            << "correct" << color_off << std::endl;
  // std::string color_valid1 =
  //     (colored) ? (is_valid1 ? "\033[0;32m" : "\033[0;31m") : "";
  // std::string color_valid2 =
  //     (colored) ? (is_valid2 ? "\033[0;32m" : "\033[0;31m") : "";
  // std::string color_off = (colored) ? "\033[0m" : "";
  // std::cout << "Tree1 is " << color_valid1 << (is_valid1 ? "" : "not ")
  //           << "correct" << color_off << "; Tree2 is " << color_valid2
  //           << (is_valid2 ? "" : "not ") << "correct" << color_off <<
  //           std::endl;
}

void TestMergeSet(int n, int m, int from, int to, bool colored = true) {
  std::random_device rd;
  // Initialize Mersenne Twister pseudo-random number generator
  std::mt19937 gen(rd());

  s21::RbTree<int, int, GetKeySet, std::less<int>> tree1, tree2;
  std::set<int> std_set1, std_set2;
  if (DEBUG) std::cout << "Inserted values: " << std::endl;
  for (int i = 0; i < n; ++i) {
    int value = GenerateRandomNumber(gen, from, to);
    tree1.insert(value);
    std_set1.insert(value);
    if (DEBUG) std::cout << value << ",";
  }
  if (DEBUG) std::cout << std::endl;

  for (int i = 0; i < m; ++i) {
    int value = GenerateRandomNumber(gen, from, to);
    tree2.insert(value);
    std_set2.insert(value);
    if (DEBUG) std::cout << value << ",";
  }
  if (DEBUG) std::cout << std::endl;

  tree1.merge(tree2, false);
  std_set1.merge(std_set2);

  bool correct_merge = tree1.is_valid_tree() && tree2.is_valid_tree() &&
                       tree1.size() == std_set1.size() &&
                       tree2.size() == std_set2.size() &&
                       *tree1.begin() == *std_set1.begin() &&
                       *tree1.rbegin() == *std_set1.rbegin() &&
                       *tree2.begin() == *std_set2.begin() &&
                       *tree2.rbegin() == *std_set2.rbegin();
  std::string color_valid =
      (colored) ? (correct_merge ? "\033[0;32m" : "\033[0;31m") : "";
  std::string color_off = (colored) ? "\033[0m" : "";
  std::cout << "Merge is " << color_valid << (correct_merge ? "" : "not ")
            << "correct" << color_off << std::endl;
}

void TestMergeMultiSet(int n, int m, int from, int to, bool colored = true) {
  std::random_device rd;
  // Initialize Mersenne Twister pseudo-random number generator
  std::mt19937 gen(rd());

  s21::RbTree<int, int, GetKeySet, std::less<int>> tree1, tree2;
  std::multiset<int> std_set1, std_set2;
  for (int i = 0; i < n; ++i) {
    int value = GenerateRandomNumber(gen, from, to);
    tree1.insert(value, true);
    std_set1.insert(value);
  }
  for (int i = 0; i < m; ++i) {
    int value = GenerateRandomNumber(gen, from, to);
    tree2.insert(value, true);
    std_set2.insert(value);
  }

  tree1.merge(tree2, true);
  std_set1.merge(std_set2);

  auto tree_begin = tree1.begin();
  auto tree_end = tree1.rbegin();
  auto set_begin = std_set1.begin();
  auto set_end = std_set1.rbegin();

  bool correct_merge = tree1.is_valid_tree() && tree2.is_valid_tree() &&
                       tree1.size() == std_set1.size() &&
                       tree2.size() == std_set2.size() &&
                       *tree_begin == *set_begin && *tree_end == *set_end;
  std::string color_valid =
      (colored) ? (correct_merge ? "\033[0;32m" : "\033[0;31m") : "";
  std::string color_off = (colored) ? "\033[0m" : "";
  std::cout << "Merge is " << color_valid << (correct_merge ? "" : "not ")
            << "correct" << color_off << std::endl;
}

int main() {
  // Test1();
  // Test2();
  // Test4();
  // Test5();
  // Test6();
  // Test7();
  // Test8();
  // Test9();
  // Test10();
  // for (int i = 0; i < 100; i++) Test3(1000, 1, 10000);
  // for (int i = 0; i < 100; i++) Test3(1000, 1, 10000, true);
  // Test3(20, 1, 100, true);
  // Test11();
  // Test12();
  // Test13();
  std::random_device rd;
  std::mt19937 gen(rd());

  for (int i = 0; i < 100; i++)
    TestMergeSet(GenerateRandomNumber(gen, 1000, 2000),
                 GenerateRandomNumber(gen, 1000, 2000), 1, 10000);
  for (int i = 0; i < 100; i++)
    TestMergeMultiSet(GenerateRandomNumber(gen, 1000, 2000),
                      GenerateRandomNumber(gen, 1000, 2000), 1, 10000);
  // TestMergeSet(20, 15, 1, 100);
}

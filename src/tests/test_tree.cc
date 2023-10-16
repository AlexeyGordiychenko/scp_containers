#include "test.h"

TEST(TreeTest, 0) {
  s21::RbTree<int, std::pair<const int, std::string>, GetKeyMap, std::less<int>>
      tree1, tree2;

  for (int i = 0; i < 100000; ++i) {
    int key = rand() % 1000000;
    tree1.insert(std::make_pair(key, std::to_string(key)));
  }
  EXPECT_TRUE(tree1.is_valid_tree());
  for (auto elem : tree1) {
    if (elem.first % 2 == 0) {
      tree1.erase(tree1.find(elem.first));
    }
  }
  EXPECT_TRUE(tree1.is_valid_tree());
  for (int i = 0; i < 100000; ++i) {
    int key = rand() % 1000000;
    tree2.insert(std::make_pair(key, std::to_string(key)));
  }
  EXPECT_TRUE(tree2.is_valid_tree());
  tree1.merge(tree2);
  EXPECT_TRUE(tree1.is_valid_tree());
  EXPECT_TRUE(tree2.is_valid_tree());
}

TEST(TreeTest, 1) {
  s21::RbTree<int, std::pair<const int, std::string>, GetKeyMap, std::less<int>>
      tree1, tree2;

  for (int i = 0; i < 100000; ++i) {
    int key = rand() % 1000;
    tree1.insert(std::make_pair(key, std::to_string(key)), true);
  }
  EXPECT_TRUE(tree1.is_valid_tree());
  for (auto elem : tree1) {
    if (elem.first % 2 == 0) {
      tree1.erase(tree1.find(elem.first));
    }
  }
  EXPECT_TRUE(tree1.is_valid_tree());
  for (int i = 0; i < 100000; ++i) {
    int key = rand() % 1000;
    tree2.insert(std::make_pair(key, std::to_string(key)));
  }
  EXPECT_TRUE(tree2.is_valid_tree());
  tree1.merge(tree2, true);
  EXPECT_TRUE(tree1.is_valid_tree());
  EXPECT_TRUE(tree2.is_valid_tree());
}

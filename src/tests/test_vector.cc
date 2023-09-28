#include "test.h"

TEST(VectorTest, DefaultConstructor_1) {
  s21::vector<int> test;
  ASSERT_EQ(3, 3);
}

TEST(VectorTest, MaxSize_1) {
  s21::vector<bool> test;
  std::vector<std::string> test_2;

  ASSERT_NE(test.max_size(), test_2.max_size());
}

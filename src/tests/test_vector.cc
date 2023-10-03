#include "test.h"

TEST(VectorTest, DefaultConstructor_1) {
  s21::vector<int> test;
  ASSERT_EQ(test.size(), 0);
  ASSERT_EQ(test.capacity(), 0);
  ASSERT_EQ(test.data(), nullptr);
}

TEST(VectorTest, ParamConstructor_1) {
  s21::vector<bool> test(1);
  std::vector<std::string> test_2(1);

  ASSERT_EQ(test.size(), test_2.size());
  ASSERT_EQ(test.capacity(), test_2.capacity());
}

TEST(VectorTest, ParamConstructor_2) {
  s21::vector<bool> test(0);
  std::vector<std::string> test_2(0);

  ASSERT_EQ(test.size(), test_2.size());
  ASSERT_EQ(test.capacity(), test_2.capacity());
  ASSERT_EQ(test.data(), nullptr);
  ASSERT_EQ(test_2.data(), nullptr);
}

TEST(VectorTest, ParamConstructor_3) {
  s21::vector<bool> test(201);
  std::vector<std::string> test_2(201);

  ASSERT_EQ(test.size(), test_2.size());
  ASSERT_EQ(test.capacity(), test_2.capacity());
}

TEST(VectorTest, MaxSize_1) {
  s21::vector<bool> test;
  std::vector<std::string> test_2;

  ASSERT_NE(test.max_size(), test_2.max_size());
}

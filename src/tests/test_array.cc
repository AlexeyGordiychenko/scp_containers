#include "test.h"

TEST(ArrayTest, DefaultConstructor_1) {
  s21::array<int, 5> test;
  std::array<int, 5> test_2;

  ASSERT_EQ(test.size(), test_2.size());
}

TEST(ArrayTest, InitListConstructor_1) {
  s21::array<std::string, 4> test = {"one", "two", "three", "four"};
  std::array<std::string, 4> test_2 = {"one", "two", "three", "four"};

  ASSERT_EQ(test.size(), test_2.size());
}

TEST(ArrayTest, CopyConstructor_1) {
  s21::array<std::string, 4> test = {"one", "two", "three", "four"};
  s21::array<std::string, 4> test_2 = test;

  ASSERT_EQ(test.size(), test_2.size());
  for (size_t i = 0; i < test.size(); ++i) ASSERT_EQ(test[i], test_2[i]);
}

TEST(ArrayTest, Data_1) {
  s21::array<std::string, 4> test = {"one", "two", "three", "four"};
  std::array<std::string, 4> test_2 = {"one", "two", "three", "four"};

  ASSERT_EQ(test.data()[3], test_2.data()[3]);
  for (size_t i = 0; i < test.size(); ++i) ASSERT_EQ(test[i], test_2[i]);
}

TEST(ArrayTest, Data_2) {
  s21::array<int, 4> test = {1, 5, 6, 7};
  std::array<int, 4> test_2 = {1, 5, 6, 7};

  ASSERT_EQ(test.data()[3], test_2.data()[3]);
  for (size_t i = 0; i < test.size(); ++i) ASSERT_EQ(test[i], test_2[i]);
}

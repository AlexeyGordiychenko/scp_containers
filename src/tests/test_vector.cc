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

TEST(VectorTest, InitListConstructor_1) {
  s21::vector<int> test = {1, 20, 3, 40, 5, 60, 7};
  std::vector<int> test_2 = {1, 20, 3, 40, 5, 60, 7};

  ASSERT_EQ(test.size(), test_2.size());
  ASSERT_EQ(test.capacity(), test_2.capacity());
}

TEST(VectorTest, InitListConstructor_2) {
  s21::vector<int> test{1, 20, 3, 40, 5, 60, 7};
  std::vector<int> test_2{1, 20, 3, 40, 5, 60, 7};

  ASSERT_EQ(test.size(), test_2.size());
  ASSERT_EQ(test.capacity(), test_2.capacity());
}

TEST(VectorTest, InitListConstructor_3) {
  s21::vector<int> test{};
  std::vector<int> test_2{};

  ASSERT_EQ(test.size(), test_2.size());
  ASSERT_EQ(test.capacity(), test_2.capacity());
  ASSERT_EQ(test.data(), nullptr);
  ASSERT_EQ(test_2.data(), nullptr);
}

TEST(VectorTest, InitListConstructor_4) {
  s21::vector<int> test = {};
  std::vector<int> test_2 = {};

  ASSERT_EQ(test.size(), test_2.size());
  ASSERT_EQ(test.capacity(), test_2.capacity());
  ASSERT_EQ(test.data(), nullptr);
  ASSERT_EQ(test_2.data(), nullptr);
}

TEST(VectorTest, CopyConstructor_1) {
  s21::vector<int> test = {1, 2, 3, 4, 5};
  s21::vector<int> test_2 = test;

  ASSERT_EQ(test.size(), test_2.size());
  ASSERT_EQ(test.capacity(), test_2.capacity());
}

TEST(VectorTest, CopyConstructor_2) {
  s21::vector<int> test = {};
  s21::vector<int> test_2 = test;

  ASSERT_EQ(test.size(), test_2.size());
  ASSERT_EQ(test.capacity(), test_2.capacity());
  ASSERT_EQ(test.data(), nullptr);
  ASSERT_EQ(test_2.data(), nullptr);
}

TEST(VectorTest, CopyConstructor_3) {
  s21::vector<int> test(123);
  s21::vector<int> test_2 = test;

  ASSERT_EQ(test.size(), test_2.size());
  ASSERT_EQ(test.capacity(), test_2.capacity());
}

TEST(VectorTest, MoveConstructor_1) {
  s21::vector<int> test(123);
  s21::vector<int> test_2 = std::move(test);
  std::vector<int> testSTD(123);
  std::vector<int> testSTD_2 = std::move(testSTD);

  ASSERT_EQ(test.size(), testSTD.size());
  ASSERT_EQ(test.capacity(), testSTD.capacity());
  ASSERT_EQ(test.data(), testSTD.data());
  ASSERT_EQ(test_2.size(), testSTD_2.size());
  ASSERT_EQ(test_2.capacity(), testSTD_2.capacity());
}

TEST(VectorTest, OperatorEquals_1) {
  s21::vector<int> test(123);
  s21::vector<int> test_2 = test;
  s21::vector<int> test_3(2);

  test_3 = std::move(test_2);

  ASSERT_EQ(test_3.size(), test.size());
  ASSERT_EQ(test_3.capacity(), test.capacity());
  ASSERT_EQ(test_2.size(), 0);
  ASSERT_EQ(test_2.capacity(), 0);
}

TEST(VectorTest, MaxSize_1) {
  s21::vector<bool> test;
  std::vector<std::string> test_2;

  ASSERT_NE(test.max_size(), test_2.max_size());
}

TEST(VectorTest, Swap_1) {
  s21::vector<std::string> test{"first"};
  s21::vector<std::string> test_2{"second", "second"};
  auto one = test.size();
  auto two = test_2.size();

  test.swap(test_2);

  ASSERT_EQ(one, 1U);
  ASSERT_EQ(two, 2U);
  ASSERT_EQ(test.size(), two);
  ASSERT_EQ(test_2.size(), one);
}

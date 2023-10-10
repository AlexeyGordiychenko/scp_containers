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

TEST(VectorTest, OperatorEquals_2) {
  std::vector<int> test = {9, 9, 9, 9, 9, 9, 9, 9, 9};
  std::vector<int> test_2 = {3, 3, 3};
  s21::vector<int> test_s21 = {9, 9, 9, 9, 9, 9, 9, 9, 9};
  s21::vector<int> test_s21_2 = {3, 3, 3};

  test_2 = std::move(test);
  test_s21_2 = std::move(test_s21);

  ASSERT_EQ(test_2.size(), test_s21_2.size());
  ASSERT_EQ(test_2.capacity(), test_s21_2.capacity());
  EXPECT_EQ(test.data(), nullptr);
  EXPECT_EQ(test_s21.data(), nullptr);
}

TEST(VectorTest, At_1) {
  s21::vector<int> test = {1, 6, 4, 9, 7};
  std::vector<int> test_2 = {1, 6, 4, 9, 7};

  ASSERT_EQ(test.at(3), test_2.at(3));
}

TEST(VectorTest, At_2) {
  s21::vector<std::string> test = {"Hello", "World!!!"};
  std::vector<std::string> test_2 = {"Hello", "World!!!"};

  ASSERT_EQ(test.at(0).compare(test_2.at(0)), 0);
}

TEST(VectorTest, EXCEPT_At_3) {
  s21::vector<std::string> test = {"Hello", "World!!!"};
  std::vector<std::string> test_2 = {"Hello", "World!!!"};

  try {
    test.at(130);
    FAIL() << "Expected std::out_of_range";
  } catch (std::out_of_range const& err) {
    EXPECT_EQ(err.what(), std::string("at: Position is out of range"));
  }

  EXPECT_THROW(test_2.at(130), std::out_of_range);
}

TEST(VectorTest, ConstAt_1) {
  const s21::vector<int> test = {1, 6, 4, 9, 7};
  const std::vector<int> test_2 = {1, 6, 4, 9, 7};

  ASSERT_EQ(test.at(3), test_2.at(3));
}

TEST(VectorTest, EXCEPT_ConstAt_2) {
  const s21::vector<std::string> test = {"Hello", "World!!!"};
  const std::vector<std::string> test_2 = {"Hello", "World!!!"};

  try {
    test.at(130);
    FAIL() << "Expected std::out_of_range";
  } catch (std::out_of_range const& err) {
    EXPECT_EQ(err.what(), std::string("at(const): Position is out of range"));
  }

  EXPECT_THROW(test_2.at(130), std::out_of_range);
}

TEST(VectorTest, OperatorSqBr_1) {
  s21::vector<int> test = {1, 6, 4, 9, 7};
  std::vector<int> test_2 = {1, 6, 4, 9, 7};

  ASSERT_EQ(test[3], test_2[3]);
}

TEST(VectorTest, OperatorSqBr_2) {
  s21::vector<std::string> test = {"Hello", "World!!!"};
  std::vector<std::string> test_2 = {"Hello", "World!!!"};

  ASSERT_EQ(test[0].compare(test_2[0]), 0);
}

TEST(VectorTest, EXCEPT_OperatorSqBr_3) {
  s21::vector<std::string> test = {"Hello", "World!!!"};
  std::vector<std::string> test_2 = {"Hello", "World!!!"};

  EXPECT_NO_THROW(test[130]);
  EXPECT_NO_THROW(test_2[130]);
}

TEST(VectorTest, ConstOperatorSqBr_1) {
  const s21::vector<int> test = {1, 6, 4, 9, 7};
  const std::vector<int> test_2 = {1, 6, 4, 9, 7};

  ASSERT_EQ(test[3], test_2[3]);
}

TEST(VectorTest, Front_1) {
  s21::vector<int> test = {1, 6, 4, 9, 7};
  std::vector<int> test_2 = {1, 6, 4, 9, 7};

  ASSERT_EQ(test.front(), test_2.front());
}

TEST(VectorTest, ConstFront_1) {
  const s21::vector<int> test = {1, 6, 4, 9, 7};
  const std::vector<int> test_2 = {1, 6, 4, 9, 7};

  ASSERT_EQ(test.front(), test_2.front());
}

TEST(VectorTest, Back_1) {
  s21::vector<int> test = {1, 6, 4, 9, 7};
  std::vector<int> test_2 = {1, 6, 4, 9, 7};

  ASSERT_EQ(test.back(), test_2.back());
}

TEST(VectorTest, ConstBack_1) {
  const s21::vector<int> test = {1, 6, 4, 9, 7};
  const std::vector<int> test_2 = {1, 6, 4, 9, 7};

  ASSERT_EQ(test.back(), test_2.back());
}

TEST(VectorTest, EXCEPT_Front_2) {
  s21::vector<int> test;
  std::vector<int> test_2;

  EXPECT_NO_THROW(test.front());
  EXPECT_NO_THROW(test.back());
  EXPECT_NO_THROW(test_2.front());
  EXPECT_NO_THROW(test_2.back());
}

TEST(VectorTest, Clear_1) {
  s21::vector<int> test = {1, 6, 4, 9, 7};
  std::vector<int> test_2 = {1, 6, 4, 9, 7};

  test.clear();
  test_2.clear();

  ASSERT_EQ(test.size(), test_2.size());
  ASSERT_EQ(test.capacity(), test_2.capacity());
  ASSERT_EQ(test[4], test_2[4]);
}

TEST(VectorTest, Clear_2) {
  s21::vector<ClassWithPrintableDestructor> test(5);
  std::vector<ClassWithPrintableDestructor> test_2(5);
  test.clear();
  test_2.clear();
  std::cout << "TTTTTTTTTTTTTTTT\n";
  ASSERT_EQ(test.size(), test_2.size());
  ASSERT_EQ(test.capacity(), test_2.capacity());
}

TEST(VectorTest, Destructor_1) {
  s21::vector<ClassWithPrintableDestructor> test(5);
  std::cout << "TTTTTTTTTTTTTTTT\n";
}

TEST(VectorTest, Reserve_1) {
  s21::vector<std::vector<std::string>> test(5);
  std::vector<std::vector<std::string>> test_2(5);

  test_2[2].push_back("ABCD");
  ASSERT_EQ(test_2[2][0], "ABCD");

  test.reserve(61);
  test_2.reserve(61);

  ASSERT_EQ(test.size(), test_2.size());
  ASSERT_EQ(test.capacity(), test_2.capacity());
}

// TEST(VectorTest, MaxSize_1) {
//   s21::vector<bool> test;
//   std::vector<std::string> test_2;

//   ASSERT_NE(test.max_size(), test_2.max_size());
// }

// TEST(VectorTest, Swap_1) {
//   s21::vector<std::string> test{"first"};
//   s21::vector<std::string> test_2{"second", "second"};
//   auto one = test.size();
//   auto two = test_2.size();

//   test.swap(test_2);

//   ASSERT_EQ(one, 1U);
//   ASSERT_EQ(two, 2U);
//   ASSERT_EQ(test.size(), two);
//   ASSERT_EQ(test_2.size(), one);
// }

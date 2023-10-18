#include "test.h"

TEST(ArrayTest, DefaultConstructor_1) {
  s21::array<std::string, 5> test;
  std::array<std::string, 5> test_2;

  ASSERT_EQ(test.size(), test_2.size());
}

TEST(ArrayTest, CopyConstructor_1) {
  s21::array<std::string, 4> test{"one", "two", "three", "four"};
  s21::array<std::string, 4> test_2 = test;

  ASSERT_EQ(test.size(), test_2.size());
  for (size_t i = 0; i < test.size(); ++i) ASSERT_EQ(test[i], test_2[i]);
}

TEST(ArrayTest, MoveConstructor_1) {
  s21::array<std::string, 4> test{"one", "two", "three", "four"};
  s21::array<std::string, 4> test_2 = std::move(test);

  ASSERT_EQ(test.size(), 4);
  ASSERT_EQ(test_2[0], "one");
}

TEST(ArrayTest, InitListConstructor_1) {
  s21::array<std::string, 4> test = {"one", "two", "three", "four"};
  std::array<std::string, 4> test_2 = {"one", "two", "three", "four"};

  ASSERT_EQ(test.size(), test_2.size());
  for (size_t i = 0; i < test.size(); ++i) ASSERT_EQ(test[i], test_2[i]);
}

TEST(ArrayTest, CopyOperator_1) {
  s21::array<std::string, 4> test = {"one", "two", "three", "four"};
  s21::array<std::string, 4> test_2;

  test_2 = test;

  ASSERT_EQ(test.size(), test_2.size());
  for (size_t i = 0; i < test.size(); ++i) ASSERT_EQ(test[i], test_2[i]);
}

TEST(ArrayTest, MoveOperator_1) {
  s21::array<std::string, 4> test = {"one", "two", "three", "four"};
  s21::array<std::string, 4> test_2;

  test_2 = std::move(test);

  ASSERT_EQ(test.size(), test_2.size());
  ASSERT_EQ(test_2[0], "one");
}

TEST(ArrayTest, At_1) {
  s21::array<std::string, 4> test{"one", "two", "three", "four"};
  std::array<std::string, 4> test_2{"one", "two", "three", "four"};

  ASSERT_EQ(test.at(2), test_2.at(2));
  EXPECT_ANY_THROW(test.at(150));
}

TEST(ArrayTest, AtConst_1) {
  const s21::array<std::string, 4> test{"one", "two", "three", "four"};
  const std::array<std::string, 4> test_2{"one", "two", "three", "four"};

  const std::string& ref = test.at(2);
  const std::string& ref_2 = test_2.at(2);

  ASSERT_EQ(ref, ref_2);
  EXPECT_ANY_THROW(test.at(150));
}

TEST(ArrayTest, OperatorBrackets_1) {
  s21::array<std::string, 4> test{"one", "two", "three", "four"};
  std::array<std::string, 4> test_2{"one", "two", "three", "four"};

  ASSERT_EQ(test[2], test_2[2]);
  EXPECT_NO_THROW(test[150]);
}

TEST(ArrayTest, OperatorBracketsConst_1) {
  const s21::array<std::string, 4> test{"one", "two", "three", "four"};
  const std::array<std::string, 4> test_2{"one", "two", "three", "four"};

  const std::string& ref = test[2];
  const std::string& ref_2 = test_2[2];

  ASSERT_EQ(ref, ref_2);
}

TEST(ArrayTest, Data_1) {
  s21::array<std::string, 4> test{"one", "two", "three", "four"};
  std::array<std::string, 4> test_2{"one", "two", "three", "four"};

  ASSERT_EQ(test.data()[3], test_2.data()[3]);
  for (size_t i = 0; i < test.size(); ++i) ASSERT_EQ(test[i], test_2[i]);
}

TEST(ArrayTest, Data_2) {
  s21::array<int, 4> test{1, 5, 6, 7};
  std::array<int, 4> test_2{1, 5, 6, 7};

  ASSERT_EQ(test.data()[3], test_2.data()[3]);
  for (size_t i = 0; i < test.size(); ++i) ASSERT_EQ(test[i], test_2[i]);
}

TEST(ArrayTest, Front_1) {
  s21::array<std::string, 4> test{"one", "two", "three", "four"};
  std::array<std::string, 4> test_2{"one", "two", "three", "four"};

  ASSERT_EQ(test.front(), test_2.front());
}

TEST(ArrayTest, FrontConst_1) {
  const s21::array<std::string, 4> test{"one", "two", "three", "four"};
  const std::array<std::string, 4> test_2{"one", "two", "three", "four"};

  const std::string& copy = test.front();
  const std::string& copy_2 = test_2.front();

  std::string tmp = copy + copy_2;

  ASSERT_EQ(copy, copy_2);
  ASSERT_EQ(tmp, "oneone");
}

TEST(ArrayTest, Back_1) {
  s21::array<std::string, 4> test{"one", "two", "three", "four"};
  std::array<std::string, 4> test_2{"one", "two", "three", "four"};

  ASSERT_EQ(test.back(), test_2.back());
}

TEST(ArrayTest, Back_2) {
  s21::array<std::string, 4> test{"one", "two", "three", "four"};
  std::array<std::string, 4> test_2{"one", "two", "three", "four"};

  test.back() = "NEW";
  test_2.back() = "NEW";

  ASSERT_EQ(test.back(), "NEW");
  ASSERT_EQ(test_2.back(), "NEW");
}

TEST(ArrayTest, BackConst_1) {
  const s21::array<std::string, 4> test{"one", "two", "three", "four"};
  const std::array<std::string, 4> test_2{"one", "two", "three", "four"};

  const std::string& copy = test.back();
  const std::string& copy_2 = test_2.back();

  ASSERT_EQ(copy, copy_2);
}

TEST(ArrayTest, MaxSize_1) {
  s21::array<std::string, 4> test{"one", "two", "three", "four"};
  std::array<std::string, 4> test_2{"one", "two", "three", "four"};

  ASSERT_EQ(test.size(), test_2.size());
  ASSERT_EQ(test.max_size(), test_2.max_size());
}

TEST(ArrayTest, Empty_1) {
  s21::array<std::string, 0> test;
  std::array<std::string, 0> test_2;
  s21::array<std::string, 3> test_3;
  std::array<std::string, 3> test_4;

  ASSERT_TRUE(test.empty());
  ASSERT_TRUE(test_2.empty());
  ASSERT_EQ(test.size(), test_2.size());
  ASSERT_FALSE(test_3.empty());
  ASSERT_FALSE(test_4.empty());
  ASSERT_EQ(test_3.size(), test_4.size());
}

TEST(ArrayTest, End_Cend_Begin_Cbegin_1) {
  s21::array<std::string, 4> test{"one", "two", "three", "four"};
  std::array<std::string, 4> test_2{"one", "two", "three", "four"};
  const s21::array<std::string, 4> test_3{"one", "two", "three", "four"};
  const std::array<std::string, 4> test_4{"one", "two", "three", "four"};

  s21::array<std::string, 4>::iterator iter = test.begin();
  auto iter_2 = test_2.begin();
  s21::array<std::string, 4>::const_iterator iter_3 = test_3.cbegin();
  auto iter_4 = test_4.cbegin();

  ASSERT_EQ(*(test.end() - 1), *(test_2.end() - 1));
  ASSERT_EQ(*(test_3.cend() - 1), *(test_4.cend() - 1));
  ASSERT_EQ(*(test.end() - 1), *(test_3.cend() - 1));
  ASSERT_EQ(*(test_2.end() - 1), *(test_4.cend() - 1));

  ASSERT_EQ(*iter, *iter_2);
  ASSERT_EQ(*iter_3, *iter_4);
  ASSERT_EQ(*iter, *iter_3);
  ASSERT_EQ(*iter_2, *iter_4);

  iter++;
  iter_2++;

  ASSERT_EQ(*iter, *iter_2);
  ASSERT_EQ(*iter_3, *iter_4);
}

TEST(ArrayTest, Fill_1) {
  s21::array<std::string, 4> test;
  std::array<std::string, 4> test_2;

  test.fill("filled");
  test_2.fill("filled");

  ASSERT_EQ(test.size(), test_2.size());
  for (size_t i = 0; i < test.size(); ++i) ASSERT_EQ(test[i], test_2[i]);
}

TEST(ArrayTest, Swap_1) {
  s21::array<std::string, 4> test{"ff", "ff", "ff"};
  std::array<std::string, 4> test_std{"ff", "ff", "ff"};
  s21::array<std::string, 4> test_2{"aa", "aa", "aa"};
  std::array<std::string, 4> test_2_std{"aa", "aa", "aa"};

  test.swap(test_2);
  test_std.swap(test_2_std);

  ASSERT_EQ(test.size(), test_2.size());
  ASSERT_EQ(test_std.size(), test_2_std.size());
  for (size_t i = 0; i < test.size(); ++i) {
    ASSERT_EQ(test[i], test_std[i]);
    ASSERT_EQ(test_2[i], test_2_std[i]);
  }
}

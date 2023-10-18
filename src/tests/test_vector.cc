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
    EXPECT_EQ(err.what(), std::string("at(): Position is out of range"));
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

// //  Uncomment to see clear() calls destructor
// TEST(VectorTest, Clear_2) {
//   s21::vector<ClassWithPrintableDestructor> test(5);
//   std::vector<ClassWithPrintableDestructor> test_2(5);
//   test.clear();
//   test_2.clear();
//   std::cout << "TTTTTTTTTTTTTTTT\n";
//   ASSERT_EQ(test.size(), test_2.size());
//   ASSERT_EQ(test.capacity(), test_2.capacity());
// }

// TEST(VectorTest, Destructor_1) {
//   s21::vector<ClassWithPrintableDestructor> test(5);
//   std::cout << "TTTTTTTTTTTTTTTT\n";
// }

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

TEST(VectorTest, Reserve_2) {
  s21::vector<std::string> test(5);
  auto addr_test_1 = std::addressof(*test.data());
  auto tmp = test[test.size() - 1];

  test.reserve(3);
  auto addr_test_2 = std::addressof(*test.data());

  ASSERT_EQ(addr_test_1, addr_test_2);

  test.reserve(55);
  auto addr_test_3 = std::addressof(*test.data());

  ASSERT_NE(addr_test_2, addr_test_3);
  ASSERT_EQ(test[test.size() - 1], tmp);
}

TEST(VectorTest, Shrink_to_fit_1) {
  s21::vector<std::vector<std::string>> test(5);
  std::vector<std::vector<std::string>> test_2(5);

  test.reserve(61);
  test_2.reserve(61);

  ASSERT_EQ(test.size(), test_2.size());
  ASSERT_EQ(test.capacity(), test_2.capacity());

  test.shrink_to_fit();
  test_2.shrink_to_fit();

  ASSERT_EQ(test.size(), test_2.size());
  ASSERT_EQ(test.capacity(), test_2.capacity());
}

TEST(VectorTest, Shrink_to_fit_2) {
  s21::vector<std::vector<std::string>> test(5);
  std::vector<std::vector<std::string>> test_2(5);

  test.shrink_to_fit();
  test_2.shrink_to_fit();

  ASSERT_EQ(test.size(), test_2.size());
  ASSERT_EQ(test.capacity(), test_2.capacity());
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
  ASSERT_EQ(test[0], "second");
}

TEST(VectorTest, Insert_1) {
  s21::vector<int> test = {1, 6, 4, 9, 7};
  std::vector<int> test_2 = {1, 6, 4, 9, 7};
  auto iter = test.begin();
  auto iter_2 = test_2.begin();
  iter++;
  iter_2++;

  test.insert(iter, 9999);
  test_2.insert(iter_2, 9999);

  ASSERT_EQ(test.size(), test_2.size());
  ASSERT_EQ(test.capacity(), test_2.capacity());

  for (s21::vector<int>::size_type i = 0; i < test.size(); ++i)
    ASSERT_EQ(test[i], test_2[i]);
}

TEST(VectorTest, Insert_2) {
  s21::vector<int> test = {1};
  std::vector<int> test_2 = {1};
  auto iter = test.begin();
  auto iter_2 = test_2.begin();
  iter++;
  iter_2++;

  test.insert(iter, 9999);
  test_2.insert(iter_2, 9999);

  ASSERT_EQ(test.size(), test_2.size());
  ASSERT_EQ(test.capacity(), test_2.capacity());

  for (s21::vector<int>::size_type i = 0; i < test.size(); ++i) {
    ASSERT_EQ(test[i], test_2[i]);
  }
}

TEST(VectorTest, Insert_3) {
  s21::vector<int> test = {1};
  std::vector<int> test_2 = {1};
  auto iter = test.begin();
  auto iter_2 = test_2.begin();

  test.insert(iter, 9999);
  test_2.insert(iter_2, 9999);

  ASSERT_EQ(test.size(), test_2.size());
  ASSERT_EQ(test.capacity(), test_2.capacity());

  for (s21::vector<int>::size_type i = 0; i < test.size(); ++i) {
    ASSERT_EQ(test[i], test_2[i]);
  }
}

TEST(VectorTest, Insert_4) {
  s21::vector<std::string> test = {"1"};
  std::vector<std::string> test_2 = {"1"};
  auto iter = test.end();
  auto iter_2 = test_2.end();

  test.insert(iter, "9999");
  test_2.insert(iter_2, "9999");
  test.insert(test.end(), "9999");
  test_2.insert(test_2.end(), "9999");
  test.insert(test.end(), "9999");
  test_2.insert(test_2.end(), "9999");
  test.insert(test.end(), "9999");
  test_2.insert(test_2.end(), "9999");

  ASSERT_EQ(test.size(), test_2.size());
  ASSERT_EQ(test.capacity(), test_2.capacity());

  for (s21::vector<std::string>::size_type i = 0; i < test.size(); ++i) {
    ASSERT_EQ(test[i], test_2[i]);
  }
}

TEST(VectorTest, Insert_5) {
  s21::vector<int> test = {1};
  auto iter = test.begin();
  iter = iter + 2;

  EXPECT_ANY_THROW(test.insert(iter, 9999));
}

TEST(VectorTest, Erase_1) {
  s21::vector<int> test = {11, 22, 33, 44};
  std::vector<int> test_2 = {11, 22, 33, 44};
  auto iter = test.begin();
  auto iter_2 = test_2.begin();

  test.erase(iter);
  test_2.erase(iter_2);

  ASSERT_EQ(test.size(), test_2.size());
  ASSERT_EQ(test.capacity(), test_2.capacity());

  for (s21::vector<int>::size_type i = 0; i < test.size(); ++i) {
    ASSERT_EQ(test[i], test_2[i]);
  }
}

TEST(VectorTest, Erase_2) {
  s21::vector<int> test = {1};
  auto iter = test.begin();
  iter = iter + 2;

  EXPECT_ANY_THROW(test.erase(iter));
}

TEST(VectorTest, Erase_3) {
  s21::vector<int> test = {11, 22, 33, 44, 1111111, 11111111, 11111111};
  std::vector<int> test_2 = {11, 22, 33, 44, 1111111, 11111111, 11111111};
  auto iter = test.begin();
  auto iter_2 = test_2.begin();
  iter = iter + 3;
  iter_2 = iter_2 + 3;

  test.erase(iter);
  test_2.erase(iter_2);

  ASSERT_EQ(test.size(), test_2.size());
  ASSERT_EQ(test.capacity(), test_2.capacity());

  for (s21::vector<int>::size_type i = 0; i < test.size(); ++i) {
    ASSERT_EQ(test[i], test_2[i]);
  }
}

TEST(VectorTest, PushBack_1) {
  s21::vector<int> test = {1};
  std::vector<int> test_2 = {1};

  test.push_back(9999);
  test_2.push_back(9999);
  test.push_back(8888);
  test_2.push_back(8888);

  ASSERT_EQ(test.size(), test_2.size());
  ASSERT_EQ(test.capacity(), test_2.capacity());

  for (s21::vector<int>::size_type i = 0; i < test.size(); ++i) {
    ASSERT_EQ(test[i], test_2[i]);
  }
}

TEST(VectorTest, PushBack_2) {
  s21::vector<std::string> test;
  std::vector<std::string> test_2;

  test.push_back("9999");
  test_2.push_back("9999");
  test.push_back("9999");
  test_2.push_back("9999");
  test.push_back("9999");
  test_2.push_back("9999");
  test.push_back("9999");
  test_2.push_back("9999");
  test.push_back("9999");
  test_2.push_back("9999");
  test.push_back("9999");
  test_2.push_back("9999");
  test.push_back("9999");
  test_2.push_back("9999");
  test.push_back("9999");
  test_2.push_back("9999");
  test.push_back("9999");
  test_2.push_back("9999");
  test.push_back("9999");
  test_2.push_back("9999");
  test.push_back("9999");
  test_2.push_back("9999");

  ASSERT_EQ(test.size(), test_2.size());
  ASSERT_EQ(test.capacity(), test_2.capacity());

  for (s21::vector<std::string>::size_type i = 0; i < test.size(); ++i) {
    ASSERT_EQ(test[i], test_2[i]);
  }
}

TEST(VectorTest, PopBack_1) {
  s21::vector<int> test = {11, 22, 33, 44, 1111111, 11111111, 11111111};
  std::vector<int> test_2 = {11, 22, 33, 44, 1111111, 11111111, 11111111};

  test.pop_back();
  test_2.pop_back();
  test.pop_back();
  test_2.pop_back();
  test.pop_back();
  test_2.pop_back();

  ASSERT_EQ(test.size(), test_2.size());
  ASSERT_EQ(test.capacity(), test_2.capacity());

  for (s21::vector<int>::size_type i = 0; i < test.size(); ++i) {
    ASSERT_EQ(test[i], test_2[i]);
  }
}

TEST(VectorTest, PopBack_2) {
  s21::vector<int> test = {};

  EXPECT_ANY_THROW(test.pop_back());
}

TEST(VectorTest, PushPopBack_1) {
  s21::vector<int> test = {11, 22, 33, 44, 1111111, 11111111, 11111111};
  std::vector<int> test_2 = {11, 22, 33, 44, 1111111, 11111111, 11111111};

  test.pop_back();
  test_2.pop_back();
  test.pop_back();
  test_2.pop_back();
  test.pop_back();
  test_2.pop_back();
  test.push_back(9999);
  test_2.push_back(9999);
  test.push_back(8888);
  test_2.push_back(8888);

  ASSERT_EQ(test.size(), test_2.size());
  ASSERT_EQ(test.capacity(), test_2.capacity());

  for (s21::vector<int>::size_type i = 0; i < test.size(); ++i) {
    ASSERT_EQ(test[i], test_2[i]);
  }
}

TEST(VectorTest, CopyOperator_1) {
  s21::vector<int> test{11, 22, 33, 44, 1111111, 11111111, 11111111};
  s21::vector<int> test_2;

  test_2 = test;

  ASSERT_EQ(test.size(), test_2.size());
  ASSERT_EQ(test_2[6], 11111111);
}

TEST(VectorTest, Empty_1) {
  s21::vector<std::string> test;

  ASSERT_EQ(test.empty(), true);

  test.push_back("pushed");

  ASSERT_EQ(test.empty(), false);
  ASSERT_EQ(test[0], "pushed");
}

TEST(VectorTest, Reserve_EXCEPTION_SIZE) {
  s21::vector<std::string> test;

  EXPECT_ANY_THROW(test.reserve(18446744073709551615UL));
}

TEST(VectorTest, InsertMany_1) {
  s21::vector<int> test = {11, 22, 33, 44, 1111111, 11111111, 11111111};

  test.insert_many(test.cbegin(), 13, 1313, 131313, 13131313);

  ASSERT_EQ(test.size(), 11);
  ASSERT_EQ(test[4], 11);
}

TEST(VectorTest, InsertMany_3) {
  s21::vector<int> test = {11, 22, 33, 44, 55555, 66666, 77777};

  test.insert_many(test.cbegin());

  ASSERT_EQ(test.size(), 7);
  ASSERT_EQ(test[6], 77777);
}

TEST(VectorTest, InsertManyBack_1) {
  s21::vector<int> test = {11, 22, 33, 44, 1111111, 11111111, 11111111};

  test.insert_many_back(13, 1313, 131313, 13131313);

  ASSERT_EQ(test.size(), 11);
  ASSERT_EQ(test[9], 131313);
}

TEST(VectorTest, InsertManyBack_2) {
  s21::vector<int> test = {11, 22, 33, 44, 1111111, 11111111, 11111111};

  test.insert_many_back();

  ASSERT_EQ(test.size(), 7);
  ASSERT_EQ(test[6], 11111111);
}

TEST(VectorTest, Cbegin_Cend_1) {
  const s21::vector<std::string> test = {"11", "22", "33", "44",
                                         "55", "66", "77"};
  const std::vector<std::string> test_2 = {"11", "22", "33", "44",
                                           "55", "66", "77"};

  ASSERT_EQ(test.cend() - test.cend(), 0);
  ASSERT_EQ(*test.cbegin(), *test_2.cbegin());
  ASSERT_TRUE(test.cbegin() == test.cbegin());
  ASSERT_FALSE(test.cbegin() != test.cbegin());
}

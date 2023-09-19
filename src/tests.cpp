#include "s21_list.hpp"
#include "s21_test_obj.hpp"
//#include "s21_node.hpp"
#include <gtest/gtest.h>
#include <iostream> 


using namespace s21;

int main(int argc, char **argv) {

  //   test_obj a;
  //   test_obj b;
  //   test_obj c;
  //   auto g = {a,b,c};

  //   std::cout<<&a<<"\n";
  //   std::cout<<&b<<"\n";
  //   std::cout<<&c<<"\n";

  //   // test_obj& r = a;
  //   // std::cout<<&r<<"\n";

  // for (auto i : g) {
  //           std::cout<<&i<<"\n";
  //          //test_obj& r = a;
  //       }


  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(s21_list_test, construct_list_size_with_test_obj) {
    list<test_obj> l(5);
    EXPECT_EQ(l.back().id, 4);
    EXPECT_EQ(l.front().id, 0);
}

// TEST(s21_list_test, construct_initializer_list) {
//     test_obj a;
//     test_obj b;
//     test_obj c;
//     list<test_obj> l{a,b,c};
//     EXPECT_EQ(l.back().id, c.id);
//     EXPECT_EQ(l.front().id, a.id);
// }

// TEST(s21_list_test, push_back) {
//     list<int> l;
//     int a = 1;
//     int b = 2;
//     int c = 3;
//     l.push_back(a);
//     EXPECT_EQ(l.front(), a);
//     EXPECT_EQ(l.back(), a);
//     l.push_back(b);
//     EXPECT_EQ(l.back(), b);
//     EXPECT_EQ(l.front(), a);
//     l.push_back(c);
//     EXPECT_EQ(l.back(), c);
//     EXPECT_EQ(l.front(), a);
// }

// TEST(s21_list_test, push_front) {
//     list<int> l;
//     int a = 1;
//     int b = 2;
//     int c = 3;
//     l.push_back(a);
//     EXPECT_EQ(l.front(), a);
//     EXPECT_EQ(l.back(), a);
//     l.push_back(b);
//     EXPECT_EQ(l.back(), b);
//     EXPECT_EQ(l.front(), a);
//     l.push_back(c);
//     EXPECT_EQ(l.back(), c);
//     EXPECT_EQ(l.front(), a);
// }
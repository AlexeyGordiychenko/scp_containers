#include "s21_list.hpp"
#include "s21_test_obj.hpp"
//#include "s21_node.hpp"
#include <gtest/gtest.h>
#include <iostream> 
//std::cout<<&r<<"\n";


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

TEST(s21_list_test, insert) {
    test_obj arr[5];
    list<test_obj> list_a{arr[1],arr[2],arr[3]};
    EXPECT_EQ(list_a.back().id, arr[3].id);
    EXPECT_EQ(list_a.front().id, arr[1].id);
    EXPECT_EQ(list_a.size(), 3);
    test_obj &d = arr[0];
    list_a.insert(list_a.begin(), d);
    EXPECT_EQ(list_a.front().id, arr[0].id);
    EXPECT_EQ(list_a.size(), 4);
    test_obj &e = arr[4];
    list_a.insert(list_a.end(), arr[4]);
    EXPECT_EQ(list_a.back().id, arr[4].id);
    EXPECT_EQ(list_a.size(), 5);
    int c = arr[0].id;
    for(auto i : list_a)
        EXPECT_EQ(i.id, c++);
}

TEST(s21_list_test, iterator) {
    test_obj a;
    test_obj b;
    test_obj c;
    list<test_obj> list_a{a,b,c};
    EXPECT_EQ(list_a.back().id, c.id);
    EXPECT_EQ(list_a.front().id, a.id);
    EXPECT_EQ((*(list_a.begin())).id, a.id);
    EXPECT_EQ((*(++list_a.begin())).id, b.id);
    EXPECT_EQ((*(--list_a.end())).id, c.id);
}

TEST(s21_list_test, list_clear) {
    test_obj a;
    test_obj b;
    test_obj c;
    list<test_obj> list_a{a,b,c};
    EXPECT_EQ(list_a.size(), 3);
    list_a.clear();
    EXPECT_EQ(list_a.size(), 0);
}

// TEST(s21_list_test, construct_list_size_with_test_obj) {
//     list<test_obj> l(5);
//     EXPECT_EQ(l.back().id, 4);
//     EXPECT_EQ(l.front().id, 0);
// }

TEST(s21_list_test, operator_assign) {
    test_obj a;
    test_obj b;
    test_obj c;
    list<test_obj> list_a{a,b,c};
    EXPECT_EQ(list_a.size(), 3);
    EXPECT_EQ(list_a.back().id, c.id);
    EXPECT_EQ(list_a.front().id, a.id);
    test_obj d;
    test_obj e;
    test_obj f;
    list_a = list<test_obj>{d, e, f};
     EXPECT_EQ(list_a.size(), 3);
    EXPECT_EQ(list_a.back().id, f.id);
    EXPECT_EQ(list_a.front().id, d.id);
}

TEST(s21_list_test, copy_constructor) {
    test_obj a;
    test_obj b;
    test_obj c;
    list<test_obj> list_a{list<test_obj>{a,b,c}};
    EXPECT_EQ(list_a.back().id, c.id);
    EXPECT_EQ(list_a.front().id, a.id);
    EXPECT_EQ(list_a.size(), 3);
}

TEST(s21_list_test, moved_constructor) {
    test_obj a;
    test_obj b;
    test_obj c;
    list<test_obj> list_a{list<test_obj>{a,b,c}};
    EXPECT_EQ(list_a.back().id, c.id);
    EXPECT_EQ(list_a.front().id, a.id);
    EXPECT_EQ(list_a.size(), 3);
}

TEST(s21_list_test, construct_initializer_list) {
    test_obj a;
    test_obj b;
    test_obj c;
    list<test_obj> l{a,b,c};
    EXPECT_EQ(l.back().id, c.id);
    EXPECT_EQ(l.front().id, a.id);
    EXPECT_EQ(l.size(), 3);
}

TEST(s21_list_test, push_back) {
    list<int> l;
    int a = 1;
    int b = 2;
    int c = 3;
    l.push_back(a);
    EXPECT_EQ(l.front(), a);
    EXPECT_EQ(l.back(), a);
    EXPECT_EQ(l.size(), 1);
    l.push_back(b);
    EXPECT_EQ(l.back(), b);
    EXPECT_EQ(l.front(), a);
    EXPECT_EQ(l.size(), 2);
    l.push_back(c);
    EXPECT_EQ(l.back(), c);
    EXPECT_EQ(l.front(), a);
    EXPECT_EQ(l.size(), 3);
}

TEST(s21_list_test, push_front) {
    list<int> l;
    int a = 1;
    int b = 2;
    int c = 3;
    l.push_back(a);
    EXPECT_EQ(l.front(), a);
    EXPECT_EQ(l.back(), a);
    EXPECT_EQ(l.size(), 1);
    l.push_back(b);
    EXPECT_EQ(l.back(), b);
    EXPECT_EQ(l.front(), a);
    EXPECT_EQ(l.size(), 2);
    l.push_back(c);
    EXPECT_EQ(l.back(), c);
    EXPECT_EQ(l.front(), a);
    EXPECT_EQ(l.size(), 3);
}
#include "s21_list.hpp"
#include "s21_test_obj.hpp"
#include <gtest/gtest.h>
#include <iostream> 
#include <utility>

using namespace s21;

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(s21_list_test, copy_constructor) {
    test_obj a;
    test_obj b;
    test_obj c;
    list<test_obj> list_a{a,b,c};
    list<test_obj> list_b(list_a);
    EXPECT_EQ(list_b.back().id, c.id);
    EXPECT_EQ(list_b.front().id, a.id);
    EXPECT_EQ(list_b.size(), 3);
}

TEST(s21_list_test, operator_copy_assign) {
    test_obj a;
    test_obj b;
    test_obj c;
    list<test_obj> list_a{a,b,c};
    test_obj d;
    test_obj e;
    test_obj f;
    list<test_obj> list_b{d,e,f};
    list_b = list_a;
    EXPECT_EQ(list_b.back().id, c.id);
    EXPECT_EQ(list_b.front().id, a.id);
    EXPECT_EQ(list_b.size(), 3);
}
#include "s21_stack.hpp"
#include "s21_test_obj.hpp"
//#include "s21_node.hpp"
#include <gtest/gtest.h>
#include <iostream> 
//std::cout<<&r<<"\n";


using namespace s21;

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(s21_stack_test, constr) {
    test_obj arr[6];
    stack<test_obj, list<test_obj>> stack_a;
    EXPECT_EQ(stack_a.size(), 0);
    EXPECT_EQ(stack_a.empty(), true);
    stack<test_obj, list<test_obj>> stack_b{arr[0], arr[1], arr[2]};
    EXPECT_EQ(stack_b.top().id, arr[2].id);
    EXPECT_EQ(stack_b.size(), 3);
    EXPECT_EQ(stack_b.empty(), false);
    stack<test_obj, list<test_obj>> stack_c(stack<test_obj, list<test_obj>>{arr[0], arr[1], arr[2]});
    EXPECT_EQ(stack_c.top().id, arr[2].id);
    EXPECT_EQ(stack_c.size(), 3);
    EXPECT_EQ(stack_c.empty(), false);
    stack<test_obj, list<test_obj>> stack_d{std::move(stack<test_obj, list<test_obj>>{arr[0], arr[1], arr[2]})};
    EXPECT_EQ(stack_d.top().id, arr[2].id);
    EXPECT_EQ(stack_d.size(), 3);
    EXPECT_EQ(stack_d.empty(), false);
    stack<test_obj, list<test_obj>> stack_e{arr[3], arr[4], arr[5]};
    stack<test_obj, list<test_obj>> stack_f{arr[0], arr[1], arr[2]};
    stack_f = std::move(stack<test_obj, list<test_obj>>{arr[3], arr[4], arr[5]});
    EXPECT_EQ(stack_e.top().id, arr[5].id);
    EXPECT_EQ(stack_e.size(), 3);
    EXPECT_EQ(stack_e.empty(), false);
    stack_f = stack<test_obj, list<test_obj>>{arr[3], arr[4], arr[5]};
    EXPECT_EQ(stack_e.top().id, arr[5].id);
    EXPECT_EQ(stack_e.size(), 3);
    EXPECT_EQ(stack_e.empty(), false);
}

TEST(s21_stack_test, push_pop) {
    stack<test_obj, list<test_obj>> stack_a;
    EXPECT_EQ(stack_a.size(), 0);
    EXPECT_EQ(stack_a.empty(), true);
    test_obj arr[3];
    stack_a.push(arr[0]);
    EXPECT_EQ(stack_a.top().id, arr[0].id);
    EXPECT_EQ(stack_a.size(), 1);
    stack_a.push(arr[1]);
    EXPECT_EQ(stack_a.top().id, arr[1].id);
    EXPECT_EQ(stack_a.size(), 2);
    stack_a.push(arr[2]);
    EXPECT_EQ(stack_a.top().id, arr[2].id);
    EXPECT_EQ(stack_a.size(), 3);
    stack_a.pop();
    EXPECT_EQ(stack_a.top().id, arr[1].id);
    EXPECT_EQ(stack_a.size(), 2);
     stack_a.pop();
    EXPECT_EQ(stack_a.top().id, arr[0].id);
    EXPECT_EQ(stack_a.size(), 1);
     stack_a.pop();
    EXPECT_EQ(stack_a.size(), 0);  
}

TEST(s21_stack_test, swap) {
    test_obj arr[7];
    stack<test_obj, list<test_obj>> stack_a{arr[0], arr[1], arr[2]};
    EXPECT_EQ(stack_a.top().id, arr[2].id);
    EXPECT_EQ(stack_a.size(), 3);
    stack<test_obj, list<test_obj>> stack_b{arr[3], arr[4], arr[5], arr[6]};
    EXPECT_EQ(stack_b.top().id, arr[6].id);
    EXPECT_EQ(stack_b.size(), 4);
    stack_a.swap(stack_b);
    EXPECT_EQ(stack_a.top().id, arr[6].id);
    EXPECT_EQ(stack_a.size(), 4);
    EXPECT_EQ(stack_b.top().id, arr[2].id);
    EXPECT_EQ(stack_b.size(), 3);
}


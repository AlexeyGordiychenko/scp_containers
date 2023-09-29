#include "s21_queue.hpp"
#include "s21_test_obj.hpp"
#include <gtest/gtest.h>
#include <iostream> 
#include <utility>

using namespace s21;

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(s21_queue_test, constr) {
    test_obj arr[3];
    queue<test_obj, list<test_obj>> queue_a;
    EXPECT_EQ(queue_a.size(), 0);
    EXPECT_EQ(queue_a.empty(), true);
    queue<test_obj, list<test_obj>> queue_b{arr[0], arr[1], arr[2]};
    EXPECT_EQ(queue_b.back().id, arr[2].id);
    EXPECT_EQ(queue_b.front().id, arr[0].id);
    EXPECT_EQ(queue_b.size(), 3);
    EXPECT_EQ(queue_b.empty(), false);
    queue<test_obj, list<test_obj>> queue_c = queue<test_obj, list<test_obj>>{arr[0], arr[1], arr[2]};
    EXPECT_EQ(queue_c.back().id, arr[2].id);
    EXPECT_EQ(queue_c.front().id, arr[0].id);
    EXPECT_EQ(queue_c.size(), 3);
    queue<test_obj, list<test_obj>> queue_d{std::move(queue<test_obj, list<test_obj>>{arr[0], arr[1], arr[2]})};
    EXPECT_EQ(queue_d.back().id, arr[2].id);
    EXPECT_EQ(queue_d.front().id, arr[0].id);
    EXPECT_EQ(queue_d.size(), 3);
    queue<test_obj, list<test_obj>> queue_f{arr[0], arr[1], arr[2]};
    queue_f = queue<test_obj, list<test_obj>>{arr[0], arr[1], arr[2]};
    EXPECT_EQ(queue_f.back().id, arr[2].id);
    EXPECT_EQ(queue_f.front().id, arr[0].id);
    EXPECT_EQ(queue_f.size(), 3);
}

TEST(s21_queue_test, push_pop) {
    queue<test_obj, list<test_obj>> queue_a;
    EXPECT_EQ(queue_a.size(), 0);
    EXPECT_EQ(queue_a.empty(), true);
    test_obj arr[3];
    queue_a.push(arr[0]);
    EXPECT_EQ(queue_a.back().id, arr[0].id);
    EXPECT_EQ(queue_a.front().id, arr[0].id);
    EXPECT_EQ(queue_a.size(), 1);
    queue_a.push(arr[1]);
    EXPECT_EQ(queue_a.back().id, arr[1].id);
    EXPECT_EQ(queue_a.front().id, arr[0].id);
    EXPECT_EQ(queue_a.size(), 2);
    queue_a.push(arr[2]);
    EXPECT_EQ(queue_a.back().id, arr[2].id);
    EXPECT_EQ(queue_a.front().id, arr[0].id);
    EXPECT_EQ(queue_a.size(), 3);
    queue_a.pop();
    EXPECT_EQ(queue_a.back().id, arr[2].id);
    EXPECT_EQ(queue_a.front().id, arr[1].id);
    EXPECT_EQ(queue_a.size(), 2);
     queue_a.pop();
    EXPECT_EQ(queue_a.back().id, arr[2].id);
    EXPECT_EQ(queue_a.front().id, arr[2].id);
    EXPECT_EQ(queue_a.size(), 1);
     queue_a.pop();
    EXPECT_EQ(queue_a.size(), 0);  
}

TEST(s21_queue_test, swap) {
    test_obj arr[7];
    queue<test_obj, list<test_obj>> queue_a{arr[0], arr[1], arr[2]};
    EXPECT_EQ(queue_a.back().id, arr[2].id);
    EXPECT_EQ(queue_a.front().id, arr[0].id);
    EXPECT_EQ(queue_a.size(), 3);
    queue<test_obj, list<test_obj>> queue_b{arr[3], arr[4], arr[5], arr[6]};
    EXPECT_EQ(queue_b.back().id, arr[6].id);
    EXPECT_EQ(queue_b.front().id, arr[3].id);
    EXPECT_EQ(queue_b.size(), 4);
    queue_a.swap(queue_b);
    EXPECT_EQ(queue_a.back().id, arr[6].id);
    EXPECT_EQ(queue_a.front().id, arr[3].id);
    EXPECT_EQ(queue_a.size(), 4);
    EXPECT_EQ(queue_b.back().id, arr[2].id);
    EXPECT_EQ(queue_b.front().id, arr[0].id);
    EXPECT_EQ(queue_b.size(), 3);
}


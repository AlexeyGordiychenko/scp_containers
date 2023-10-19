#include "test.h"

TEST(StackTest, constr) {
  test_obj arr[6];

  // default constructor
  s21::stack<test_obj, s21::list<test_obj>> stack_a;
  EXPECT_EQ(stack_a.size(), 0);
  EXPECT_EQ(stack_a.empty(), true);

  // initializer list constructor
  s21::stack<test_obj, s21::list<test_obj>> stack_b{arr[0], arr[1], arr[2]};
  EXPECT_EQ(stack_b.top().id, arr[2].id);
  EXPECT_EQ(stack_b.size(), 3);
  EXPECT_EQ(stack_b.empty(), false);

  // copy constructor
  s21::stack<test_obj, s21::list<test_obj>> stack_g{arr[0], arr[1], arr[2]};
  s21::stack<test_obj, s21::list<test_obj>> stack_c(stack_g);
  EXPECT_EQ(stack_c.top().id, arr[2].id);
  EXPECT_EQ(stack_c.size(), 3);
  EXPECT_EQ(stack_c.empty(), false);

  // move constructor
  s21::stack<test_obj, s21::list<test_obj>> stack_d{std::move(
      s21::stack<test_obj, s21::list<test_obj>>{arr[0], arr[1], arr[2]})};
  EXPECT_EQ(stack_d.top().id, arr[2].id);
  EXPECT_EQ(stack_d.size(), 3);
  EXPECT_EQ(stack_d.empty(), false);

  // move assign operator
  s21::stack<test_obj, s21::list<test_obj>> stack_e{arr[3], arr[4], arr[5]};
  s21::stack<test_obj, s21::list<test_obj>> stack_f{arr[0], arr[1], arr[2]};
  stack_f = std::move(
      s21::stack<test_obj, s21::list<test_obj>>{arr[3], arr[4], arr[5]});
  EXPECT_EQ(stack_f.top().id, arr[5].id);
  EXPECT_EQ(stack_f.size(), 3);
  EXPECT_EQ(stack_f.empty(), false);

  // copy assign operator
  stack_f = stack_g;
  EXPECT_EQ(stack_f.top().id, arr[2].id);
  EXPECT_EQ(stack_f.size(), 3);
  EXPECT_EQ(stack_f.empty(), false);
}

TEST(StackTest, push_pop) {
  s21::stack<test_obj, s21::list<test_obj>> stack_a;
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

TEST(StackTest, swap) {
  test_obj arr[7];
  s21::stack<test_obj, s21::list<test_obj>> stack_a{arr[0], arr[1], arr[2]};
  EXPECT_EQ(stack_a.top().id, arr[2].id);
  EXPECT_EQ(stack_a.size(), 3);
  s21::stack<test_obj, s21::list<test_obj>> stack_b{arr[3], arr[4], arr[5],
                                                    arr[6]};
  EXPECT_EQ(stack_b.top().id, arr[6].id);
  EXPECT_EQ(stack_b.size(), 4);
  stack_a.swap(stack_b);
  EXPECT_EQ(stack_a.top().id, arr[6].id);
  EXPECT_EQ(stack_a.size(), 4);
  EXPECT_EQ(stack_b.top().id, arr[2].id);
  EXPECT_EQ(stack_b.size(), 3);
}

TEST(StackTest, insert_many_front) {
  s21::stack<test_obj, s21::list<test_obj>> s;
  test_obj arr[6];
  s.insert_many_front(arr[0], arr[1], arr[2]);
  EXPECT_EQ(s.top(), arr[2]);
  EXPECT_EQ(s.size(), 3);
  s.insert_many_front(arr[3], arr[4], arr[5]);
  EXPECT_EQ(s.top().id, arr[5].id);
  EXPECT_EQ(s.size(), 6);
  for (int i = 5; i >= 0; --i) {
    EXPECT_EQ(s.top().id, arr[i].id);
    s.pop();
  }
  EXPECT_EQ(s.size(), 0);
}

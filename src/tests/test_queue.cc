#include "test.h"

using namespace s21;

TEST(QueueTest, constr) {
  test_obj arr[3];

  //default constructor
  queue<test_obj, list<test_obj>> queue_a;
  EXPECT_EQ(queue_a.size(), 0);
  EXPECT_EQ(queue_a.empty(), true);

  //initializer list constructor
  queue<test_obj, list<test_obj>> queue_b{arr[0], arr[1], arr[2]};
  EXPECT_EQ(queue_b.back().id, arr[2].id);
  EXPECT_EQ(queue_b.front().id, arr[0].id);
  EXPECT_EQ(queue_b.size(), 3);
  EXPECT_EQ(queue_b.empty(), false);

  //copy constructor
  queue<test_obj, list<test_obj>> queue_c(queue_b);
  EXPECT_EQ(queue_c.back().id, arr[2].id);
  EXPECT_EQ(queue_c.front().id, arr[0].id);
  EXPECT_EQ(queue_c.size(), 3);

  //move constructor
  queue<test_obj, list<test_obj>> queue_d{
      std::move(queue<test_obj, list<test_obj>>{arr[0], arr[1], arr[2]})};
  EXPECT_EQ(queue_d.back().id, arr[2].id);
  EXPECT_EQ(queue_d.front().id, arr[0].id);
  EXPECT_EQ(queue_d.size(), 3);

  //copy assign operator
  queue<test_obj, list<test_obj>> queue_f{arr[0], arr[1], arr[2]};
  queue_f = queue_d;
  EXPECT_EQ(queue_f.back().id, arr[2].id);
  EXPECT_EQ(queue_f.front().id, arr[0].id);
  EXPECT_EQ(queue_f.size(), 3);

  //move assign operator
  queue_f = std::move(queue<test_obj, list<test_obj>>{arr[0], arr[1], arr[2]});
  EXPECT_EQ(queue_f.back().id, arr[2].id);
  EXPECT_EQ(queue_f.front().id, arr[0].id);
  EXPECT_EQ(queue_f.size(), 3);
}

TEST(QueueTest, push_pop) {
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

TEST(QueueTest, swap) {
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

TEST(QueueTest, insert_many_back) {
  queue<test_obj, list<test_obj>> q;
  test_obj arr[6];
  q.insert_many_back(arr[0], arr[1], arr[2]);
  EXPECT_EQ(q.front(), arr[0]);
  EXPECT_EQ(q.back(), arr[2]);
  EXPECT_EQ(q.size(), 3);
  q.insert_many_back(arr[3], arr[4], arr[5]);
  EXPECT_EQ(q.front(), arr[0]);
  EXPECT_EQ(q.back(), arr[5]);
  EXPECT_EQ(q.size(), 6);
  int size = q.size();
  for (int i = 0; i < size; ++i) {
    EXPECT_EQ(q.front(), arr[i]);
    q.pop();
  }
  EXPECT_EQ(q.size(), 0);
}

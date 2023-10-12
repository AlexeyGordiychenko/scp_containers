#include "test.h"

using namespace s21;

TEST(ListTest, construct_list_size_with_test_obj) {
  list<test_obj> l(5);
  EXPECT_EQ(l.back().id, 4);
  EXPECT_EQ(l.front().id, 0);
  EXPECT_EQ(l.max_size(), 384307168202282325);
  EXPECT_EQ(l.empty(), false);
}

TEST(ListTest, copy_constructor) {
  test_obj a;
  test_obj b;
  test_obj c;
  list<test_obj> list_a{a, b, c};
  list<test_obj> list_b(list_a);
  EXPECT_EQ(list_b.back().id, c.id);
  EXPECT_EQ(list_b.front().id, a.id);
  EXPECT_EQ(list_b.size(), 3);
}

TEST(ListTest, moved_constructor) {
  test_obj a;
  test_obj b;
  test_obj c;
  list<test_obj> list_a{std::move(list<test_obj>{a, b, c})};
  EXPECT_EQ(list_a.back().id, c.id);
  EXPECT_EQ(list_a.front().id, a.id);
  EXPECT_EQ(list_a.size(), 3);
}

TEST(ListTest, construct_initializer_list) {
  test_obj a;
  test_obj b;
  test_obj c;
  list<test_obj> l{a, b, c};
  EXPECT_EQ(l.back().id, c.id);
  EXPECT_EQ(l.front().id, a.id);
  EXPECT_EQ(l.size(), 3);
}

TEST(ListTest, operator_move_assign) {
  test_obj a;
  test_obj b;
  test_obj c;
  list<test_obj> list_a{a, b, c};
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

TEST(ListTest, operator_copy_assign) {
  test_obj a;
  test_obj b;
  test_obj c;
  list<test_obj> list_a{a, b, c};
  test_obj d;
  test_obj e;
  test_obj f;
  list<test_obj> list_b{d, e, f};
  list_b = list_a;
  EXPECT_EQ(list_b.back().id, c.id);
  EXPECT_EQ(list_b.front().id, a.id);
  EXPECT_EQ(list_b.size(), 3);
}

TEST(ListTest, sort) {
  list<int> list_a{1, 4, 3, 2, 5};
  EXPECT_EQ(list_a.size(), 5);
  list_a.sort();
  EXPECT_EQ(list_a.size(), 5);
  EXPECT_EQ(list_a.front(), 1);
  EXPECT_EQ(list_a.back(), 5);
  int c = 1;
  for (auto i : list_a) EXPECT_EQ(i, c++);
}

TEST(ListTest, merger) {
  list<int> list_a{1, 3, 5};
  list<int> list_b{2, 4};
  EXPECT_EQ(list_a.size(), 3);
  EXPECT_EQ(list_b.size(), 2);
  list_a.merge(list_b);
  EXPECT_EQ(list_a.size(), 5);
  EXPECT_EQ(list_a.front(), 1);
  EXPECT_EQ(list_a.back(), 5);
  int c = 1;
  for (auto i : list_a) EXPECT_EQ(i, c++);
  EXPECT_EQ(list_b.size(), 0);
}

TEST(ListTest, unique) {
  list<int> list_a{0, 0, 1, 1, 2, 3, 3};
  EXPECT_EQ(list_a.size(), 7);
  list_a.unique();
  EXPECT_EQ(list_a.size(), 4);
  int c = 0;
  for (auto i : list_a) EXPECT_EQ(i, c++);
}

TEST(ListTest, splice) {
  test_obj arr[7];
  list<test_obj> list_a{arr[0], arr[5], arr[6]};
  list<test_obj> list_b{arr[1], arr[2], arr[3], arr[4]};
  EXPECT_EQ(list_a.size(), 3);
  EXPECT_EQ(list_b.size(), 4);
  auto it = ++list_a.begin();
  list_a.splice(it, list_b);
  EXPECT_EQ(list_a.size(), 7);
  EXPECT_EQ(list_b.size(), 0);
  int c = arr[0].id;
  for (auto i : list_a) EXPECT_EQ(i.id, c++);
}

TEST(ListTest, reverse) {
  test_obj arr[7];
  list<test_obj> list_a{arr[0], arr[1], arr[2]};
  EXPECT_EQ(list_a.size(), 3);
  int c = arr[0].id;
  for (auto i : list_a) EXPECT_EQ(i.id, c++);
  list_a.reverse();
  EXPECT_EQ(list_a.size(), 3);
  c = arr[2].id;
  for (auto i : list_a) EXPECT_EQ(i.id, c--);
}

TEST(ListTest, erase) {
  test_obj arr[3];
  list<test_obj> list_a{arr[0], arr[2], arr[1]};
  auto it = ++list_a.begin();
  EXPECT_EQ(it->id, arr[2].id);
  EXPECT_EQ(list_a.size(), 3);
  list_a.erase(it);
  EXPECT_EQ(list_a.size(), 2);
  int c = arr[0].id;
  for (auto i : list_a) EXPECT_EQ(i.id, c++);
}

TEST(ListTest, swap) {
  test_obj arr[7];
  list<test_obj> list_a{arr[0], arr[1], arr[2]};
  list<test_obj> list_b{arr[3], arr[4], arr[5], arr[6]};
  list_a.swap(list_b);
  EXPECT_EQ(list_a.back().id, arr[6].id);
  EXPECT_EQ(list_a.front().id, arr[3].id);
  EXPECT_EQ(list_a.size(), 4);
  EXPECT_EQ(list_b.back().id, arr[2].id);
  EXPECT_EQ(list_b.front().id, arr[0].id);
  EXPECT_EQ(list_b.size(), 3);
}

TEST(ListTest, push_back) {
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

TEST(ListTest, push_front) {
  list<int> l;
  int a = 1;
  int b = 2;
  int c = 3;
  l.push_front(a);
  EXPECT_EQ(l.front(), a);
  EXPECT_EQ(l.back(), a);
  EXPECT_EQ(l.size(), 1);
  l.push_front(b);
  EXPECT_EQ(l.back(), a);
  EXPECT_EQ(l.front(), b);
  EXPECT_EQ(l.size(), 2);
  l.push_front(c);
  EXPECT_EQ(l.back(), a);
  EXPECT_EQ(l.front(), c);
  EXPECT_EQ(l.size(), 3);
}

TEST(ListTest, pop_back) {
  test_obj arr[5];
  list<test_obj> list_a{arr[1], arr[2], arr[3]};
  EXPECT_EQ(list_a.back().id, arr[3].id);
  EXPECT_EQ(list_a.front().id, arr[1].id);
  EXPECT_EQ(list_a.size(), 3);
  list_a.pop_back();
  EXPECT_EQ(list_a.front().id, arr[1].id);
  EXPECT_EQ(list_a.back().id, arr[2].id);
  EXPECT_EQ(list_a.size(), 2);
  int c = arr[1].id;
  for (auto i : list_a) EXPECT_EQ(i.id, c++);
}

TEST(ListTest, pop_front) {
  test_obj arr[5];
  list<test_obj> list_a{arr[1], arr[2], arr[3]};
  EXPECT_EQ(list_a.back().id, arr[3].id);
  EXPECT_EQ(list_a.front().id, arr[1].id);
  EXPECT_EQ(list_a.size(), 3);
  list_a.pop_front();
  EXPECT_EQ(list_a.front().id, arr[2].id);
  EXPECT_EQ(list_a.back().id, arr[3].id);
  EXPECT_EQ(list_a.size(), 2);
  int c = arr[2].id;
  for (auto i : list_a) EXPECT_EQ(i.id, c++);
}

TEST(ListTest, insert) {
  test_obj arr[5];
  list<test_obj> list_a{arr[1], arr[2], arr[3]};
  EXPECT_EQ(list_a.back().id, arr[3].id);
  EXPECT_EQ(list_a.front().id, arr[1].id);
  EXPECT_EQ(list_a.size(), 3);
  list_a.insert(list_a.begin(), arr[0]);
  EXPECT_EQ(list_a.front().id, arr[0].id);
  EXPECT_EQ(list_a.size(), 4);
  list_a.insert(list_a.end(), arr[4]);
  EXPECT_EQ(list_a.back().id, arr[4].id);
  EXPECT_EQ(list_a.size(), 5);
  int c = arr[0].id;
  for (auto i : list_a) EXPECT_EQ(i.id, c++);
}

TEST(ListTest, iterator) {
  test_obj a;
  test_obj b;
  test_obj c;
  list<test_obj> list_a{a, b, c};
  EXPECT_EQ(list_a.back().id, c.id);
  EXPECT_EQ(list_a.front().id, a.id);
  EXPECT_EQ((*(list_a.begin())).id, a.id);
  EXPECT_EQ((*(++list_a.begin())).id, b.id);
  EXPECT_EQ((*(--list_a.end())).id, c.id);
}

TEST(ListTest, list_clear) {
  test_obj a;
  test_obj b;
  test_obj c;
  list<test_obj> list_a{a, b, c};
  EXPECT_EQ(list_a.size(), 3);
  list_a.clear();
  EXPECT_EQ(list_a.size(), 0);
  int j = 0;
  for (auto i : list_a) j++;
  EXPECT_EQ(j, 0);
}

TEST(ListTest, insert_many) {
  test_obj arr[7];
  list<test_obj> list_a{arr[0], arr[5], arr[6]};
  EXPECT_EQ(list_a.back().id, arr[6].id);
  EXPECT_EQ(list_a.front().id, arr[0].id);
  EXPECT_EQ(list_a.size(), 3);
  auto it = ++list_a.begin();
  auto res_it = list_a.insert_many(it, arr[1], arr[2], arr[3], arr[4]);
  EXPECT_EQ(list_a.front().id, arr[0].id);
  EXPECT_EQ(list_a.back().id, arr[6].id);
  EXPECT_EQ(list_a.size(), 7);
  int c = arr[0].id;
  for (auto i : list_a) EXPECT_EQ(i.id, c++);
  EXPECT_EQ(++arr[6].id, c);
  EXPECT_EQ(arr[4].id, res_it->id);
}

TEST(ListTest, push_back_many) {
  list<test_obj> l;
  test_obj arr[6];
  l.insert_many_back(arr[0], arr[1], arr[2]);
  EXPECT_EQ(l.front(), arr[0]);
  EXPECT_EQ(l.back(), arr[2]);
  EXPECT_EQ(l.size(), 3);
  l.insert_many_back(arr[3], arr[4], arr[5]);
  EXPECT_EQ(l.front(), arr[0]);
  EXPECT_EQ(l.back(), arr[5]);
  EXPECT_EQ(l.size(), 6);
  int c = arr[0].id;
  for (auto i : l) EXPECT_EQ(i.id, c++);
}

TEST(ListTest, push_front_many) {
  list<test_obj> l;
  test_obj arr[6];
  l.insert_many_back(arr[3], arr[4], arr[5]);
  EXPECT_EQ(l.front(), arr[3]);
  EXPECT_EQ(l.back(), arr[5]);
  EXPECT_EQ(l.size(), 3);
  l.insert_many_front(arr[0], arr[1], arr[2]);
  EXPECT_EQ(l.front(), arr[0]);
  EXPECT_EQ(l.back(), arr[5]);
  EXPECT_EQ(l.size(), 6);
  int c = arr[0].id;
  for (auto i : l) EXPECT_EQ(i.id, c++);
}

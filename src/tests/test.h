#ifndef CPP2_S21_CONTAINERS_TESTS_TEST_H_
#define CPP2_S21_CONTAINERS_TESTS_TEST_H_

#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>

#include "../s21_containers/s21_containers.h"
#include "../s21_containersplus/s21_containersplus.h"
#include "gtest/gtest.h"

class ClassWithPrintableDestructor {
 public:
  ClassWithPrintableDestructor();
  ~ClassWithPrintableDestructor();

 private:
  int* a;
};

class ClassNoDefaultConstructor {
 public:
  ClassNoDefaultConstructor() = delete;
  ClassNoDefaultConstructor(int n);
  ~ClassNoDefaultConstructor();

 private:
  int a;
};

class test_obj {
 public:
  int id;
  bool operator==(test_obj other) const { return id == other.id; }
  test_obj(/* args */);
  ~test_obj();

 private:
  static inline int ID{};
};

class MapTest : public ::testing::Test {
 public:
  void SetUp(void) override {
    std::srand(69);

    for (int i = 0; i < 1000; ++i) {
      int key = rand();
      auto key_value = std::make_pair(key, std::to_string(key + i));
      s21_m_rnd.insert(key_value);
      std_m_rnd.insert(key_value);
    }

    std::array<int, 13> values = {60, 40, 90,  30,  50,  70, 130,
                                  10, 80, 110, 140, 100, 120};
    for (auto i : values) {
      auto key_value = std::make_pair(i, std::to_string(i));
      s21_m_static.insert(key_value);
      std_m_static.insert(key_value);
    }
  }

  template <typename Key, typename Value>
  bool MapsAreEqual(const s21::map<Key, Value>& lhs,
                    const s21::map<Key, Value>& rhs) {
    return lhs.empty() == rhs.empty() && lhs.size() == rhs.size() &&
           std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
  }
  template <typename Key, typename Value>
  bool MapsAreEqual(const s21::map<Key, Value>& lhs,
                    const std::map<Key, Value>& rhs) {
    return lhs.empty() == rhs.empty() && lhs.size() == rhs.size() &&
           std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
  }
  template <typename Key, typename Value>
  bool MapsAreEqual(const std::map<Key, Value>& lhs,
                    const s21::map<Key, Value>& rhs) {
    return lhs.empty() == rhs.empty() && lhs.size() == rhs.size() &&
           std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
  }

  template <typename Iterator1, typename Iterator2>
  void MoveForwardBackward(Iterator1& s21_it, Iterator2& std_it) {
    ++(++s21_it);
    ++(++std_it);
    EXPECT_EQ(*s21_it, *std_it);
    EXPECT_EQ(*++s21_it, *++std_it);
    EXPECT_EQ(*s21_it++, *std_it++);
    EXPECT_EQ(*s21_it, *std_it);
    EXPECT_EQ(*s21_it--, *std_it--);
    EXPECT_EQ(*s21_it, *std_it);
    EXPECT_EQ(*--s21_it, *--std_it);
    EXPECT_EQ(*s21_it, *std_it);
    --s21_it;
    --std_it;
    EXPECT_EQ(s21_it->second, std_it->second);
    EXPECT_EQ(s21_it++->first, std_it++->first);

    auto s21_it2 = s21_it++;
    auto std_it2 = std_it++;
    EXPECT_FALSE(s21_it2 == s21_it);
    EXPECT_FALSE(std_it2 == std_it);
    ++s21_it2;
    ++std_it2;
    EXPECT_TRUE(s21_it2 == s21_it);
    EXPECT_TRUE(std_it2 == std_it);
  }

  template <typename Iterator1, typename Iterator2>
  void MoveBackwardForward(Iterator1& s21_it, Iterator2& std_it) {
    --(--s21_it);
    --(--std_it);
    EXPECT_EQ(*s21_it, *std_it);
    EXPECT_EQ(*--s21_it, *--std_it);
    EXPECT_EQ(*s21_it--, *std_it--);
    EXPECT_EQ(*s21_it, *std_it);
    EXPECT_EQ(*s21_it++, *std_it++);
    EXPECT_EQ(*s21_it, *std_it);
    EXPECT_EQ(*++s21_it, *++std_it);
    EXPECT_EQ(*s21_it, *std_it);
    ++s21_it;
    ++std_it;
    EXPECT_EQ(s21_it->second, std_it->second);
    EXPECT_EQ(s21_it--->first, std_it--->first);

    auto s21_it2 = s21_it--;
    auto std_it2 = std_it--;
    EXPECT_FALSE(s21_it2 == s21_it);
    EXPECT_FALSE(std_it2 == std_it);
    --s21_it2;
    --std_it2;
    EXPECT_TRUE(s21_it2 == s21_it);
    EXPECT_TRUE(std_it2 == std_it);
  }

  s21::map<int, std::string> s21_m_rnd;
  std::map<int, std::string> std_m_rnd;

  s21::map<int, std::string> s21_m_static;
  std::map<int, std::string> std_m_static;

  double max_size_ratio = 1 + 1.0 / 3;
};

class MultisetTest : public ::testing::Test {
 public:
  void SetUp(void) override {
    std::srand(69);

    for (int i = 0; i < 1000; ++i) {
      int key = rand() % 100;
      s21_ms_rnd.insert(key);
      std_ms_rnd.insert(key);
    }

    std::array<int, 16> values = {60, 40, 90, 30,  40,  50,  70,  130,
                                  10, 80, 90, 110, 120, 140, 100, 120};
    for (auto i : values) {
      s21_ms_static.insert(i);
      std_ms_static.insert(i);
    }
  }

  template <typename Key>
  bool MultisetsAreEqual(const s21::multiset<Key>& lhs,
                         const s21::multiset<Key>& rhs) {
    return lhs.empty() == rhs.empty() && lhs.size() == rhs.size() &&
           std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
  }
  template <typename Key>
  bool MultisetsAreEqual(const s21::multiset<Key>& lhs,
                         const std::multiset<Key>& rhs) {
    return lhs.empty() == rhs.empty() && lhs.size() == rhs.size() &&
           std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
  }
  template <typename Key>
  bool MultisetsAreEqual(const std::multiset<Key>& lhs,
                         const s21::multiset<Key>& rhs) {
    return lhs.empty() == rhs.empty() && lhs.size() == rhs.size() &&
           std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
  }

  template <typename Iterator1, typename Iterator2>
  void MoveForwardBackward(Iterator1& s21_it, Iterator2& std_it) {
    ++(++s21_it);
    ++(++std_it);
    EXPECT_EQ(*s21_it, *std_it);
    EXPECT_EQ(*++s21_it, *++std_it);
    EXPECT_EQ(*s21_it++, *std_it++);
    EXPECT_EQ(*s21_it, *std_it);
    EXPECT_EQ(*s21_it--, *std_it--);
    EXPECT_EQ(*s21_it, *std_it);
    EXPECT_EQ(*--s21_it, *--std_it);
    EXPECT_EQ(*s21_it, *std_it);
    --s21_it;
    --std_it;
    EXPECT_EQ(*s21_it, *std_it);
    EXPECT_EQ(*s21_it++, *std_it++);

    auto s21_it2 = s21_it++;
    auto std_it2 = std_it++;
    EXPECT_FALSE(s21_it2 == s21_it);
    EXPECT_FALSE(std_it2 == std_it);
    ++s21_it2;
    ++std_it2;
    EXPECT_TRUE(s21_it2 == s21_it);
    EXPECT_TRUE(std_it2 == std_it);
  }

  template <typename Iterator1, typename Iterator2>
  void MoveBackwardForward(Iterator1& s21_it, Iterator2& std_it) {
    --(--s21_it);
    --(--std_it);
    EXPECT_EQ(*s21_it, *std_it);
    EXPECT_EQ(*--s21_it, *--std_it);
    EXPECT_EQ(*s21_it--, *std_it--);
    EXPECT_EQ(*s21_it, *std_it);
    EXPECT_EQ(*s21_it++, *std_it++);
    EXPECT_EQ(*s21_it, *std_it);
    EXPECT_EQ(*++s21_it, *++std_it);
    EXPECT_EQ(*s21_it, *std_it);
    ++s21_it;
    ++std_it;
    EXPECT_EQ(*s21_it, *std_it);
    EXPECT_EQ(*s21_it--, *std_it--);

    auto s21_it2 = s21_it--;
    auto std_it2 = std_it--;
    EXPECT_FALSE(s21_it2 == s21_it);
    EXPECT_FALSE(std_it2 == std_it);
    --s21_it2;
    --std_it2;
    EXPECT_TRUE(s21_it2 == s21_it);
    EXPECT_TRUE(std_it2 == std_it);
  }

  s21::multiset<int> s21_ms_rnd;
  std::multiset<int> std_ms_rnd;

  s21::multiset<int> s21_ms_static;
  std::multiset<int> std_ms_static;

  double max_size_ratio = 2.4;
};

class SetTest : public ::testing::Test {
 public:
  void SetUp(void) override {
    std::srand(69);

    for (int i = 0; i < 1000; ++i) {
      int key = rand();
      s21_s_rnd.insert(key);
      std_s_rnd.insert(key);
    }

    std::array<int, 13> values = {60, 40, 90,  30,  50,  70, 130,
                                  10, 80, 110, 140, 100, 120};
    for (auto i : values) {
      s21_s_static.insert(i);
      std_s_static.insert(i);
    }
  }

  template <typename Key>
  bool SetsAreEqual(const s21::set<Key>& lhs, const s21::set<Key>& rhs) {
    return lhs.empty() == rhs.empty() && lhs.size() == rhs.size() &&
           std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
  }
  template <typename Key>
  bool SetsAreEqual(const s21::set<Key>& lhs, const std::set<Key>& rhs) {
    return lhs.empty() == rhs.empty() && lhs.size() == rhs.size() &&
           std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
  }
  template <typename Key>
  bool SetsAreEqual(const std::set<Key>& lhs, const s21::set<Key>& rhs) {
    return lhs.empty() == rhs.empty() && lhs.size() == rhs.size() &&
           std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
  }

  template <typename Iterator1, typename Iterator2>
  void MoveForwardBackward(Iterator1& s21_it, Iterator2& std_it) {
    ++(++s21_it);
    ++(++std_it);
    EXPECT_EQ(*s21_it, *std_it);
    EXPECT_EQ(*++s21_it, *++std_it);
    EXPECT_EQ(*s21_it++, *std_it++);
    EXPECT_EQ(*s21_it, *std_it);
    EXPECT_EQ(*s21_it--, *std_it--);
    EXPECT_EQ(*s21_it, *std_it);
    EXPECT_EQ(*--s21_it, *--std_it);
    EXPECT_EQ(*s21_it, *std_it);
    --s21_it;
    --std_it;
    EXPECT_EQ(*s21_it, *std_it);
    EXPECT_EQ(*s21_it++, *std_it++);

    auto s21_it2 = s21_it++;
    auto std_it2 = std_it++;
    EXPECT_FALSE(s21_it2 == s21_it);
    EXPECT_FALSE(std_it2 == std_it);
    ++s21_it2;
    ++std_it2;
    EXPECT_TRUE(s21_it2 == s21_it);
    EXPECT_TRUE(std_it2 == std_it);
  }

  template <typename Iterator1, typename Iterator2>
  void MoveBackwardForward(Iterator1& s21_it, Iterator2& std_it) {
    --(--s21_it);
    --(--std_it);
    EXPECT_EQ(*s21_it, *std_it);
    EXPECT_EQ(*--s21_it, *--std_it);
    EXPECT_EQ(*s21_it--, *std_it--);
    EXPECT_EQ(*s21_it, *std_it);
    EXPECT_EQ(*s21_it++, *std_it++);
    EXPECT_EQ(*s21_it, *std_it);
    EXPECT_EQ(*++s21_it, *++std_it);
    EXPECT_EQ(*s21_it, *std_it);
    ++s21_it;
    ++std_it;
    EXPECT_EQ(*s21_it, *std_it);
    EXPECT_EQ(*s21_it--, *std_it--);

    auto s21_it2 = s21_it--;
    auto std_it2 = std_it--;
    EXPECT_FALSE(s21_it2 == s21_it);
    EXPECT_FALSE(std_it2 == std_it);
    --s21_it2;
    --std_it2;
    EXPECT_TRUE(s21_it2 == s21_it);
    EXPECT_TRUE(std_it2 == std_it);
  }

  s21::set<int> s21_s_rnd;
  std::set<int> std_s_rnd;

  s21::set<int> s21_s_static;
  std::set<int> std_s_static;

  double max_size_ratio = 2.4;
};

struct GetKeyMap {
  template <typename K, typename V>
  const K& operator()(const std::pair<K, V>& value) const {
    return value.first;
  }
};

template class s21::vector<std::string>;
template class s21::array<int, 2>;

#endif  // CPP2_S21_CONTAINERS_TESTS_TEST_H_

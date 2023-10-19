#ifndef CPP2_SCP_CONTAINERS_TESTS_TEST_H_
#define CPP2_SCP_CONTAINERS_TESTS_TEST_H_

#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>

#include "../scp_containers/scp_containers.h"
#include "../scp_containersplus/scp_containersplus.h"
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
      scp_m_rnd.insert(key_value);
      std_m_rnd.insert(key_value);
    }

    std::array<int, 13> values = {60, 40, 90,  30,  50,  70, 130,
                                  10, 80, 110, 140, 100, 120};
    for (auto i : values) {
      auto key_value = std::make_pair(i, std::to_string(i));
      scp_m_static.insert(key_value);
      std_m_static.insert(key_value);
    }
  }

  template <typename Key, typename Value>
  bool MapsAreEqual(const scp::map<Key, Value>& lhs,
                    const scp::map<Key, Value>& rhs) {
    return lhs.empty() == rhs.empty() && lhs.size() == rhs.size() &&
           std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
  }
  template <typename Key, typename Value>
  bool MapsAreEqual(const scp::map<Key, Value>& lhs,
                    const std::map<Key, Value>& rhs) {
    return lhs.empty() == rhs.empty() && lhs.size() == rhs.size() &&
           std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
  }
  template <typename Key, typename Value>
  bool MapsAreEqual(const std::map<Key, Value>& lhs,
                    const scp::map<Key, Value>& rhs) {
    return lhs.empty() == rhs.empty() && lhs.size() == rhs.size() &&
           std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
  }

  template <typename Iterator1, typename Iterator2>
  void MoveForwardBackward(Iterator1& scp_it, Iterator2& std_it) {
    ++(++scp_it);
    ++(++std_it);
    EXPECT_EQ(*scp_it, *std_it);
    EXPECT_EQ(*++scp_it, *++std_it);
    EXPECT_EQ(*scp_it++, *std_it++);
    EXPECT_EQ(*scp_it, *std_it);
    EXPECT_EQ(*scp_it--, *std_it--);
    EXPECT_EQ(*scp_it, *std_it);
    EXPECT_EQ(*--scp_it, *--std_it);
    EXPECT_EQ(*scp_it, *std_it);
    --scp_it;
    --std_it;
    EXPECT_EQ(scp_it->second, std_it->second);
    EXPECT_EQ(scp_it++->first, std_it++->first);

    auto scp_it2 = scp_it++;
    auto std_it2 = std_it++;
    EXPECT_FALSE(scp_it2 == scp_it);
    EXPECT_FALSE(std_it2 == std_it);
    ++scp_it2;
    ++std_it2;
    EXPECT_TRUE(scp_it2 == scp_it);
    EXPECT_TRUE(std_it2 == std_it);
  }

  template <typename Iterator1, typename Iterator2>
  void MoveBackwardForward(Iterator1& scp_it, Iterator2& std_it) {
    --(--scp_it);
    --(--std_it);
    EXPECT_EQ(*scp_it, *std_it);
    EXPECT_EQ(*--scp_it, *--std_it);
    EXPECT_EQ(*scp_it--, *std_it--);
    EXPECT_EQ(*scp_it, *std_it);
    EXPECT_EQ(*scp_it++, *std_it++);
    EXPECT_EQ(*scp_it, *std_it);
    EXPECT_EQ(*++scp_it, *++std_it);
    EXPECT_EQ(*scp_it, *std_it);
    ++scp_it;
    ++std_it;
    EXPECT_EQ(scp_it->second, std_it->second);
    EXPECT_EQ(scp_it--->first, std_it--->first);

    auto scp_it2 = scp_it--;
    auto std_it2 = std_it--;
    EXPECT_FALSE(scp_it2 == scp_it);
    EXPECT_FALSE(std_it2 == std_it);
    --scp_it2;
    --std_it2;
    EXPECT_TRUE(scp_it2 == scp_it);
    EXPECT_TRUE(std_it2 == std_it);
  }

  scp::map<int, std::string> scp_m_rnd;
  std::map<int, std::string> std_m_rnd;

  scp::map<int, std::string> scp_m_static;
  std::map<int, std::string> std_m_static;

  double max_size_ratio = 1 + 1.0 / 3;
};

class MultisetTest : public ::testing::Test {
 public:
  void SetUp(void) override {
    std::srand(69);

    for (int i = 0; i < 1000; ++i) {
      int key = rand() % 100;
      scp_ms_rnd.insert(key);
      std_ms_rnd.insert(key);
    }

    std::array<int, 16> values = {60, 40, 90, 30,  40,  50,  70,  130,
                                  10, 80, 90, 110, 120, 140, 100, 120};
    for (auto i : values) {
      scp_ms_static.insert(i);
      std_ms_static.insert(i);
    }
  }

  template <typename Key>
  bool MultisetsAreEqual(const scp::multiset<Key>& lhs,
                         const scp::multiset<Key>& rhs) {
    return lhs.empty() == rhs.empty() && lhs.size() == rhs.size() &&
           std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
  }
  template <typename Key>
  bool MultisetsAreEqual(const scp::multiset<Key>& lhs,
                         const std::multiset<Key>& rhs) {
    return lhs.empty() == rhs.empty() && lhs.size() == rhs.size() &&
           std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
  }
  template <typename Key>
  bool MultisetsAreEqual(const std::multiset<Key>& lhs,
                         const scp::multiset<Key>& rhs) {
    return lhs.empty() == rhs.empty() && lhs.size() == rhs.size() &&
           std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
  }

  template <typename Iterator1, typename Iterator2>
  void MoveForwardBackward(Iterator1& scp_it, Iterator2& std_it) {
    ++(++scp_it);
    ++(++std_it);
    EXPECT_EQ(*scp_it, *std_it);
    EXPECT_EQ(*++scp_it, *++std_it);
    EXPECT_EQ(*scp_it++, *std_it++);
    EXPECT_EQ(*scp_it, *std_it);
    EXPECT_EQ(*scp_it--, *std_it--);
    EXPECT_EQ(*scp_it, *std_it);
    EXPECT_EQ(*--scp_it, *--std_it);
    EXPECT_EQ(*scp_it, *std_it);
    --scp_it;
    --std_it;
    EXPECT_EQ(*scp_it, *std_it);
    EXPECT_EQ(*scp_it++, *std_it++);

    auto scp_it2 = scp_it++;
    auto std_it2 = std_it++;
    EXPECT_FALSE(scp_it2 == scp_it);
    EXPECT_FALSE(std_it2 == std_it);
    ++scp_it2;
    ++std_it2;
    EXPECT_TRUE(scp_it2 == scp_it);
    EXPECT_TRUE(std_it2 == std_it);
  }

  template <typename Iterator1, typename Iterator2>
  void MoveBackwardForward(Iterator1& scp_it, Iterator2& std_it) {
    --(--scp_it);
    --(--std_it);
    EXPECT_EQ(*scp_it, *std_it);
    EXPECT_EQ(*--scp_it, *--std_it);
    EXPECT_EQ(*scp_it--, *std_it--);
    EXPECT_EQ(*scp_it, *std_it);
    EXPECT_EQ(*scp_it++, *std_it++);
    EXPECT_EQ(*scp_it, *std_it);
    EXPECT_EQ(*++scp_it, *++std_it);
    EXPECT_EQ(*scp_it, *std_it);
    ++scp_it;
    ++std_it;
    EXPECT_EQ(*scp_it, *std_it);
    EXPECT_EQ(*scp_it--, *std_it--);

    auto scp_it2 = scp_it--;
    auto std_it2 = std_it--;
    EXPECT_FALSE(scp_it2 == scp_it);
    EXPECT_FALSE(std_it2 == std_it);
    --scp_it2;
    --std_it2;
    EXPECT_TRUE(scp_it2 == scp_it);
    EXPECT_TRUE(std_it2 == std_it);
  }

  scp::multiset<int> scp_ms_rnd;
  std::multiset<int> std_ms_rnd;

  scp::multiset<int> scp_ms_static;
  std::multiset<int> std_ms_static;

  double max_size_ratio = 2.4;
};

class SetTest : public ::testing::Test {
 public:
  void SetUp(void) override {
    std::srand(69);

    for (int i = 0; i < 1000; ++i) {
      int key = rand();
      scp_s_rnd.insert(key);
      std_s_rnd.insert(key);
    }

    std::array<int, 13> values = {60, 40, 90,  30,  50,  70, 130,
                                  10, 80, 110, 140, 100, 120};
    for (auto i : values) {
      scp_s_static.insert(i);
      std_s_static.insert(i);
    }
  }

  template <typename Key>
  bool SetsAreEqual(const scp::set<Key>& lhs, const scp::set<Key>& rhs) {
    return lhs.empty() == rhs.empty() && lhs.size() == rhs.size() &&
           std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
  }
  template <typename Key>
  bool SetsAreEqual(const scp::set<Key>& lhs, const std::set<Key>& rhs) {
    return lhs.empty() == rhs.empty() && lhs.size() == rhs.size() &&
           std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
  }
  template <typename Key>
  bool SetsAreEqual(const std::set<Key>& lhs, const scp::set<Key>& rhs) {
    return lhs.empty() == rhs.empty() && lhs.size() == rhs.size() &&
           std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
  }

  template <typename Iterator1, typename Iterator2>
  void MoveForwardBackward(Iterator1& scp_it, Iterator2& std_it) {
    ++(++scp_it);
    ++(++std_it);
    EXPECT_EQ(*scp_it, *std_it);
    EXPECT_EQ(*++scp_it, *++std_it);
    EXPECT_EQ(*scp_it++, *std_it++);
    EXPECT_EQ(*scp_it, *std_it);
    EXPECT_EQ(*scp_it--, *std_it--);
    EXPECT_EQ(*scp_it, *std_it);
    EXPECT_EQ(*--scp_it, *--std_it);
    EXPECT_EQ(*scp_it, *std_it);
    --scp_it;
    --std_it;
    EXPECT_EQ(*scp_it, *std_it);
    EXPECT_EQ(*scp_it++, *std_it++);

    auto scp_it2 = scp_it++;
    auto std_it2 = std_it++;
    EXPECT_FALSE(scp_it2 == scp_it);
    EXPECT_FALSE(std_it2 == std_it);
    ++scp_it2;
    ++std_it2;
    EXPECT_TRUE(scp_it2 == scp_it);
    EXPECT_TRUE(std_it2 == std_it);
  }

  template <typename Iterator1, typename Iterator2>
  void MoveBackwardForward(Iterator1& scp_it, Iterator2& std_it) {
    --(--scp_it);
    --(--std_it);
    EXPECT_EQ(*scp_it, *std_it);
    EXPECT_EQ(*--scp_it, *--std_it);
    EXPECT_EQ(*scp_it--, *std_it--);
    EXPECT_EQ(*scp_it, *std_it);
    EXPECT_EQ(*scp_it++, *std_it++);
    EXPECT_EQ(*scp_it, *std_it);
    EXPECT_EQ(*++scp_it, *++std_it);
    EXPECT_EQ(*scp_it, *std_it);
    ++scp_it;
    ++std_it;
    EXPECT_EQ(*scp_it, *std_it);
    EXPECT_EQ(*scp_it--, *std_it--);

    auto scp_it2 = scp_it--;
    auto std_it2 = std_it--;
    EXPECT_FALSE(scp_it2 == scp_it);
    EXPECT_FALSE(std_it2 == std_it);
    --scp_it2;
    --std_it2;
    EXPECT_TRUE(scp_it2 == scp_it);
    EXPECT_TRUE(std_it2 == std_it);
  }

  scp::set<int> scp_s_rnd;
  std::set<int> std_s_rnd;

  scp::set<int> scp_s_static;
  std::set<int> std_s_static;

  double max_size_ratio = 2.4;
};

struct GetKeyMap {
  template <typename K, typename V>
  const K& operator()(const std::pair<K, V>& value) const {
    return value.first;
  }
};

template class scp::vector<int>;
template class scp::VectorIterator<int>;
template class scp::VectorConstIterator<int>;
template class scp::array<int, 5>;

template class scp::list<int>;
template class scp::ListConstIterator<int>;
template class scp::ListIterator<int>;
template class scp::scp_node<int>;

template class scp::queue<int>;
template class scp::stack<int>;

template class scp::set<int>;
template class scp::multiset<int>;
template class scp::map<int, std::pair<int, int>>;

#endif  // CPP2_SCP_CONTAINERS_TESTS_TEST_H_

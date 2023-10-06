#include "../s21_map.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <cstdlib>
#include <map>
#include <string>

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
};

TEST_F(MapTest, DefaultCtor) {
  {
    s21::map<int, std::string> s21_m;
    EXPECT_TRUE(s21_m.empty());
    EXPECT_EQ(s21_m.size(), 0);
  }
  {
    const s21::map<int, std::string> s21_m;
    EXPECT_TRUE(s21_m.empty());
    EXPECT_EQ(s21_m.size(), 0);
  }
}

TEST_F(MapTest, InitializeCtor) {
  {
    s21::map<int, std::string> s21_m = {
        {1, "one"}, {2, "two"},   {3, "three"}, {4, "four"}, {5, "five"},
        {6, "six"}, {7, "seven"}, {8, "eight"}, {9, "nine"}, {10, "ten"}};
    std::map<int, std::string> std_m = {
        {1, "one"}, {2, "two"},   {3, "three"}, {4, "four"}, {5, "five"},
        {6, "six"}, {7, "seven"}, {8, "eight"}, {9, "nine"}, {10, "ten"}};

    EXPECT_TRUE(MapsAreEqual(s21_m, std_m));
  }
  {
    const s21::map<int, std::string> s21_m = {
        {1, "one"}, {2, "two"},   {3, "three"}, {4, "four"}, {5, "five"},
        {6, "six"}, {7, "seven"}, {8, "eight"}, {9, "nine"}, {10, "ten"}};
    const std::map<int, std::string> std_m = {
        {1, "one"}, {2, "two"},   {3, "three"}, {4, "four"}, {5, "five"},
        {6, "six"}, {7, "seven"}, {8, "eight"}, {9, "nine"}, {10, "ten"}};

    EXPECT_TRUE(MapsAreEqual(s21_m, std_m));
  }
}

TEST_F(MapTest, CopyCtor) {
  {
    s21::map<int, int> s21_m1;
    s21::map<int, int> s21_m2(s21_m1);
    std::map<int, int> std_m1;
    std::map<int, int> std_m2(std_m1);

    EXPECT_TRUE(MapsAreEqual(s21_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(s21_m2, std_m2));
  }
  {
    const s21::map<int, int> s21_m1;
    const s21::map<int, int> s21_m2(s21_m1);
    const std::map<int, int> std_m1;
    const std::map<int, int> std_m2(std_m1);

    EXPECT_TRUE(MapsAreEqual(s21_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(s21_m2, std_m2));
  }
  {
    s21::map<int, std::string> s21_m1 = {{10, "10"}};
    s21::map<int, std::string> s21_m2(s21_m1);
    std::map<int, std::string> std_m1 = {{10, "10"}};
    std::map<int, std::string> std_m2(std_m1);
    EXPECT_TRUE(MapsAreEqual(s21_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(s21_m2, std_m2));
  }
  {
    const s21::map<int, std::string> s21_m1 = {{10, "10"}};
    const s21::map<int, std::string> s21_m2(s21_m1);
    const std::map<int, std::string> std_m1 = {{10, "10"}};
    const std::map<int, std::string> std_m2(std_m1);

    EXPECT_TRUE(MapsAreEqual(s21_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(s21_m2, std_m2));
  }
  {
    s21::map<int, std::string> s21_m1 = {
        {10, "10"}, {5, "5"}, {15, "15"}, {6, "6"}, {12, "12"}};
    s21::map<int, std::string> s21_m2(s21_m1);
    std::map<int, std::string> std_m1 = {
        {10, "10"}, {5, "5"}, {15, "15"}, {6, "6"}, {12, "12"}};
    std::map<int, std::string> std_m2(std_m1);

    EXPECT_TRUE(MapsAreEqual(s21_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(s21_m2, std_m2));
  }
  {
    s21::map<int, std::string> s21_m(s21_m_rnd);
    std::map<int, std::string> std_m(std_m_rnd);

    EXPECT_TRUE(MapsAreEqual(s21_m, std_m));
  }
  {
    const s21::map<int, std::string> s21_m(s21_m_rnd);
    const std::map<int, std::string> std_m(std_m_rnd);

    EXPECT_TRUE(MapsAreEqual(s21_m, std_m));
  }
}

TEST_F(MapTest, MoveCtor) {
  {
    s21::map<int, std::string> s21_m1;
    s21::map<int, std::string> s21_m2(std::move(s21_m1));
    std::map<int, std::string> std_m1;
    std::map<int, std::string> std_m2(std::move(std_m1));

    EXPECT_TRUE(MapsAreEqual(s21_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(s21_m2, std_m2));
  }
  {
    const s21::map<int, std::string> s21_m1;
    const s21::map<int, std::string> s21_m2(std::move(s21_m1));
    const std::map<int, std::string> std_m1;
    const std::map<int, std::string> std_m2(std::move(std_m1));

    EXPECT_TRUE(MapsAreEqual(s21_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(s21_m2, std_m2));
  }
  {
    s21::map<int, int> s21_m1 = {{1, 2}};
    s21::map<int, int> s21_m2(std::move(s21_m1));
    std::map<int, int> std_m1 = {{1, 2}};
    std::map<int, int> std_m2(std::move(std_m1));

    EXPECT_TRUE(MapsAreEqual(s21_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(s21_m2, std_m2));
  }
  {
    const s21::map<int, int> s21_m1 = {{1, 2}};
    const s21::map<int, int> s21_m2(std::move(s21_m1));
    const std::map<int, int> std_m1 = {{1, 2}};
    const std::map<int, int> std_m2(std::move(std_m1));

    EXPECT_TRUE(MapsAreEqual(s21_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(s21_m2, std_m2));
  }
  {
    s21::map<int, std::string> s21_m(std::move(s21_m_rnd));
    std::map<int, std::string> std_m(std::move(std_m_rnd));

    EXPECT_TRUE(MapsAreEqual(s21_m, std_m));
  }
  {
    const s21::map<int, std::string> s21_m(std::move(s21_m_rnd));
    const std::map<int, std::string> std_m(std::move(std_m_rnd));

    EXPECT_TRUE(MapsAreEqual(s21_m, std_m));
  }
}

TEST_F(MapTest, AssignmentOperator) {
  {
    s21::map<int, std::string> s21_m1, s21_m2;
    std::map<int, std::string> std_m1, std_m2;

    s21_m2 = s21_m1;
    std_m2 = std_m1;

    EXPECT_TRUE(MapsAreEqual(s21_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(s21_m2, std_m2));
  }
  {
    const s21::map<int, std::string> s21_m1;
    const std::map<int, std::string> std_m1;
    s21::map<int, std::string> s21_m2;
    std::map<int, std::string> std_m2;

    s21_m2 = s21_m1;
    std_m2 = std_m1;

    EXPECT_TRUE(MapsAreEqual(s21_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(s21_m2, std_m2));
  }
  {
    s21::map<int, std::string> s21_m1, s21_m2;
    std::map<int, std::string> std_m1, std_m2;

    s21_m2 = std::move(s21_m1);
    std_m2 = std::move(std_m1);

    EXPECT_TRUE(MapsAreEqual(s21_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(s21_m2, std_m2));
  }
  {
    const s21::map<int, std::string> s21_m1;
    const std::map<int, std::string> std_m1;
    s21::map<int, std::string> s21_m2;
    std::map<int, std::string> std_m2;

    s21_m2 = std::move(s21_m1);
    std_m2 = std::move(std_m1);

    EXPECT_TRUE(MapsAreEqual(s21_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(s21_m2, std_m2));
  }
  {
    s21::map<int, std::string> s21_m1 = {{10, "10"}};
    s21::map<int, std::string> s21_m2;
    std::map<int, std::string> std_m1 = {{10, "10"}};
    std::map<int, std::string> std_m2;

    s21_m2 = s21_m1;
    std_m2 = std_m1;

    EXPECT_TRUE(MapsAreEqual(s21_m1, std_m2));
    EXPECT_TRUE(MapsAreEqual(s21_m1, std_m2));
  }
  {
    const s21::map<int, std::string> s21_m1 = {{10, "10"}};
    s21::map<int, std::string> s21_m2;
    const std::map<int, std::string> std_m1 = {{10, "10"}};
    std::map<int, std::string> std_m2;

    s21_m2 = s21_m1;
    std_m2 = std_m1;

    EXPECT_TRUE(MapsAreEqual(s21_m1, std_m2));
    EXPECT_TRUE(MapsAreEqual(s21_m1, std_m2));
  }
  {
    s21::map<int, std::string> s21_m1 = {{10, "10"}};
    s21::map<int, std::string> s21_m2;
    std::map<int, std::string> std_m1 = {{10, "10"}};
    std::map<int, std::string> std_m2;

    s21_m2 = std::move(s21_m1);
    std_m2 = std::move(std_m1);

    EXPECT_TRUE(MapsAreEqual(s21_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(s21_m2, std_m2));
  }
  {
    const s21::map<int, std::string> s21_m1 = {{10, "10"}};
    s21::map<int, std::string> s21_m2;
    const std::map<int, std::string> std_m1 = {{10, "10"}};
    std::map<int, std::string> std_m2;

    s21_m2 = std::move(s21_m1);
    std_m2 = std::move(std_m1);

    EXPECT_TRUE(MapsAreEqual(s21_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(s21_m2, std_m2));
  }
  {
    s21::map<int, int> s21_m1 = {{69, 42}, {25, 8}, {51, 25}};
    s21::map<int, int> s21_m2 = {{69, 42}};
    std::map<int, int> std_m1 = {{69, 42}, {25, 8}, {51, 25}};
    std::map<int, int> std_m2 = {{69, 42}};

    s21_m2 = s21_m1;
    std_m2 = std_m1;

    EXPECT_TRUE(MapsAreEqual(s21_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(s21_m2, std_m2));
  }
  {
    const s21::map<int, int> s21_m1 = {{69, 42}, {25, 8}, {51, 25}};
    s21::map<int, int> s21_m2 = {{69, 42}};
    const std::map<int, int> std_m1 = {{69, 42}, {25, 8}, {51, 25}};
    std::map<int, int> std_m2 = {{69, 42}};

    s21_m2 = s21_m1;
    std_m2 = std_m1;

    EXPECT_TRUE(MapsAreEqual(s21_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(s21_m2, std_m2));
  }
  {
    s21::map<int, int> s21_m1 = {{69, 42}, {25, 8}, {51, 25}};
    s21::map<int, int> s21_m2 = {{69, 42}};
    std::map<int, int> std_m1 = {{69, 42}, {25, 8}, {51, 25}};
    std::map<int, int> std_m2 = {{69, 42}};

    s21_m2 = std::move(s21_m1);
    std_m2 = std::move(std_m1);

    EXPECT_TRUE(MapsAreEqual(s21_m2, std_m2));
  }
  {
    const s21::map<int, int> s21_m1 = {{69, 42}, {25, 8}, {51, 25}};
    s21::map<int, int> s21_m2 = {{69, 42}};
    const std::map<int, int> std_m1 = {{69, 42}, {25, 8}, {51, 25}};
    std::map<int, int> std_m2 = {{69, 42}};

    s21_m2 = std::move(s21_m1);
    std_m2 = std::move(std_m1);

    EXPECT_TRUE(MapsAreEqual(s21_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(s21_m2, std_m2));
  }
  {
    s21::map<int, std::string> s21_m = {{69, "42"}};
    std::map<int, std::string> std_m = {{69, "42"}};

    s21_m = s21_m_rnd;
    std_m = std_m_rnd;

    EXPECT_TRUE(MapsAreEqual(s21_m, std_m));
  }
  {
    s21::map<int, std::string> s21_m = {{69, "42"}};
    std::map<int, std::string> std_m = {{69, "42"}};

    s21_m = std::move(s21_m_rnd);
    std_m = std::move(std_m_rnd);

    EXPECT_TRUE(MapsAreEqual(s21_m, std_m));
  }
}

TEST_F(MapTest, ElementAccess) {
  {
    EXPECT_EQ(s21_m_static.at(10), "10");
    EXPECT_EQ(s21_m_static.at(50), "50");
    EXPECT_EQ(std_m_static.at(10), "10");
    EXPECT_EQ(std_m_static.at(50), "50");
    EXPECT_THROW(s21_m_static.at(-1), std::out_of_range);
    EXPECT_THROW(s21_m_static.at(1), std::out_of_range);
  }
  {
    const s21::map<int, std::string> s21_m = s21_m_static;
    const std::map<int, std::string> std_m = std_m_static;
    EXPECT_EQ(s21_m.at(10), "10");
    EXPECT_EQ(s21_m.at(50), "50");
    EXPECT_THROW(s21_m.at(-1), std::out_of_range);
    EXPECT_THROW(s21_m.at(1), std::out_of_range);
    EXPECT_EQ(std_m.at(10), "10");
    EXPECT_EQ(std_m.at(50), "50");
    EXPECT_THROW(std_m.at(-1), std::out_of_range);
    EXPECT_THROW(std_m.at(1), std::out_of_range);
  }
  {
    s21::map<int, std::string> s21_m = s21_m_static;
    std::map<int, std::string> std_m = std_m_static;
    EXPECT_EQ(s21_m[50], "50");
    EXPECT_EQ(std_m[50], "50");
    s21_m[50] = "new_50";
    std_m[50] = "new_50";
    s21_m[1] = "100";
    std_m[1] = "100";

    EXPECT_TRUE(MapsAreEqual(s21_m, std_m));
  }
}

TEST_F(MapTest, Iterator) {
  {
    auto s21_it = s21_m_rnd.begin();
    auto std_it = std_m_rnd.begin();
    MoveForwardBackward(s21_it, std_it);
  }
  {
    auto s21_it = s21_m_rnd.end();
    auto std_it = std_m_rnd.end();
    MoveBackwardForward(s21_it, std_it);
  }
  {
    auto s21_it = s21_m_rnd.rbegin();
    auto std_it = std_m_rnd.rbegin();
    MoveForwardBackward(s21_it, std_it);
  }
  {
    auto s21_it = s21_m_rnd.rend();
    auto std_it = std_m_rnd.rend();
    MoveBackwardForward(s21_it, std_it);
  }
  {
    auto s21_it = s21_m_rnd.cbegin();
    auto std_it = std_m_rnd.cbegin();
    MoveForwardBackward(s21_it, std_it);
  }
  {
    auto s21_it = s21_m_rnd.cend();
    auto std_it = std_m_rnd.cend();
    MoveBackwardForward(s21_it, std_it);
  }
  {
    auto s21_it = s21_m_rnd.crbegin();
    auto std_it = std_m_rnd.crbegin();
    MoveForwardBackward(s21_it, std_it);
  }
  {
    auto s21_it = s21_m_rnd.crend();
    auto std_it = std_m_rnd.crend();
    MoveBackwardForward(s21_it, std_it);
  }
}

TEST_F(MapTest, Capacity) {
  {
    s21::map<int, int> s21_m;
    std::map<int, int> std_m;
    EXPECT_EQ(s21_m.empty(), std_m.empty());
    EXPECT_EQ(s21_m.size(), std_m.size());
    // EXPECT_EQ(s21_m.max_size(), std_m.max_size());
  }
  {
    s21::map<int, std::string> s21_m = {{10, "10"}};
    std::map<int, std::string> std_m = {{10, "10"}};
    EXPECT_EQ(s21_m.empty(), std_m.empty());
    EXPECT_EQ(s21_m.size(), std_m.size());
    // EXPECT_EQ(s21_m.max_size(), std_m.max_size());
  }
  {
    EXPECT_EQ(s21_m_rnd.empty(), std_m_rnd.empty());
    EXPECT_EQ(s21_m_rnd.size(), std_m_rnd.size());
    // EXPECT_EQ(s21_m_rnd.max_size(), std_m_rnd.max_size());
  }
  {
    EXPECT_EQ(s21_m_static.empty(), s21_m_static.empty());
    EXPECT_EQ(s21_m_static.size(), s21_m_static.size());
    // EXPECT_EQ(cms21.max_size(), cmstd.max_size());
  }
}

TEST_F(MapTest, Clear) {
  {
    s21::map<int, int> s21_m;
    std::map<int, int> std_m;
    s21_m.clear();
    std_m.clear();
    EXPECT_EQ(s21_m.empty(), std_m.empty());
    EXPECT_EQ(s21_m.size(), std_m.size());
    EXPECT_TRUE(MapsAreEqual(s21_m, std_m));
  }
  {
    auto s21_m = s21_m_rnd;
    auto std_m = std_m_rnd;
    s21_m.clear();
    std_m.clear();
    EXPECT_EQ(s21_m.empty(), std_m.empty());
    EXPECT_EQ(s21_m.size(), std_m.size());
    EXPECT_TRUE(MapsAreEqual(s21_m, std_m));
  }
}

TEST_F(MapTest, Insert) {
  {
    auto s21_e = s21_m_static.insert_or_assign(10, "ten");
    auto std_e = std_m_static.insert_or_assign(10, "ten");
    EXPECT_EQ(*s21_e.first, *std_e.first);
    EXPECT_EQ(s21_e.second, std_e.second);
  }
  {
    auto s21_e = s21_m_static.insert_or_assign(115, "115");
    auto std_e = std_m_static.insert_or_assign(115, "115");
    EXPECT_EQ(*s21_e.first, *std_e.first);
    EXPECT_EQ(s21_e.second, std_e.second);
  }
  {
    s21::map<int, std::string> s21_m;
    std::map<int, std::string> std_m;
    for (auto i = 0; i < 10000; ++i) {
      auto key = rand() % 1000000;
      auto key_str = std::to_string(key);
      auto s21_e = s21_m.insert(key, key_str);
      auto std_e = std_m.insert(std::make_pair(key, key_str));
      EXPECT_EQ(*s21_e.first, *std_e.first);
      EXPECT_EQ(s21_e.second, std_e.second);
    }
    EXPECT_TRUE(MapsAreEqual(s21_m, std_m));
    auto key_str = "rnd";
    for (auto i : s21_m_rnd) {
      auto s21_e = s21_m.insert_or_assign(i.first, key_str);
      auto std_e = std_m.insert_or_assign(i.first, key_str);
      EXPECT_EQ(*s21_e.first, *std_e.first);
      EXPECT_EQ(s21_e.second, std_e.second);
    }
    EXPECT_TRUE(MapsAreEqual(s21_m, std_m));
  }
}

TEST_F(MapTest, InsertMany) {
  {
    s21::map<int, std::string> s21_m;
    std::map<int, std::string> std_m;

    s21_m.insert_many(std::make_pair(10, std::string("10")),
                      std::make_pair(20, std::string("20")),
                      std::make_pair(30, std::string("30")),
                      std::make_pair(40, std::string("40")));
    std_m.insert({{10, "10"}, {20, "20"}, {30, "30"}, {40, "40"}});
    EXPECT_TRUE(MapsAreEqual(s21_m, std_m));
  }
  {
    s21::map<int, std::string> s21_m = {{10, "10"}, {20, "20"}};
    std::map<int, std::string> std_m = {{10, "10"}, {20, "20"}};

    s21_m.insert_many(std::make_pair(50, std::string("50")),
                      std::make_pair(30, std::string("30")),
                      std::make_pair(30, std::string("30")),
                      std::make_pair(40, std::string("40")));
    std_m.insert({{50, "50"}, {30, "30"}, {30, "30"}, {40, "40"}});
    EXPECT_TRUE(MapsAreEqual(s21_m, std_m));
  }
  {
    s21::map<int, std::string> s21_m = {{10, "10"}, {20, "20"}};
    std::map<int, std::string> std_m = {{10, "10"}, {20, "20"}};

    s21_m.insert_many(std::make_pair(10, std::string("10")),
                      std::make_pair(20, std::string("20")));
    std_m.insert({{10, "10"}, {20, "20"}});
    EXPECT_TRUE(MapsAreEqual(s21_m, std_m));
  }
}

TEST_F(MapTest, Erase) {
  {
    s21_m_rnd.erase(s21_m_rnd.begin());
    std_m_rnd.erase(std_m_rnd.begin());
    EXPECT_TRUE(MapsAreEqual(s21_m_rnd, std_m_rnd));

    s21_m_rnd.erase(--s21_m_rnd.end());
    std_m_rnd.erase(--std_m_rnd.end());
    EXPECT_TRUE(MapsAreEqual(s21_m_rnd, std_m_rnd));

    s21_m_rnd.erase(++s21_m_rnd.begin());
    std_m_rnd.erase(++std_m_rnd.begin());
    EXPECT_TRUE(MapsAreEqual(s21_m_rnd, std_m_rnd));

    s21_m_rnd.erase(--(--s21_m_rnd.end()));
    std_m_rnd.erase(--(--std_m_rnd.end()));
    EXPECT_TRUE(MapsAreEqual(s21_m_rnd, std_m_rnd));

    auto s21_it = s21_m_rnd.end();
    auto std_it = std_m_rnd.end();
    for (int i = 0; i < 111; ++i, --s21_it, --std_it) {
    }
    s21_m_rnd.erase(s21_it);
    std_m_rnd.erase(std_it);
    EXPECT_TRUE(MapsAreEqual(s21_m_rnd, std_m_rnd));

    s21_it = s21_m_rnd.begin();
    std_it = std_m_rnd.begin();
    for (int i = 0; i < 111; ++i, ++s21_it, ++std_it) {
    }
    s21_m_rnd.erase(s21_it);
    std_m_rnd.erase(std_it);
    EXPECT_TRUE(MapsAreEqual(s21_m_rnd, std_m_rnd));
  }
  {
    s21::map<int, std::string> s21_m = {{10, "10"}};
    std::map<int, std::string> std_m = {{10, "10"}};
    s21_m.erase(s21_m.begin());
    std_m.erase(std_m.begin());
    EXPECT_TRUE(MapsAreEqual(s21_m, std_m));
  }
  {
    auto s21_m = s21_m_static;
    auto std_m = std_m_static;
    s21_m.erase(s21_m.find(70));
    std_m.erase(std_m.find(70));
    EXPECT_TRUE(MapsAreEqual(s21_m, std_m));
  }
  {
    auto s21_m = s21_m_static;
    auto std_m = std_m_static;
    s21_m.erase(s21_m.find(30));
    std_m.erase(std_m.find(30));
    EXPECT_TRUE(MapsAreEqual(s21_m, std_m));
  }
  {
    auto s21_m = s21_m_static;
    auto std_m = std_m_static;
    auto key_value = std::make_pair(45, "45");
    s21_m.insert(key_value);
    std_m.insert(key_value);
    s21_m.erase(s21_m.find(40));
    std_m.erase(std_m.find(40));
    EXPECT_TRUE(MapsAreEqual(s21_m, std_m));
  }
  {
    auto s21_m = s21_m_static;
    auto std_m = std_m_static;
    s21_m.erase(s21_m.find(90));
    std_m.erase(std_m.find(90));
    EXPECT_TRUE(MapsAreEqual(s21_m, std_m));
  }
  {
    auto s21_m = s21_m_static;
    auto std_m = std_m_static;
    s21_m.erase(s21_m.find(100));
    std_m.erase(std_m.find(100));
    s21_m.erase(s21_m.find(90));
    std_m.erase(std_m.find(90));
    EXPECT_TRUE(MapsAreEqual(s21_m, std_m));
  }
  {
    auto s21_m = s21_m_static;
    auto std_m = std_m_static;
    s21_m.erase(s21_m.find(100));
    std_m.erase(std_m.find(100));
    s21_m.erase(s21_m.find(90));
    std_m.erase(std_m.find(90));
    s21_m.erase(s21_m.find(40));
    std_m.erase(std_m.find(40));
    s21_m.erase(s21_m.find(110));
    std_m.erase(std_m.find(110));
    EXPECT_TRUE(MapsAreEqual(s21_m, std_m));
  }
  {
    auto std_m_rnd_copy = std_m_rnd;
    int i = 0;
    for (auto elem : std_m_rnd_copy) {
      if (i++ % 3 == 0) {
        s21_m_rnd.erase(s21_m_rnd.find(elem.first));
        std_m_rnd.erase(std_m_rnd.find(elem.first));
      }
    }
    EXPECT_TRUE(MapsAreEqual(s21_m_rnd, std_m_rnd));
  }
}

TEST_F(MapTest, Swap) {
  {
    s21::map<int, std::string> s21_m1, s21_m2;
    std::map<int, std::string> std_m1, std_m2;
    s21_m1.swap(s21_m2);
    std_m1.swap(std_m2);
    EXPECT_TRUE(MapsAreEqual(s21_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(s21_m2, std_m2));
  }
  {
    s21::map<int, std::string> s21_m1;
    s21::map<int, std::string> s21_m2 = {{1, "1"}};
    std::map<int, std::string> std_m1;
    std::map<int, std::string> std_m2 = {{1, "1"}};
    s21_m1.swap(s21_m2);
    std_m1.swap(std_m2);
    EXPECT_TRUE(MapsAreEqual(s21_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(s21_m2, std_m2));
    s21_m2.swap(s21_m1);
    std_m2.swap(std_m1);
    EXPECT_TRUE(MapsAreEqual(s21_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(s21_m2, std_m2));
  }
  {
    s21_m_static.swap(s21_m_rnd);
    std_m_static.swap(std_m_rnd);
    EXPECT_TRUE(MapsAreEqual(s21_m_rnd, std_m_rnd));
    EXPECT_TRUE(MapsAreEqual(s21_m_static, std_m_static));
  }
}

TEST_F(MapTest, Merge) {
  {
    s21::map<int, std::string> s21_m1, s21_m2;
    std::map<int, std::string> std_m1, std_m2;
    s21_m1.merge(s21_m2);
    std_m1.merge(std_m2);
    EXPECT_TRUE(MapsAreEqual(s21_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(s21_m2, std_m2));
  }
  {
    s21::map<int, std::string> s21_m1 = {{1, "1"}};
    s21::map<int, std::string> s21_m2;
    std::map<int, std::string> std_m1 = {{1, "1"}};
    std::map<int, std::string> std_m2;
    s21_m1.merge(s21_m2);
    std_m1.merge(std_m2);
    EXPECT_TRUE(MapsAreEqual(s21_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(s21_m2, std_m2));
  }
  {
    s21::map<int, std::string> s21_m1;
    s21::map<int, std::string> s21_m2 = {{1, "1"}};
    std::map<int, std::string> std_m1;
    std::map<int, std::string> std_m2 = {{1, "1"}};
    s21_m1.merge(s21_m2);
    std_m1.merge(std_m2);
    EXPECT_TRUE(MapsAreEqual(s21_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(s21_m2, std_m2));
  }
  {
    s21::map<int, std::string> s21_m1 = {{2, "2"}};
    s21::map<int, std::string> s21_m2 = {{1, "1"}};
    std::map<int, std::string> std_m1 = {{2, "2"}};
    std::map<int, std::string> std_m2 = {{1, "1"}};
    s21_m1.merge(s21_m2);
    std_m1.merge(std_m2);
    EXPECT_TRUE(MapsAreEqual(s21_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(s21_m2, std_m2));
  }
  {
    s21::map<int, std::string> s21_m1 = {{1, "1"}, {2, "2"}};
    s21::map<int, std::string> s21_m2 = {{1, "1"}};
    std::map<int, std::string> std_m1 = {{1, "1"}, {2, "2"}};
    std::map<int, std::string> std_m2 = {{1, "1"}};
    s21_m1.merge(s21_m2);
    std_m1.merge(std_m2);
    EXPECT_TRUE(MapsAreEqual(s21_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(s21_m2, std_m2));
  }
  {
    s21::map<int, std::string> s21_m1 = {{1, "1"}, {2, "2"}};
    s21::map<int, std::string> s21_m2 = {{1, "1"}, {3, "3"}};
    std::map<int, std::string> std_m1 = {{1, "1"}, {2, "2"}};
    std::map<int, std::string> std_m2 = {{1, "1"}, {3, "3"}};
    s21_m1.merge(s21_m2);
    std_m1.merge(std_m2);
    EXPECT_TRUE(MapsAreEqual(s21_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(s21_m2, std_m2));
  }
  {
    s21::map<int, std::string> s21_m1 = {
        {1, "1"}, {2, "2"}, {0, "0"}, {-1, "-1"}, {2, "2"}};
    s21::map<int, std::string> s21_m2 = {
        {1, "1"}, {3, "3"}, {2, "2"}, {4, "4"}, {5, "5"}};
    std::map<int, std::string> std_m1 = {
        {1, "1"}, {2, "2"}, {0, "0"}, {-1, "-1"}, {2, "2"}};
    std::map<int, std::string> std_m2 = {
        {1, "1"}, {3, "3"}, {2, "2"}, {4, "4"}, {5, "5"}};
    s21_m1.merge(s21_m2);
    std_m1.merge(std_m2);
    EXPECT_TRUE(MapsAreEqual(s21_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(s21_m2, std_m2));
  }
  {
    s21::map<int, std::string> s21_m;
    std::map<int, std::string> std_m;
    for (int i = 0; i < 100000; ++i) {
      auto key = rand() % 1000000;
      auto key_value = std::make_pair(key, std::to_string(key));
      s21_m.insert(key_value);
      std_m.insert(key_value);
    }
    s21_m.merge(s21_m_rnd);
    std_m.merge(std_m_rnd);
    EXPECT_TRUE(MapsAreEqual(s21_m, std_m));
    EXPECT_TRUE(MapsAreEqual(s21_m_rnd, std_m_rnd));
  }
}

TEST_F(MapTest, Lookup) {
  {
    EXPECT_TRUE(s21_m_static.contains(70));
    EXPECT_TRUE(s21_m_static.contains(30));
    EXPECT_TRUE(s21_m_static.contains(40));
    EXPECT_FALSE(s21_m_static.contains(1));
    EXPECT_FALSE(s21_m_static.contains(65));
    EXPECT_FALSE(s21_m_static.contains(200));
  }
  {
    s21::map<int, std::string> s21_m;
    EXPECT_FALSE(s21_m.contains(1));
  }
  {
    const s21::map<int, std::string> s21_m = s21_m_static;
    const std::map<int, std::string> std_m = std_m_static;
    EXPECT_TRUE(s21_m.find(100)->first == 100);
    EXPECT_TRUE(std_m.find(100)->first == 100);
    EXPECT_TRUE(s21_m.find(1000) == s21_m.cend());
    EXPECT_TRUE(std_m.find(1000) == std_m.cend());
  }
}

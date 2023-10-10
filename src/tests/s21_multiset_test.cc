#include "../s21_multiset.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <cstdlib>
#include <set>
#include <string>

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
};

TEST_F(MultisetTest, DefaultCtor) {
  {
    s21::multiset<int> s21_ms;
    EXPECT_TRUE(s21_ms.empty());
    EXPECT_EQ(s21_ms.size(), 0);
  }
  {
    const s21::multiset<int> s21_ms;
    EXPECT_TRUE(s21_ms.empty());
    EXPECT_EQ(s21_ms.size(), 0);
  }
}

TEST_F(MultisetTest, InitializeCtor) {
  {
    s21::multiset<int> s21_ms = {1,  2, 3, 4, 5, 6, 7, 8, 9, 10,
                                 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    std::multiset<int> std_ms = {1,  2, 3, 4, 5, 6, 7, 8, 9, 10,
                                 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    EXPECT_TRUE(MultisetsAreEqual(s21_ms, std_ms));
  }
  {
    const s21::multiset<int> s21_ms = {1,  2, 3, 4, 5, 6, 7, 8, 9, 10,
                                       10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    const std::multiset<int> std_ms = {1,  2, 3, 4, 5, 6, 7, 8, 9, 10,
                                       10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    EXPECT_TRUE(MultisetsAreEqual(s21_ms, std_ms));
  }
}

TEST_F(MultisetTest, CopyCtor) {
  {
    s21::multiset<int> s21_ms1;
    s21::multiset<int> s21_ms2(s21_ms1);
    std::multiset<int> std_ms1;
    std::multiset<int> std_ms2(std_ms1);

    EXPECT_TRUE(MultisetsAreEqual(s21_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(s21_ms2, std_ms2));
  }
  {
    const s21::multiset<int> s21_ms1;
    const s21::multiset<int> s21_ms2(s21_ms1);
    const std::multiset<int> std_ms1;
    const std::multiset<int> std_ms2(std_ms1);

    EXPECT_TRUE(MultisetsAreEqual(s21_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(s21_ms2, std_ms2));
  }
  {
    s21::multiset<int> s21_ms1 = {10};
    s21::multiset<int> s21_ms2(s21_ms1);
    std::multiset<int> std_ms1 = {10};
    std::multiset<int> std_ms2(std_ms1);
    EXPECT_TRUE(MultisetsAreEqual(s21_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(s21_ms2, std_ms2));
  }
  {
    const s21::multiset<int> s21_ms1 = {10};
    const s21::multiset<int> s21_ms2(s21_ms1);
    const std::multiset<int> std_ms1 = {10};
    const std::multiset<int> std_ms2(std_ms1);

    EXPECT_TRUE(MultisetsAreEqual(s21_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(s21_ms2, std_ms2));
  }
  {
    s21::multiset<int> s21_ms(s21_ms_rnd);
    std::multiset<int> std_ms(std_ms_rnd);

    EXPECT_TRUE(MultisetsAreEqual(s21_ms, std_ms));
  }
  {
    const s21::multiset<int> s21_ms(s21_ms_rnd);
    const std::multiset<int> std_ms(std_ms_rnd);

    EXPECT_TRUE(MultisetsAreEqual(s21_ms, std_ms));
  }
}

TEST_F(MultisetTest, MoveCtor) {
  {
    s21::multiset<int> s21_ms1;
    s21::multiset<int> s21_ms2(std::move(s21_ms1));
    std::multiset<int> std_ms1;
    std::multiset<int> std_ms2(std::move(std_ms1));

    EXPECT_TRUE(MultisetsAreEqual(s21_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(s21_ms2, std_ms2));
  }
  {
    const s21::multiset<int> s21_ms1;
    const s21::multiset<int> s21_ms2(std::move(s21_ms1));
    const std::multiset<int> std_ms1;
    const std::multiset<int> std_ms2(std::move(std_ms1));

    EXPECT_TRUE(MultisetsAreEqual(s21_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(s21_ms2, std_ms2));
  }
  {
    s21::multiset<int> s21_ms1 = {1};
    s21::multiset<int> s21_ms2(std::move(s21_ms1));
    std::multiset<int> std_ms1 = {1};
    std::multiset<int> std_ms2(std::move(std_ms1));

    EXPECT_TRUE(MultisetsAreEqual(s21_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(s21_ms2, std_ms2));
  }
  {
    const s21::multiset<int> s21_ms1 = {1};
    const s21::multiset<int> s21_ms2(std::move(s21_ms1));
    const std::multiset<int> std_ms1 = {1};
    const std::multiset<int> std_ms2(std::move(std_ms1));

    EXPECT_TRUE(MultisetsAreEqual(s21_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(s21_ms2, std_ms2));
  }
  {
    s21::multiset<int> s21_ms(std::move(s21_ms_rnd));
    std::multiset<int> std_ms(std::move(std_ms_rnd));

    EXPECT_TRUE(MultisetsAreEqual(s21_ms, std_ms));
  }
  {
    const s21::multiset<int> s21_ms(std::move(s21_ms_rnd));
    const std::multiset<int> std_ms(std::move(std_ms_rnd));

    EXPECT_TRUE(MultisetsAreEqual(s21_ms, std_ms));
  }
}

TEST_F(MultisetTest, AssignmentOperator) {
  {
    s21::multiset<int> s21_ms1, s21_ms2;
    std::multiset<int> std_ms1, std_ms2;

    s21_ms2 = s21_ms1;
    std_ms2 = std_ms1;

    EXPECT_TRUE(MultisetsAreEqual(s21_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(s21_ms2, std_ms2));
  }
  {
    const s21::multiset<int> s21_ms1;
    const std::multiset<int> std_ms1;
    s21::multiset<int> s21_ms2;
    std::multiset<int> std_ms2;

    s21_ms2 = s21_ms1;
    std_ms2 = std_ms1;

    EXPECT_TRUE(MultisetsAreEqual(s21_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(s21_ms2, std_ms2));
  }
  {
    s21::multiset<int> s21_ms1, s21_ms2;
    std::multiset<int> std_ms1, std_ms2;

    s21_ms2 = std::move(s21_ms1);
    std_ms2 = std::move(std_ms1);

    EXPECT_TRUE(MultisetsAreEqual(s21_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(s21_ms2, std_ms2));
  }
  {
    const s21::multiset<int> s21_ms1;
    const std::multiset<int> std_ms1;
    s21::multiset<int> s21_ms2;
    std::multiset<int> std_ms2;

    s21_ms2 = std::move(s21_ms1);
    std_ms2 = std::move(std_ms1);

    EXPECT_TRUE(MultisetsAreEqual(s21_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(s21_ms2, std_ms2));
  }
  {
    s21::multiset<int> s21_ms1 = {10};
    s21::multiset<int> s21_ms2;
    std::multiset<int> std_ms1 = {10};
    std::multiset<int> std_ms2;

    s21_ms2 = s21_ms1;
    std_ms2 = std_ms1;

    EXPECT_TRUE(MultisetsAreEqual(s21_ms1, std_ms2));
    EXPECT_TRUE(MultisetsAreEqual(s21_ms1, std_ms2));
  }
  {
    const s21::multiset<int> s21_ms1 = {10};
    s21::multiset<int> s21_ms2;
    const std::multiset<int> std_ms1 = {10};
    std::multiset<int> std_ms2;

    s21_ms2 = s21_ms1;
    std_ms2 = std_ms1;

    EXPECT_TRUE(MultisetsAreEqual(s21_ms1, std_ms2));
    EXPECT_TRUE(MultisetsAreEqual(s21_ms1, std_ms2));
  }
  {
    s21::multiset<int> s21_ms1 = {10};
    s21::multiset<int> s21_ms2;
    std::multiset<int> std_ms1 = {10};
    std::multiset<int> std_ms2;

    s21_ms2 = std::move(s21_ms1);
    std_ms2 = std::move(std_ms1);

    EXPECT_TRUE(MultisetsAreEqual(s21_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(s21_ms2, std_ms2));
  }
  {
    const s21::multiset<int> s21_ms1 = {10};
    s21::multiset<int> s21_ms2;
    const std::multiset<int> std_ms1 = {10};
    std::multiset<int> std_ms2;

    s21_ms2 = std::move(s21_ms1);
    std_ms2 = std::move(std_ms1);

    EXPECT_TRUE(MultisetsAreEqual(s21_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(s21_ms2, std_ms2));
  }
  {
    s21::multiset<int> s21_ms1 = {69, 25, 69};
    s21::multiset<int> s21_ms2 = {69};
    std::multiset<int> std_ms1 = {69, 25, 69};
    std::multiset<int> std_ms2 = {69};

    s21_ms2 = s21_ms1;
    std_ms2 = std_ms1;

    EXPECT_TRUE(MultisetsAreEqual(s21_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(s21_ms2, std_ms2));
  }
  {
    const s21::multiset<int> s21_ms1 = {69, 25, 69};
    s21::multiset<int> s21_ms2 = {69};
    const std::multiset<int> std_ms1 = {69, 25, 69};
    std::multiset<int> std_ms2 = {69};

    s21_ms2 = s21_ms1;
    std_ms2 = std_ms1;

    EXPECT_TRUE(MultisetsAreEqual(s21_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(s21_ms2, std_ms2));
  }
  {
    s21::multiset<int> s21_ms1 = {69, 25, 69};
    s21::multiset<int> s21_ms2 = {69};
    std::multiset<int> std_ms1 = {69, 25, 69};
    std::multiset<int> std_ms2 = {69};

    s21_ms2 = std::move(s21_ms1);
    std_ms2 = std::move(std_ms1);

    EXPECT_TRUE(MultisetsAreEqual(s21_ms2, std_ms2));
  }
  {
    const s21::multiset<int> s21_ms1 = {69, 25, 69};
    s21::multiset<int> s21_ms2 = {69};
    const std::multiset<int> std_ms1 = {69, 25, 69};
    std::multiset<int> std_ms2 = {69};

    s21_ms2 = std::move(s21_ms1);
    std_ms2 = std::move(std_ms1);

    EXPECT_TRUE(MultisetsAreEqual(s21_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(s21_ms2, std_ms2));
  }
  {
    s21::multiset<int> s21_ms = {69};
    std::multiset<int> std_ms = {69};

    s21_ms = s21_ms_rnd;
    std_ms = std_ms_rnd;

    EXPECT_TRUE(MultisetsAreEqual(s21_ms, std_ms));
  }
  {
    s21::multiset<int> s21_ms = {69};
    std::multiset<int> std_ms = {69};

    s21_ms = std::move(s21_ms_rnd);
    std_ms = std::move(std_ms_rnd);

    EXPECT_TRUE(MultisetsAreEqual(s21_ms, std_ms));
  }
}

TEST_F(MultisetTest, Iterator) {
  {
    auto s21_it = s21_ms_rnd.begin();
    auto std_it = std_ms_rnd.begin();
    MoveForwardBackward(s21_it, std_it);
  }
  {
    auto s21_it = s21_ms_rnd.end();
    auto std_it = std_ms_rnd.end();
    MoveBackwardForward(s21_it, std_it);
  }
  {
    auto s21_it = s21_ms_rnd.rbegin();
    auto std_it = std_ms_rnd.rbegin();
    MoveForwardBackward(s21_it, std_it);
  }
  {
    auto s21_it = s21_ms_rnd.rend();
    auto std_it = std_ms_rnd.rend();
    MoveBackwardForward(s21_it, std_it);
  }
  {
    auto s21_it = s21_ms_rnd.cbegin();
    auto std_it = std_ms_rnd.cbegin();
    MoveForwardBackward(s21_it, std_it);
  }
  {
    auto s21_it = s21_ms_rnd.cend();
    auto std_it = std_ms_rnd.cend();
    MoveBackwardForward(s21_it, std_it);
  }
  {
    auto s21_it = s21_ms_rnd.crbegin();
    auto std_it = std_ms_rnd.crbegin();
    MoveForwardBackward(s21_it, std_it);
  }
  {
    auto s21_it = s21_ms_rnd.crend();
    auto std_it = std_ms_rnd.crend();
    MoveBackwardForward(s21_it, std_it);
  }
  {
    s21::multiset<int> s21_ms;
    std::multiset<int> std_ms;

    for (auto i = 2; i < 100000; ++i) {
      auto s21_it = s21_ms.insert(i);
      auto std_it = std_ms.insert(i);

      EXPECT_EQ(*s21_it, *std_it);
    }

    for (auto i = 2; i < 1000; i++) {
      auto it_s21 = s21_ms.begin();
      auto it_std = std_ms.begin();
      while (it_s21 != s21_ms.end()) {
        if (*it_s21 % i == 0) {
          s21_ms.erase(it_s21++);
          std_ms.erase(it_std++);
        } else {
          ++it_s21;
          ++it_std;
        }
      }
    }

    EXPECT_TRUE(MultisetsAreEqual(s21_ms, std_ms));
  }
}

TEST_F(MultisetTest, Capacity) {
  {
    s21::multiset<int> s21_ms;
    std::multiset<int> std_ms;
    EXPECT_EQ(s21_ms.empty(), std_ms.empty());
    EXPECT_EQ(s21_ms.size(), std_ms.size());
    // EXPECT_EQ(s21_ms.max_size(), std_ms.max_size());
  }
  {
    s21::multiset<int> s21_ms = {10};
    std::multiset<int> std_ms = {10};
    EXPECT_EQ(s21_ms.empty(), std_ms.empty());
    EXPECT_EQ(s21_ms.size(), std_ms.size());
    // EXPECT_EQ(s21_ms.max_size(), std_ms.max_size());
  }
  {
    EXPECT_EQ(s21_ms_rnd.empty(), std_ms_rnd.empty());
    EXPECT_EQ(s21_ms_rnd.size(), std_ms_rnd.size());
    // EXPECT_EQ(s21_ms_rnd.max_size(), std_ms_rnd.max_size());
  }
  {
    EXPECT_EQ(s21_ms_static.empty(), s21_ms_static.empty());
    EXPECT_EQ(s21_ms_static.size(), s21_ms_static.size());
    // EXPECT_EQ(cms21.max_size(), cmstd.max_size());
  }
}

TEST_F(MultisetTest, Clear) {
  {
    s21::multiset<int> s21_ms;
    std::multiset<int> std_ms;
    s21_ms.clear();
    std_ms.clear();
    EXPECT_EQ(s21_ms.empty(), std_ms.empty());
    EXPECT_EQ(s21_ms.size(), std_ms.size());
    EXPECT_TRUE(MultisetsAreEqual(s21_ms, std_ms));
  }
  {
    auto s21_ms = s21_ms_rnd;
    auto std_ms = std_ms_rnd;
    s21_ms.clear();
    std_ms.clear();
    EXPECT_EQ(s21_ms.empty(), std_ms.empty());
    EXPECT_EQ(s21_ms.size(), std_ms.size());
    EXPECT_TRUE(MultisetsAreEqual(s21_ms, std_ms));
  }
}

TEST_F(MultisetTest, Insert) {
  {
    s21::multiset<int> s21_ms;
    std::multiset<int> std_ms;
    for (auto i = 0; i < 10000; ++i) {
      auto key = rand() % 1000;
      auto s21_e = s21_ms.insert(key);
      auto std_e = std_ms.insert(key);
      EXPECT_EQ(*s21_e, *std_e);
    }
    EXPECT_TRUE(MultisetsAreEqual(s21_ms, std_ms));
  }
}

TEST_F(MultisetTest, InsertMany) {
  {
    s21::multiset<int> s21_ms;
    std::multiset<int> std_ms;

    s21_ms.insert_many(10, 20, 30, 40, 30, 20, 10);
    std_ms.insert({10, 20, 30, 40, 30, 20, 10});
    EXPECT_TRUE(MultisetsAreEqual(s21_ms, std_ms));
  }
  {
    s21::multiset<int> s21_ms = {10, 20};
    std::multiset<int> std_ms = {10, 20};

    s21_ms.insert_many(50, 30, 30, 40);
    std_ms.insert({50, 30, 30, 40});
    EXPECT_TRUE(MultisetsAreEqual(s21_ms, std_ms));
  }
  {
    s21::multiset<int> s21_ms = {10, 20};
    std::multiset<int> std_ms = {10, 20};

    s21_ms.insert_many(10, 20);
    std_ms.insert({10, 20});
    EXPECT_TRUE(MultisetsAreEqual(s21_ms, std_ms));
  }
}

TEST_F(MultisetTest, Erase) {
  {
    s21_ms_rnd.erase(s21_ms_rnd.begin());
    std_ms_rnd.erase(std_ms_rnd.begin());
    EXPECT_TRUE(MultisetsAreEqual(s21_ms_rnd, std_ms_rnd));

    s21_ms_rnd.erase(--s21_ms_rnd.end());
    std_ms_rnd.erase(--std_ms_rnd.end());
    EXPECT_TRUE(MultisetsAreEqual(s21_ms_rnd, std_ms_rnd));

    s21_ms_rnd.erase(++s21_ms_rnd.begin());
    std_ms_rnd.erase(++std_ms_rnd.begin());
    EXPECT_TRUE(MultisetsAreEqual(s21_ms_rnd, std_ms_rnd));

    s21_ms_rnd.erase(--(--s21_ms_rnd.end()));
    std_ms_rnd.erase(--(--std_ms_rnd.end()));
    EXPECT_TRUE(MultisetsAreEqual(s21_ms_rnd, std_ms_rnd));

    auto s21_it = s21_ms_rnd.end();
    auto std_it = std_ms_rnd.end();
    for (int i = 0; i < 111; ++i, --s21_it, --std_it) {
    }
    s21_ms_rnd.erase(s21_it);
    std_ms_rnd.erase(std_it);
    EXPECT_TRUE(MultisetsAreEqual(s21_ms_rnd, std_ms_rnd));

    s21_it = s21_ms_rnd.begin();
    std_it = std_ms_rnd.begin();
    for (int i = 0; i < 111; ++i, ++s21_it, ++std_it) {
    }
    s21_ms_rnd.erase(s21_it);
    std_ms_rnd.erase(std_it);
    EXPECT_TRUE(MultisetsAreEqual(s21_ms_rnd, std_ms_rnd));
  }
  {
    s21::multiset<int> s21_ms = {10};
    std::multiset<int> std_ms = {10};
    s21_ms.erase(s21_ms.begin());
    std_ms.erase(std_ms.begin());
    EXPECT_TRUE(MultisetsAreEqual(s21_ms, std_ms));
  }
  {
    auto s21_ms = s21_ms_static;
    auto std_ms = std_ms_static;
    s21_ms.erase(s21_ms.find(70));
    std_ms.erase(std_ms.find(70));
    EXPECT_TRUE(MultisetsAreEqual(s21_ms, std_ms));
  }
  {
    auto s21_ms = s21_ms_static;
    auto std_ms = std_ms_static;
    s21_ms.erase(s21_ms.find(30));
    std_ms.erase(std_ms.find(30));
    EXPECT_TRUE(MultisetsAreEqual(s21_ms, std_ms));
  }
  {
    auto s21_ms = s21_ms_static;
    auto std_ms = std_ms_static;
    s21_ms.insert(45);
    std_ms.insert(45);
    s21_ms.erase(s21_ms.find(40));
    std_ms.erase(std_ms.find(40));
    EXPECT_TRUE(MultisetsAreEqual(s21_ms, std_ms));
  }
  {
    auto s21_ms = s21_ms_static;
    auto std_ms = std_ms_static;
    s21_ms.erase(s21_ms.find(90));
    std_ms.erase(std_ms.find(90));
    EXPECT_TRUE(MultisetsAreEqual(s21_ms, std_ms));
  }
  {
    auto s21_ms = s21_ms_static;
    auto std_ms = std_ms_static;
    s21_ms.erase(s21_ms.find(100));
    std_ms.erase(std_ms.find(100));
    s21_ms.erase(s21_ms.find(90));
    std_ms.erase(std_ms.find(90));
    EXPECT_TRUE(MultisetsAreEqual(s21_ms, std_ms));
  }
  {
    auto s21_ms = s21_ms_static;
    auto std_ms = std_ms_static;
    s21_ms.erase(s21_ms.find(100));
    std_ms.erase(std_ms.find(100));
    s21_ms.erase(s21_ms.find(90));
    std_ms.erase(std_ms.find(90));
    s21_ms.erase(s21_ms.find(40));
    std_ms.erase(std_ms.find(40));
    s21_ms.erase(s21_ms.find(110));
    std_ms.erase(std_ms.find(110));
    EXPECT_TRUE(MultisetsAreEqual(s21_ms, std_ms));
  }
  {
    auto std_ms_rnd_copy = std_ms_rnd;
    int i = 0;
    for (auto elem : std_ms_rnd_copy) {
      if (i++ % 3 == 0) {
        s21_ms_rnd.erase(s21_ms_rnd.find(elem));
        std_ms_rnd.erase(std_ms_rnd.find(elem));
      }
    }
    EXPECT_TRUE(MultisetsAreEqual(s21_ms_rnd, std_ms_rnd));
  }
}

TEST_F(MultisetTest, Swap) {
  {
    s21::multiset<int> s21_ms1, s21_ms2;
    std::multiset<int> std_ms1, std_ms2;
    s21_ms1.swap(s21_ms2);
    std_ms1.swap(std_ms2);
    EXPECT_TRUE(MultisetsAreEqual(s21_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(s21_ms2, std_ms2));
  }
  {
    s21::multiset<int> s21_ms1;
    s21::multiset<int> s21_ms2 = {1};
    std::multiset<int> std_ms1;
    std::multiset<int> std_ms2 = {1};
    s21_ms1.swap(s21_ms2);
    std_ms1.swap(std_ms2);
    EXPECT_TRUE(MultisetsAreEqual(s21_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(s21_ms2, std_ms2));
    s21_ms2.swap(s21_ms1);
    std_ms2.swap(std_ms1);
    EXPECT_TRUE(MultisetsAreEqual(s21_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(s21_ms2, std_ms2));
  }
  {
    s21_ms_static.swap(s21_ms_rnd);
    std_ms_static.swap(std_ms_rnd);
    EXPECT_TRUE(MultisetsAreEqual(s21_ms_rnd, std_ms_rnd));
    EXPECT_TRUE(MultisetsAreEqual(s21_ms_static, std_ms_static));
  }
}

TEST_F(MultisetTest, Merge) {
  {
    s21::multiset<int> s21_ms1, s21_ms2;
    std::multiset<int> std_ms1, std_ms2;
    s21_ms1.merge(s21_ms2);
    std_ms1.merge(std_ms2);
    EXPECT_TRUE(MultisetsAreEqual(s21_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(s21_ms2, std_ms2));
  }
  {
    s21::multiset<int> s21_ms1 = {1};
    s21::multiset<int> s21_ms2;
    std::multiset<int> std_ms1 = {1};
    std::multiset<int> std_ms2;
    s21_ms1.merge(s21_ms2);
    std_ms1.merge(std_ms2);
    EXPECT_TRUE(MultisetsAreEqual(s21_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(s21_ms2, std_ms2));
  }
  {
    s21::multiset<int> s21_ms1;
    s21::multiset<int> s21_ms2 = {1};
    std::multiset<int> std_ms1;
    std::multiset<int> std_ms2 = {1};
    s21_ms1.merge(s21_ms2);
    std_ms1.merge(std_ms2);
    EXPECT_TRUE(MultisetsAreEqual(s21_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(s21_ms2, std_ms2));
  }
  {
    s21::multiset<int> s21_ms1 = {2};
    s21::multiset<int> s21_ms2 = {1};
    std::multiset<int> std_ms1 = {2};
    std::multiset<int> std_ms2 = {1};
    s21_ms1.merge(s21_ms2);
    std_ms1.merge(std_ms2);
    EXPECT_TRUE(MultisetsAreEqual(s21_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(s21_ms2, std_ms2));
  }
  {
    s21::multiset<int> s21_ms1 = {1, 2};
    s21::multiset<int> s21_ms2 = {1};
    std::multiset<int> std_ms1 = {1, 2};
    std::multiset<int> std_ms2 = {1};
    s21_ms1.merge(s21_ms2);
    std_ms1.merge(std_ms2);
    EXPECT_TRUE(MultisetsAreEqual(s21_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(s21_ms2, std_ms2));
  }
  {
    s21::multiset<int> s21_ms1 = {1, 2};
    s21::multiset<int> s21_ms2 = {1, 3};
    std::multiset<int> std_ms1 = {1, 2};
    std::multiset<int> std_ms2 = {1, 3};
    s21_ms1.merge(s21_ms2);
    std_ms1.merge(std_ms2);
    EXPECT_TRUE(MultisetsAreEqual(s21_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(s21_ms2, std_ms2));
  }
  {
    s21::multiset<int> s21_ms1 = {1, 2, 0, -1, 2};
    s21::multiset<int> s21_ms2 = {1, 3, 2, 4, 5};
    std::multiset<int> std_ms1 = {1, 2, 0, -1, 2};
    std::multiset<int> std_ms2 = {1, 3, 2, 4, 5};
    s21_ms1.merge(s21_ms2);
    std_ms1.merge(std_ms2);
    EXPECT_TRUE(MultisetsAreEqual(s21_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(s21_ms2, std_ms2));
  }
  {
    s21::multiset<int> s21_ms;
    std::multiset<int> std_ms;
    for (int i = 0; i < 100000; ++i) {
      auto key = rand() % 100000;
      s21_ms.insert(key);
      std_ms.insert(key);
    }
    s21_ms.merge(s21_ms_rnd);
    std_ms.merge(std_ms_rnd);
    EXPECT_TRUE(MultisetsAreEqual(s21_ms, std_ms));
    EXPECT_TRUE(MultisetsAreEqual(s21_ms_rnd, std_ms_rnd));
  }
}

TEST_F(MultisetTest, Lookup) {
  {
    EXPECT_TRUE(s21_ms_static.contains(70));
    EXPECT_TRUE(s21_ms_static.contains(30));
    EXPECT_TRUE(s21_ms_static.contains(40));
    EXPECT_FALSE(s21_ms_static.contains(1));
    EXPECT_FALSE(s21_ms_static.contains(65));
    EXPECT_FALSE(s21_ms_static.contains(200));
  }
  {
    s21::multiset<int> s21_ms;
    EXPECT_FALSE(s21_ms.contains(1));
  }
  {
    const s21::multiset<int> s21_ms = s21_ms_static;
    const std::multiset<int> std_ms = std_ms_static;
    EXPECT_TRUE(*s21_ms.find(100) == 100);
    EXPECT_TRUE(*std_ms.find(100) == 100);
    EXPECT_TRUE(s21_ms.find(1000) == s21_ms.cend());
    EXPECT_TRUE(std_ms.find(1000) == std_ms.cend());
  }
}

TEST_F(MultisetTest, Bounds) {
  {
    const s21::multiset<int> s21_ms;
    const std::multiset<int> std_ms;
    auto s21_it_lower = s21_ms.lower_bound(10);
    auto s21_it_upper = s21_ms.upper_bound(10);
    auto std_it_lower = std_ms.lower_bound(10);
    auto std_it_upper = std_ms.upper_bound(10);
    EXPECT_TRUE(s21_it_lower == s21_ms.cend());
    EXPECT_TRUE(s21_it_upper == s21_ms.cend());
    EXPECT_TRUE(std_it_lower == std_ms.cend());
    EXPECT_TRUE(std_it_upper == std_ms.cend());
  }
  {
    const s21::multiset<int> s21_ms = {10};
    const std::multiset<int> std_ms = {10};
    auto s21_it_lower = s21_ms.lower_bound(10);
    auto s21_it_upper = s21_ms.upper_bound(10);
    auto std_it_lower = std_ms.lower_bound(10);
    auto std_it_upper = std_ms.upper_bound(10);
    EXPECT_EQ(*s21_it_lower, *std_it_lower);
    EXPECT_TRUE(s21_it_upper == s21_ms.cend());
    EXPECT_TRUE(std_it_upper == std_ms.cend());
  }
  {
    const s21::multiset<int> s21_ms = {11};
    const std::multiset<int> std_ms = {11};
    auto s21_it_lower = s21_ms.lower_bound(10);
    auto s21_it_upper = s21_ms.upper_bound(10);
    auto std_it_lower = std_ms.lower_bound(10);
    auto std_it_upper = std_ms.upper_bound(10);
    EXPECT_EQ(*s21_it_lower, *std_it_lower);
    EXPECT_EQ(*s21_it_upper, *std_it_upper);
  }
  {
    const s21::multiset<int> s21_ms = {11};
    const std::multiset<int> std_ms = {11};
    auto s21_it_lower = s21_ms.lower_bound(12);
    auto s21_it_upper = s21_ms.upper_bound(12);
    auto std_it_lower = std_ms.lower_bound(12);
    auto std_it_upper = std_ms.upper_bound(12);
    EXPECT_TRUE(s21_it_lower == s21_ms.cend());
    EXPECT_TRUE(std_it_lower == std_ms.cend());
    EXPECT_TRUE(s21_it_upper == s21_ms.cend());
    EXPECT_TRUE(std_it_upper == std_ms.cend());
  }
  {
    const s21::multiset<int> s21_ms = {10, 12, 11, 10, 11, 12,
                                       12, 10, 11, 12, 11, 10};
    const std::multiset<int> std_ms = {10, 12, 11, 10, 11, 12,
                                       12, 10, 11, 12, 11, 10};
    auto s21_it_lower = s21_ms.lower_bound(10);
    auto s21_it_upper = s21_ms.upper_bound(11);
    auto std_it_lower = std_ms.lower_bound(10);
    auto std_it_upper = std_ms.upper_bound(11);
    EXPECT_EQ(*s21_it_upper, *std_it_upper);
    EXPECT_EQ(*s21_it_lower, *std_it_lower);
  }
  {
    for (int i = 0; i < 2000; ++i) {
      int key = rand() % 1000;
      auto s21_it_lower = s21_ms_rnd.lower_bound(key);
      auto std_it_lower = std_ms_rnd.lower_bound(key);
      auto s21_it_upper = s21_ms_rnd.upper_bound(key);
      auto std_it_upper = std_ms_rnd.upper_bound(key);
      if (std_it_lower != std_ms_rnd.end()) {
        EXPECT_EQ(*s21_it_lower, *std_it_lower);
      } else {
        EXPECT_TRUE(s21_it_lower == s21_ms_rnd.end());
      }
      if (std_it_upper != std_ms_rnd.end()) {
        EXPECT_EQ(*s21_it_upper, *std_it_upper);
      } else {
        EXPECT_TRUE(s21_it_upper == s21_ms_rnd.end());
      }
    }
  }
}

TEST_F(MultisetTest, Count) {
  {
    const s21::multiset<int> s21_ms;
    const std::multiset<int> std_ms;
    EXPECT_TRUE(s21_ms.count(10) == std_ms.count(10));
  }
  {
    const s21::multiset<int> s21_ms = {10};
    const std::multiset<int> std_ms = {10};
    EXPECT_TRUE(s21_ms.count(10) == std_ms.count(10));
  }
  {
    const s21::multiset<int> s21_ms = {11};
    const std::multiset<int> std_ms = {11};
    EXPECT_TRUE(s21_ms.count(10) == std_ms.count(10));
  }
  {
    const s21::multiset<int> s21_ms = {11, 11, 11, 10, 11, 11, 11};
    const std::multiset<int> std_ms = {11, 11, 11, 10, 11, 11, 11};
    EXPECT_TRUE(s21_ms.count(11) == std_ms.count(11));
  }
  {
    const s21::multiset<int> s21_ms = {10, 12, 11, 10, 11, 12,
                                       12, 10, 11, 12, 11, 10};
    const std::multiset<int> std_ms = {10, 12, 11, 10, 11, 12,
                                       12, 10, 11, 12, 11, 10};
    EXPECT_TRUE(s21_ms.count(10) == std_ms.count(10));
    EXPECT_TRUE(s21_ms.count(11) == std_ms.count(11));
    EXPECT_TRUE(s21_ms.count(12) == std_ms.count(12));
  }
  {
    for (int i = 0; i < 2000; ++i) {
      int key = rand() % 1000;
      EXPECT_TRUE(s21_ms_rnd.count(key) == std_ms_rnd.count(key));
    }
  }
}

TEST_F(MultisetTest, EqualRange) {
  {
    const s21::multiset<int> s21_ms;
    const std::multiset<int> std_ms;
    auto s21_its = s21_ms.equal_range(10);
    auto std_its = std_ms.equal_range(10);
    EXPECT_TRUE(
        equal(s21_its.first, s21_its.second, std_its.first, std_its.second));
  }
  {
    const s21::multiset<int> s21_ms = {10};
    const std::multiset<int> std_ms = {10};
    auto s21_its = s21_ms.equal_range(10);
    auto std_its = std_ms.equal_range(10);
    EXPECT_TRUE(
        equal(s21_its.first, s21_its.second, std_its.first, std_its.second));
  }
  {
    const s21::multiset<int> s21_ms = {11};
    const std::multiset<int> std_ms = {11};
    auto s21_its = s21_ms.equal_range(10);
    auto std_its = std_ms.equal_range(10);
    EXPECT_TRUE(
        equal(s21_its.first, s21_its.second, std_its.first, std_its.second));
  }
  {
    const s21::multiset<int> s21_ms = {11, 11, 11, 10, 11, 11, 11};
    const std::multiset<int> std_ms = {11, 11, 11, 10, 11, 11, 11};
    auto s21_its = s21_ms.equal_range(11);
    auto std_its = std_ms.equal_range(11);
    EXPECT_TRUE(
        equal(s21_its.first, s21_its.second, std_its.first, std_its.second));
  }
  {
    const s21::multiset<int> s21_ms = {10, 12, 11, 10, 11, 12,
                                       12, 10, 11, 12, 11, 10};
    const std::multiset<int> std_ms = {10, 12, 11, 10, 11, 12,
                                       12, 10, 11, 12, 11, 10};
    auto s21_its = s21_ms.equal_range(10);
    auto std_its = std_ms.equal_range(10);
    EXPECT_TRUE(
        equal(s21_its.first, s21_its.second, std_its.first, std_its.second));
  }
  {
    for (int i = 0; i < 2000; ++i) {
      int key = rand() % 1000;
      auto s21_its = s21_ms_rnd.equal_range(key);
      auto std_its = std_ms_rnd.equal_range(key);
      EXPECT_TRUE(
          equal(s21_its.first, s21_its.second, std_its.first, std_its.second));
    }
  }
}
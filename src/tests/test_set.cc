#include "test.h"

TEST_F(SetTest, DefaultCtor) {
  {
    s21::set<int> s21_s;
    EXPECT_TRUE(s21_s.empty());
    EXPECT_EQ(s21_s.size(), 0);
  }
  {
    const s21::set<int> s21_s;
    EXPECT_TRUE(s21_s.empty());
    EXPECT_EQ(s21_s.size(), 0);
  }
}

TEST_F(SetTest, InitializeCtor) {
  {
    s21::set<int> s21_s = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::set<int> std_s = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    EXPECT_TRUE(SetsAreEqual(s21_s, std_s));
  }
  {
    const s21::set<int> s21_s = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    const std::set<int> std_s = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    EXPECT_TRUE(SetsAreEqual(s21_s, std_s));
  }
}

TEST_F(SetTest, CopyCtor) {
  {
    s21::set<int> s21_s1;
    s21::set<int> s21_s2(s21_s1);
    std::set<int> std_s1;
    std::set<int> std_s2(std_s1);

    EXPECT_TRUE(SetsAreEqual(s21_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(s21_s2, std_s2));
  }
  {
    const s21::set<int> s21_s1;
    const s21::set<int> s21_s2(s21_s1);
    const std::set<int> std_s1;
    const std::set<int> std_s2(std_s1);

    EXPECT_TRUE(SetsAreEqual(s21_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(s21_s2, std_s2));
  }
  {
    s21::set<int> s21_s1 = {10};
    s21::set<int> s21_s2(s21_s1);
    std::set<int> std_s1 = {10};
    std::set<int> std_s2(std_s1);
    EXPECT_TRUE(SetsAreEqual(s21_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(s21_s2, std_s2));
  }
  {
    const s21::set<int> s21_s1 = {10};
    const s21::set<int> s21_s2(s21_s1);
    const std::set<int> std_s1 = {10};
    const std::set<int> std_s2(std_s1);

    EXPECT_TRUE(SetsAreEqual(s21_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(s21_s2, std_s2));
  }
  {
    s21::set<int> s21_s(s21_s_rnd);
    std::set<int> std_s(std_s_rnd);

    EXPECT_TRUE(SetsAreEqual(s21_s, std_s));
  }
  {
    const s21::set<int> s21_s(s21_s_rnd);
    const std::set<int> std_s(std_s_rnd);

    EXPECT_TRUE(SetsAreEqual(s21_s, std_s));
  }
}

TEST_F(SetTest, MoveCtor) {
  {
    s21::set<int> s21_s1;
    s21::set<int> s21_s2(std::move(s21_s1));
    std::set<int> std_s1;
    std::set<int> std_s2(std::move(std_s1));

    EXPECT_TRUE(SetsAreEqual(s21_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(s21_s2, std_s2));
  }
  {
    const s21::set<int> s21_s1;
    const s21::set<int> s21_s2(std::move(s21_s1));
    const std::set<int> std_s1;
    const std::set<int> std_s2(std::move(std_s1));

    EXPECT_TRUE(SetsAreEqual(s21_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(s21_s2, std_s2));
  }
  {
    s21::set<int> s21_s1 = {1};
    s21::set<int> s21_s2(std::move(s21_s1));
    std::set<int> std_s1 = {1};
    std::set<int> std_s2(std::move(std_s1));

    EXPECT_TRUE(SetsAreEqual(s21_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(s21_s2, std_s2));
  }
  {
    const s21::set<int> s21_s1 = {1};
    const s21::set<int> s21_s2(std::move(s21_s1));
    const std::set<int> std_s1 = {1};
    const std::set<int> std_s2(std::move(std_s1));

    EXPECT_TRUE(SetsAreEqual(s21_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(s21_s2, std_s2));
  }
  {
    s21::set<int> s21_s(std::move(s21_s_rnd));
    std::set<int> std_s(std::move(std_s_rnd));

    EXPECT_TRUE(SetsAreEqual(s21_s, std_s));
  }
  {
    const s21::set<int> s21_s(std::move(s21_s_rnd));
    const std::set<int> std_s(std::move(std_s_rnd));

    EXPECT_TRUE(SetsAreEqual(s21_s, std_s));
  }
}

TEST_F(SetTest, AssignmentOperator) {
  {
    s21::set<int> s21_s1, s21_s2;
    std::set<int> std_s1, std_s2;

    s21_s2 = s21_s1;
    std_s2 = std_s1;

    EXPECT_TRUE(SetsAreEqual(s21_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(s21_s2, std_s2));
  }
  {
    const s21::set<int> s21_s1;
    const std::set<int> std_s1;
    s21::set<int> s21_s2;
    std::set<int> std_s2;

    s21_s2 = s21_s1;
    std_s2 = std_s1;

    EXPECT_TRUE(SetsAreEqual(s21_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(s21_s2, std_s2));
  }
  {
    s21::set<int> s21_s1, s21_s2;
    std::set<int> std_s1, std_s2;

    s21_s2 = std::move(s21_s1);
    std_s2 = std::move(std_s1);

    EXPECT_TRUE(SetsAreEqual(s21_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(s21_s2, std_s2));
  }
  {
    const s21::set<int> s21_s1;
    const std::set<int> std_s1;
    s21::set<int> s21_s2;
    std::set<int> std_s2;

    s21_s2 = std::move(s21_s1);
    std_s2 = std::move(std_s1);

    EXPECT_TRUE(SetsAreEqual(s21_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(s21_s2, std_s2));
  }
  {
    s21::set<int> s21_s1 = {10};
    s21::set<int> s21_s2;
    std::set<int> std_s1 = {10};
    std::set<int> std_s2;

    s21_s2 = s21_s1;
    std_s2 = std_s1;

    EXPECT_TRUE(SetsAreEqual(s21_s1, std_s2));
    EXPECT_TRUE(SetsAreEqual(s21_s1, std_s2));
  }
  {
    const s21::set<int> s21_s1 = {10};
    s21::set<int> s21_s2;
    const std::set<int> std_s1 = {10};
    std::set<int> std_s2;

    s21_s2 = s21_s1;
    std_s2 = std_s1;

    EXPECT_TRUE(SetsAreEqual(s21_s1, std_s2));
    EXPECT_TRUE(SetsAreEqual(s21_s1, std_s2));
  }
  {
    s21::set<int> s21_s1 = {10};
    s21::set<int> s21_s2;
    std::set<int> std_s1 = {10};
    std::set<int> std_s2;

    s21_s2 = std::move(s21_s1);
    std_s2 = std::move(std_s1);

    EXPECT_TRUE(SetsAreEqual(s21_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(s21_s2, std_s2));
  }
  {
    const s21::set<int> s21_s1 = {10};
    s21::set<int> s21_s2;
    const std::set<int> std_s1 = {10};
    std::set<int> std_s2;

    s21_s2 = std::move(s21_s1);
    std_s2 = std::move(std_s1);

    EXPECT_TRUE(SetsAreEqual(s21_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(s21_s2, std_s2));
  }
  {
    s21::set<int> s21_s1 = {69, 25, 51};
    s21::set<int> s21_s2 = {69};
    std::set<int> std_s1 = {69, 25, 51};
    std::set<int> std_s2 = {69};

    s21_s2 = s21_s1;
    std_s2 = std_s1;

    EXPECT_TRUE(SetsAreEqual(s21_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(s21_s2, std_s2));
  }
  {
    const s21::set<int> s21_s1 = {69, 25, 51};
    s21::set<int> s21_s2 = {69};
    const std::set<int> std_s1 = {69, 25, 51};
    std::set<int> std_s2 = {69};

    s21_s2 = s21_s1;
    std_s2 = std_s1;

    EXPECT_TRUE(SetsAreEqual(s21_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(s21_s2, std_s2));
  }
  {
    s21::set<int> s21_s1 = {69, 25, 51};
    s21::set<int> s21_s2 = {69};
    std::set<int> std_s1 = {69, 25, 51};
    std::set<int> std_s2 = {69};

    s21_s2 = std::move(s21_s1);
    std_s2 = std::move(std_s1);

    EXPECT_TRUE(SetsAreEqual(s21_s2, std_s2));
  }
  {
    const s21::set<int> s21_s1 = {69, 25, 51};
    s21::set<int> s21_s2 = {69};
    const std::set<int> std_s1 = {69, 25, 51};
    std::set<int> std_s2 = {69};

    s21_s2 = std::move(s21_s1);
    std_s2 = std::move(std_s1);

    EXPECT_TRUE(SetsAreEqual(s21_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(s21_s2, std_s2));
  }
  {
    s21::set<int> s21_s = {69};
    std::set<int> std_s = {69};

    s21_s = s21_s_rnd;
    std_s = std_s_rnd;

    EXPECT_TRUE(SetsAreEqual(s21_s, std_s));
  }
  {
    s21::set<int> s21_s = {69};
    std::set<int> std_s = {69};

    s21_s = std::move(s21_s_rnd);
    std_s = std::move(std_s_rnd);

    EXPECT_TRUE(SetsAreEqual(s21_s, std_s));
  }
}

TEST_F(SetTest, Iterator) {
  {
    auto s21_it = s21_s_rnd.begin();
    auto std_it = std_s_rnd.begin();
    MoveForwardBackward(s21_it, std_it);
  }
  {
    const auto s21_s = s21_s_rnd;
    const auto std_s = std_s_rnd;
    auto s21_it = s21_s.begin();
    auto std_it = std_s.begin();
    MoveForwardBackward(s21_it, std_it);
  }
  {
    auto s21_it = s21_s_rnd.end();
    auto std_it = std_s_rnd.end();
    MoveBackwardForward(s21_it, std_it);
  }
  {
    const auto s21_s = s21_s_rnd;
    const auto std_s = std_s_rnd;
    auto s21_it = s21_s.end();
    auto std_it = std_s.end();
    MoveBackwardForward(s21_it, std_it);
  }
  {
    auto s21_it = s21_s_rnd.rbegin();
    auto std_it = std_s_rnd.rbegin();
    MoveForwardBackward(s21_it, std_it);
  }
  {
    const auto s21_s = s21_s_rnd;
    const auto std_s = std_s_rnd;
    auto s21_it = s21_s.rbegin();
    auto std_it = std_s.rbegin();
    MoveForwardBackward(s21_it, std_it);
  }
  {
    auto s21_it = s21_s_rnd.rend();
    auto std_it = std_s_rnd.rend();
    MoveBackwardForward(s21_it, std_it);
  }
  {
    const auto s21_s = s21_s_rnd;
    const auto std_s = std_s_rnd;
    auto s21_it = s21_s.rend();
    auto std_it = std_s.rend();
    MoveBackwardForward(s21_it, std_it);
  }
  {
    auto s21_it = s21_s_rnd.cbegin();
    auto std_it = std_s_rnd.cbegin();
    MoveForwardBackward(s21_it, std_it);
  }
  {
    auto s21_it = s21_s_rnd.cend();
    auto std_it = std_s_rnd.cend();
    MoveBackwardForward(s21_it, std_it);
  }
  {
    auto s21_it = s21_s_rnd.crbegin();
    auto std_it = std_s_rnd.crbegin();
    MoveForwardBackward(s21_it, std_it);
  }
  {
    auto s21_it = s21_s_rnd.crend();
    auto std_it = std_s_rnd.crend();
    MoveBackwardForward(s21_it, std_it);
  }
  {
    s21::set<int> s21_s;
    std::set<int> std_s;

    for (auto i = 2; i < 100000; ++i) {
      auto s21_it = s21_s.insert(i);
      auto std_it = std_s.insert(i);

      EXPECT_EQ(*s21_it.first, *std_it.first);
      EXPECT_EQ(s21_it.second, std_it.second);
    }

    for (auto i = 2; i < 1000; i++) {
      auto it_s21 = s21_s.begin();
      auto it_std = std_s.begin();
      while (it_s21 != s21_s.end()) {
        if (*it_s21 % i == 0) {
          s21_s.erase(it_s21++);
          std_s.erase(it_std++);
        } else {
          ++it_s21;
          ++it_std;
        }
      }
    }

    EXPECT_TRUE(SetsAreEqual(s21_s, std_s));
  }
}

TEST_F(SetTest, Capacity) {
  {
    s21::set<int> s21_s;
    std::set<int> std_s;
    EXPECT_EQ(s21_s.empty(), std_s.empty());
    EXPECT_EQ(s21_s.size(), std_s.size());
    EXPECT_DOUBLE_EQ(static_cast<double>(std_s.max_size()) / s21_s.max_size(),
                     max_size_ratio);
  }
  {
    s21::set<int> s21_s = {10};
    std::set<int> std_s = {10};
    EXPECT_EQ(s21_s.empty(), std_s.empty());
    EXPECT_EQ(s21_s.size(), std_s.size());
    EXPECT_DOUBLE_EQ(static_cast<double>(std_s.max_size()) / s21_s.max_size(),
                     max_size_ratio);
  }
  {
    EXPECT_EQ(s21_s_rnd.empty(), std_s_rnd.empty());
    EXPECT_EQ(s21_s_rnd.size(), std_s_rnd.size());
    EXPECT_DOUBLE_EQ(
        static_cast<double>(std_s_rnd.max_size()) / s21_s_rnd.max_size(),
        max_size_ratio);
  }
  {
    EXPECT_EQ(s21_s_static.empty(), s21_s_static.empty());
    EXPECT_EQ(s21_s_static.size(), s21_s_static.size());
    EXPECT_DOUBLE_EQ(
        static_cast<double>(std_s_static.max_size()) / s21_s_static.max_size(),
        max_size_ratio);
  }
}

TEST_F(SetTest, Clear) {
  {
    s21::set<int> s21_s;
    std::set<int> std_s;
    s21_s.clear();
    std_s.clear();
    EXPECT_EQ(s21_s.empty(), std_s.empty());
    EXPECT_EQ(s21_s.size(), std_s.size());
    EXPECT_TRUE(SetsAreEqual(s21_s, std_s));
  }
  {
    auto s21_s = s21_s_rnd;
    auto std_s = std_s_rnd;
    s21_s.clear();
    std_s.clear();
    EXPECT_EQ(s21_s.empty(), std_s.empty());
    EXPECT_EQ(s21_s.size(), std_s.size());
    EXPECT_TRUE(SetsAreEqual(s21_s, std_s));
  }
}

TEST_F(SetTest, Insert) {
  {
    s21::set<int> s21_s;
    std::set<int> std_s;
    for (auto i = 0; i < 10000; ++i) {
      auto key = rand() % 1000000;
      auto s21_e = s21_s.insert(key);
      auto std_e = std_s.insert(key);
      EXPECT_EQ(*s21_e.first, *std_e.first);
      EXPECT_EQ(s21_e.second, std_e.second);
    }
    EXPECT_TRUE(SetsAreEqual(s21_s, std_s));
  }
}

TEST_F(SetTest, InsertMany) {
  {
    s21::set<int> s21_s;
    std::set<int> std_s;

    s21_s.insert_many(10, 20, 30, 40);
    std_s.insert({10, 20, 30, 40});
    EXPECT_TRUE(SetsAreEqual(s21_s, std_s));
  }
  {
    s21::set<int> s21_s = {10, 20};
    std::set<int> std_s = {10, 20};

    s21_s.insert_many(50, 30, 30, 40);
    std_s.insert({50, 30, 30, 40});
    EXPECT_TRUE(SetsAreEqual(s21_s, std_s));
  }
  {
    s21::set<int> s21_s = {10, 20};
    std::set<int> std_s = {10, 20};

    s21_s.insert_many(10, 20);
    std_s.insert({10, 20});
    EXPECT_TRUE(SetsAreEqual(s21_s, std_s));
  }
}

TEST_F(SetTest, Erase) {
  {
    s21_s_rnd.erase(s21_s_rnd.begin());
    std_s_rnd.erase(std_s_rnd.begin());
    EXPECT_TRUE(SetsAreEqual(s21_s_rnd, std_s_rnd));

    s21_s_rnd.erase(--s21_s_rnd.end());
    std_s_rnd.erase(--std_s_rnd.end());
    EXPECT_TRUE(SetsAreEqual(s21_s_rnd, std_s_rnd));

    s21_s_rnd.erase(++s21_s_rnd.begin());
    std_s_rnd.erase(++std_s_rnd.begin());
    EXPECT_TRUE(SetsAreEqual(s21_s_rnd, std_s_rnd));

    s21_s_rnd.erase(--(--s21_s_rnd.end()));
    std_s_rnd.erase(--(--std_s_rnd.end()));
    EXPECT_TRUE(SetsAreEqual(s21_s_rnd, std_s_rnd));

    auto s21_it = s21_s_rnd.end();
    auto std_it = std_s_rnd.end();
    for (int i = 0; i < 111; ++i, --s21_it, --std_it) {
    }
    s21_s_rnd.erase(s21_it);
    std_s_rnd.erase(std_it);
    EXPECT_TRUE(SetsAreEqual(s21_s_rnd, std_s_rnd));

    s21_it = s21_s_rnd.begin();
    std_it = std_s_rnd.begin();
    for (int i = 0; i < 111; ++i, ++s21_it, ++std_it) {
    }
    s21_s_rnd.erase(s21_it);
    std_s_rnd.erase(std_it);
    EXPECT_TRUE(SetsAreEqual(s21_s_rnd, std_s_rnd));
  }
  {
    s21::set<int> s21_s = {10};
    std::set<int> std_s = {10};
    s21_s.erase(s21_s.begin());
    std_s.erase(std_s.begin());
    EXPECT_TRUE(SetsAreEqual(s21_s, std_s));
  }
  {
    auto s21_s = s21_s_static;
    auto std_s = std_s_static;
    s21_s.erase(s21_s.find(70));
    std_s.erase(std_s.find(70));
    EXPECT_TRUE(SetsAreEqual(s21_s, std_s));
  }
  {
    auto s21_s = s21_s_static;
    auto std_s = std_s_static;
    s21_s.erase(s21_s.find(30));
    std_s.erase(std_s.find(30));
    EXPECT_TRUE(SetsAreEqual(s21_s, std_s));
  }
  {
    auto s21_s = s21_s_static;
    auto std_s = std_s_static;
    s21_s.insert(45);
    std_s.insert(45);
    s21_s.erase(s21_s.find(40));
    std_s.erase(std_s.find(40));
    EXPECT_TRUE(SetsAreEqual(s21_s, std_s));
  }
  {
    auto s21_s = s21_s_static;
    auto std_s = std_s_static;
    s21_s.erase(s21_s.find(90));
    std_s.erase(std_s.find(90));
    EXPECT_TRUE(SetsAreEqual(s21_s, std_s));
  }
  {
    auto s21_s = s21_s_static;
    auto std_s = std_s_static;
    s21_s.erase(s21_s.find(100));
    std_s.erase(std_s.find(100));
    s21_s.erase(s21_s.find(90));
    std_s.erase(std_s.find(90));
    EXPECT_TRUE(SetsAreEqual(s21_s, std_s));
  }
  {
    auto s21_s = s21_s_static;
    auto std_s = std_s_static;
    s21_s.erase(s21_s.find(100));
    std_s.erase(std_s.find(100));
    s21_s.erase(s21_s.find(90));
    std_s.erase(std_s.find(90));
    s21_s.erase(s21_s.find(40));
    std_s.erase(std_s.find(40));
    s21_s.erase(s21_s.find(110));
    std_s.erase(std_s.find(110));
    EXPECT_TRUE(SetsAreEqual(s21_s, std_s));
  }
  {
    auto std_s_rnd_copy = std_s_rnd;
    int i = 0;
    for (auto elem : std_s_rnd_copy) {
      if (i++ % 3 == 0) {
        s21_s_rnd.erase(s21_s_rnd.find(elem));
        std_s_rnd.erase(std_s_rnd.find(elem));
      }
    }
    EXPECT_TRUE(SetsAreEqual(s21_s_rnd, std_s_rnd));
  }
}

TEST_F(SetTest, Swap) {
  {
    s21::set<int> s21_s1, s21_s2;
    std::set<int> std_s1, std_s2;
    s21_s1.swap(s21_s2);
    std_s1.swap(std_s2);
    EXPECT_TRUE(SetsAreEqual(s21_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(s21_s2, std_s2));
  }
  {
    s21::set<int> s21_s1;
    s21::set<int> s21_s2 = {1};
    std::set<int> std_s1;
    std::set<int> std_s2 = {1};
    s21_s1.swap(s21_s2);
    std_s1.swap(std_s2);
    EXPECT_TRUE(SetsAreEqual(s21_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(s21_s2, std_s2));
    s21_s2.swap(s21_s1);
    std_s2.swap(std_s1);
    EXPECT_TRUE(SetsAreEqual(s21_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(s21_s2, std_s2));
  }
  {
    s21_s_static.swap(s21_s_rnd);
    std_s_static.swap(std_s_rnd);
    EXPECT_TRUE(SetsAreEqual(s21_s_rnd, std_s_rnd));
    EXPECT_TRUE(SetsAreEqual(s21_s_static, std_s_static));
  }
}

TEST_F(SetTest, Merge) {
  {
    s21::set<int> s21_s1, s21_s2;
    std::set<int> std_s1, std_s2;
    s21_s1.merge(s21_s2);
    std_s1.merge(std_s2);
    EXPECT_TRUE(SetsAreEqual(s21_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(s21_s2, std_s2));
  }
  {
    s21::set<int> s21_s1 = {1};
    s21::set<int> s21_s2;
    std::set<int> std_s1 = {1};
    std::set<int> std_s2;
    s21_s1.merge(s21_s2);
    std_s1.merge(std_s2);
    EXPECT_TRUE(SetsAreEqual(s21_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(s21_s2, std_s2));
  }
  {
    s21::set<int> s21_s1;
    s21::set<int> s21_s2 = {1};
    std::set<int> std_s1;
    std::set<int> std_s2 = {1};
    s21_s1.merge(s21_s2);
    std_s1.merge(std_s2);
    EXPECT_TRUE(SetsAreEqual(s21_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(s21_s2, std_s2));
  }
  {
    s21::set<int> s21_s1 = {2};
    s21::set<int> s21_s2 = {1};
    std::set<int> std_s1 = {2};
    std::set<int> std_s2 = {1};
    s21_s1.merge(s21_s2);
    std_s1.merge(std_s2);
    EXPECT_TRUE(SetsAreEqual(s21_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(s21_s2, std_s2));
  }
  {
    s21::set<int> s21_s1 = {1, 2};
    s21::set<int> s21_s2 = {1};
    std::set<int> std_s1 = {1, 2};
    std::set<int> std_s2 = {1};
    s21_s1.merge(s21_s2);
    std_s1.merge(std_s2);
    EXPECT_TRUE(SetsAreEqual(s21_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(s21_s2, std_s2));
  }
  {
    s21::set<int> s21_s1 = {1, 2};
    s21::set<int> s21_s2 = {1, 3};
    std::set<int> std_s1 = {1, 2};
    std::set<int> std_s2 = {1, 3};
    s21_s1.merge(s21_s2);
    std_s1.merge(std_s2);
    EXPECT_TRUE(SetsAreEqual(s21_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(s21_s2, std_s2));
  }
  {
    s21::set<int> s21_s1 = {1, 2, 0, -1, 2};
    s21::set<int> s21_s2 = {1, 3, 2, 4, 5};
    std::set<int> std_s1 = {1, 2, 0, -1, 2};
    std::set<int> std_s2 = {1, 3, 2, 4, 5};
    s21_s1.merge(s21_s2);
    std_s1.merge(std_s2);
    EXPECT_TRUE(SetsAreEqual(s21_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(s21_s2, std_s2));
  }
  {
    s21::set<int> s21_s;
    std::set<int> std_s;
    for (int i = 0; i < 100000; ++i) {
      auto key = rand() % 1000000;
      s21_s.insert(key);
      std_s.insert(key);
    }
    s21_s.merge(s21_s_rnd);
    std_s.merge(std_s_rnd);
    EXPECT_TRUE(SetsAreEqual(s21_s, std_s));
    EXPECT_TRUE(SetsAreEqual(s21_s_rnd, std_s_rnd));
  }
}

TEST_F(SetTest, Lookup) {
  {
    EXPECT_TRUE(s21_s_static.contains(70));
    EXPECT_TRUE(s21_s_static.contains(30));
    EXPECT_TRUE(s21_s_static.contains(40));
    EXPECT_FALSE(s21_s_static.contains(1));
    EXPECT_FALSE(s21_s_static.contains(65));
    EXPECT_FALSE(s21_s_static.contains(200));
  }
  {
    s21::set<int> s21_s;
    EXPECT_FALSE(s21_s.contains(1));
  }
  {
    const s21::set<int> s21_s = s21_s_static;
    const std::set<int> std_s = std_s_static;
    EXPECT_TRUE(*s21_s.find(100) == 100);
    EXPECT_TRUE(*std_s.find(100) == 100);
    EXPECT_TRUE(s21_s.find(1000) == s21_s.cend());
    EXPECT_TRUE(std_s.find(1000) == std_s.cend());
  }
}

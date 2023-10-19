#include "test.h"

TEST_F(SetTest, DefaultCtor) {
  {
    scp::set<int> scp_s;
    EXPECT_TRUE(scp_s.empty());
    EXPECT_EQ(scp_s.size(), 0);
  }
  {
    const scp::set<int> scp_s;
    EXPECT_TRUE(scp_s.empty());
    EXPECT_EQ(scp_s.size(), 0);
  }
}

TEST_F(SetTest, InitializeCtor) {
  {
    scp::set<int> scp_s = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::set<int> std_s = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    EXPECT_TRUE(SetsAreEqual(scp_s, std_s));
  }
  {
    const scp::set<int> scp_s = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    const std::set<int> std_s = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    EXPECT_TRUE(SetsAreEqual(scp_s, std_s));
  }
}

TEST_F(SetTest, CopyCtor) {
  {
    scp::set<int> scp_s1;
    scp::set<int> scp_s2(scp_s1);
    std::set<int> std_s1;
    std::set<int> std_s2(std_s1);

    EXPECT_TRUE(SetsAreEqual(scp_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(scp_s2, std_s2));
  }
  {
    const scp::set<int> scp_s1;
    const scp::set<int> scp_s2(scp_s1);
    const std::set<int> std_s1;
    const std::set<int> std_s2(std_s1);

    EXPECT_TRUE(SetsAreEqual(scp_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(scp_s2, std_s2));
  }
  {
    scp::set<int> scp_s1 = {10};
    scp::set<int> scp_s2(scp_s1);
    std::set<int> std_s1 = {10};
    std::set<int> std_s2(std_s1);
    EXPECT_TRUE(SetsAreEqual(scp_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(scp_s2, std_s2));
  }
  {
    const scp::set<int> scp_s1 = {10};
    const scp::set<int> scp_s2(scp_s1);
    const std::set<int> std_s1 = {10};
    const std::set<int> std_s2(std_s1);

    EXPECT_TRUE(SetsAreEqual(scp_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(scp_s2, std_s2));
  }
  {
    scp::set<int> scp_s(scp_s_rnd);
    std::set<int> std_s(std_s_rnd);

    EXPECT_TRUE(SetsAreEqual(scp_s, std_s));
  }
  {
    const scp::set<int> scp_s(scp_s_rnd);
    const std::set<int> std_s(std_s_rnd);

    EXPECT_TRUE(SetsAreEqual(scp_s, std_s));
  }
}

TEST_F(SetTest, MoveCtor) {
  {
    scp::set<int> scp_s1;
    scp::set<int> scp_s2(std::move(scp_s1));
    std::set<int> std_s1;
    std::set<int> std_s2(std::move(std_s1));

    EXPECT_TRUE(SetsAreEqual(scp_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(scp_s2, std_s2));
  }
  {
    const scp::set<int> scp_s1;
    const scp::set<int> scp_s2(std::move(scp_s1));
    const std::set<int> std_s1;
    const std::set<int> std_s2(std::move(std_s1));

    EXPECT_TRUE(SetsAreEqual(scp_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(scp_s2, std_s2));
  }
  {
    scp::set<int> scp_s1 = {1};
    scp::set<int> scp_s2(std::move(scp_s1));
    std::set<int> std_s1 = {1};
    std::set<int> std_s2(std::move(std_s1));

    EXPECT_TRUE(SetsAreEqual(scp_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(scp_s2, std_s2));
  }
  {
    const scp::set<int> scp_s1 = {1};
    const scp::set<int> scp_s2(std::move(scp_s1));
    const std::set<int> std_s1 = {1};
    const std::set<int> std_s2(std::move(std_s1));

    EXPECT_TRUE(SetsAreEqual(scp_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(scp_s2, std_s2));
  }
  {
    scp::set<int> scp_s(std::move(scp_s_rnd));
    std::set<int> std_s(std::move(std_s_rnd));

    EXPECT_TRUE(SetsAreEqual(scp_s, std_s));
  }
  {
    const scp::set<int> scp_s(std::move(scp_s_rnd));
    const std::set<int> std_s(std::move(std_s_rnd));

    EXPECT_TRUE(SetsAreEqual(scp_s, std_s));
  }
}

TEST_F(SetTest, AssignmentOperator) {
  {
    scp::set<int> scp_s1, scp_s2;
    std::set<int> std_s1, std_s2;

    scp_s2 = scp_s1;
    std_s2 = std_s1;

    EXPECT_TRUE(SetsAreEqual(scp_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(scp_s2, std_s2));
  }
  {
    const scp::set<int> scp_s1;
    const std::set<int> std_s1;
    scp::set<int> scp_s2;
    std::set<int> std_s2;

    scp_s2 = scp_s1;
    std_s2 = std_s1;

    EXPECT_TRUE(SetsAreEqual(scp_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(scp_s2, std_s2));
  }
  {
    scp::set<int> scp_s1, scp_s2;
    std::set<int> std_s1, std_s2;

    scp_s2 = std::move(scp_s1);
    std_s2 = std::move(std_s1);

    EXPECT_TRUE(SetsAreEqual(scp_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(scp_s2, std_s2));
  }
  {
    const scp::set<int> scp_s1;
    const std::set<int> std_s1;
    scp::set<int> scp_s2;
    std::set<int> std_s2;

    scp_s2 = std::move(scp_s1);
    std_s2 = std::move(std_s1);

    EXPECT_TRUE(SetsAreEqual(scp_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(scp_s2, std_s2));
  }
  {
    scp::set<int> scp_s1 = {10};
    scp::set<int> scp_s2;
    std::set<int> std_s1 = {10};
    std::set<int> std_s2;

    scp_s2 = scp_s1;
    std_s2 = std_s1;

    EXPECT_TRUE(SetsAreEqual(scp_s1, std_s2));
    EXPECT_TRUE(SetsAreEqual(scp_s1, std_s2));
  }
  {
    const scp::set<int> scp_s1 = {10};
    scp::set<int> scp_s2;
    const std::set<int> std_s1 = {10};
    std::set<int> std_s2;

    scp_s2 = scp_s1;
    std_s2 = std_s1;

    EXPECT_TRUE(SetsAreEqual(scp_s1, std_s2));
    EXPECT_TRUE(SetsAreEqual(scp_s1, std_s2));
  }
  {
    scp::set<int> scp_s1 = {10};
    scp::set<int> scp_s2;
    std::set<int> std_s1 = {10};
    std::set<int> std_s2;

    scp_s2 = std::move(scp_s1);
    std_s2 = std::move(std_s1);

    EXPECT_TRUE(SetsAreEqual(scp_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(scp_s2, std_s2));
  }
  {
    const scp::set<int> scp_s1 = {10};
    scp::set<int> scp_s2;
    const std::set<int> std_s1 = {10};
    std::set<int> std_s2;

    scp_s2 = std::move(scp_s1);
    std_s2 = std::move(std_s1);

    EXPECT_TRUE(SetsAreEqual(scp_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(scp_s2, std_s2));
  }
  {
    scp::set<int> scp_s1 = {69, 25, 51};
    scp::set<int> scp_s2 = {69};
    std::set<int> std_s1 = {69, 25, 51};
    std::set<int> std_s2 = {69};

    scp_s2 = scp_s1;
    std_s2 = std_s1;

    EXPECT_TRUE(SetsAreEqual(scp_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(scp_s2, std_s2));
  }
  {
    const scp::set<int> scp_s1 = {69, 25, 51};
    scp::set<int> scp_s2 = {69};
    const std::set<int> std_s1 = {69, 25, 51};
    std::set<int> std_s2 = {69};

    scp_s2 = scp_s1;
    std_s2 = std_s1;

    EXPECT_TRUE(SetsAreEqual(scp_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(scp_s2, std_s2));
  }
  {
    scp::set<int> scp_s1 = {69, 25, 51};
    scp::set<int> scp_s2 = {69};
    std::set<int> std_s1 = {69, 25, 51};
    std::set<int> std_s2 = {69};

    scp_s2 = std::move(scp_s1);
    std_s2 = std::move(std_s1);

    EXPECT_TRUE(SetsAreEqual(scp_s2, std_s2));
  }
  {
    const scp::set<int> scp_s1 = {69, 25, 51};
    scp::set<int> scp_s2 = {69};
    const std::set<int> std_s1 = {69, 25, 51};
    std::set<int> std_s2 = {69};

    scp_s2 = std::move(scp_s1);
    std_s2 = std::move(std_s1);

    EXPECT_TRUE(SetsAreEqual(scp_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(scp_s2, std_s2));
  }
  {
    scp::set<int> scp_s = {69};
    std::set<int> std_s = {69};

    scp_s = scp_s_rnd;
    std_s = std_s_rnd;

    EXPECT_TRUE(SetsAreEqual(scp_s, std_s));
  }
  {
    scp::set<int> scp_s = {69};
    std::set<int> std_s = {69};

    scp_s = std::move(scp_s_rnd);
    std_s = std::move(std_s_rnd);

    EXPECT_TRUE(SetsAreEqual(scp_s, std_s));
  }
}

TEST_F(SetTest, Iterator) {
  {
    auto scp_it = scp_s_rnd.begin();
    auto std_it = std_s_rnd.begin();
    MoveForwardBackward(scp_it, std_it);
  }
  {
    const auto scp_s = scp_s_rnd;
    const auto std_s = std_s_rnd;
    auto scp_it = scp_s.begin();
    auto std_it = std_s.begin();
    MoveForwardBackward(scp_it, std_it);
  }
  {
    auto scp_it = scp_s_rnd.end();
    auto std_it = std_s_rnd.end();
    MoveBackwardForward(scp_it, std_it);
  }
  {
    const auto scp_s = scp_s_rnd;
    const auto std_s = std_s_rnd;
    auto scp_it = scp_s.end();
    auto std_it = std_s.end();
    MoveBackwardForward(scp_it, std_it);
  }
  {
    auto scp_it = scp_s_rnd.rbegin();
    auto std_it = std_s_rnd.rbegin();
    MoveForwardBackward(scp_it, std_it);
  }
  {
    const auto scp_s = scp_s_rnd;
    const auto std_s = std_s_rnd;
    auto scp_it = scp_s.rbegin();
    auto std_it = std_s.rbegin();
    MoveForwardBackward(scp_it, std_it);
  }
  {
    auto scp_it = scp_s_rnd.rend();
    auto std_it = std_s_rnd.rend();
    MoveBackwardForward(scp_it, std_it);
  }
  {
    const auto scp_s = scp_s_rnd;
    const auto std_s = std_s_rnd;
    auto scp_it = scp_s.rend();
    auto std_it = std_s.rend();
    MoveBackwardForward(scp_it, std_it);
  }
  {
    auto scp_it = scp_s_rnd.cbegin();
    auto std_it = std_s_rnd.cbegin();
    MoveForwardBackward(scp_it, std_it);
  }
  {
    auto scp_it = scp_s_rnd.cend();
    auto std_it = std_s_rnd.cend();
    MoveBackwardForward(scp_it, std_it);
  }
  {
    auto scp_it = scp_s_rnd.crbegin();
    auto std_it = std_s_rnd.crbegin();
    MoveForwardBackward(scp_it, std_it);
  }
  {
    auto scp_it = scp_s_rnd.crend();
    auto std_it = std_s_rnd.crend();
    MoveBackwardForward(scp_it, std_it);
  }
  {
    scp::set<int> scp_s;
    std::set<int> std_s;

    for (auto i = 2; i < 100000; ++i) {
      auto scp_it = scp_s.insert(i);
      auto std_it = std_s.insert(i);

      EXPECT_EQ(*scp_it.first, *std_it.first);
      EXPECT_EQ(scp_it.second, std_it.second);
    }

    for (auto i = 2; i < 1000; i++) {
      auto it_scp = scp_s.begin();
      auto it_std = std_s.begin();
      while (it_scp != scp_s.end()) {
        if (*it_scp % i == 0) {
          scp_s.erase(it_scp++);
          std_s.erase(it_std++);
        } else {
          ++it_scp;
          ++it_std;
        }
      }
    }

    EXPECT_TRUE(SetsAreEqual(scp_s, std_s));
  }
}

TEST_F(SetTest, Capacity) {
  {
    scp::set<int> scp_s;
    std::set<int> std_s;
    EXPECT_EQ(scp_s.empty(), std_s.empty());
    EXPECT_EQ(scp_s.size(), std_s.size());
    EXPECT_DOUBLE_EQ(static_cast<double>(std_s.max_size()) / scp_s.max_size(),
                     max_size_ratio);
  }
  {
    scp::set<int> scp_s = {10};
    std::set<int> std_s = {10};
    EXPECT_EQ(scp_s.empty(), std_s.empty());
    EXPECT_EQ(scp_s.size(), std_s.size());
    EXPECT_DOUBLE_EQ(static_cast<double>(std_s.max_size()) / scp_s.max_size(),
                     max_size_ratio);
  }
  {
    EXPECT_EQ(scp_s_rnd.empty(), std_s_rnd.empty());
    EXPECT_EQ(scp_s_rnd.size(), std_s_rnd.size());
    EXPECT_DOUBLE_EQ(
        static_cast<double>(std_s_rnd.max_size()) / scp_s_rnd.max_size(),
        max_size_ratio);
  }
  {
    EXPECT_EQ(scp_s_static.empty(), scp_s_static.empty());
    EXPECT_EQ(scp_s_static.size(), scp_s_static.size());
    EXPECT_DOUBLE_EQ(
        static_cast<double>(std_s_static.max_size()) / scp_s_static.max_size(),
        max_size_ratio);
  }
}

TEST_F(SetTest, Clear) {
  {
    scp::set<int> scp_s;
    std::set<int> std_s;
    scp_s.clear();
    std_s.clear();
    EXPECT_EQ(scp_s.empty(), std_s.empty());
    EXPECT_EQ(scp_s.size(), std_s.size());
    EXPECT_TRUE(SetsAreEqual(scp_s, std_s));
  }
  {
    auto scp_s = scp_s_rnd;
    auto std_s = std_s_rnd;
    scp_s.clear();
    std_s.clear();
    EXPECT_EQ(scp_s.empty(), std_s.empty());
    EXPECT_EQ(scp_s.size(), std_s.size());
    EXPECT_TRUE(SetsAreEqual(scp_s, std_s));
  }
}

TEST_F(SetTest, Insert) {
  {
    scp::set<int> scp_s;
    std::set<int> std_s;
    for (auto i = 0; i < 10000; ++i) {
      auto key = rand() % 1000000;
      auto scp_e = scp_s.insert(key);
      auto std_e = std_s.insert(key);
      EXPECT_EQ(*scp_e.first, *std_e.first);
      EXPECT_EQ(scp_e.second, std_e.second);
    }
    EXPECT_TRUE(SetsAreEqual(scp_s, std_s));
  }
}

TEST_F(SetTest, InsertMany) {
  {
    scp::set<int> scp_s;
    std::set<int> std_s;

    scp_s.insert_many(10, 20, 30, 40);
    std_s.insert({10, 20, 30, 40});
    EXPECT_TRUE(SetsAreEqual(scp_s, std_s));
  }
  {
    scp::set<int> scp_s = {10, 20};
    std::set<int> std_s = {10, 20};

    scp_s.insert_many(50, 30, 30, 40);
    std_s.insert({50, 30, 30, 40});
    EXPECT_TRUE(SetsAreEqual(scp_s, std_s));
  }
  {
    scp::set<int> scp_s = {10, 20};
    std::set<int> std_s = {10, 20};

    scp_s.insert_many(10, 20);
    std_s.insert({10, 20});
    EXPECT_TRUE(SetsAreEqual(scp_s, std_s));
  }
}

TEST_F(SetTest, Erase) {
  {
    scp_s_rnd.erase(scp_s_rnd.begin());
    std_s_rnd.erase(std_s_rnd.begin());
    EXPECT_TRUE(SetsAreEqual(scp_s_rnd, std_s_rnd));

    scp_s_rnd.erase(--scp_s_rnd.end());
    std_s_rnd.erase(--std_s_rnd.end());
    EXPECT_TRUE(SetsAreEqual(scp_s_rnd, std_s_rnd));

    scp_s_rnd.erase(++scp_s_rnd.begin());
    std_s_rnd.erase(++std_s_rnd.begin());
    EXPECT_TRUE(SetsAreEqual(scp_s_rnd, std_s_rnd));

    scp_s_rnd.erase(--(--scp_s_rnd.end()));
    std_s_rnd.erase(--(--std_s_rnd.end()));
    EXPECT_TRUE(SetsAreEqual(scp_s_rnd, std_s_rnd));

    auto scp_it = scp_s_rnd.end();
    auto std_it = std_s_rnd.end();
    for (int i = 0; i < 111; ++i, --scp_it, --std_it) {
    }
    scp_s_rnd.erase(scp_it);
    std_s_rnd.erase(std_it);
    EXPECT_TRUE(SetsAreEqual(scp_s_rnd, std_s_rnd));

    scp_it = scp_s_rnd.begin();
    std_it = std_s_rnd.begin();
    for (int i = 0; i < 111; ++i, ++scp_it, ++std_it) {
    }
    scp_s_rnd.erase(scp_it);
    std_s_rnd.erase(std_it);
    EXPECT_TRUE(SetsAreEqual(scp_s_rnd, std_s_rnd));
  }
  {
    scp::set<int> scp_s = {10};
    std::set<int> std_s = {10};
    scp_s.erase(scp_s.begin());
    std_s.erase(std_s.begin());
    EXPECT_TRUE(SetsAreEqual(scp_s, std_s));
  }
  {
    auto scp_s = scp_s_static;
    auto std_s = std_s_static;
    scp_s.erase(scp_s.find(70));
    std_s.erase(std_s.find(70));
    EXPECT_TRUE(SetsAreEqual(scp_s, std_s));
  }
  {
    auto scp_s = scp_s_static;
    auto std_s = std_s_static;
    scp_s.erase(scp_s.find(30));
    std_s.erase(std_s.find(30));
    EXPECT_TRUE(SetsAreEqual(scp_s, std_s));
  }
  {
    auto scp_s = scp_s_static;
    auto std_s = std_s_static;
    scp_s.insert(45);
    std_s.insert(45);
    scp_s.erase(scp_s.find(40));
    std_s.erase(std_s.find(40));
    EXPECT_TRUE(SetsAreEqual(scp_s, std_s));
  }
  {
    auto scp_s = scp_s_static;
    auto std_s = std_s_static;
    scp_s.erase(scp_s.find(90));
    std_s.erase(std_s.find(90));
    EXPECT_TRUE(SetsAreEqual(scp_s, std_s));
  }
  {
    auto scp_s = scp_s_static;
    auto std_s = std_s_static;
    scp_s.erase(scp_s.find(100));
    std_s.erase(std_s.find(100));
    scp_s.erase(scp_s.find(90));
    std_s.erase(std_s.find(90));
    EXPECT_TRUE(SetsAreEqual(scp_s, std_s));
  }
  {
    auto scp_s = scp_s_static;
    auto std_s = std_s_static;
    scp_s.erase(scp_s.find(100));
    std_s.erase(std_s.find(100));
    scp_s.erase(scp_s.find(90));
    std_s.erase(std_s.find(90));
    scp_s.erase(scp_s.find(40));
    std_s.erase(std_s.find(40));
    scp_s.erase(scp_s.find(110));
    std_s.erase(std_s.find(110));
    EXPECT_TRUE(SetsAreEqual(scp_s, std_s));
  }
  {
    auto std_s_rnd_copy = std_s_rnd;
    int i = 0;
    for (auto elem : std_s_rnd_copy) {
      if (i++ % 3 == 0) {
        scp_s_rnd.erase(scp_s_rnd.find(elem));
        std_s_rnd.erase(std_s_rnd.find(elem));
      }
    }
    EXPECT_TRUE(SetsAreEqual(scp_s_rnd, std_s_rnd));
  }
}

TEST_F(SetTest, Swap) {
  {
    scp::set<int> scp_s1, scp_s2;
    std::set<int> std_s1, std_s2;
    scp_s1.swap(scp_s2);
    std_s1.swap(std_s2);
    EXPECT_TRUE(SetsAreEqual(scp_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(scp_s2, std_s2));
  }
  {
    scp::set<int> scp_s1;
    scp::set<int> scp_s2 = {1};
    std::set<int> std_s1;
    std::set<int> std_s2 = {1};
    scp_s1.swap(scp_s2);
    std_s1.swap(std_s2);
    EXPECT_TRUE(SetsAreEqual(scp_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(scp_s2, std_s2));
    scp_s2.swap(scp_s1);
    std_s2.swap(std_s1);
    EXPECT_TRUE(SetsAreEqual(scp_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(scp_s2, std_s2));
  }
  {
    scp_s_static.swap(scp_s_rnd);
    std_s_static.swap(std_s_rnd);
    EXPECT_TRUE(SetsAreEqual(scp_s_rnd, std_s_rnd));
    EXPECT_TRUE(SetsAreEqual(scp_s_static, std_s_static));
  }
}

TEST_F(SetTest, Merge) {
  {
    scp::set<int> scp_s1, scp_s2;
    std::set<int> std_s1, std_s2;
    scp_s1.merge(scp_s2);
    std_s1.merge(std_s2);
    EXPECT_TRUE(SetsAreEqual(scp_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(scp_s2, std_s2));
  }
  {
    scp::set<int> scp_s1 = {1};
    scp::set<int> scp_s2;
    std::set<int> std_s1 = {1};
    std::set<int> std_s2;
    scp_s1.merge(scp_s2);
    std_s1.merge(std_s2);
    EXPECT_TRUE(SetsAreEqual(scp_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(scp_s2, std_s2));
  }
  {
    scp::set<int> scp_s1;
    scp::set<int> scp_s2 = {1};
    std::set<int> std_s1;
    std::set<int> std_s2 = {1};
    scp_s1.merge(scp_s2);
    std_s1.merge(std_s2);
    EXPECT_TRUE(SetsAreEqual(scp_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(scp_s2, std_s2));
  }
  {
    scp::set<int> scp_s1 = {2};
    scp::set<int> scp_s2 = {1};
    std::set<int> std_s1 = {2};
    std::set<int> std_s2 = {1};
    scp_s1.merge(scp_s2);
    std_s1.merge(std_s2);
    EXPECT_TRUE(SetsAreEqual(scp_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(scp_s2, std_s2));
  }
  {
    scp::set<int> scp_s1 = {1, 2};
    scp::set<int> scp_s2 = {1};
    std::set<int> std_s1 = {1, 2};
    std::set<int> std_s2 = {1};
    scp_s1.merge(scp_s2);
    std_s1.merge(std_s2);
    EXPECT_TRUE(SetsAreEqual(scp_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(scp_s2, std_s2));
  }
  {
    scp::set<int> scp_s1 = {1, 2};
    scp::set<int> scp_s2 = {1, 3};
    std::set<int> std_s1 = {1, 2};
    std::set<int> std_s2 = {1, 3};
    scp_s1.merge(scp_s2);
    std_s1.merge(std_s2);
    EXPECT_TRUE(SetsAreEqual(scp_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(scp_s2, std_s2));
  }
  {
    scp::set<int> scp_s1 = {1, 2, 0, -1, 2};
    scp::set<int> scp_s2 = {1, 3, 2, 4, 5};
    std::set<int> std_s1 = {1, 2, 0, -1, 2};
    std::set<int> std_s2 = {1, 3, 2, 4, 5};
    scp_s1.merge(scp_s2);
    std_s1.merge(std_s2);
    EXPECT_TRUE(SetsAreEqual(scp_s1, std_s1));
    EXPECT_TRUE(SetsAreEqual(scp_s2, std_s2));
  }
  {
    scp::set<int> scp_s;
    std::set<int> std_s;
    for (int i = 0; i < 100000; ++i) {
      auto key = rand() % 1000000;
      scp_s.insert(key);
      std_s.insert(key);
    }
    scp_s.merge(scp_s_rnd);
    std_s.merge(std_s_rnd);
    EXPECT_TRUE(SetsAreEqual(scp_s, std_s));
    EXPECT_TRUE(SetsAreEqual(scp_s_rnd, std_s_rnd));
  }
}

TEST_F(SetTest, Lookup) {
  {
    EXPECT_TRUE(scp_s_static.contains(70));
    EXPECT_TRUE(scp_s_static.contains(30));
    EXPECT_TRUE(scp_s_static.contains(40));
    EXPECT_FALSE(scp_s_static.contains(1));
    EXPECT_FALSE(scp_s_static.contains(65));
    EXPECT_FALSE(scp_s_static.contains(200));
  }
  {
    scp::set<int> scp_s;
    EXPECT_FALSE(scp_s.contains(1));
  }
  {
    const scp::set<int> scp_s = scp_s_static;
    const std::set<int> std_s = std_s_static;
    EXPECT_TRUE(*scp_s.find(100) == 100);
    EXPECT_TRUE(*std_s.find(100) == 100);
    EXPECT_TRUE(scp_s.find(1000) == scp_s.cend());
    EXPECT_TRUE(std_s.find(1000) == std_s.cend());
  }
}

#include "test.h"

TEST_F(MultisetTest, DefaultCtor) {
  {
    scp::multiset<int> scp_ms;
    EXPECT_TRUE(scp_ms.empty());
    EXPECT_EQ(scp_ms.size(), 0);
  }
  {
    const scp::multiset<int> scp_ms;
    EXPECT_TRUE(scp_ms.empty());
    EXPECT_EQ(scp_ms.size(), 0);
  }
}

TEST_F(MultisetTest, InitializeCtor) {
  {
    scp::multiset<int> scp_ms = {1,  2, 3, 4, 5, 6, 7, 8, 9, 10,
                                 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    std::multiset<int> std_ms = {1,  2, 3, 4, 5, 6, 7, 8, 9, 10,
                                 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    EXPECT_TRUE(MultisetsAreEqual(scp_ms, std_ms));
  }
  {
    const scp::multiset<int> scp_ms = {1,  2, 3, 4, 5, 6, 7, 8, 9, 10,
                                       10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    const std::multiset<int> std_ms = {1,  2, 3, 4, 5, 6, 7, 8, 9, 10,
                                       10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    EXPECT_TRUE(MultisetsAreEqual(scp_ms, std_ms));
  }
}

TEST_F(MultisetTest, CopyCtor) {
  {
    scp::multiset<int> scp_ms1;
    scp::multiset<int> scp_ms2(scp_ms1);
    std::multiset<int> std_ms1;
    std::multiset<int> std_ms2(std_ms1);

    EXPECT_TRUE(MultisetsAreEqual(scp_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(scp_ms2, std_ms2));
  }
  {
    const scp::multiset<int> scp_ms1;
    const scp::multiset<int> scp_ms2(scp_ms1);
    const std::multiset<int> std_ms1;
    const std::multiset<int> std_ms2(std_ms1);

    EXPECT_TRUE(MultisetsAreEqual(scp_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(scp_ms2, std_ms2));
  }
  {
    scp::multiset<int> scp_ms1 = {10};
    scp::multiset<int> scp_ms2(scp_ms1);
    std::multiset<int> std_ms1 = {10};
    std::multiset<int> std_ms2(std_ms1);
    EXPECT_TRUE(MultisetsAreEqual(scp_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(scp_ms2, std_ms2));
  }
  {
    const scp::multiset<int> scp_ms1 = {10};
    const scp::multiset<int> scp_ms2(scp_ms1);
    const std::multiset<int> std_ms1 = {10};
    const std::multiset<int> std_ms2(std_ms1);

    EXPECT_TRUE(MultisetsAreEqual(scp_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(scp_ms2, std_ms2));
  }
  {
    scp::multiset<int> scp_ms(scp_ms_rnd);
    std::multiset<int> std_ms(std_ms_rnd);

    EXPECT_TRUE(MultisetsAreEqual(scp_ms, std_ms));
  }
  {
    const scp::multiset<int> scp_ms(scp_ms_rnd);
    const std::multiset<int> std_ms(std_ms_rnd);

    EXPECT_TRUE(MultisetsAreEqual(scp_ms, std_ms));
  }
}

TEST_F(MultisetTest, MoveCtor) {
  {
    scp::multiset<int> scp_ms1;
    scp::multiset<int> scp_ms2(std::move(scp_ms1));
    std::multiset<int> std_ms1;
    std::multiset<int> std_ms2(std::move(std_ms1));

    EXPECT_TRUE(MultisetsAreEqual(scp_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(scp_ms2, std_ms2));
  }
  {
    const scp::multiset<int> scp_ms1;
    const scp::multiset<int> scp_ms2(std::move(scp_ms1));
    const std::multiset<int> std_ms1;
    const std::multiset<int> std_ms2(std::move(std_ms1));

    EXPECT_TRUE(MultisetsAreEqual(scp_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(scp_ms2, std_ms2));
  }
  {
    scp::multiset<int> scp_ms1 = {1};
    scp::multiset<int> scp_ms2(std::move(scp_ms1));
    std::multiset<int> std_ms1 = {1};
    std::multiset<int> std_ms2(std::move(std_ms1));

    EXPECT_TRUE(MultisetsAreEqual(scp_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(scp_ms2, std_ms2));
  }
  {
    const scp::multiset<int> scp_ms1 = {1};
    const scp::multiset<int> scp_ms2(std::move(scp_ms1));
    const std::multiset<int> std_ms1 = {1};
    const std::multiset<int> std_ms2(std::move(std_ms1));

    EXPECT_TRUE(MultisetsAreEqual(scp_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(scp_ms2, std_ms2));
  }
  {
    scp::multiset<int> scp_ms(std::move(scp_ms_rnd));
    std::multiset<int> std_ms(std::move(std_ms_rnd));

    EXPECT_TRUE(MultisetsAreEqual(scp_ms, std_ms));
  }
  {
    const scp::multiset<int> scp_ms(std::move(scp_ms_rnd));
    const std::multiset<int> std_ms(std::move(std_ms_rnd));

    EXPECT_TRUE(MultisetsAreEqual(scp_ms, std_ms));
  }
}

TEST_F(MultisetTest, AssignmentOperator) {
  {
    scp::multiset<int> scp_ms1, scp_ms2;
    std::multiset<int> std_ms1, std_ms2;

    scp_ms2 = scp_ms1;
    std_ms2 = std_ms1;

    EXPECT_TRUE(MultisetsAreEqual(scp_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(scp_ms2, std_ms2));
  }
  {
    const scp::multiset<int> scp_ms1;
    const std::multiset<int> std_ms1;
    scp::multiset<int> scp_ms2;
    std::multiset<int> std_ms2;

    scp_ms2 = scp_ms1;
    std_ms2 = std_ms1;

    EXPECT_TRUE(MultisetsAreEqual(scp_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(scp_ms2, std_ms2));
  }
  {
    scp::multiset<int> scp_ms1, scp_ms2;
    std::multiset<int> std_ms1, std_ms2;

    scp_ms2 = std::move(scp_ms1);
    std_ms2 = std::move(std_ms1);

    EXPECT_TRUE(MultisetsAreEqual(scp_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(scp_ms2, std_ms2));
  }
  {
    const scp::multiset<int> scp_ms1;
    const std::multiset<int> std_ms1;
    scp::multiset<int> scp_ms2;
    std::multiset<int> std_ms2;

    scp_ms2 = std::move(scp_ms1);
    std_ms2 = std::move(std_ms1);

    EXPECT_TRUE(MultisetsAreEqual(scp_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(scp_ms2, std_ms2));
  }
  {
    scp::multiset<int> scp_ms1 = {10};
    scp::multiset<int> scp_ms2;
    std::multiset<int> std_ms1 = {10};
    std::multiset<int> std_ms2;

    scp_ms2 = scp_ms1;
    std_ms2 = std_ms1;

    EXPECT_TRUE(MultisetsAreEqual(scp_ms1, std_ms2));
    EXPECT_TRUE(MultisetsAreEqual(scp_ms1, std_ms2));
  }
  {
    const scp::multiset<int> scp_ms1 = {10};
    scp::multiset<int> scp_ms2;
    const std::multiset<int> std_ms1 = {10};
    std::multiset<int> std_ms2;

    scp_ms2 = scp_ms1;
    std_ms2 = std_ms1;

    EXPECT_TRUE(MultisetsAreEqual(scp_ms1, std_ms2));
    EXPECT_TRUE(MultisetsAreEqual(scp_ms1, std_ms2));
  }
  {
    scp::multiset<int> scp_ms1 = {10};
    scp::multiset<int> scp_ms2;
    std::multiset<int> std_ms1 = {10};
    std::multiset<int> std_ms2;

    scp_ms2 = std::move(scp_ms1);
    std_ms2 = std::move(std_ms1);

    EXPECT_TRUE(MultisetsAreEqual(scp_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(scp_ms2, std_ms2));
  }
  {
    const scp::multiset<int> scp_ms1 = {10};
    scp::multiset<int> scp_ms2;
    const std::multiset<int> std_ms1 = {10};
    std::multiset<int> std_ms2;

    scp_ms2 = std::move(scp_ms1);
    std_ms2 = std::move(std_ms1);

    EXPECT_TRUE(MultisetsAreEqual(scp_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(scp_ms2, std_ms2));
  }
  {
    scp::multiset<int> scp_ms1 = {69, 25, 69};
    scp::multiset<int> scp_ms2 = {69};
    std::multiset<int> std_ms1 = {69, 25, 69};
    std::multiset<int> std_ms2 = {69};

    scp_ms2 = scp_ms1;
    std_ms2 = std_ms1;

    EXPECT_TRUE(MultisetsAreEqual(scp_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(scp_ms2, std_ms2));
  }
  {
    const scp::multiset<int> scp_ms1 = {69, 25, 69};
    scp::multiset<int> scp_ms2 = {69};
    const std::multiset<int> std_ms1 = {69, 25, 69};
    std::multiset<int> std_ms2 = {69};

    scp_ms2 = scp_ms1;
    std_ms2 = std_ms1;

    EXPECT_TRUE(MultisetsAreEqual(scp_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(scp_ms2, std_ms2));
  }
  {
    scp::multiset<int> scp_ms1 = {69, 25, 69};
    scp::multiset<int> scp_ms2 = {69};
    std::multiset<int> std_ms1 = {69, 25, 69};
    std::multiset<int> std_ms2 = {69};

    scp_ms2 = std::move(scp_ms1);
    std_ms2 = std::move(std_ms1);

    EXPECT_TRUE(MultisetsAreEqual(scp_ms2, std_ms2));
  }
  {
    const scp::multiset<int> scp_ms1 = {69, 25, 69};
    scp::multiset<int> scp_ms2 = {69};
    const std::multiset<int> std_ms1 = {69, 25, 69};
    std::multiset<int> std_ms2 = {69};

    scp_ms2 = std::move(scp_ms1);
    std_ms2 = std::move(std_ms1);

    EXPECT_TRUE(MultisetsAreEqual(scp_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(scp_ms2, std_ms2));
  }
  {
    scp::multiset<int> scp_ms = {69};
    std::multiset<int> std_ms = {69};

    scp_ms = scp_ms_rnd;
    std_ms = std_ms_rnd;

    EXPECT_TRUE(MultisetsAreEqual(scp_ms, std_ms));
  }
  {
    scp::multiset<int> scp_ms = {69};
    std::multiset<int> std_ms = {69};

    scp_ms = std::move(scp_ms_rnd);
    std_ms = std::move(std_ms_rnd);

    EXPECT_TRUE(MultisetsAreEqual(scp_ms, std_ms));
  }
}

TEST_F(MultisetTest, Iterator) {
  {
    auto scp_it = scp_ms_rnd.begin();
    auto std_it = std_ms_rnd.begin();
    MoveForwardBackward(scp_it, std_it);
  }
  {
    const auto scp_ms = scp_ms_rnd;
    const auto std_ms = std_ms_rnd;
    auto scp_it = scp_ms.begin();
    auto std_it = std_ms.begin();
    MoveForwardBackward(scp_it, std_it);
  }
  {
    auto scp_it = scp_ms_rnd.end();
    auto std_it = std_ms_rnd.end();
    MoveBackwardForward(scp_it, std_it);
  }
  {
    const auto scp_ms = scp_ms_rnd;
    const auto std_ms = std_ms_rnd;
    auto scp_it = scp_ms.end();
    auto std_it = std_ms.end();
    MoveBackwardForward(scp_it, std_it);
  }
  {
    auto scp_it = scp_ms_rnd.rbegin();
    auto std_it = std_ms_rnd.rbegin();
    MoveForwardBackward(scp_it, std_it);
  }
  {
    const auto scp_ms = scp_ms_rnd;
    const auto std_ms = std_ms_rnd;
    auto scp_it = scp_ms.rbegin();
    auto std_it = std_ms.rbegin();
    MoveForwardBackward(scp_it, std_it);
  }
  {
    auto scp_it = scp_ms_rnd.rend();
    auto std_it = std_ms_rnd.rend();
    MoveBackwardForward(scp_it, std_it);
  }
  {
    const auto scp_ms = scp_ms_rnd;
    const auto std_ms = std_ms_rnd;
    auto scp_it = scp_ms.rend();
    auto std_it = std_ms.rend();
    MoveBackwardForward(scp_it, std_it);
  }
  {
    auto scp_it = scp_ms_rnd.cbegin();
    auto std_it = std_ms_rnd.cbegin();
    MoveForwardBackward(scp_it, std_it);
  }
  {
    auto scp_it = scp_ms_rnd.cend();
    auto std_it = std_ms_rnd.cend();
    MoveBackwardForward(scp_it, std_it);
  }
  {
    auto scp_it = scp_ms_rnd.crbegin();
    auto std_it = std_ms_rnd.crbegin();
    MoveForwardBackward(scp_it, std_it);
  }
  {
    auto scp_it = scp_ms_rnd.crend();
    auto std_it = std_ms_rnd.crend();
    MoveBackwardForward(scp_it, std_it);
  }
  {
    scp::multiset<int> scp_ms;
    std::multiset<int> std_ms;

    for (auto i = 2; i < 100000; ++i) {
      auto scp_it = scp_ms.insert(i);
      auto std_it = std_ms.insert(i);

      EXPECT_EQ(*scp_it, *std_it);
    }

    for (auto i = 2; i < 1000; i++) {
      auto it_scp = scp_ms.begin();
      auto it_std = std_ms.begin();
      while (it_scp != scp_ms.end()) {
        if (*it_scp % i == 0) {
          scp_ms.erase(it_scp++);
          std_ms.erase(it_std++);
        } else {
          ++it_scp;
          ++it_std;
        }
      }
    }

    EXPECT_TRUE(MultisetsAreEqual(scp_ms, std_ms));
  }
}

TEST_F(MultisetTest, Capacity) {
  {
    scp::multiset<int> scp_ms;
    std::multiset<int> std_ms;
    EXPECT_EQ(scp_ms.empty(), std_ms.empty());
    EXPECT_EQ(scp_ms.size(), std_ms.size());
    EXPECT_DOUBLE_EQ(static_cast<double>(std_ms.max_size()) / scp_ms.max_size(),
                     max_size_ratio);
  }
  {
    scp::multiset<int> scp_ms = {10};
    std::multiset<int> std_ms = {10};
    EXPECT_EQ(scp_ms.empty(), std_ms.empty());
    EXPECT_EQ(scp_ms.size(), std_ms.size());
    EXPECT_DOUBLE_EQ(static_cast<double>(std_ms.max_size()) / scp_ms.max_size(),
                     max_size_ratio);
  }
  {
    EXPECT_EQ(scp_ms_rnd.empty(), std_ms_rnd.empty());
    EXPECT_EQ(scp_ms_rnd.size(), std_ms_rnd.size());
    EXPECT_DOUBLE_EQ(
        static_cast<double>(std_ms_rnd.max_size()) / scp_ms_rnd.max_size(),
        max_size_ratio);
  }
  {
    EXPECT_EQ(scp_ms_static.empty(), scp_ms_static.empty());
    EXPECT_EQ(scp_ms_static.size(), scp_ms_static.size());
    EXPECT_DOUBLE_EQ(static_cast<double>(std_ms_static.max_size()) /
                         scp_ms_static.max_size(),
                     max_size_ratio);
  }
}

TEST_F(MultisetTest, Clear) {
  {
    scp::multiset<int> scp_ms;
    std::multiset<int> std_ms;
    scp_ms.clear();
    std_ms.clear();
    EXPECT_EQ(scp_ms.empty(), std_ms.empty());
    EXPECT_EQ(scp_ms.size(), std_ms.size());
    EXPECT_TRUE(MultisetsAreEqual(scp_ms, std_ms));
  }
  {
    auto scp_ms = scp_ms_rnd;
    auto std_ms = std_ms_rnd;
    scp_ms.clear();
    std_ms.clear();
    EXPECT_EQ(scp_ms.empty(), std_ms.empty());
    EXPECT_EQ(scp_ms.size(), std_ms.size());
    EXPECT_TRUE(MultisetsAreEqual(scp_ms, std_ms));
  }
}

TEST_F(MultisetTest, Insert) {
  {
    scp::multiset<int> scp_ms;
    std::multiset<int> std_ms;
    for (auto i = 0; i < 10000; ++i) {
      auto key = rand() % 1000;
      auto scp_e = scp_ms.insert(key);
      auto std_e = std_ms.insert(key);
      EXPECT_EQ(*scp_e, *std_e);
    }
    EXPECT_TRUE(MultisetsAreEqual(scp_ms, std_ms));
  }
}

TEST_F(MultisetTest, InsertMany) {
  {
    scp::multiset<int> scp_ms;
    std::multiset<int> std_ms;

    scp_ms.insert_many(10, 20, 30, 40, 30, 20, 10);
    std_ms.insert({10, 20, 30, 40, 30, 20, 10});
    EXPECT_TRUE(MultisetsAreEqual(scp_ms, std_ms));
  }
  {
    scp::multiset<int> scp_ms = {10, 20};
    std::multiset<int> std_ms = {10, 20};

    scp_ms.insert_many(50, 30, 30, 40);
    std_ms.insert({50, 30, 30, 40});
    EXPECT_TRUE(MultisetsAreEqual(scp_ms, std_ms));
  }
  {
    scp::multiset<int> scp_ms = {10, 20};
    std::multiset<int> std_ms = {10, 20};

    scp_ms.insert_many(10, 20);
    std_ms.insert({10, 20});
    EXPECT_TRUE(MultisetsAreEqual(scp_ms, std_ms));
  }
}

TEST_F(MultisetTest, Erase) {
  {
    scp_ms_rnd.erase(scp_ms_rnd.begin());
    std_ms_rnd.erase(std_ms_rnd.begin());
    EXPECT_TRUE(MultisetsAreEqual(scp_ms_rnd, std_ms_rnd));

    scp_ms_rnd.erase(--scp_ms_rnd.end());
    std_ms_rnd.erase(--std_ms_rnd.end());
    EXPECT_TRUE(MultisetsAreEqual(scp_ms_rnd, std_ms_rnd));

    scp_ms_rnd.erase(++scp_ms_rnd.begin());
    std_ms_rnd.erase(++std_ms_rnd.begin());
    EXPECT_TRUE(MultisetsAreEqual(scp_ms_rnd, std_ms_rnd));

    scp_ms_rnd.erase(--(--scp_ms_rnd.end()));
    std_ms_rnd.erase(--(--std_ms_rnd.end()));
    EXPECT_TRUE(MultisetsAreEqual(scp_ms_rnd, std_ms_rnd));

    auto scp_it = scp_ms_rnd.end();
    auto std_it = std_ms_rnd.end();
    for (int i = 0; i < 111; ++i, --scp_it, --std_it) {
    }
    scp_ms_rnd.erase(scp_it);
    std_ms_rnd.erase(std_it);
    EXPECT_TRUE(MultisetsAreEqual(scp_ms_rnd, std_ms_rnd));

    scp_it = scp_ms_rnd.begin();
    std_it = std_ms_rnd.begin();
    for (int i = 0; i < 111; ++i, ++scp_it, ++std_it) {
    }
    scp_ms_rnd.erase(scp_it);
    std_ms_rnd.erase(std_it);
    EXPECT_TRUE(MultisetsAreEqual(scp_ms_rnd, std_ms_rnd));
  }
  {
    scp::multiset<int> scp_ms = {10};
    std::multiset<int> std_ms = {10};
    scp_ms.erase(scp_ms.begin());
    std_ms.erase(std_ms.begin());
    EXPECT_TRUE(MultisetsAreEqual(scp_ms, std_ms));
  }
  {
    auto scp_ms = scp_ms_static;
    auto std_ms = std_ms_static;
    scp_ms.erase(scp_ms.find(70));
    std_ms.erase(std_ms.find(70));
    EXPECT_TRUE(MultisetsAreEqual(scp_ms, std_ms));
  }
  {
    auto scp_ms = scp_ms_static;
    auto std_ms = std_ms_static;
    scp_ms.erase(scp_ms.find(30));
    std_ms.erase(std_ms.find(30));
    EXPECT_TRUE(MultisetsAreEqual(scp_ms, std_ms));
  }
  {
    auto scp_ms = scp_ms_static;
    auto std_ms = std_ms_static;
    scp_ms.insert(45);
    std_ms.insert(45);
    scp_ms.erase(scp_ms.find(40));
    std_ms.erase(std_ms.find(40));
    EXPECT_TRUE(MultisetsAreEqual(scp_ms, std_ms));
  }
  {
    auto scp_ms = scp_ms_static;
    auto std_ms = std_ms_static;
    scp_ms.erase(scp_ms.find(90));
    std_ms.erase(std_ms.find(90));
    EXPECT_TRUE(MultisetsAreEqual(scp_ms, std_ms));
  }
  {
    auto scp_ms = scp_ms_static;
    auto std_ms = std_ms_static;
    scp_ms.erase(scp_ms.find(100));
    std_ms.erase(std_ms.find(100));
    scp_ms.erase(scp_ms.find(90));
    std_ms.erase(std_ms.find(90));
    EXPECT_TRUE(MultisetsAreEqual(scp_ms, std_ms));
  }
  {
    auto scp_ms = scp_ms_static;
    auto std_ms = std_ms_static;
    scp_ms.erase(scp_ms.find(100));
    std_ms.erase(std_ms.find(100));
    scp_ms.erase(scp_ms.find(90));
    std_ms.erase(std_ms.find(90));
    scp_ms.erase(scp_ms.find(40));
    std_ms.erase(std_ms.find(40));
    scp_ms.erase(scp_ms.find(110));
    std_ms.erase(std_ms.find(110));
    EXPECT_TRUE(MultisetsAreEqual(scp_ms, std_ms));
  }
  {
    auto std_ms_rnd_copy = std_ms_rnd;
    int i = 0;
    for (auto elem : std_ms_rnd_copy) {
      if (i++ % 3 == 0) {
        scp_ms_rnd.erase(scp_ms_rnd.find(elem));
        std_ms_rnd.erase(std_ms_rnd.find(elem));
      }
    }
    EXPECT_TRUE(MultisetsAreEqual(scp_ms_rnd, std_ms_rnd));
  }
}

TEST_F(MultisetTest, Swap) {
  {
    scp::multiset<int> scp_ms1, scp_ms2;
    std::multiset<int> std_ms1, std_ms2;
    scp_ms1.swap(scp_ms2);
    std_ms1.swap(std_ms2);
    EXPECT_TRUE(MultisetsAreEqual(scp_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(scp_ms2, std_ms2));
  }
  {
    scp::multiset<int> scp_ms1;
    scp::multiset<int> scp_ms2 = {1};
    std::multiset<int> std_ms1;
    std::multiset<int> std_ms2 = {1};
    scp_ms1.swap(scp_ms2);
    std_ms1.swap(std_ms2);
    EXPECT_TRUE(MultisetsAreEqual(scp_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(scp_ms2, std_ms2));
    scp_ms2.swap(scp_ms1);
    std_ms2.swap(std_ms1);
    EXPECT_TRUE(MultisetsAreEqual(scp_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(scp_ms2, std_ms2));
  }
  {
    scp_ms_static.swap(scp_ms_rnd);
    std_ms_static.swap(std_ms_rnd);
    EXPECT_TRUE(MultisetsAreEqual(scp_ms_rnd, std_ms_rnd));
    EXPECT_TRUE(MultisetsAreEqual(scp_ms_static, std_ms_static));
  }
}

TEST_F(MultisetTest, Merge) {
  {
    scp::multiset<int> scp_ms1, scp_ms2;
    std::multiset<int> std_ms1, std_ms2;
    scp_ms1.merge(scp_ms2);
    std_ms1.merge(std_ms2);
    EXPECT_TRUE(MultisetsAreEqual(scp_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(scp_ms2, std_ms2));
  }
  {
    scp::multiset<int> scp_ms1 = {1};
    scp::multiset<int> scp_ms2;
    std::multiset<int> std_ms1 = {1};
    std::multiset<int> std_ms2;
    scp_ms1.merge(scp_ms2);
    std_ms1.merge(std_ms2);
    EXPECT_TRUE(MultisetsAreEqual(scp_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(scp_ms2, std_ms2));
  }
  {
    scp::multiset<int> scp_ms1;
    scp::multiset<int> scp_ms2 = {1};
    std::multiset<int> std_ms1;
    std::multiset<int> std_ms2 = {1};
    scp_ms1.merge(scp_ms2);
    std_ms1.merge(std_ms2);
    EXPECT_TRUE(MultisetsAreEqual(scp_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(scp_ms2, std_ms2));
  }
  {
    scp::multiset<int> scp_ms1 = {2};
    scp::multiset<int> scp_ms2 = {1};
    std::multiset<int> std_ms1 = {2};
    std::multiset<int> std_ms2 = {1};
    scp_ms1.merge(scp_ms2);
    std_ms1.merge(std_ms2);
    EXPECT_TRUE(MultisetsAreEqual(scp_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(scp_ms2, std_ms2));
  }
  {
    scp::multiset<int> scp_ms1 = {1, 2};
    scp::multiset<int> scp_ms2 = {1};
    std::multiset<int> std_ms1 = {1, 2};
    std::multiset<int> std_ms2 = {1};
    scp_ms1.merge(scp_ms2);
    std_ms1.merge(std_ms2);
    EXPECT_TRUE(MultisetsAreEqual(scp_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(scp_ms2, std_ms2));
  }
  {
    scp::multiset<int> scp_ms1 = {1, 2};
    scp::multiset<int> scp_ms2 = {1, 3};
    std::multiset<int> std_ms1 = {1, 2};
    std::multiset<int> std_ms2 = {1, 3};
    scp_ms1.merge(scp_ms2);
    std_ms1.merge(std_ms2);
    EXPECT_TRUE(MultisetsAreEqual(scp_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(scp_ms2, std_ms2));
  }
  {
    scp::multiset<int> scp_ms1 = {1, 2, 0, -1, 2};
    scp::multiset<int> scp_ms2 = {1, 3, 2, 4, 5};
    std::multiset<int> std_ms1 = {1, 2, 0, -1, 2};
    std::multiset<int> std_ms2 = {1, 3, 2, 4, 5};
    scp_ms1.merge(scp_ms2);
    std_ms1.merge(std_ms2);
    EXPECT_TRUE(MultisetsAreEqual(scp_ms1, std_ms1));
    EXPECT_TRUE(MultisetsAreEqual(scp_ms2, std_ms2));
  }
  {
    scp::multiset<int> scp_ms;
    std::multiset<int> std_ms;
    for (int i = 0; i < 100000; ++i) {
      auto key = rand() % 100000;
      scp_ms.insert(key);
      std_ms.insert(key);
    }
    scp_ms.merge(scp_ms_rnd);
    std_ms.merge(std_ms_rnd);
    EXPECT_TRUE(MultisetsAreEqual(scp_ms, std_ms));
    EXPECT_TRUE(MultisetsAreEqual(scp_ms_rnd, std_ms_rnd));
  }
}

TEST_F(MultisetTest, Lookup) {
  {
    EXPECT_TRUE(scp_ms_static.contains(70));
    EXPECT_TRUE(scp_ms_static.contains(30));
    EXPECT_TRUE(scp_ms_static.contains(40));
    EXPECT_FALSE(scp_ms_static.contains(1));
    EXPECT_FALSE(scp_ms_static.contains(65));
    EXPECT_FALSE(scp_ms_static.contains(200));
  }
  {
    scp::multiset<int> scp_ms;
    EXPECT_FALSE(scp_ms.contains(1));
  }
  {
    const scp::multiset<int> scp_ms = scp_ms_static;
    const std::multiset<int> std_ms = std_ms_static;
    EXPECT_TRUE(*scp_ms.find(100) == 100);
    EXPECT_TRUE(*std_ms.find(100) == 100);
    EXPECT_TRUE(scp_ms.find(1000) == scp_ms.cend());
    EXPECT_TRUE(std_ms.find(1000) == std_ms.cend());
  }
}

TEST_F(MultisetTest, Bounds) {
  {
    const scp::multiset<int> scp_ms;
    const std::multiset<int> std_ms;
    auto scp_it_lower = scp_ms.lower_bound(10);
    auto scp_it_upper = scp_ms.upper_bound(10);
    auto std_it_lower = std_ms.lower_bound(10);
    auto std_it_upper = std_ms.upper_bound(10);
    EXPECT_TRUE(scp_it_lower == scp_ms.cend());
    EXPECT_TRUE(scp_it_upper == scp_ms.cend());
    EXPECT_TRUE(std_it_lower == std_ms.cend());
    EXPECT_TRUE(std_it_upper == std_ms.cend());
  }
  {
    const scp::multiset<int> scp_ms = {10};
    const std::multiset<int> std_ms = {10};
    auto scp_it_lower = scp_ms.lower_bound(10);
    auto scp_it_upper = scp_ms.upper_bound(10);
    auto std_it_lower = std_ms.lower_bound(10);
    auto std_it_upper = std_ms.upper_bound(10);
    EXPECT_EQ(*scp_it_lower, *std_it_lower);
    EXPECT_TRUE(scp_it_upper == scp_ms.cend());
    EXPECT_TRUE(std_it_upper == std_ms.cend());
  }
  {
    const scp::multiset<int> scp_ms = {11};
    const std::multiset<int> std_ms = {11};
    auto scp_it_lower = scp_ms.lower_bound(10);
    auto scp_it_upper = scp_ms.upper_bound(10);
    auto std_it_lower = std_ms.lower_bound(10);
    auto std_it_upper = std_ms.upper_bound(10);
    EXPECT_EQ(*scp_it_lower, *std_it_lower);
    EXPECT_EQ(*scp_it_upper, *std_it_upper);
  }
  {
    const scp::multiset<int> scp_ms = {11};
    const std::multiset<int> std_ms = {11};
    auto scp_it_lower = scp_ms.lower_bound(12);
    auto scp_it_upper = scp_ms.upper_bound(12);
    auto std_it_lower = std_ms.lower_bound(12);
    auto std_it_upper = std_ms.upper_bound(12);
    EXPECT_TRUE(scp_it_lower == scp_ms.cend());
    EXPECT_TRUE(std_it_lower == std_ms.cend());
    EXPECT_TRUE(scp_it_upper == scp_ms.cend());
    EXPECT_TRUE(std_it_upper == std_ms.cend());
  }
  {
    const scp::multiset<int> scp_ms = {10, 12, 11, 10, 11, 12,
                                       12, 10, 11, 12, 11, 10};
    const std::multiset<int> std_ms = {10, 12, 11, 10, 11, 12,
                                       12, 10, 11, 12, 11, 10};
    auto scp_it_lower = scp_ms.lower_bound(10);
    auto scp_it_upper = scp_ms.upper_bound(11);
    auto std_it_lower = std_ms.lower_bound(10);
    auto std_it_upper = std_ms.upper_bound(11);
    EXPECT_EQ(*scp_it_upper, *std_it_upper);
    EXPECT_EQ(*scp_it_lower, *std_it_lower);
  }
  {
    for (int i = 0; i < 2000; ++i) {
      int key = rand() % 1000;
      auto scp_it_lower = scp_ms_rnd.lower_bound(key);
      auto std_it_lower = std_ms_rnd.lower_bound(key);
      auto scp_it_upper = scp_ms_rnd.upper_bound(key);
      auto std_it_upper = std_ms_rnd.upper_bound(key);
      if (std_it_lower != std_ms_rnd.end()) {
        EXPECT_EQ(*scp_it_lower, *std_it_lower);
      } else {
        EXPECT_TRUE(scp_it_lower == scp_ms_rnd.end());
      }
      if (std_it_upper != std_ms_rnd.end()) {
        EXPECT_EQ(*scp_it_upper, *std_it_upper);
      } else {
        EXPECT_TRUE(scp_it_upper == scp_ms_rnd.end());
      }
    }
  }
}

TEST_F(MultisetTest, Count) {
  {
    const scp::multiset<int> scp_ms;
    const std::multiset<int> std_ms;
    EXPECT_TRUE(scp_ms.count(10) == std_ms.count(10));
  }
  {
    const scp::multiset<int> scp_ms = {10};
    const std::multiset<int> std_ms = {10};
    EXPECT_TRUE(scp_ms.count(10) == std_ms.count(10));
  }
  {
    const scp::multiset<int> scp_ms = {11};
    const std::multiset<int> std_ms = {11};
    EXPECT_TRUE(scp_ms.count(10) == std_ms.count(10));
  }
  {
    const scp::multiset<int> scp_ms = {11, 11, 11, 10, 11, 11, 11};
    const std::multiset<int> std_ms = {11, 11, 11, 10, 11, 11, 11};
    EXPECT_TRUE(scp_ms.count(11) == std_ms.count(11));
  }
  {
    const scp::multiset<int> scp_ms = {10, 12, 11, 10, 11, 12,
                                       12, 10, 11, 12, 11, 10};
    const std::multiset<int> std_ms = {10, 12, 11, 10, 11, 12,
                                       12, 10, 11, 12, 11, 10};
    EXPECT_TRUE(scp_ms.count(10) == std_ms.count(10));
    EXPECT_TRUE(scp_ms.count(11) == std_ms.count(11));
    EXPECT_TRUE(scp_ms.count(12) == std_ms.count(12));
  }
  {
    for (int i = 0; i < 2000; ++i) {
      int key = rand() % 1000;
      EXPECT_TRUE(scp_ms_rnd.count(key) == std_ms_rnd.count(key));
    }
  }
}

TEST_F(MultisetTest, EqualRange) {
  {
    const scp::multiset<int> scp_ms;
    const std::multiset<int> std_ms;
    auto scp_its = scp_ms.equal_range(10);
    auto std_its = std_ms.equal_range(10);
    EXPECT_TRUE(
        equal(scp_its.first, scp_its.second, std_its.first, std_its.second));
  }
  {
    const scp::multiset<int> scp_ms = {10};
    const std::multiset<int> std_ms = {10};
    auto scp_its = scp_ms.equal_range(10);
    auto std_its = std_ms.equal_range(10);
    EXPECT_TRUE(
        equal(scp_its.first, scp_its.second, std_its.first, std_its.second));
  }
  {
    const scp::multiset<int> scp_ms = {11};
    const std::multiset<int> std_ms = {11};
    auto scp_its = scp_ms.equal_range(10);
    auto std_its = std_ms.equal_range(10);
    EXPECT_TRUE(
        equal(scp_its.first, scp_its.second, std_its.first, std_its.second));
  }
  {
    const scp::multiset<int> scp_ms = {11, 11, 11, 10, 11, 11, 11};
    const std::multiset<int> std_ms = {11, 11, 11, 10, 11, 11, 11};
    auto scp_its = scp_ms.equal_range(11);
    auto std_its = std_ms.equal_range(11);
    EXPECT_TRUE(
        equal(scp_its.first, scp_its.second, std_its.first, std_its.second));
  }
  {
    const scp::multiset<int> scp_ms = {10, 12, 11, 10, 11, 12,
                                       12, 10, 11, 12, 11, 10};
    const std::multiset<int> std_ms = {10, 12, 11, 10, 11, 12,
                                       12, 10, 11, 12, 11, 10};
    auto scp_its = scp_ms.equal_range(10);
    auto std_its = std_ms.equal_range(10);
    EXPECT_TRUE(
        equal(scp_its.first, scp_its.second, std_its.first, std_its.second));
  }
  {
    for (int i = 0; i < 2000; ++i) {
      int key = rand() % 1000;
      auto scp_its = scp_ms_rnd.equal_range(key);
      auto std_its = std_ms_rnd.equal_range(key);
      EXPECT_TRUE(
          equal(scp_its.first, scp_its.second, std_its.first, std_its.second));
    }
  }
}

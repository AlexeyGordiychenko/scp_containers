#include "test.h"

TEST_F(MapTest, DefaultCtor) {
  {
    scp::map<int, std::string> scp_m;
    EXPECT_TRUE(scp_m.empty());
    EXPECT_EQ(scp_m.size(), 0);
  }
  {
    const scp::map<int, std::string> scp_m;
    EXPECT_TRUE(scp_m.empty());
    EXPECT_EQ(scp_m.size(), 0);
  }
}

TEST_F(MapTest, InitializeCtor) {
  {
    scp::map<int, std::string> scp_m = {
        {1, "one"}, {2, "two"},   {3, "three"}, {4, "four"}, {5, "five"},
        {6, "six"}, {7, "seven"}, {8, "eight"}, {9, "nine"}, {10, "ten"}};
    std::map<int, std::string> std_m = {
        {1, "one"}, {2, "two"},   {3, "three"}, {4, "four"}, {5, "five"},
        {6, "six"}, {7, "seven"}, {8, "eight"}, {9, "nine"}, {10, "ten"}};

    EXPECT_TRUE(MapsAreEqual(scp_m, std_m));
  }
  {
    const scp::map<int, std::string> scp_m = {
        {1, "one"}, {2, "two"},   {3, "three"}, {4, "four"}, {5, "five"},
        {6, "six"}, {7, "seven"}, {8, "eight"}, {9, "nine"}, {10, "ten"}};
    const std::map<int, std::string> std_m = {
        {1, "one"}, {2, "two"},   {3, "three"}, {4, "four"}, {5, "five"},
        {6, "six"}, {7, "seven"}, {8, "eight"}, {9, "nine"}, {10, "ten"}};

    EXPECT_TRUE(MapsAreEqual(scp_m, std_m));
  }
}

TEST_F(MapTest, CopyCtor) {
  {
    scp::map<int, int> scp_m1;
    scp::map<int, int> scp_m2(scp_m1);
    std::map<int, int> std_m1;
    std::map<int, int> std_m2(std_m1);

    EXPECT_TRUE(MapsAreEqual(scp_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(scp_m2, std_m2));
  }
  {
    const scp::map<int, int> scp_m1;
    const scp::map<int, int> scp_m2(scp_m1);
    const std::map<int, int> std_m1;
    const std::map<int, int> std_m2(std_m1);

    EXPECT_TRUE(MapsAreEqual(scp_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(scp_m2, std_m2));
  }
  {
    scp::map<int, std::string> scp_m1 = {{10, "10"}};
    scp::map<int, std::string> scp_m2(scp_m1);
    std::map<int, std::string> std_m1 = {{10, "10"}};
    std::map<int, std::string> std_m2(std_m1);
    EXPECT_TRUE(MapsAreEqual(scp_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(scp_m2, std_m2));
  }
  {
    const scp::map<int, std::string> scp_m1 = {{10, "10"}};
    const scp::map<int, std::string> scp_m2(scp_m1);
    const std::map<int, std::string> std_m1 = {{10, "10"}};
    const std::map<int, std::string> std_m2(std_m1);

    EXPECT_TRUE(MapsAreEqual(scp_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(scp_m2, std_m2));
  }
  {
    scp::map<int, std::string> scp_m1 = {
        {10, "10"}, {5, "5"}, {15, "15"}, {6, "6"}, {12, "12"}};
    scp::map<int, std::string> scp_m2(scp_m1);
    std::map<int, std::string> std_m1 = {
        {10, "10"}, {5, "5"}, {15, "15"}, {6, "6"}, {12, "12"}};
    std::map<int, std::string> std_m2(std_m1);

    EXPECT_TRUE(MapsAreEqual(scp_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(scp_m2, std_m2));
  }
  {
    scp::map<int, std::string> scp_m(scp_m_rnd);
    std::map<int, std::string> std_m(std_m_rnd);

    EXPECT_TRUE(MapsAreEqual(scp_m, std_m));
  }
  {
    const scp::map<int, std::string> scp_m(scp_m_rnd);
    const std::map<int, std::string> std_m(std_m_rnd);

    EXPECT_TRUE(MapsAreEqual(scp_m, std_m));
  }
}

TEST_F(MapTest, MoveCtor) {
  {
    scp::map<int, std::string> scp_m1;
    scp::map<int, std::string> scp_m2(std::move(scp_m1));
    std::map<int, std::string> std_m1;
    std::map<int, std::string> std_m2(std::move(std_m1));

    EXPECT_TRUE(MapsAreEqual(scp_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(scp_m2, std_m2));
  }
  {
    const scp::map<int, std::string> scp_m1;
    const scp::map<int, std::string> scp_m2(std::move(scp_m1));
    const std::map<int, std::string> std_m1;
    const std::map<int, std::string> std_m2(std::move(std_m1));

    EXPECT_TRUE(MapsAreEqual(scp_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(scp_m2, std_m2));
  }
  {
    scp::map<int, int> scp_m1 = {{1, 2}};
    scp::map<int, int> scp_m2(std::move(scp_m1));
    std::map<int, int> std_m1 = {{1, 2}};
    std::map<int, int> std_m2(std::move(std_m1));

    EXPECT_TRUE(MapsAreEqual(scp_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(scp_m2, std_m2));
  }
  {
    const scp::map<int, int> scp_m1 = {{1, 2}};
    const scp::map<int, int> scp_m2(std::move(scp_m1));
    const std::map<int, int> std_m1 = {{1, 2}};
    const std::map<int, int> std_m2(std::move(std_m1));

    EXPECT_TRUE(MapsAreEqual(scp_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(scp_m2, std_m2));
  }
  {
    scp::map<int, std::string> scp_m(std::move(scp_m_rnd));
    std::map<int, std::string> std_m(std::move(std_m_rnd));

    EXPECT_TRUE(MapsAreEqual(scp_m, std_m));
  }
  {
    const scp::map<int, std::string> scp_m(std::move(scp_m_rnd));
    const std::map<int, std::string> std_m(std::move(std_m_rnd));

    EXPECT_TRUE(MapsAreEqual(scp_m, std_m));
  }
}

TEST_F(MapTest, AssignmentOperator) {
  {
    scp::map<int, std::string> scp_m1, scp_m2;
    std::map<int, std::string> std_m1, std_m2;

    scp_m2 = scp_m1;
    std_m2 = std_m1;

    EXPECT_TRUE(MapsAreEqual(scp_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(scp_m2, std_m2));
  }
  {
    const scp::map<int, std::string> scp_m1;
    const std::map<int, std::string> std_m1;
    scp::map<int, std::string> scp_m2;
    std::map<int, std::string> std_m2;

    scp_m2 = scp_m1;
    std_m2 = std_m1;

    EXPECT_TRUE(MapsAreEqual(scp_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(scp_m2, std_m2));
  }
  {
    scp::map<int, std::string> scp_m1, scp_m2;
    std::map<int, std::string> std_m1, std_m2;

    scp_m2 = std::move(scp_m1);
    std_m2 = std::move(std_m1);

    EXPECT_TRUE(MapsAreEqual(scp_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(scp_m2, std_m2));
  }
  {
    const scp::map<int, std::string> scp_m1;
    const std::map<int, std::string> std_m1;
    scp::map<int, std::string> scp_m2;
    std::map<int, std::string> std_m2;

    scp_m2 = std::move(scp_m1);
    std_m2 = std::move(std_m1);

    EXPECT_TRUE(MapsAreEqual(scp_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(scp_m2, std_m2));
  }
  {
    scp::map<int, std::string> scp_m1 = {{10, "10"}};
    scp::map<int, std::string> scp_m2;
    std::map<int, std::string> std_m1 = {{10, "10"}};
    std::map<int, std::string> std_m2;

    scp_m2 = scp_m1;
    std_m2 = std_m1;

    EXPECT_TRUE(MapsAreEqual(scp_m1, std_m2));
    EXPECT_TRUE(MapsAreEqual(scp_m1, std_m2));
  }
  {
    const scp::map<int, std::string> scp_m1 = {{10, "10"}};
    scp::map<int, std::string> scp_m2;
    const std::map<int, std::string> std_m1 = {{10, "10"}};
    std::map<int, std::string> std_m2;

    scp_m2 = scp_m1;
    std_m2 = std_m1;

    EXPECT_TRUE(MapsAreEqual(scp_m1, std_m2));
    EXPECT_TRUE(MapsAreEqual(scp_m1, std_m2));
  }
  {
    scp::map<int, std::string> scp_m1 = {{10, "10"}};
    scp::map<int, std::string> scp_m2;
    std::map<int, std::string> std_m1 = {{10, "10"}};
    std::map<int, std::string> std_m2;

    scp_m2 = std::move(scp_m1);
    std_m2 = std::move(std_m1);

    EXPECT_TRUE(MapsAreEqual(scp_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(scp_m2, std_m2));
  }
  {
    const scp::map<int, std::string> scp_m1 = {{10, "10"}};
    scp::map<int, std::string> scp_m2;
    const std::map<int, std::string> std_m1 = {{10, "10"}};
    std::map<int, std::string> std_m2;

    scp_m2 = std::move(scp_m1);
    std_m2 = std::move(std_m1);

    EXPECT_TRUE(MapsAreEqual(scp_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(scp_m2, std_m2));
  }
  {
    scp::map<int, int> scp_m1 = {{69, 42}, {25, 8}, {51, 25}};
    scp::map<int, int> scp_m2 = {{69, 42}};
    std::map<int, int> std_m1 = {{69, 42}, {25, 8}, {51, 25}};
    std::map<int, int> std_m2 = {{69, 42}};

    scp_m2 = scp_m1;
    std_m2 = std_m1;

    EXPECT_TRUE(MapsAreEqual(scp_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(scp_m2, std_m2));
  }
  {
    const scp::map<int, int> scp_m1 = {{69, 42}, {25, 8}, {51, 25}};
    scp::map<int, int> scp_m2 = {{69, 42}};
    const std::map<int, int> std_m1 = {{69, 42}, {25, 8}, {51, 25}};
    std::map<int, int> std_m2 = {{69, 42}};

    scp_m2 = scp_m1;
    std_m2 = std_m1;

    EXPECT_TRUE(MapsAreEqual(scp_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(scp_m2, std_m2));
  }
  {
    scp::map<int, int> scp_m1 = {{69, 42}, {25, 8}, {51, 25}};
    scp::map<int, int> scp_m2 = {{69, 42}};
    std::map<int, int> std_m1 = {{69, 42}, {25, 8}, {51, 25}};
    std::map<int, int> std_m2 = {{69, 42}};

    scp_m2 = std::move(scp_m1);
    std_m2 = std::move(std_m1);

    EXPECT_TRUE(MapsAreEqual(scp_m2, std_m2));
  }
  {
    const scp::map<int, int> scp_m1 = {{69, 42}, {25, 8}, {51, 25}};
    scp::map<int, int> scp_m2 = {{69, 42}};
    const std::map<int, int> std_m1 = {{69, 42}, {25, 8}, {51, 25}};
    std::map<int, int> std_m2 = {{69, 42}};

    scp_m2 = std::move(scp_m1);
    std_m2 = std::move(std_m1);

    EXPECT_TRUE(MapsAreEqual(scp_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(scp_m2, std_m2));
  }
  {
    scp::map<int, std::string> scp_m = {{69, "42"}};
    std::map<int, std::string> std_m = {{69, "42"}};

    scp_m = scp_m_rnd;
    std_m = std_m_rnd;

    EXPECT_TRUE(MapsAreEqual(scp_m, std_m));
  }
  {
    scp::map<int, std::string> scp_m = {{69, "42"}};
    std::map<int, std::string> std_m = {{69, "42"}};

    scp_m = std::move(scp_m_rnd);
    std_m = std::move(std_m_rnd);

    EXPECT_TRUE(MapsAreEqual(scp_m, std_m));
  }
}

TEST_F(MapTest, ElementAccess) {
  {
    EXPECT_EQ(scp_m_static.at(10), "10");
    EXPECT_EQ(scp_m_static.at(50), "50");
    EXPECT_EQ(std_m_static.at(10), "10");
    EXPECT_EQ(std_m_static.at(50), "50");
    EXPECT_THROW(scp_m_static.at(-1), std::out_of_range);
    EXPECT_THROW(scp_m_static.at(1), std::out_of_range);
  }
  {
    const scp::map<int, std::string> scp_m = scp_m_static;
    const std::map<int, std::string> std_m = std_m_static;
    EXPECT_EQ(scp_m.at(10), "10");
    EXPECT_EQ(scp_m.at(50), "50");
    EXPECT_THROW(scp_m.at(-1), std::out_of_range);
    EXPECT_THROW(scp_m.at(1), std::out_of_range);
    EXPECT_EQ(std_m.at(10), "10");
    EXPECT_EQ(std_m.at(50), "50");
    EXPECT_THROW(std_m.at(-1), std::out_of_range);
    EXPECT_THROW(std_m.at(1), std::out_of_range);
  }
  {
    scp::map<int, std::string> scp_m = scp_m_static;
    std::map<int, std::string> std_m = std_m_static;
    EXPECT_EQ(scp_m[50], "50");
    EXPECT_EQ(std_m[50], "50");
    scp_m[50] = "new_50";
    std_m[50] = "new_50";
    scp_m[1] = "100";
    std_m[1] = "100";

    EXPECT_TRUE(MapsAreEqual(scp_m, std_m));
  }
}

TEST_F(MapTest, Iterator) {
  {
    auto scp_it = scp_m_rnd.begin();
    auto std_it = std_m_rnd.begin();
    MoveForwardBackward(scp_it, std_it);
  }
  {
    const auto scp_m = scp_m_rnd;
    const auto std_m = std_m_rnd;
    auto scp_it = scp_m.begin();
    auto std_it = std_m.begin();
    MoveForwardBackward(scp_it, std_it);
  }
  {
    auto scp_it = scp_m_rnd.end();
    auto std_it = std_m_rnd.end();
    MoveBackwardForward(scp_it, std_it);
  }
  {
    const auto scp_m = scp_m_rnd;
    const auto std_m = std_m_rnd;
    auto scp_it = scp_m.end();
    auto std_it = std_m.end();
    MoveBackwardForward(scp_it, std_it);
  }
  {
    auto scp_it = scp_m_rnd.rbegin();
    auto std_it = std_m_rnd.rbegin();
    MoveForwardBackward(scp_it, std_it);
  }
  {
    const auto scp_m = scp_m_rnd;
    const auto std_m = std_m_rnd;
    auto scp_it = scp_m.rbegin();
    auto std_it = std_m.rbegin();
    MoveForwardBackward(scp_it, std_it);
  }
  {
    auto scp_it = scp_m_rnd.rend();
    auto std_it = std_m_rnd.rend();
    MoveBackwardForward(scp_it, std_it);
  }
  {
    const auto scp_m = scp_m_rnd;
    const auto std_m = std_m_rnd;
    auto scp_it = scp_m.rend();
    auto std_it = std_m.rend();
    MoveBackwardForward(scp_it, std_it);
  }
  {
    auto scp_it = scp_m_rnd.cbegin();
    auto std_it = std_m_rnd.cbegin();
    MoveForwardBackward(scp_it, std_it);
  }
  {
    auto scp_it = scp_m_rnd.cend();
    auto std_it = std_m_rnd.cend();
    MoveBackwardForward(scp_it, std_it);
  }
  {
    auto scp_it = scp_m_rnd.crbegin();
    auto std_it = std_m_rnd.crbegin();
    MoveForwardBackward(scp_it, std_it);
  }
  {
    auto scp_it = scp_m_rnd.crend();
    auto std_it = std_m_rnd.crend();
    MoveBackwardForward(scp_it, std_it);
  }
  {
    scp::map<int, std::string> scp_m;
    std::map<int, std::string> std_m;

    for (auto i = 2; i < 100000; ++i) {
      auto key_value = std::make_pair(i, std::to_string(i));
      auto scp_it = scp_m.insert(key_value);
      auto std_it = std_m.insert(key_value);

      EXPECT_EQ(*scp_it.first, *std_it.first);
      EXPECT_EQ(scp_it.second, std_it.second);
    }

    for (auto i = 2; i < 1000; i++) {
      auto it_scp = scp_m.begin();
      auto it_std = std_m.begin();
      while (it_scp != scp_m.end()) {
        if (it_scp->first % i == 0) {
          scp_m.erase(it_scp++);
          std_m.erase(it_std++);
        } else {
          ++it_scp;
          ++it_std;
        }
      }
    }

    EXPECT_TRUE(MapsAreEqual(scp_m, std_m));
  }
}

TEST_F(MapTest, Capacity) {
  {
    scp::map<int, int> scp_m;
    std::map<int, int> std_m;
    EXPECT_EQ(scp_m.empty(), std_m.empty());
    EXPECT_EQ(scp_m.size(), std_m.size());
  }
  {
    scp::map<int, std::string> scp_m = {{10, "10"}};
    std::map<int, std::string> std_m = {{10, "10"}};
    EXPECT_EQ(scp_m.empty(), std_m.empty());
    EXPECT_EQ(scp_m.size(), std_m.size());
    EXPECT_DOUBLE_EQ(static_cast<double>(std_m.max_size()) / scp_m.max_size(),
                     max_size_ratio);
  }
  {
    EXPECT_EQ(scp_m_rnd.empty(), std_m_rnd.empty());
    EXPECT_EQ(scp_m_rnd.size(), std_m_rnd.size());
    EXPECT_DOUBLE_EQ(
        static_cast<double>(std_m_rnd.max_size()) / scp_m_rnd.max_size(),
        max_size_ratio);
  }
  {
    EXPECT_EQ(scp_m_static.empty(), scp_m_static.empty());
    EXPECT_EQ(scp_m_static.size(), scp_m_static.size());
    EXPECT_DOUBLE_EQ(
        static_cast<double>(std_m_static.max_size()) / scp_m_static.max_size(),
        max_size_ratio);
  }
}

TEST_F(MapTest, Clear) {
  {
    scp::map<int, int> scp_m;
    std::map<int, int> std_m;
    scp_m.clear();
    std_m.clear();
    EXPECT_EQ(scp_m.empty(), std_m.empty());
    EXPECT_EQ(scp_m.size(), std_m.size());
    EXPECT_TRUE(MapsAreEqual(scp_m, std_m));
  }
  {
    auto scp_m = scp_m_rnd;
    auto std_m = std_m_rnd;
    scp_m.clear();
    std_m.clear();
    EXPECT_EQ(scp_m.empty(), std_m.empty());
    EXPECT_EQ(scp_m.size(), std_m.size());
    EXPECT_TRUE(MapsAreEqual(scp_m, std_m));
  }
}

TEST_F(MapTest, Insert) {
  {
    auto scp_e = scp_m_static.insert_or_assign(10, "ten");
    auto std_e = std_m_static.insert_or_assign(10, "ten");
    EXPECT_EQ(*scp_e.first, *std_e.first);
    EXPECT_EQ(scp_e.second, std_e.second);
  }
  {
    auto scp_e = scp_m_static.insert_or_assign(115, "115");
    auto std_e = std_m_static.insert_or_assign(115, "115");
    EXPECT_EQ(*scp_e.first, *std_e.first);
    EXPECT_EQ(scp_e.second, std_e.second);
  }
  {
    scp::map<int, std::string> scp_m;
    std::map<int, std::string> std_m;
    for (auto i = 0; i < 10000; ++i) {
      auto key = rand() % 1000000;
      auto key_str = std::to_string(key);
      auto scp_e = scp_m.insert(key, key_str);
      auto std_e = std_m.insert(std::make_pair(key, key_str));
      EXPECT_EQ(*scp_e.first, *std_e.first);
      EXPECT_EQ(scp_e.second, std_e.second);
    }
    EXPECT_TRUE(MapsAreEqual(scp_m, std_m));
    auto key_str = "rnd";
    for (auto i : scp_m_rnd) {
      auto scp_e = scp_m.insert_or_assign(i.first, key_str);
      auto std_e = std_m.insert_or_assign(i.first, key_str);
      EXPECT_EQ(*scp_e.first, *std_e.first);
      EXPECT_EQ(scp_e.second, std_e.second);
    }
    EXPECT_TRUE(MapsAreEqual(scp_m, std_m));
  }
}

TEST_F(MapTest, InsertMany_1) {
  scp::map<int, std::string> scp_m;
  std::map<int, std::string> std_m;

  scp_m.insert_many(std::make_pair(10, std::string("10")),
                    std::make_pair(20, std::string("20")),
                    std::make_pair(30, std::string("30")),
                    std::make_pair(40, std::string("40")));
  std_m.insert({{10, "10"}, {20, "20"}, {30, "30"}, {40, "40"}});
  EXPECT_TRUE(MapsAreEqual(scp_m, std_m));
}

TEST_F(MapTest, InsertMany_2) {
  scp::map<int, std::string> scp_m = {{10, "10"}, {20, "20"}};
  std::map<int, std::string> std_m = {{10, "10"}, {20, "20"}};

  scp_m.insert_many(std::make_pair(50, std::string("50")),
                    std::make_pair(30, std::string("30")),
                    std::make_pair(30, std::string("30")),
                    std::make_pair(40, std::string("40")));
  std_m.insert({{50, "50"}, {30, "30"}, {30, "30"}, {40, "40"}});
  EXPECT_TRUE(MapsAreEqual(scp_m, std_m));
}

TEST_F(MapTest, InsertMany_3) {
  scp::map<int, std::string> scp_m = {{10, "10"}, {20, "20"}};
  std::map<int, std::string> std_m = {{10, "10"}, {20, "20"}};

  scp_m.insert_many(std::make_pair(10, std::string("10")),
                    std::make_pair(20, std::string("20")));
  std_m.insert({{10, "10"}, {20, "20"}});
  EXPECT_TRUE(MapsAreEqual(scp_m, std_m));
}

TEST_F(MapTest, Erase) {
  {
    scp_m_rnd.erase(scp_m_rnd.begin());
    std_m_rnd.erase(std_m_rnd.begin());
    EXPECT_TRUE(MapsAreEqual(scp_m_rnd, std_m_rnd));

    scp_m_rnd.erase(--scp_m_rnd.end());
    std_m_rnd.erase(--std_m_rnd.end());
    EXPECT_TRUE(MapsAreEqual(scp_m_rnd, std_m_rnd));

    scp_m_rnd.erase(++scp_m_rnd.begin());
    std_m_rnd.erase(++std_m_rnd.begin());
    EXPECT_TRUE(MapsAreEqual(scp_m_rnd, std_m_rnd));

    scp_m_rnd.erase(--(--scp_m_rnd.end()));
    std_m_rnd.erase(--(--std_m_rnd.end()));
    EXPECT_TRUE(MapsAreEqual(scp_m_rnd, std_m_rnd));

    auto scp_it = scp_m_rnd.end();
    auto std_it = std_m_rnd.end();
    for (int i = 0; i < 111; ++i, --scp_it, --std_it) {
    }
    scp_m_rnd.erase(scp_it);
    std_m_rnd.erase(std_it);
    EXPECT_TRUE(MapsAreEqual(scp_m_rnd, std_m_rnd));

    scp_it = scp_m_rnd.begin();
    std_it = std_m_rnd.begin();
    for (int i = 0; i < 111; ++i, ++scp_it, ++std_it) {
    }
    scp_m_rnd.erase(scp_it);
    std_m_rnd.erase(std_it);
    EXPECT_TRUE(MapsAreEqual(scp_m_rnd, std_m_rnd));
  }
  {
    scp::map<int, std::string> scp_m = {{10, "10"}};
    std::map<int, std::string> std_m = {{10, "10"}};
    scp_m.erase(scp_m.begin());
    std_m.erase(std_m.begin());
    EXPECT_TRUE(MapsAreEqual(scp_m, std_m));
  }
  {
    auto scp_m = scp_m_static;
    auto std_m = std_m_static;
    scp_m.erase(scp_m.find(70));
    std_m.erase(std_m.find(70));
    EXPECT_TRUE(MapsAreEqual(scp_m, std_m));
  }
  {
    auto scp_m = scp_m_static;
    auto std_m = std_m_static;
    scp_m.erase(scp_m.find(30));
    std_m.erase(std_m.find(30));
    EXPECT_TRUE(MapsAreEqual(scp_m, std_m));
  }
  {
    auto scp_m = scp_m_static;
    auto std_m = std_m_static;
    auto key_value = std::make_pair(45, "45");
    scp_m.insert(key_value);
    std_m.insert(key_value);
    scp_m.erase(scp_m.find(40));
    std_m.erase(std_m.find(40));
    EXPECT_TRUE(MapsAreEqual(scp_m, std_m));
  }
  {
    auto scp_m = scp_m_static;
    auto std_m = std_m_static;
    scp_m.erase(scp_m.find(90));
    std_m.erase(std_m.find(90));
    EXPECT_TRUE(MapsAreEqual(scp_m, std_m));
  }
  {
    auto scp_m = scp_m_static;
    auto std_m = std_m_static;
    scp_m.erase(scp_m.find(100));
    std_m.erase(std_m.find(100));
    scp_m.erase(scp_m.find(90));
    std_m.erase(std_m.find(90));
    EXPECT_TRUE(MapsAreEqual(scp_m, std_m));
  }
  {
    auto scp_m = scp_m_static;
    auto std_m = std_m_static;
    scp_m.erase(scp_m.find(100));
    std_m.erase(std_m.find(100));
    scp_m.erase(scp_m.find(90));
    std_m.erase(std_m.find(90));
    scp_m.erase(scp_m.find(40));
    std_m.erase(std_m.find(40));
    scp_m.erase(scp_m.find(110));
    std_m.erase(std_m.find(110));
    EXPECT_TRUE(MapsAreEqual(scp_m, std_m));
  }
  {
    auto std_m_rnd_copy = std_m_rnd;
    int i = 0;
    for (auto elem : std_m_rnd_copy) {
      if (i++ % 3 == 0) {
        scp_m_rnd.erase(scp_m_rnd.find(elem.first));
        std_m_rnd.erase(std_m_rnd.find(elem.first));
      }
    }
    EXPECT_TRUE(MapsAreEqual(scp_m_rnd, std_m_rnd));
  }
}

TEST_F(MapTest, Swap) {
  {
    scp::map<int, std::string> scp_m1, scp_m2;
    std::map<int, std::string> std_m1, std_m2;
    scp_m1.swap(scp_m2);
    std_m1.swap(std_m2);
    EXPECT_TRUE(MapsAreEqual(scp_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(scp_m2, std_m2));
  }
  {
    scp::map<int, std::string> scp_m1;
    scp::map<int, std::string> scp_m2 = {{1, "1"}};
    std::map<int, std::string> std_m1;
    std::map<int, std::string> std_m2 = {{1, "1"}};
    scp_m1.swap(scp_m2);
    std_m1.swap(std_m2);
    EXPECT_TRUE(MapsAreEqual(scp_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(scp_m2, std_m2));
    scp_m2.swap(scp_m1);
    std_m2.swap(std_m1);
    EXPECT_TRUE(MapsAreEqual(scp_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(scp_m2, std_m2));
  }
  {
    scp_m_static.swap(scp_m_rnd);
    std_m_static.swap(std_m_rnd);
    EXPECT_TRUE(MapsAreEqual(scp_m_rnd, std_m_rnd));
    EXPECT_TRUE(MapsAreEqual(scp_m_static, std_m_static));
  }
}

TEST_F(MapTest, Merge) {
  {
    scp::map<int, std::string> scp_m1, scp_m2;
    std::map<int, std::string> std_m1, std_m2;
    scp_m1.merge(scp_m2);
    std_m1.merge(std_m2);
    EXPECT_TRUE(MapsAreEqual(scp_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(scp_m2, std_m2));
  }
  {
    scp::map<int, std::string> scp_m1 = {{1, "1"}};
    scp::map<int, std::string> scp_m2;
    std::map<int, std::string> std_m1 = {{1, "1"}};
    std::map<int, std::string> std_m2;
    scp_m1.merge(scp_m2);
    std_m1.merge(std_m2);
    EXPECT_TRUE(MapsAreEqual(scp_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(scp_m2, std_m2));
  }
  {
    scp::map<int, std::string> scp_m1;
    scp::map<int, std::string> scp_m2 = {{1, "1"}};
    std::map<int, std::string> std_m1;
    std::map<int, std::string> std_m2 = {{1, "1"}};
    scp_m1.merge(scp_m2);
    std_m1.merge(std_m2);
    EXPECT_TRUE(MapsAreEqual(scp_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(scp_m2, std_m2));
  }
  {
    scp::map<int, std::string> scp_m1 = {{2, "2"}};
    scp::map<int, std::string> scp_m2 = {{1, "1"}};
    std::map<int, std::string> std_m1 = {{2, "2"}};
    std::map<int, std::string> std_m2 = {{1, "1"}};
    scp_m1.merge(scp_m2);
    std_m1.merge(std_m2);
    EXPECT_TRUE(MapsAreEqual(scp_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(scp_m2, std_m2));
  }
  {
    scp::map<int, std::string> scp_m1 = {{1, "1"}, {2, "2"}};
    scp::map<int, std::string> scp_m2 = {{1, "1"}};
    std::map<int, std::string> std_m1 = {{1, "1"}, {2, "2"}};
    std::map<int, std::string> std_m2 = {{1, "1"}};
    scp_m1.merge(scp_m2);
    std_m1.merge(std_m2);
    EXPECT_TRUE(MapsAreEqual(scp_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(scp_m2, std_m2));
  }
  {
    scp::map<int, std::string> scp_m1 = {{1, "1"}, {2, "2"}};
    scp::map<int, std::string> scp_m2 = {{1, "1"}, {3, "3"}};
    std::map<int, std::string> std_m1 = {{1, "1"}, {2, "2"}};
    std::map<int, std::string> std_m2 = {{1, "1"}, {3, "3"}};
    scp_m1.merge(scp_m2);
    std_m1.merge(std_m2);
    EXPECT_TRUE(MapsAreEqual(scp_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(scp_m2, std_m2));
  }
  {
    scp::map<int, std::string> scp_m1 = {
        {1, "1"}, {2, "2"}, {0, "0"}, {-1, "-1"}, {2, "2"}};
    scp::map<int, std::string> scp_m2 = {
        {1, "1"}, {3, "3"}, {2, "2"}, {4, "4"}, {5, "5"}};
    std::map<int, std::string> std_m1 = {
        {1, "1"}, {2, "2"}, {0, "0"}, {-1, "-1"}, {2, "2"}};
    std::map<int, std::string> std_m2 = {
        {1, "1"}, {3, "3"}, {2, "2"}, {4, "4"}, {5, "5"}};
    scp_m1.merge(scp_m2);
    std_m1.merge(std_m2);
    EXPECT_TRUE(MapsAreEqual(scp_m1, std_m1));
    EXPECT_TRUE(MapsAreEqual(scp_m2, std_m2));
  }
  {
    scp::map<int, std::string> scp_m;
    std::map<int, std::string> std_m;
    for (int i = 0; i < 100000; ++i) {
      auto key = rand() % 1000000;
      auto key_value = std::make_pair(key, std::to_string(key));
      scp_m.insert(key_value);
      std_m.insert(key_value);
    }
    scp_m.merge(scp_m_rnd);
    std_m.merge(std_m_rnd);
    EXPECT_TRUE(MapsAreEqual(scp_m, std_m));
    EXPECT_TRUE(MapsAreEqual(scp_m_rnd, std_m_rnd));
  }
}

TEST_F(MapTest, Lookup) {
  {
    EXPECT_TRUE(scp_m_static.contains(70));
    EXPECT_TRUE(scp_m_static.contains(30));
    EXPECT_TRUE(scp_m_static.contains(40));
    EXPECT_FALSE(scp_m_static.contains(1));
    EXPECT_FALSE(scp_m_static.contains(65));
    EXPECT_FALSE(scp_m_static.contains(200));
  }
  {
    scp::map<int, std::string> scp_m;
    EXPECT_FALSE(scp_m.contains(1));
  }
  {
    const scp::map<int, std::string> scp_m = scp_m_static;
    const std::map<int, std::string> std_m = std_m_static;
    EXPECT_TRUE(scp_m.find(100)->first == 100);
    EXPECT_TRUE(std_m.find(100)->first == 100);
    EXPECT_TRUE(scp_m.find(1000) == scp_m.cend());
    EXPECT_TRUE(std_m.find(1000) == std_m.cend());
  }
}

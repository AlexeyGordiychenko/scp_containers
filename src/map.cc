#include "map.h"

int main() {
  {
    std::cout << "MAP TEST SIZE, EMPTY (non-empty)" << std::endl;
    s21::map<int, std::string> m;
    m.insert({1, "one"});
    m.insert({2, "two"});
    std::cout << m.size() << std::endl;
    std::cout << m.empty() << std::endl;
  }
  {
    std::cout << "MAP TEST SIZE, EMPTY (empty)" << std::endl;
    s21::map<int, std::string> m;
    std::cout << m.size() << std::endl;
    std::cout << m.empty() << std::endl;
  }
  {
    std::cout << "MAP TEST CONTAINS" << std::endl;
    s21::map<int, std::string> m;
    m.insert({1, "one"});
    m.insert({3, "three"});
    std::cout << m.contains(2) << std::endl;
    std::cout << m.contains(1) << std::endl;
  }
  {
    std::cout << "MAP TEST ERASE" << std::endl;
    s21::map<int, std::string> m;
    m.insert({1, "one"});
    auto it = m.insert({3, "three"});
    std::cout << "before" << std::endl;
    for (auto i = m.begin(); i != m.end(); i++) {
      std::cout << i->first << std::endl;
    }
    m.erase(it.first);
    std::cout << "after" << std::endl;
    for (auto i = m.begin(); i != m.end(); i++) {
      std::cout << i->first << std::endl;
    }
  }
  {
    std::cout << "MAP TEST CLEAR" << std::endl;
    s21::map<int, std::string> m;
    m.insert({1, "one"});
    m.insert({3, "three"});
    m.clear();
    std::cout << m.empty() << std::endl;
  }
  {
    std::cout << "MAP INSERT OR ASSIGN" << std::endl;
    s21::map<int, std::string> m;
    m.insert({1, "one"});
    m.insert({3, "three"});
    std::cout << m.insert_or_assign(3, "tree").second;
    std::cout << m.insert_or_assign(4, "four").second << std::endl;
    for (auto i = m.begin(); i != m.end(); i++) {
      std::cout << i->first << ": " << i->second << std::endl;
    }
  }
  {
    std::cout << "MAP COPY CONSTRUCTOR" << std::endl;
    s21::map<int, std::string> m1;
    m1.insert({1, "one"});
    m1.insert({3, "three"});
    s21::map<int, std::string> m2(m1);
    for (auto i = m1.begin(); i != m1.end(); i++) {
      std::cout << i->first << ": " << i->second << std::endl;
    }
    for (auto i = m2.begin(); i != m2.end(); i++) {
      std::cout << i->first << ": " << i->second << std::endl;
    }
  }
  {
    std::cout << "MAP COPY CONSTRUCTOR 2" << std::endl;
    s21::map<int, std::string> m1;
    m1.insert({3, "three"});
    m1.insert({1, "one"});
    s21::map<int, std::string> m2(m1);
    for (auto i = m1.begin(); i != m1.end(); i++) {
      std::cout << i->first << ": " << i->second << std::endl;
    }
    for (auto i = m2.begin(); i != m2.end(); i++) {
      std::cout << i->first << ": " << i->second << std::endl;
    }
  }

  {
    std::cout << "MAP COPY OPERATOR" << std::endl;
    s21::map<int, std::string> m1;
    m1.insert({3, "three"});
    m1.insert({1, "one"});
    s21::map<int, std::string> m2;
    m2 = m1;
    for (auto i = m1.begin(); i != m1.end(); i++) {
      std::cout << i->first << ": " << i->second << std::endl;
    }
    for (auto i = m2.begin(); i != m2.end(); i++) {
      std::cout << i->first << ": " << i->second << std::endl;
    }
  }

  {
    std::cout << "MAP MOVE CONSTRUCTOR" << std::endl;
    s21::map<int, std::string> m1;
    m1.insert({3, "three"});
    m1.insert({1, "one"});
    s21::map<int, std::string> m2 = std::move(m1);
    for (auto i = m2.begin(); i != m2.end(); i++) {
      std::cout << i->first << ": " << i->second << std::endl;
    }
  }

  {
    std::cout << "MAP MOVE OPERATOR" << std::endl;
    s21::map<int, std::string> m1;
    m1.insert({3, "three"});
    m1.insert({1, "one"});
    s21::map<int, std::string> m2;
    m2 = std::move(m1);
    for (auto i = m2.begin(); i != m2.end(); i++) {
      std::cout << i->first << ": " << i->second << std::endl;
    }
  }

  {
    std::cout << "MAP SWAP" << std::endl;
    s21::map<int, std::string> m1;
    m1.insert({1, "one"});
    m1.insert({2, "two"});
    s21::map<int, std::string> m2;
    m2.insert({3, "three"});
    m2.insert({4, " four"});
    m1.swap(m2);
    for (auto i = m1.begin(); i != m1.end(); i++) {
      std::cout << i->first << ": " << i->second << std::endl;
    }
    for (auto i = m2.begin(); i != m2.end(); i++) {
      std::cout << i->first << ": " << i->second << std::endl;
    }
  }
}
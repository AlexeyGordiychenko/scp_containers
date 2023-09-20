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
}
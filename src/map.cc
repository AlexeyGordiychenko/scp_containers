#include "map.h"

int main() {
  {
    s21::map<int, std::string> m;
    m.insert({1, "one"});
    m.insert({2, "two"});
    std::cout << m.size() << std::endl;
    std::cout << m.empty() << std::endl;
  }
  {
    s21::map<int, std::string> m;
    std::cout << m.empty() << std::endl;
  }
}
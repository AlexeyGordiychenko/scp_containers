#ifndef CPP2_S21_CONTAINERS_TESTS_TEST_H_
#define CPP2_S21_CONTAINERS_TESTS_TEST_H_

#include <iostream>
#include <utility>
#include "gtest/gtest.h"

#include "../s21_containers/s21_containers.h"
#include "../s21_containersplus/s21_containersplus.h"

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

template class s21::vector<std::string>;
template class s21::array<int, 2>;

#endif  // CPP2_S21_CONTAINERS_TESTS_TEST_H_

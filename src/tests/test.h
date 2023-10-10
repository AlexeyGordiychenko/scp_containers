#ifndef CPP2_S21_CONTAINERS_TESTS_TEST_H_
#define CPP2_S21_CONTAINERS_TESTS_TEST_H_

#include <iostream>

#include "../s21_containers/s21_containers.h"
#include "../s21_containersplus/s21_containersplus.h"
#include "gtest/gtest.h"

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

#endif  // CPP2_S21_CONTAINERS_TESTS_TEST_H_

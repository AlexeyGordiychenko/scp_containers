#include "test.h"

ClassWithPrintableDestructor::ClassWithPrintableDestructor() : a(new int[33]) {
  std::cout << "_Constructor called" << std::endl;
}

ClassWithPrintableDestructor::~ClassWithPrintableDestructor() {
  delete[] a;
  std::cout << "___Destructor called" << std::endl;
}

ClassNoDefaultConstructor::ClassNoDefaultConstructor(int n) : a(n) {}

ClassNoDefaultConstructor::~ClassNoDefaultConstructor() {
  a = 0;
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
#ifdef __APPLE__
  free(__cxxabiv1::__cxa_get_globals());
#endif
  return RUN_ALL_TESTS();
}

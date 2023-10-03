#ifndef CPP2_S21_CONTAINERS_S21_CONTAINERS_VECTOR_S21_VECTOR_CONST_ITERATOR_H_
#define CPP2_S21_CONTAINERS_S21_CONTAINERS_VECTOR_S21_VECTOR_CONST_ITERATOR_H_

#include "s21_vector.h"

namespace s21 {
template <typename T>
class VectorConstIterator {
 public:
  VectorConstIterator() = delete;

 private:
  const T* pointer_;
};
}  //  namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_CONTAINERS_VECTOR_S21_VECTOR_CONST_ITERATOR_H_

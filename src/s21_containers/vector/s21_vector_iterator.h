#ifndef CPP2_S21_CONTAINERS_S21_CONTAINERS_VECTOR_S21_VECTOR_ITERATOR_H_
#define CPP2_S21_CONTAINERS_S21_CONTAINERS_VECTOR_S21_VECTOR_ITERATOR_H_

#include "s21_vector.h"

namespace s21 {
template <typename T>
class VectorIterator {
 public:
  VectorIterator() = delete;
  VectorIterator(T* ptr) noexcept;
  ~VectorIterator();

 private:
  T* pointer_;
};

template <typename T>
VectorIterator<T>::VectorIterator(T* ptr) noexcept : pointer_(ptr) {}

template <typename T>
VectorIterator<T>::~VectorIterator() {
  pointer_ = nullptr;
}
}  //  namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_CONTAINERS_VECTOR_S21_VECTOR_ITERATOR_H_

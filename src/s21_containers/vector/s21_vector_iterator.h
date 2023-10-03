#ifndef CPP2_S21_CONTAINERS_S21_CONTAINERS_VECTOR_S21_VECTOR_ITERATOR_H_
#define CPP2_S21_CONTAINERS_S21_CONTAINERS_VECTOR_S21_VECTOR_ITERATOR_H_

#include "s21_vector.h"

namespace s21 {
  template <typename T>
  class vector<T>::VectorIterator {
   public:
    vector<T>::VectorIterator::VectorIterator() = delete;
    vector<T>::VectorIterator::VectorIterator(T* ptr) noexcept;
    vector<T>::VectorIterator::~VectorIterator() noexcept;



   private:
    T * pointer_;
  };
} //  namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_CONTAINERS_VECTOR_S21_VECTOR_ITERATOR_H_

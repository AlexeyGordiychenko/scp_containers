#ifndef CPP2_S21_CONTAINERS_S21_CONTAINERS_VECTOR_S21_VECTOR_CONST_ITERATOR_H_
#define CPP2_S21_CONTAINERS_S21_CONTAINERS_VECTOR_S21_VECTOR_CONST_ITERATOR_H_

#include "s21_vector.h"

namespace s21 {
template <typename T>
class VectorConstIterator {
 public:
  using reference = T &;

  VectorConstIterator() = delete;
  VectorConstIterator(T* ptr) noexcept;
  ~VectorConstIterator();

  reference operator*();
  VectorConstIterator<T> operator++(int);
  VectorConstIterator<T>& operator++();
  VectorConstIterator<T> operator--(int);
  VectorConstIterator<T>& operator--();
  bool operator==(const VectorConstIterator<T>& other) const noexcept;
  bool operator!=(const VectorConstIterator<T>& other) const noexcept;

 private:
  const T* pointer_;
};

template <typename T>
VectorConstIterator<T>::VectorConstIterator(T* ptr) noexcept : pointer_(ptr) {}

template <typename T>
VectorConstIterator<T>::~VectorConstIterator() {
  pointer_ = nullptr;
}

template <typename T>
typename VectorConstIterator<T>::reference VectorConstIterator<T>::operator*() { 
  return *pointer_;
}

template <typename T>
VectorConstIterator<T> VectorConstIterator<T>::operator++(int) { 
  VectorConstIterator tmp(*this);
  ++pointer_;

  return tmp;
}

template <typename T>
VectorConstIterator<T>& VectorConstIterator<T>::operator++() { 
  ++pointer_;

  return *this;
}

template <typename T>
VectorConstIterator<T> VectorConstIterator<T>::operator--(int) { 
  VectorConstIterator tmp(*this);
  --pointer_;

  return tmp;
}

template <typename T>
VectorConstIterator<T>& VectorConstIterator<T>::operator--() { 
  --pointer_;

  return *this;
}

template <typename T>
bool VectorConstIterator<T>::operator==(const VectorConstIterator<T>& other) const noexcept {
  return pointer_ == other.pointer_;
}

template <typename T>
bool VectorConstIterator<T>::operator!=(const VectorConstIterator<T>& other) const noexcept {
  return pointer_ != other.pointer_;
}

}  //  namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_CONTAINERS_VECTOR_S21_VECTOR_CONST_ITERATOR_H_

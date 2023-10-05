#ifndef CPP2_S21_CONTAINERS_S21_CONTAINERS_VECTOR_S21_VECTOR_ITERATOR_H_
#define CPP2_S21_CONTAINERS_S21_CONTAINERS_VECTOR_S21_VECTOR_ITERATOR_H_

#include "s21_vector.h"

namespace s21 {
template <typename T>
class VectorIterator {
 public:
  using reference = T &;

  VectorIterator() = delete;
  VectorIterator(T* ptr) noexcept;
  ~VectorIterator();

  reference operator*();
  VectorIterator<T> operator++(int);
  VectorIterator<T>& operator++();
  VectorIterator<T> operator--(int);
  VectorIterator<T>& operator--();
  bool operator==(const VectorIterator<T>& other) const noexcept;
  bool operator!=(const VectorIterator<T>& other) const noexcept;

 private:
  T* pointer_;
};

template <typename T>
VectorIterator<T>::VectorIterator(T* ptr) noexcept : pointer_(ptr) {}

template <typename T>
VectorIterator<T>::~VectorIterator() {
  pointer_ = nullptr;
}

template <typename T>
typename VectorIterator<T>::reference VectorIterator<T>::operator*() { 
  return *pointer_;
}

template <typename T>
VectorIterator<T> VectorIterator<T>::operator++(int) { 
  VectorIterator tmp(*this);
  ++pointer_;

  return tmp;
}

template <typename T>
VectorIterator<T>& VectorIterator<T>::operator++() { 
  ++pointer_;

  return *this;
}

template <typename T>
VectorIterator<T> VectorIterator<T>::operator--(int) { 
  VectorIterator tmp(*this);
  --pointer_;

  return tmp;
}

template <typename T>
VectorIterator<T>& VectorIterator<T>::operator--() { 
  --pointer_;

  return *this;
}

template <typename T>
bool VectorIterator<T>::operator==(const VectorIterator<T>& other) const noexcept {
  return pointer_ == other.pointer_;
}

template <typename T>
bool VectorIterator<T>::operator!=(const VectorIterator<T>& other) const noexcept {
  return pointer_ != other.pointer_;
}

}  //  namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_CONTAINERS_VECTOR_S21_VECTOR_ITERATOR_H_

#ifndef CPP2_S21_CONTAINERS_S21_CONTAINERS_VECTOR_S21_VECTOR_CONST_ITERATOR_H_
#define CPP2_S21_CONTAINERS_S21_CONTAINERS_VECTOR_S21_VECTOR_CONST_ITERATOR_H_

#include "s21_vector.h"

namespace s21 {
template <typename T>
class VectorConstIterator {
 public:
  using const_reference = const T&;
  using size_type = size_t;

  VectorConstIterator() = delete;
  explicit VectorConstIterator(T* ptr) noexcept;
  ~VectorConstIterator();

  const_reference operator*() const;
  bool operator==(const VectorConstIterator<T>& other) const noexcept;
  bool operator!=(const VectorConstIterator<T>& other) const noexcept;

  ptrdiff_t operator-(const VectorConstIterator<T>& other) const;

 protected:
  const T* pointer_;
};

template <typename T>
VectorConstIterator<T>::VectorConstIterator(T* ptr) noexcept : pointer_(ptr) {}

template <typename T>
VectorConstIterator<T>::~VectorConstIterator() {}

template <typename T>
typename VectorConstIterator<T>::const_reference VectorConstIterator<T>::operator*() const {
  return *pointer_;
}

template <typename T>
bool VectorConstIterator<T>::operator==(
    const VectorConstIterator<T>& other) const noexcept {
  return pointer_ == other.pointer_;
}

template <typename T>
bool VectorConstIterator<T>::operator!=(
    const VectorConstIterator<T>& other) const noexcept {
  return pointer_ != other.pointer_;
}

template <typename T>
ptrdiff_t VectorConstIterator<T>::operator-(
    const VectorConstIterator<T>& other) const {
  return pointer_ - other.pointer_;
}
}  //  namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_CONTAINERS_VECTOR_S21_VECTOR_CONST_ITERATOR_H_

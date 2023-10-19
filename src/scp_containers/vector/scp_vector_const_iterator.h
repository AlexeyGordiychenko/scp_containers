#ifndef CPP2_SCP_CONTAINERS_SCP_CONTAINERS_VECTOR_SCP_VECTOR_CONST_ITERATOR_H_
#define CPP2_SCP_CONTAINERS_SCP_CONTAINERS_VECTOR_SCP_VECTOR_CONST_ITERATOR_H_

#include "scp_vector.h"

namespace scp {
template <typename T>
class VectorConstIterator {
 public:
  using const_reference = const T&;
  using size_type = size_t;

  VectorConstIterator() = delete;
  explicit VectorConstIterator(T* ptr) noexcept;
  ~VectorConstIterator();

  const_reference operator*();
  VectorConstIterator<T> operator++(int);
  VectorConstIterator<T>& operator++();
  VectorConstIterator<T> operator--(int);
  VectorConstIterator<T>& operator--();

  bool operator==(const VectorConstIterator<T>& other) const noexcept;
  bool operator!=(const VectorConstIterator<T>& other) const noexcept;

  ptrdiff_t operator-(const VectorConstIterator<T>& other) const;
  VectorConstIterator<T> operator-(size_type n) const;
  VectorConstIterator<T> operator+(size_type n) const;

 protected:
  T* pointer_;
};

template <typename T>
VectorConstIterator<T>::VectorConstIterator(T* ptr) noexcept : pointer_(ptr) {}

template <typename T>
VectorConstIterator<T>::~VectorConstIterator() {}

template <typename T>
typename VectorConstIterator<T>::const_reference
VectorConstIterator<T>::operator*() {
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
VectorConstIterator<T> VectorConstIterator<T>::operator-(size_type n) const {
  VectorConstIterator tmp(*this);

  for (size_type i = 0; i < n; ++i) tmp--;

  return tmp;
}

template <typename T>
VectorConstIterator<T> VectorConstIterator<T>::operator+(size_type n) const {
  VectorConstIterator tmp(*this);

  for (size_type i = 0; i < n; ++i) tmp++;

  return tmp;
}
}  //  namespace scp

#endif  // CPP2_SCP_CONTAINERS_SCP_CONTAINERS_VECTOR_SCP_VECTOR_CONST_ITERATOR_H_

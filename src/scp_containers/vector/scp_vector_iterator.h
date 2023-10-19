#ifndef CPP2_SCP_CONTAINERS_SCP_CONTAINERS_VECTOR_SCP_VECTOR_ITERATOR_H_
#define CPP2_SCP_CONTAINERS_SCP_CONTAINERS_VECTOR_SCP_VECTOR_ITERATOR_H_

#include "scp_vector.h"

namespace scp {
template <typename T>
class VectorIterator {
 public:
  using reference = T&;
  using size_type = size_t;

  VectorIterator() = delete;
  explicit VectorIterator(T* ptr) noexcept;
  ~VectorIterator();

  reference operator*();
  VectorIterator<T> operator++(int);
  VectorIterator<T>& operator++();
  VectorIterator<T> operator--(int);
  VectorIterator<T>& operator--();
  bool operator==(const VectorIterator<T>& other) const noexcept;
  bool operator!=(const VectorIterator<T>& other) const noexcept;

  ptrdiff_t operator-(const VectorIterator<T>& other) const;
  VectorIterator<T> operator-(size_type n) const;
  VectorIterator<T> operator+(size_type n) const;

 protected:
  T* pointer_;
};

template <typename T>
VectorIterator<T>::VectorIterator(T* ptr) noexcept : pointer_(ptr) {}

template <typename T>
VectorIterator<T>::~VectorIterator() {}

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
bool VectorIterator<T>::operator==(
    const VectorIterator<T>& other) const noexcept {
  return pointer_ == other.pointer_;
}

template <typename T>
bool VectorIterator<T>::operator!=(
    const VectorIterator<T>& other) const noexcept {
  return pointer_ != other.pointer_;
}

template <typename T>
ptrdiff_t VectorIterator<T>::operator-(const VectorIterator<T>& other) const {
  return pointer_ - other.pointer_;
}

template <typename T>
VectorIterator<T> VectorIterator<T>::operator-(size_type n) const {
  VectorIterator tmp(*this);

  for (size_type i = 0; i < n; ++i) tmp--;

  return tmp;
}

template <typename T>
VectorIterator<T> VectorIterator<T>::operator+(size_type n) const {
  VectorIterator tmp(*this);

  for (size_type i = 0; i < n; ++i) tmp++;

  return tmp;
}

}  //  namespace scp

#endif  // CPP2_SCP_CONTAINERS_SCP_CONTAINERS_VECTOR_SCP_VECTOR_ITERATOR_H_

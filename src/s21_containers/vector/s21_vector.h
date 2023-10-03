#ifndef CPP2_S21_CONTAINERS_S21_CONTAINERS_VECTOR_S21_VECTOR_H_
#define CPP2_S21_CONTAINERS_S21_CONTAINERS_VECTOR_S21_VECTOR_H_

#include <initializer_list>
#include <limits>

#include "s21_vector_const_iterator.h"
#include "s21_vector_iterator.h"

namespace s21 {
template <typename T>
class vector {
 public:
  class VectorIterator<T>;
  class VectorConstIterator<T>;

  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  using iterator = VectorIterator<T>;
  using const_iterator = VectorConstIterator<T>;
  // using iterator_simple = T *;
  // using const_iterator_simple = const T *;

  vector();
  vector(size_type n);
  vector(std::initializer_list<value_type> const &items);
  vector(const vector &v);
  vector(vector &&v);
  ~vector();
  vector &operator=(vector &&v);

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;
  const_reference front() const;
  const_reference back() const;
  T *data() const noexcept;

  iterator begin();
  iterator end();
  const_iterator cbegin();
  const_iterator cend();

  bool empty();
  size_type size() const noexcept;
  size_type max_size() const noexcept;
  void reserve(size_type size);
  size_type capacity() const noexcept;
  void shrink_to_fit();

  void clear();
  // iterator insert(iterator pos, const_reference value);
  // void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other);

 private:
  T *data_;
  size_type size_;
  size_type capacity_;
};

///===VECTOR_MEMBER_FUNCTIONS==============================
template <typename T>
vector<T>::vector() : data_(nullptr), size_(0), capacity_(0) {}

template <typename T>
vector<T>::~vector() {
  delete[] data_;

  size_ = 0;
  capacity_ = 0;
  data_ = nullptr;
}

template <typename T>
vector<T>::vector(size_type n)
    : data_(n > 0 ? new value_type[n] : nullptr), size_(n), capacity_(n) {
  if (data_ == nullptr && n > 0) {
    throw std::bad_alloc();
  }

  std::fill_n(data_, n, value_type());
}

template <typename T>
vector<T>::vector(std::initializer_list<value_type> const &items)
    : data_(items.size() > 0 ? new value_type[items.size()] : nullptr),
      size_(items.size()),
      capacity_(items.size()) {
  if (data_ == nullptr && items.size() > 0) {
    throw std::bad_alloc();
  }

  // std::copy();
}

///===VECTOR_ELEMENT_ACCESS================================
template <typename T>
T *vector<T>::data() const noexcept {
  return data_;
}

///===VECTOR_ITERATORS=====================================

///===VECTOR_CAPACITY======================================
template <typename T>
typename vector<T>::size_type vector<T>::size() const noexcept {
  return size_;
}

template <typename T>
typename vector<T>::size_type vector<T>::max_size() const noexcept {
  return (std::numeric_limits<std::size_t>::max() / sizeof(value_type));
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() const noexcept {
  return capacity_;
}

///===VECTOR_MODIFIERS=====================================

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_CONTAINERS_VECTOR_S21_VECTOR_H_

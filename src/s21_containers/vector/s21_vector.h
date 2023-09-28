#ifndef CPP2_S21_CONTAINERS_S21_CONTAINERS_VECTOR_S21_VECTOR_H_
#define CPP2_S21_CONTAINERS_S21_CONTAINERS_VECTOR_S21_VECTOR_H_

#include <iostream>

namespace s21 {
template <typename T>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  // using iterator = ...
  // using const_iterator = ...
  using iterator_simple = T *;
  using const_iterator_simple = const T *;

  vector();
  vector(size_type n);
  vector(std::initializer_list<value_type> const &items);
  vector(const vector &v);
  vector(vector &&v);

  vector& operator=(vector &&v);

  ~vector();

 private:
  iterator_simple data_;
  size_type size_;
  size_type capacity_;
};

template <typename T>
vector<T>::vector() : data_(nullptr), size_(0), capacity_(0)  {}

template <typename T>
vector<T>::~vector() {
  delete[] data_;

  size_ = 0;
  capacity_ = 0;
  data_ = nullptr;
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_CONTAINERS_VECTOR_S21_VECTOR_H_

#ifndef CPP2_S21_CONTAINERS_S21_CONTAINERSPLUS_ARRAY_S21_ARRAY_H_
#define CPP2_S21_CONTAINERS_S21_CONTAINERSPLUS_ARRAY_S21_ARRAY_H_

#include <initializer_list>
#include <limits>

#include "../../s21_containers/vector/s21_vector_const_iterator.h"
#include "../../s21_containers/vector/s21_vector_iterator.h"

namespace s21 {
template <class T, std::size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  using iterator = T *;
  using const_iterator = const T *;

  array() = default;
  array(const array<T, N> &v) = default;
  array(array<T, N> &&v) = default;
  ~array() = default;
  array<T, N> &operator=(array<T, N> &&v) = default;
  array<T, N> &operator=(const array<T, N> &v) = default;
  array(std::initializer_list<value_type> const &items);

  reference at(size_type pos);
  const_reference at(size_type pos) const;
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;
  reference front();
  const_reference front() const;
  reference back();
  const_reference back() const;
  T *data() noexcept;

  iterator begin() noexcept;
  iterator end() noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;

  bool empty() noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  void swap(array<T, N> &other) noexcept;
  void fill(const_reference value);

 private:
  T data_[N > 0 ? N : 1];
};

template <typename T, std::size_t N>
array<T, N>::array(std::initializer_list<value_type> const &items) {
  std::copy(items.begin(), items.end(), data_);
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::at(size_type pos) {
  if (pos >= size()) {
    throw std::out_of_range("at(): Position is out of range");
  }

  return data_[pos];
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::at(size_type pos) const {
  if (pos >= size()) {
    throw std::out_of_range("at(const): Position is out of range");
  }

  return data_[pos];
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::operator[](size_type pos) {
  return data_[pos];
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::operator[](
    size_type pos) const {
  return data_[pos];
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::front() {
  return data_[0];
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::front() const {
  return data_[0];
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::back() {
  return N > 0 ? data_[size() - 1] : data_[size()];
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::back() const {
  return N > 0 ? data_[size() - 1] : data_[size()];
}

template <typename T, std::size_t N>
T *array<T, N>::data() noexcept {
  return data_;
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::begin() noexcept {
  return data_;
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::end() noexcept {
  return data_ + size();
}

template <typename T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::cbegin() const noexcept {
  return data_;
}

template <typename T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::cend() const noexcept {
  return data_ + size();
}

template <typename T, std::size_t N>
bool array<T, N>::empty() noexcept {
  return begin() == end();
}

template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::size() const noexcept {
  return N;
}

template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::max_size() const noexcept {
  return N;
}

template <typename T, std::size_t N>
void array<T, N>::swap(array<T, N> &other) noexcept {
  std::swap_ranges(data_, data_ + N, other.data_);
}

template <typename T, std::size_t N>
void array<T, N>::fill(const_reference value) {
  std::fill_n(begin(), size(), value);
}
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_CONTAINERSPLUS_ARRAY_S21_ARRAY_H_

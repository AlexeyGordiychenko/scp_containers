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

  vector();
  vector(size_type n);
  vector(std::initializer_list<value_type> const &items);
  vector(const vector &v);
  vector(vector &&v);
  ~vector() noexcept;
  vector<T>& operator=(vector<T> &&v) noexcept;

  reference at(size_type pos);
  const_reference at(size_type pos) const;
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;
  reference front();
  const_reference front() const;
  reference back();
  const_reference back() const;
  T *data() const noexcept;

  iterator begin() const noexcept;
  iterator end() const noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;
  void reserve(size_type size);
  size_type capacity() const noexcept;
  // void shrink_to_fit();

  void clear() noexcept;
  // iterator insert(iterator pos, const_reference value);
  // void erase(iterator pos);
  // void push_back(const_reference value);
  // void pop_back();
  void swap(vector &other) noexcept;

 private:
  size_type size_;
  size_type capacity_;
  T* data_;
};

///===VECTOR_MEMBER_FUNCTIONS==============================
template <typename T>
vector<T>::vector() : size_(0U), capacity_(0U), data_(nullptr) {}

template <typename T>
vector<T>::~vector() noexcept {
  if (data_) delete[] data_;

  size_ = 0;
  capacity_ = 0;
  data_ = nullptr;
}

template <typename T>
vector<T>::vector(size_type n)
    : size_(n), capacity_(n), data_(n > 0 ? new value_type[n] : nullptr) {
  if (data_ == nullptr && n > 0) {
    throw std::bad_alloc();
  }
}

template <typename T>
vector<T>::vector(std::initializer_list<value_type> const &items) : vector(items.size()) {
  size_type i = 0;
  for (auto it = items.begin(); it != items.end(); ++it, ++i) {
    data_[i] = *it;
  }
}

template <typename T>
vector<T>::vector(const vector &v) : vector(v.size_) {
  capacity_ = v.capacity_;
  for (size_type i = 0; i < size_; ++i) {
    data_[i] = v.data_[i];
  }
}

template <typename T>
vector<T>::vector(vector &&v) : size_(v.size_), capacity_(v.capacity_), data_(v.data_) { 
  v.size_ = 0;
  v.capacity_ = 0;
  v.data_ = nullptr;
}

template <typename T>
vector<T>& vector<T>::operator=(vector<T> &&v) noexcept { 
  if (this != &v) {
    this->swap(v);
    v.~vector();
  }

  return *this;
} 

///===VECTOR_ELEMENT_ACCESS================================
template <typename T>
typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("at: Position is out of range");
  }

  return data_[pos];
}

template <typename T>
typename vector<T>::const_reference vector<T>::at(size_type pos) const {
  if (pos >= size_) {
    throw std::out_of_range("at(const): Position is out of range");
  }

  return data_[pos];
}

template <typename T>
typename vector<T>::reference vector<T>::operator[](size_type pos) {
  return data_[pos];
}

template <typename T>
typename vector<T>::const_reference vector<T>::operator[](size_type pos) const {
  return data_[pos];
}

template <typename T>
typename vector<T>::reference vector<T>::front() {
  return data_[0];
}

template <typename T>
typename vector<T>::const_reference vector<T>::front() const {
  return data_[0];
}

template <typename T>
typename vector<T>::reference vector<T>::back() {
  return data_[size_ - 1];
}

template <typename T>
typename vector<T>::const_reference vector<T>::back() const {
  return data_[size_ - 1];
}

template <typename T>
T *vector<T>::data() const noexcept {
  return data_;
}

///===VECTOR_ITERATORS=====================================
template <typename T>
typename vector<T>::iterator vector<T>::begin() const noexcept {
  return iterator(data_);
}

template <typename T>
typename vector<T>::iterator vector<T>::end() const noexcept {
  return iterator(data_ + size_);
}

template <typename T>
typename vector<T>::const_iterator vector<T>::cbegin() const noexcept {
  return const_iterator(data_);
}

template <typename T>
typename vector<T>::const_iterator vector<T>::cend() const noexcept {
  return const_iterator(data_ + size_);
}

///===VECTOR_CAPACITY======================================
template <typename T>
bool vector<T>::empty() const noexcept {
  return begin() == end();
}

template <typename T>
typename vector<T>::size_type vector<T>::size() const noexcept {
  return size_;
}

template <typename T>
typename vector<T>::size_type vector<T>::max_size() const noexcept {
  return (std::numeric_limits<std::size_t>::max() / sizeof(value_type));
}

template <typename T>
void vector<T>::reserve(size_type new_cap) {
  if (new_cap > max_size())
    throw std::length_error("reserve(): Can't reserve larger than max size");

  if (new_cap > capacity_) {
    value_type* new_data = (value_type*)::operator new(sizeof(value_type));
    std::copy(data_, data_ + size_, new_data);
    delete[] data_;
    data_ = new_data;
    capacity_ = new_cap;
  }
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() const noexcept {
  return capacity_;
}

///===VECTOR_MODIFIERS=====================================
template <typename T>
void vector<T>::clear() noexcept {
  for (VectorIterator<T> iter = begin(); iter != end(); ++iter) {
    std::destroy_at(&(*iter));
  }

  size_ = 0;
}






template <typename T>
void vector<T>::swap(vector<T> &other) noexcept { 
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
  std::swap(data_, other.data_);
} 
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_CONTAINERS_VECTOR_S21_VECTOR_H_

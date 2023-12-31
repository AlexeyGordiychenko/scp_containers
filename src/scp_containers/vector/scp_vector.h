#ifndef CPP2_SCP_CONTAINERS_SCP_CONTAINERS_VECTOR_SCP_VECTOR_H_
#define CPP2_SCP_CONTAINERS_SCP_CONTAINERS_VECTOR_SCP_VECTOR_H_

#include <initializer_list>
#include <limits>

#include "scp_vector_const_iterator.h"
#include "scp_vector_iterator.h"

namespace scp {
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
  vector<T> &operator=(vector<T> &&v) noexcept;
  vector<T> &operator=(const vector<T> &other);

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
  void shrink_to_fit();

  void clear() noexcept;
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other) noexcept;

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <typename... Args>
  void insert_many_back(Args &&...args);

 private:
  size_type size_;
  size_type capacity_;
  T *data_;
};

///===VECTOR_MEMBER_FUNCTIONS==============================
template <typename T>
vector<T>::vector() : size_(0U), capacity_(0U), data_(nullptr) {}

template <typename T>
vector<T>::~vector() noexcept {
  std::destroy_n(data_, size_);
  ::operator delete(data_);

  size_ = 0;
  capacity_ = 0;
  data_ = nullptr;
}

template <typename T>
vector<T>::vector(size_type n)
    : size_(n),
      capacity_(n),
      data_(n > 0 ? (value_type *)::operator new(sizeof(value_type) * n)
                  : nullptr) {
  if (data_ == nullptr && n > 0) {
    throw std::bad_alloc();
  }

  for (size_type i = 0; i < n; ++i) new (data_ + i) value_type;
}

template <typename T>
vector<T>::vector(std::initializer_list<value_type> const &items)
    : vector(items.size()) {
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
vector<T>::vector(vector &&v)
    : size_(v.size_), capacity_(v.capacity_), data_(v.data_) {
  v.size_ = 0;
  v.capacity_ = 0;
  v.data_ = nullptr;
}

template <typename T>
vector<T> &vector<T>::operator=(vector<T> &&v) noexcept {
  if (this != &v) {
    this->swap(v);
  }

  return *this;
}

template <typename T>
vector<T> &vector<T>::operator=(const vector<T> &other) {
  if (this != &other) {
    data_ = (value_type *)::operator new(sizeof(value_type) * other.size());
    capacity_ = other.capacity_;
    size_ = other.size_;
    for (size_type i = 0; i < other.size(); ++i) {
      new (data_ + i) value_type;
      data_[i] = other.data_[i];
    }

    capacity_ = other.capacity_;
    size_ = other.size_;
  }

  return *this;
}

///===VECTOR_ELEMENT_ACCESS================================
template <typename T>
typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("at(): Position is out of range");
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
    value_type *new_data =
        (value_type *)::operator new(sizeof(value_type) * new_cap);
    for (size_type i = 0; i < size_; ++i) new (new_data + i) value_type(at(i));

    std::destroy_n(data_, size_);

    ::operator delete(data_);
    data_ = new_data;
    capacity_ = new_cap;
  }
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() const noexcept {
  return capacity_;
}

template <typename T>
void vector<T>::shrink_to_fit() {
  if (capacity_ > size_) {
    value_type *new_data =
        (value_type *)::operator new(sizeof(value_type) * size_);
    for (size_type i = 0; i < size_; ++i) new (new_data + i) value_type(at(i));

    // std::copy(data_, data_ + size_, new_data);
    for (size_type i = 0; i < size_; ++i) std::destroy_at(data_ + i);

    ::operator delete(data_);
    data_ = new_data;
    capacity_ = size_;
  }
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
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  size_type diff = pos - begin();

  if (diff > size_) {
    throw std::out_of_range("insert(): Position is out of range");
  }

  if (size_ == capacity_) {
    reserve(capacity_ > 0 ? (2U * capacity_) : (1U));
  }
  new (data_ + size_) value_type(value);

  iterator new_pos = begin() + diff;

  for (iterator iter = end(); iter != new_pos; --iter) {
    *iter = *(iter - 1);
  }
  *new_pos = value;
  size_ += 1;

  return new_pos;
}

template <typename T>
void vector<T>::erase(iterator pos) {
  size_type diff = pos - begin();

  if (diff > size_) {
    throw std::out_of_range("erase(): Position is out of range");
  }

  for (iterator iter = pos; iter != end() - 1; ++iter) {
    *iter = *(iter + 1);
  }

  std::destroy_at((&(*end())));
  size_ -= 1;
}

template <typename T>
void vector<T>::push_back(const_reference value) {
  insert(end(), value);
}

template <typename T>
void vector<T>::pop_back() {
  erase(end() - 1);
}

template <typename T>
void vector<T>::swap(vector<T> &other) noexcept {
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
  std::swap(data_, other.data_);
}

template <typename T>
template <typename... Args>
typename vector<T>::iterator vector<T>::insert_many(const_iterator pos,
                                                    Args &&...args) {
  vector<value_type> buffer = {args...};
  size_type diff = pos - cbegin();
  iterator new_pos = begin() + diff;

  for (size_type i = 0; i < buffer.size(); ++i) {
    new_pos = insert(new_pos, buffer[i]);
    ++new_pos;
  }

  return new_pos;
}

template <typename T>
template <typename... Args>
void vector<T>::insert_many_back(Args &&...args) {
  insert_many(cend(), args...);
}
}  // namespace scp

#endif  // CPP2_SCP_CONTAINERS_SCP_CONTAINERS_VECTOR_SCP_VECTOR_H_

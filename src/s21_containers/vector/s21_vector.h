#ifndef CPP2_S21_CONTAINERS_S21_CONTAINERS_VECTOR_S21_VECTOR_H_
#define CPP2_S21_CONTAINERS_S21_CONTAINERS_VECTOR_S21_VECTOR_H_

#include <limits>

namespace s21 {
template <typename T>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  // using iterator = ...
  // using const_iterator = ...
  using iterator_simple = T *;
  using const_iterator_simple = const T *;

  vector();
  vector(size_type n);
  vector(std::initializer_list<value_type> const &items);
  vector(const vector &v);
  vector(vector &&v);
  ~vector();

  vector& operator=(vector &&v);

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;
  const_reference front() const;
  const_reference back() const;
  iterator_simple data();

  // iterator begin();
  // iterator end();

  bool empty();
  size_type size(); 
  size_type max_size() const noexcept;
  void reserve(size_type size);
  size_type capacity();
  void shrink_to_fit();

  void clear();
  // iterator insert(iterator pos, const_reference value);
  // void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector& other);

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

template <typename T>
typename vector<T>::size_type vector<T>::max_size() const noexcept {
  return (std::numeric_limits<std::size_t>::max() / sizeof(value_type));
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_CONTAINERS_VECTOR_S21_VECTOR_H_

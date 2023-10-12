#ifndef CPP2_S21_CONTAINERS_S21_CONTAINERS_QUEUE_S21_QUEUE_H_
#define CPP2_S21_CONTAINERS_S21_CONTAINERS_QUEUE_S21_QUEUE_H_

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <utility>

#include "../list/s21_list.h"
#include "../list/s21_node.h"

namespace s21 {
template <class T, class C = list<T>>
class queue {
  typedef T value_type;
  typedef T &reference;
  typedef const T &const_reference;
  typedef size_t size_type;

 private:
  C list_;

 public:
  queue();
  queue(std::initializer_list<value_type> const &items);
  queue(const queue &q);
  queue(queue &&q);
  ~queue();
  queue<T, C> &operator=(queue &&q) noexcept;
  queue<T, C> &operator=(const queue &q) noexcept;

  const_reference front();
  const_reference back();

  bool empty();
  size_type size();
  void push(const_reference value);
  void pop();
  void swap(queue &other);

  template <class... Args>
  void insert_many_back(Args &&...args) noexcept {
    list_.insert_many_back(args...);
  }
};

template <class T, class C>
inline queue<T, C>::queue() {
  // std::cout << "\nconst call";
}

template <class T, class C>
inline queue<T, C>::queue(std::initializer_list<value_type> const &items) {
  list_ = list(items);
}

template <class T, class C>
inline queue<T, C>::queue(const queue &q) {
  // std::cout << "\ncopy const call queue";
  list_ = list(q.list_);
}

template <class T, class C>
inline queue<T, C>::queue(queue &&q) {
  // std::cout << "\nmoved const call";
  list_ = std::move(q.list_);
}

template <class T, class C>
inline queue<T, C>::~queue() {}

template <class T, class C>
inline queue<T, C> &queue<T, C>::operator=(queue &&q) noexcept {
  // std::cout << "\nmove assign call";
  list_ = std::move(q.list_);
  return *this;
}

template <class T, class C>
inline queue<T, C> &queue<T, C>::operator=(const queue &q) noexcept {
  // std::cout << "copy assign call queue\n";
  list_ = q.list_;
  return *this;
}

template <class T, class C>
inline typename queue<T, C>::const_reference queue<T, C>::front() {
  return list_.front();
}

template <class T, class C>
inline typename queue<T, C>::const_reference queue<T, C>::back() {
  return list_.back();
}

template <class T, class C>
inline bool queue<T, C>::empty() {
  return list_.empty();
}

template <class T, class C>
inline typename queue<T, C>::size_type queue<T, C>::size() {
  return list_.size();
}

template <class T, class C>
inline void queue<T, C>::push(const_reference value) {
  list_.push_back(value);
}

template <class T, class C>
inline void queue<T, C>::pop() {
  list_.pop_front();
}

template <class T, class C>
inline void queue<T, C>::swap(queue &other) {
  list_.swap(other.list_);
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_CONTAINERS_QUEUE_S21_QUEUE_H_

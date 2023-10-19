#ifndef CPP2_SCP_CONTAINERS_SCP_CONTAINERS_LIST_SCP_LISTITERATOR_H_
#define CPP2_SCP_CONTAINERS_SCP_CONTAINERS_LIST_SCP_LISTITERATOR_H_

#include "scp_list.h"
#include "scp_node.h"

namespace scp {

template <class T>
class list;

template <class T>
class ListIterator {
  typedef scp_node<T> node;

 protected:
  node *ptr_;

 public:
  ListIterator(node *ptr) noexcept;
  ListIterator(const ListIterator<T> &it) noexcept;
  ~ListIterator();

  ListIterator<T> &operator++() noexcept;
  ListIterator<T> &operator--() noexcept;
  bool operator==(const ListIterator<T> &other) const noexcept;
  bool operator!=(const ListIterator<T> &other) const noexcept;
  T &operator*() const noexcept;
  T *operator->() const noexcept;

  friend class list<T>;
};

template <class T>
inline ListIterator<T>::ListIterator(node *ptr) noexcept : ptr_(ptr) {}

template <class T>
inline ListIterator<T>::ListIterator(const ListIterator<T> &it) noexcept
    : ptr_(it.ptr_) {}

template <class T>
inline ListIterator<T>::~ListIterator() {}

template <class T>
inline ListIterator<T> &ListIterator<T>::operator++() noexcept {
  ptr_ = ptr_->next_;
  return *this;
}

template <class T>
inline ListIterator<T> &ListIterator<T>::operator--() noexcept {
  ptr_ = ptr_->prev_;
  return *this;
}

template <class T>
inline bool ListIterator<T>::operator==(
    const ListIterator<T> &other) const noexcept {
  return ptr_ == other.ptr_;
}

template <class T>
inline bool ListIterator<T>::operator!=(
    const ListIterator<T> &other) const noexcept {
  return !(*this == other);
}

template <class T>
inline T &ListIterator<T>::operator*() const noexcept {
  return *ptr_->data_;
}

template <class T>
inline T *ListIterator<T>::operator->() const noexcept {
  return ptr_->data_;
}
}  // namespace scp

#endif  // CPP2_SCP_CONTAINERS_SCP_CONTAINERS_LIST_SCP_LISTITERATOR_H_

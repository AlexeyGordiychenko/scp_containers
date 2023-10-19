#ifndef CPP2_SCP_CONTAINERS_SCP_CONTAINERS_LIST_SCP_LISTCONSTITERATOR_H_
#define CPP2_SCP_CONTAINERS_SCP_CONTAINERS_LIST_SCP_LISTCONSTITERATOR_H_

#include "scp_list_iterator.h"
#include "scp_node.h"

namespace scp {
template <class T>
class ListConstIterator : public ListIterator<T> {
 public:
  ListConstIterator(scp_node<T> *ptr) noexcept;
  ListConstIterator(ListIterator<T> it) noexcept;
  ~ListConstIterator();

  ListConstIterator<T> &operator++() noexcept;
  ListConstIterator<T> &operator--() noexcept;
  bool operator==(const ListConstIterator<T> &other) const noexcept;
  bool operator!=(const ListConstIterator<T> &other) const noexcept;
  const T &operator*() const noexcept;
  const T *operator->() const noexcept;
};

template <class T>
inline ListConstIterator<T>::ListConstIterator(scp_node<T> *ptr) noexcept
    : ListIterator<T>(ptr) {}

template <class T>
inline ListConstIterator<T>::ListConstIterator(ListIterator<T> it) noexcept
    : ListIterator<T>(it) {}

template <class T>
inline ListConstIterator<T>::~ListConstIterator() {}

template <class T>
inline bool ListConstIterator<T>::operator==(
    const ListConstIterator<T> &other) const noexcept {
  return this->ptr_ == other.ptr_;
}

template <class T>
inline bool ListConstIterator<T>::operator!=(
    const ListConstIterator<T> &other) const noexcept {
  return this->ptr_ != other.ptr_;
}

template <class T>
inline const T &ListConstIterator<T>::operator*() const noexcept {
  return *this->ptr_->data_;
}

template <class T>
inline const T *ListConstIterator<T>::operator->() const noexcept {
  return this->ptr_->data_;
}

template <class T>
inline ListConstIterator<T> &ListConstIterator<T>::operator++() noexcept {
  this->ptr_ = this->ptr_->next_;
  return *this;
}

template <class T>
inline ListConstIterator<T> &ListConstIterator<T>::operator--() noexcept {
  this->ptr_ = this->ptr_->prev_;
  return *this;
}

}  // namespace scp

#endif  // CPP2_SCP_CONTAINERS_SCP_CONTAINERS_LIST_SCP_LISTCONSTITERATOR_H_

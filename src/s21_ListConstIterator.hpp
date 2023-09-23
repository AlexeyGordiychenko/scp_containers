#ifndef CPP2_S21_CONTAINERS_SRC_LIST_LISTCONSTITERATOR_H_
#define CPP2_S21_CONTAINERS_SRC_LIST_LISTCONSTITERATOR_H_
#include "s21_ListIterator.hpp"
#include "s21_node.hpp"

namespace s21 {
    template<class T>
    class ListConstIterator : public ListIterator<T>
    {
      private:
          /* data */
          //const s21_node<T>* ptr_;
      public:
          ListConstIterator(s21_node<T>* ptr);// : ptr_(ptr) {};
          ListConstIterator(ListIterator<T> it);// : ListIterator<T>(it) {};// : ptr_(ptr) 
          ~ListConstIterator();

          bool operator==(const ListConstIterator<T>& other) const;
          bool operator!=(const ListConstIterator<T>& other) const;
          const T& operator*() const;
          const T* operator->() const;
    };

    template <class T>
    inline ListConstIterator<T>::ListConstIterator(s21_node<T>* ptr) : ListIterator<T>(ptr) {}

    template <class T>
    inline ListConstIterator<T>::ListConstIterator(ListIterator<T> it) : ListIterator<T>(it) {};

    template <class T>
    inline ListConstIterator<T>::~ListConstIterator(){};

    template <class T>
    inline bool ListConstIterator<T>::operator==(
        const ListConstIterator<T>& other) const {
      return this->ptr_ == other.ptr_;
    }

    template <class T>
    inline bool ListConstIterator<T>::operator!=(
        const ListConstIterator<T>& other) const {
      return this->ptr_ != other.ptr_;
    }

    template <class T>
    inline const T& ListConstIterator<T>::operator*() const {
        return *this->ptr_->data_;
    }

    template <class T>
    inline const T* ListConstIterator<T>::operator->() const {
      return this->ptr_->data_;
    };

    }  // namespace s21

#endif
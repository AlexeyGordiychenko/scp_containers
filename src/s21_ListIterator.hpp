#ifndef CPP2_S21_CONTAINERS_SRC_LIST_LISTITERATOR_H_
#define CPP2_S21_CONTAINERS_SRC_LIST_LISTITERATOR_H_

#include "s21_node.hpp"
#include "s21_list.hpp"



namespace s21 {

    template <class T> class list;

    template<class T>
    class ListIterator
    {
        typedef  s21_node<T> node;

        protected:
            node* ptr_;
        public:
            ListIterator(node* ptr);
            ListIterator(const ListIterator<T>& it);
            ~ListIterator();

            ListIterator<T>& operator++();
            ListIterator<T>& operator--();
            bool operator==(const ListIterator<T>& other) const;
            bool operator!=(const ListIterator<T>& other) const;
            T& operator*() const;
            T* operator->() const;

        friend class list<T>;
    };

    template <class T>
    inline ListIterator<T>::ListIterator(node* ptr) : ptr_(ptr) {}

    template <class T>
    inline ListIterator<T>::ListIterator(const ListIterator<T>& it) : ptr_(it.ptr_) {};

    template <class T>
    inline ListIterator<T>::~ListIterator()
    {
    }

    template <class T>
    inline ListIterator<T>& ListIterator<T>::operator++()
    {
        ptr_= ptr_->next_;
        return *this;
    }

    template <class T>
    inline ListIterator<T> &ListIterator<T>::operator--()
    {
        ptr_= ptr_->prev_;
        return *this;
    }

    template <class T>
    inline bool ListIterator<T>::operator==(const ListIterator<T>& other) const
    {
        return ptr_ == other.ptr_;
    }

    template <class T>
    inline bool ListIterator<T>::operator!=(const ListIterator<T>& other) const
    {
        return ptr_ != other.ptr_;
    }

    template <class T>
    inline T &ListIterator<T>::operator*() const
    {
        return *ptr_->data_;
    }

    template <class T>
    inline T *ListIterator<T>::operator->() const
    {
        return ptr_->data_;
    }
}

#endif
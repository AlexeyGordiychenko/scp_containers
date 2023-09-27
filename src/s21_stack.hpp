#ifndef CPP2_S21_CONTAINERS_SRC_STACK__STACK_H_
#define CPP2_S21_CONTAINERS_SRC__STACK__STACK_H_

#include "s21_node.hpp"
#include <cstddef>
#include <initializer_list>
#include "s21_list.hpp"
#include <utility>

namespace s21 {
    template <class T, class C = list<T>>
    class stack
    {
        typedef  T value_type;
        typedef  T& reference;
        typedef  const T& const_reference;
        typedef  size_t size_type;

    private:
      C list_;
    public:
        stack();
        stack(std::initializer_list<value_type> const& items);
        stack(const stack& q);
        stack(stack &&q);
        ~stack();
        stack<T, C>& operator=(stack&& q) noexcept;

        const_reference top();

        bool empty();
        size_type size();
        void push(const_reference value);
        void pop();
        void swap(stack& other);
    };

    template <class T, class C>
    inline stack<T, C>::stack() {}

    template <class T, class C>
    inline stack<T, C>::stack(
    std::initializer_list<value_type> const& items) { list_ = list(items); }

    template <class T, class C>
    inline stack<T, C>::stack(const stack& q) { list_ = list(q.list_); }

    template <class T, class C>
    inline stack<T, C>::stack(stack&& q) { list_ = std::move(q.list_); }

    template <class T, class C>
    inline stack<T, C>::~stack() {}

    template <class T, class C>
    inline stack<T, C>& stack<T, C>::operator=(stack&& q) noexcept {
      list_ = std::move(q.list_);
      return *this;
    }

    template <class T, class C>
    inline typename stack<T, C>::const_reference stack<T, C>::top() { return list_.back(); }

    template <class T, class C>
    inline bool stack<T, C>::empty() { return list_.empty(); }

    template <class T, class C>
    inline typename stack<T, C>::size_type stack<T, C>::size() { return list_.size(); }

    template <class T, class C>
    inline void stack<T, C>::push(const_reference value) { list_.push_back(value); }

    template <class T, class C>
    inline void stack<T, C>::pop() { list_.pop_back(); }

    template <class T, class C>
    inline void stack<T, C>::swap(stack& other) { list_.swap(other.list_); }

  }  // namespace s21

#endif
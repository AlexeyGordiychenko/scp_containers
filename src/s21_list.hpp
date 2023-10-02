#ifndef CPP2_S21_CONTAINERS_SRC_LIST_LIST_H_
#define CPP2_S21_CONTAINERS_SRC_LIST_LIST_H_

#include "s21_node.hpp"
#include "s21_ListIterator.hpp"
#include "s21_ListConstIterator.hpp"
#include <cstddef>
#include <initializer_list>
#include <iostream>

namespace s21 {
    template <class T>
    class list
    {
        typedef  T value_type;
        typedef  T& reference;
        typedef  const T& const_reference;
        typedef  ListIterator<T> iterator;
        typedef  ListConstIterator<T> const_iterator;
        typedef  size_t size_type;
        typedef  s21_node<T> node;

    private:
        s21_node<T>* null_node_;
        size_type size_;

        void init(node *node) noexcept;
        void add(node* n) noexcept;
        void copy(const list &list) noexcept;

    public:
        list() noexcept;
        explicit list(size_type n) noexcept;
        list(std::initializer_list<value_type> const& items) noexcept;
        list(const list& l) noexcept;
        list(list &&l) noexcept;
        ~list();
        list<T>& operator=(list&& l) noexcept;
        list<T>& operator=(const list& l) noexcept;

        const_reference front() const noexcept;
        const_reference back() const noexcept;

        iterator begin() const noexcept;
        iterator end() const noexcept;

        bool empty() const noexcept;
        size_type size() const noexcept;
        size_type max_size() const noexcept;

        void clear() noexcept;
        iterator insert(iterator pos, const_reference value) noexcept;
        void erase(iterator pos) noexcept;
        void push_back(const_reference value) noexcept;
        void pop_back() noexcept;
        void push_front(const_reference value) noexcept;
        void pop_front() noexcept;
        void swap(list& other) noexcept;
        void merge(list& other) noexcept;
        void splice(const_iterator pos, list& other) noexcept;
        void reverse() noexcept;
        void unique() noexcept;
        void sort() noexcept;

        template<class... Args>
        iterator insert_many(const_iterator pos, Args&&... args) noexcept { return (this->insert(pos, args), ...); }

        template<class... Args>
        void insert_many_back(Args&&... args) noexcept {
          (this->push_back(args), ...);
        }
    };

    template <class T>
    inline void list<T>::init(node *node) noexcept
    {
        size_ = 0;
        null_node_ = node;
        null_node_->next_ = null_node_;
        null_node_->prev_ = null_node_;
    }

    template <class T>
    inline list<T>::list() noexcept { init(new node); }

    template <class T>
    inline list<T>::list(size_type n) noexcept
    {
      init(new node);
      size_ = n;
      node *old = null_node_;
      for (int i = 0; i < n; i++) {
          node* new_node = new node;
          new_node->data_ = new T;
          new_node->prev_ = old;
          old->next_ = new_node;
          old = new_node;
      }
      old->next_ = null_node_;
      null_node_->prev_ = old;
    }

    template <class T>
    inline list<T>::list(std::initializer_list<value_type> const &items) noexcept
    {
        init(new node);
        size_ = items.size();
        node *old = null_node_;
        for (auto i = items.begin(); i != items.end(); ++i) {
            node* new_node = new node;
            new_node->data_ = new value_type(*i);
            new_node->prev_ = old;
            old->next_ = new_node;
            old = new_node;
        }
        old->next_ = null_node_;
        null_node_->prev_ = old;
    }

    template <class T>
    inline void list<T>::copy(const list& l) noexcept {
        init(new node);
        size_ = l.size_;
        node *old = null_node_;
        for (auto i = l.begin(); i != l.end(); ++i) {
            node* new_node = new node;
            new_node->data_ = new value_type(*i);
            new_node->prev_ = old;
            old->next_ = new_node;
            old = new_node;
        }
        old->next_ = null_node_;
        null_node_->prev_ = old;
    }

    template <class T>
    inline list<T>::list(const list &l) noexcept { 
       std::cout << "copy constr call list";
      copy(l); }

    template <class T>
    inline list<T>::list(list &&l) noexcept
    {
        //std::cout << "moved constr call";
        null_node_ = l.null_node_;
        size_ = l.size();

        l.init(new node);
        l.size_ = 0;
    }

    template <class T>
    inline list<T> &list<T>::operator=(list &&l) noexcept
    {
        //std::cout << "moved assign call";
        clear();
        delete null_node_;
        null_node_ = l.null_node_;
        size_ = l.size();
        l.init(new node);
        return *this;
    }

    template <class T>
    inline list<T>& list<T>::operator=(const list& l) noexcept {
      std::cout << "copy assign call list\n";
      clear();
      delete null_node_;
      copy(l);
      return *this;
    }

    template <class T>
    inline list<T>::~list()
    {
        //std::cout << "dest call";
        clear();
        delete null_node_;
        size_ = 0;
    }

     template <class T>
    inline void list<T>::clear() noexcept
    {
        node* n = null_node_->next_;
        while(n->data_) {
            node* del = n;
            n = n->next_;
            delete del;
        }
        init(null_node_);
    }


    template <class T>
    inline typename list<T>::const_reference list<T>::front() const noexcept { return *null_node_->next_->data_; }

    template <class T>
    inline typename list<T>::const_reference list<T>::back() const noexcept { return *null_node_->prev_->data_; }

    template <class T>
    inline bool list<T>::empty() const noexcept { return size_ == 0; }

    template <class T>
    inline typename list<T>::iterator list<T>::begin() const noexcept { return iterator(null_node_->next_); }

    template <class T>
    inline typename list<T>::iterator list<T>::end() const noexcept { return iterator(null_node_); }

    template <class T>
    inline typename list<T>::size_type list<T>::size() const noexcept { return size_; }

    template <class T>
    inline typename list<T>::size_type list<T>::max_size() const noexcept { return 384307168202282325; }

    template <class T>
    inline typename list<T>::iterator list<T>::insert(iterator pos, const_reference value) noexcept
    {
        node* new_node = new node;
        new_node->data_ = new value_type(value);
        new_node->prev_ = pos.ptr_->prev_;
        new_node->next_ = pos.ptr_;
        pos.ptr_->prev_->next_ = new_node;
        pos.ptr_->prev_ = new_node;
        size_++;
        return iterator(new_node);
    }

    template <class T>
    inline void list<T>::erase(iterator pos) noexcept {
      node* ptr =  pos.ptr_;
      if (ptr == null_node_) return;
      node* prev = ptr->prev_;
      node* next = ptr->next_;
      prev->next_ = next;
      next->prev_ = prev;
      delete ptr;
      size_--;
      //iterator ivalid after erase
      //https://www.geeksforgeeks.org/iterator-invalidation-cpp/
    }

    template <class T>
    inline void list<T>::push_back(const_reference value) noexcept { insert(end(), value); }

    template <class T>
    inline void list<T>::pop_back() noexcept {
      erase(--end());
    }

    template <class T>
    inline void list<T>::push_front(const_reference value) noexcept { insert(begin(), value); }

    template <class T>
    inline void list<T>::pop_front() noexcept {
      erase(begin());
    }

    template <class T>
    inline void list<T>::swap(list& other) noexcept {
      node *tmp_node = this->null_node_;
      this->null_node_ = other.null_node_;
      other.null_node_ = tmp_node;
      size_type tmp_size = this->size_;
      this->size_ = other.size_;
      other.size_ = tmp_size;
    }

    template <class T>
    inline void list<T>::splice(const_iterator pos, list& other) noexcept {
      node* start = other.null_node_->next_;
      node* end = other.null_node_->prev_;
      pos.ptr_->prev_->next_ = start;
      start->prev_ = pos.ptr_->prev_;
      pos.ptr_->prev_ = end;
      end->next_ = pos.ptr_;
      size_ += other.size_;

      other.init(other.null_node_);
    }

    template <class T>
    inline void list<T>::reverse() noexcept {
      node* n = null_node_->next_;
      while(n->data_) {
        node* next = n->next_;
        n->next_ = n->prev_;
        n->prev_ = next;
        n = next;
      }
      n = null_node_->next_;
      null_node_->next_ = null_node_->prev_;
      null_node_->prev_ = n;
    }

    template <class T>
    inline void list<T>::unique() noexcept {
      node* n = null_node_->next_;
      value_type* next_data;
      while(next_data = n->next_->data_) {
        node* next = n->next_;
        if (*next_data == *n->data_)
          erase(iterator(n));
        n = next;
      }
    }

    template <class T>
    inline void list<T>::sort() noexcept {
      if (size_ <= 1) return;
      list<T>* left = new list;
      list<T>* right = new list;
      node* n = null_node_->next_;
      int i = 0;
      while(n->data_) {
        node* next = n->next_;
        if (i < size_ / 2) left->add(n);
        else right->add(n);
        ++i;
        n = next;
      }
      left->sort();
      right->sort();
      left->merge(*right);
      swap(*left);
      right->init(right->null_node_);
      left->init(left->null_node_);
      delete right;
      delete left;
    }

    // template <class T>
    // inline typename list<T>::iterator list<T>::insert_many(const_iterator pos, T&&... args) {
    //   //insert(pos, args);
    //   (insert(pos, args),);
      
    //   //return iterator();
    // }

    template <class T>
    inline void list<T>::merge(list& other) noexcept {
      list* tmp = new list;
      node* n1 = null_node_->next_;
      node* n2 = other.null_node_->next_;
      while(n1->data_ && n2->data_)
      {
        node *insrt;
        if (*n1->data_ < *n2->data_) {
          insrt = n1;
          n1 = n1->next_;
        }
        else {
          insrt = n2;
          n2 = n2->next_;
        }
        tmp->add(insrt);
      }

      while(n1->data_) {
        tmp->add(n1);
        n1 = n1->next_;
      }
      while(n2->data_) {
        tmp->add(n2);
        n2 = n2->next_;
      }

      swap(*tmp);
      tmp->init(tmp->null_node_);
      other.init(other.null_node_);
      delete tmp;
    }

    template <class T>
    inline void list<T>::add(node* n) noexcept {
      null_node_->prev_->set_next(n);
      size_++;
    }

}  // namespace s21

#endif 
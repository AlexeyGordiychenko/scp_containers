#ifndef CPP2_S21_CONTAINERS_SRC_LIST_LIST_H_
#define CPP2_S21_CONTAINERS_SRC_LIST_LIST_H_

#include "s21_node.hpp"
#include "s21_ListIterator.hpp"
#include "s21_ListConstIterator.hpp"
#include <cstddef>
#include <initializer_list>

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
        // s21_node<T>* front_null_;
        // s21_node<T>* back_null_;
        // size_type size_;
        // s21_node<T>* front_;
        // s21_node<T>* back_;


        s21_node<T>* null_node_;// = new node;
        size_type size_;

        void init(node *node);
        void init_many(size_type n);
        void merge_sort(list& m);
        node* tail();
        void add(node* n);
        //  {
        //     node* null_node_a = new node;
        //     node* null_node_b = new node;
        //     front_null_ = null_node_a;
        //     back_null_ = null_node_b;
        //     front_null_->next_ = back_null_;
        //     back_null_->prev_ = front_null_;
        // }

    public:
        list();
        list(size_type n);
        list(std::initializer_list<value_type> const& items);
        list(const list& l); //copy nodes or not
        list(list &&l);
        ~list();
        list<T>& operator=(list&& l) noexcept; //!!!!!

        const_reference front();
        const_reference back();

        iterator begin() const;
        iterator end() const;

        bool empty();
        size_type size();
        size_type max_size();

        void clear();
        iterator insert(iterator pos, const_reference value);
        void erase(iterator pos);
        void push_back(const_reference value);
        void pop_back();
        void push_front(const_reference value);
        void pop_front();
        void swap(list& other);
        void merge(list& other);
        void splice(const_iterator pos, list& other); //!!!!
        void reverse();
        void unique();
        void sort();
    };

    template <class T>
    inline void list<T>::init(node *node)
    {
        size_ = 0;
        null_node_ = node;
        null_node_->next_ = null_node_;
        null_node_->prev_ = null_node_;
    }

    // template <class T>
    // inline void list<T>::init_many(size_type n)
    // {
    //     init(new node);
    //     size_ = n;
    //     node *old = null_node_;
    //     for (int i = 0; i < n; i++) {
    //         node* new_node = new node;
    //         new_node->data_ = new T;
    //         new_node->prev_ = old;
    //         old->next_ = new_node;
    //         old = new_node;
    //     }
    //     old->next_ = null_node_;
    //     null_node_->prev_ = old;
    // }

    template <class T>
    inline list<T>::list() { init(new node); }

    template <class T>
    inline list<T>::list(size_type n)
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
    inline list<T>::list(std::initializer_list<value_type> const &items)
    {
        init(new node);
        size_ = items.size();
        node *old = null_node_;
        for (auto i = items.begin(); i != items.end(); ++i) {
            node* new_node = new node;
            //new_node->data_ = i;
            new_node->data_ = new value_type(*i);
            new_node->prev_ = old;
            old->next_ = new_node;
            old = new_node;
        }
        old->next_ = null_node_;
        null_node_->prev_ = old;
        // node *old = front_null_;
        // for (int i = 0; i < n; i++) {
        //     node* new_node = new node;
        //     new_node->data_ = new T;
        //     new_node->prev_ = old;
        //     old->next_ = new_node;
        //     old = new_node;
        // }
        // old->next_ = back_null_;
        // back_null_->prev_ = old;
    }

    template <class T>
    inline list<T>::list(const list &l)
    {
        init(new node);
        size_ = l.size_;
        node *old = null_node_;
        for (auto i = l.begin(); i != l.end(); ++i) {
            node* new_node = new node;
            //new_node->data_ = i;
            new_node->data_ = new value_type(*i);
            new_node->prev_ = old;
            old->next_ = new_node;
            old = new_node;
        }
        old->next_ = null_node_;
        null_node_->prev_ = old;
    }

    template <class T>
    inline list<T>::list(list &&l)
    {
        null_node_ = l.null_node_;
        size_ = l.size();

        l.null_node_ = nullptr;
        l.size_ = 0;
    }

    template <class T>
    inline list<T>::~list()
    {
        clear();
        delete null_node_;
        size_ = 0;
    }

     template <class T>
    inline void list<T>::clear()
    {
        node* n = null_node_->next_;
        while(n->data_) {
            //delete n->data_;
            node* del = n;
            n = n->next_;
            delete del;
        }
        init(null_node_);
        // null_node_->next_ = null_node_;
        // null_node_->prev_ = null_node_;
        // size_ = 0;
    }

    template <class T>
    inline list<T> &list<T>::operator=(list &&l) noexcept
    {
        // back_null_ = l.back_null_;
        // front_null_ = l.front_null_;
        null_node_ = l.null_node_;
        size_ = l.size();
        
        //destructor called for temporary object
        //need to save nodes from freeing by clear method
        l.null_node_ = new node;
        l.null_node_->next_ = l.null_node_;

        return *this;
    }
    
    template <class T>
    inline typename list<T>::const_reference list<T>::front() { return *null_node_->next_->data_; }

    template <class T>
    inline typename list<T>::const_reference list<T>::back() { return *null_node_->prev_->data_; }

    template <class T>
    inline bool list<T>::empty() { return size_ == 0; }

    template <class T>
    inline typename list<T>::iterator list<T>::begin() const { return iterator(null_node_->next_); }

    template <class T>
    inline typename list<T>::iterator list<T>::end() const { return iterator(null_node_); }

    template <class T>
    inline typename list<T>::size_type list<T>::size() { return size_; }

    template <class T>
    inline typename list<T>::size_type list<T>::max_size() { return 384307168202282325; }

    template <class T>
    inline typename list<T>::iterator list<T>::insert(iterator pos, const_reference value)
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
    inline void list<T>::erase(iterator pos) {
      node* ptr =  pos.ptr_;
      if (ptr == null_node_) return;
      node* prev = ptr->prev_;
      node* next = ptr->next_;
      prev->next_ = next;
      next->prev_ = prev;
      //delete ptr->data_;
      delete ptr;
      size_--;
      //iterator ivalid after erase
      //https://www.geeksforgeeks.org/iterator-invalidation-cpp/
    }

    template <class T>
    inline void list<T>::push_back(const_reference value) { insert(end(), value); }

    template <class T>
    inline void list<T>::pop_back() {
      erase(--end());
      // node *del = null_node_->prev_;
      // null_node_->prev_ = del->prev_;
      // del->prev_->next_ = null_node_;
      // delete del->data_;
      // delete del;
      // size_--;
    }

    template <class T>
    inline void list<T>::push_front(const_reference value) { insert(begin(), value); }

    template <class T>
    inline void list<T>::pop_front() {
      erase(begin());
      // node *del = null_node_->next_;
      // null_node_->next_ = del->next_;
      // del->next_->prev_ = null_node_;
      // delete del->data_;
      // delete del;
      // size_--;
    }

    template <class T>
    inline void list<T>::swap(list& other) {
      node *tmp_node = this->null_node_;
      this->null_node_ = other.null_node_;
      other.null_node_ = tmp_node;
      size_type tmp_size = this->size_;
      this->size_ = other.size_;
      other.size_ = tmp_size;
    }

    template <class T>
    inline void list<T>::splice(const_iterator pos, list& other) {
      node* start = other.null_node_->next_;
      node* end = other.null_node_->prev_;
      pos.ptr_->prev_->next_ = start;
      start->prev_ = pos.ptr_->prev_;
      pos.ptr_->prev_ = end;
      end->next_ = pos.ptr_;
      size_ += other.size_;

      other.init(other.null_node_);
      // start->prev_ = pos.ptr->prev_;
      // pos.ptr->pre
      // start->prev_ = 
      // pos->prev-
    }

    template <class T>
    inline void list<T>::reverse() {
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
    inline void list<T>::unique() {
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
    inline void list<T>::sort() {
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

    template <class T>
    inline void list<T>::merge(list& other) {
      //sort!!
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

        //tmp->tail()->set_next(insrt);
        //tmp->size_++;
        tmp->add(insrt);
      }

      while(n1->data_) {
        //tmp->tail()->set_next(n1);
        tmp->add(n1);
        n1 = n1->next_;
        //tmp->size_++;
      }
      while(n2->data_) {
        //tmp->tail()->set_next(n2);
        tmp->add(n2);
        n2 = n2->next_;
        //tmp->size_++;
      }

      swap(*tmp);
      tmp->init(tmp->null_node_);
      other.init(other.null_node_);
      delete tmp;

      // null_node_->next_ = tmp.null_node_->next_;
      // null_node_->prev_ = tmp.null_node_->prev_;
      // node *dummy1 = new node;
      // node *dummy2 = new node;
      // int a = 1;
      // int b = 2;
      // dummy1->data_ = &a;
      // dummy2->data_ = &b;
      // tmp.null_node_->next_ = dummy1;
      // tmp.null_node_->prev_ = dummy2;
    }

    template <class T>
    inline void list<T>::merge_sort(list& m) {
      list left, right;
      node *n = null_node_->next_;
      int i = 0;
      while(n->data_) {
        if (i < size() / 2) left.push_back(n);
        else right.push_back(n);
        n = n->next_;
      }

      left = merge_sort(left);
      right = merge_sort(right);
      
    }

    template <class T>
    inline typename list<T>::node* list<T>::tail() {
      return null_node_->prev_;
    }

    template <class T>
    inline void list<T>::add(node* n) {
      null_node_->prev_->set_next(n);
      size_++;
    }
  }  // namespace s21

#endif 
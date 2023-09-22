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

        iterator begin();
        iterator end();

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
        void splice(const_iterator pos, list& other);
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

    template <class T>
    inline void list<T>::init_many(size_type n)
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
    inline list<T>::list() { init(new node); }

    template <class T>
    inline list<T>::list(size_type n)
    {
        init(new node);
        init_many(n);
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
        size_ = l.size();
        node *old = null_node_;
        for (auto i = l.begin(); i != l.end(); ++l) {
            node* new_node = new node;
            //new_node->data_ = i;
            new_node->data_ = new value_type(i);
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
        while(n != null_node_) {
            delete n->data_;
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
    inline typename list<T>::iterator list<T>::begin() { return iterator(null_node_->next_); }

    template <class T>
    inline typename list<T>::iterator list<T>::end() { return iterator(null_node_); }

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
    inline void list<T>::push_back(const_reference value) { insert(end(), value); }

    template <class T>
    inline void list<T>::push_front(const_reference value) { insert(begin(), value); }

};

#endif 
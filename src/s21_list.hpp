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
        s21_node<T>* front_null_;
        s21_node<T>* back_null_;
        size_type size_;
        // s21_node<T>* front_;
        // s21_node<T>* back_;


        //s21_node<T> null_node_;

        void init();
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
    inline void list<T>::init()
    {
        size_ = 0;
        node* null_node_a = new node;
        node* null_node_b = new node;
        front_null_ = null_node_a;
        back_null_ = null_node_b;
        front_null_->next_ = back_null_;
        back_null_->prev_ = front_null_;

        // back_null_->next_ = front_null_;
        // front_null_->prev_ = back_null_;
    }

    template <class T>
    inline void list<T>::init_many(size_type n)
    {
        init();
        size_ = n;
        node *old = front_null_;
        for (int i = 0; i < n; i++) {
            node* new_node = new node;
            new_node->data_ = new T;
            new_node->prev_ = old;
            old->next_ = new_node;
            old = new_node;
        }
        old->next_ = back_null_;
        back_null_->prev_ = old;
    }

    template <class T>
    inline list<T>::list()
    {
        init();
    }

    template <class T>
    inline list<T>::list(size_type n)
    {
        init();
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
        init();
        size_ = items.size();
        node *old = front_null_;
        for (auto i = items.begin(); i != items.end(); ++i) {
            node* new_node = new node;
            //new_node->data_ = i;
            new_node->data_ = new value_type(*i);
            new_node->prev_ = old;
            old->next_ = new_node;
            old = new_node;
        }
        old->next_ = back_null_;
        back_null_->prev_ = old;
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
        // back_null_ = l.back_null_;
        // front_null_ = l.front_null_;
        init();
        size_ = l.size();
        node *old = front_null_;
        for (auto i = l.begin(); i != l.end(); ++l) {
            node* new_node = new node;
            //new_node->data_ = i;
            new_node->data_ = new value_type(i);
            new_node->prev_ = old;
            old->next_ = new_node;
            old = new_node;
        }
        old->next_ = back_null_;
        back_null_->prev_ = old;
    }

    template <class T>
    inline list<T>::list(list &&l)
    {
        back_null_ = l.back_null_;
        front_null_ = l.front_null_;
        size_ = l.size();

        l.back_null_ = nullptr;
        l.front_null_ = nullptr;
        l.size_ = 0;
    }

    template <class T>
    inline list<T>::~list()
    {
        clear();
        delete front_null_;
        delete back_null_;
        size_ = 0;
    }

     template <class T>
    inline void list<T>::clear()
    {
        node* n = front_null_->next_;
        while(n != back_null_) {
            delete n->data_;
            node* del = n;
            n = n->next_;
            delete del;
        }
        front_null_->next_ = back_null_;
        back_null_->prev_ = front_null_;
        // back_null_->next_ = front_null_;
        // front_null_->prev_ = back_null_;
        size_ = 0;
    }

    template <class T>
    inline list<T> &list<T>::operator=(list &&l) noexcept
    {
        back_null_ = l.back_null_;
        front_null_ = l.front_null_;
        size_ = l.size();
        
        //destructor called for temporary object
        //need to save nodes from freeing by clear method
        l.back_null_ = new node;
        l.front_null_ = new node;
        l.front_null_->next_ = l.back_null_;

        return *this;
    }
    

    template <class T>
    inline typename list<T>::const_reference list<T>::front() {
        //return *front_->data_;
        return *front_null_->next_->data_;
    }

    template <class T>
    inline typename list<T>::const_reference list<T>::back()
    {
        return *back_null_->prev_->data_;
    }

    template <class T>
    inline bool list<T>::empty()
    {
        return size_ == 0;
    }

    template <class T>
    inline typename list<T>::iterator list<T>::begin()
    {
        return iterator(front_null_->next_);
    }

    template <class T>
    inline typename list<T>::iterator list<T>::end()
    {
        return iterator(back_null_);
    }

    template <class T>
    inline typename list<T>::size_type list<T>::size()
    {
        return size_;
    }

    template <class T>
    inline typename list<T>::size_type list<T>::max_size()
    {
        return 384307168202282325;
    }

    template <class T>
    inline typename list<T>::iterator list<T>::insert(iterator pos, const_reference value)
    {
        node* new_node = new node;
        new_node->data_ = new value_type(value);//&value;
        new_node->prev_ = pos.ptr_->prev_;
        new_node->next_ = pos.ptr_;
        pos.ptr_->prev_->next_ = new_node;
        pos.ptr_->prev_ = new_node;
        size_++;
        return iterator(new_node);
    }

    template <class T>
    inline void list<T>::push_back(const_reference value)
    {
        node* new_back = new node;
        new_back->data_ = new value_type(value);//&value;
        node* old_back = back_null_->prev_;
        new_back->prev_ = old_back;
        new_back->next_ = back_null_;
        old_back->next_ = new_back;
        //old back prev same
        back_null_->prev_ = new_back;

        size_++;
        

        // new_back->prev_ = back_;
        // back_->next_ = new_back;
        // back_ = new_back;


    }

    template <class T>
    inline void list<T>::push_front(const_reference value)
    {
        // node* new_node = new node;
        // new_node->data_ = &value;
        // new_node->next_ = front_;
        // front_->prev_ = new_node;
        // front_ = new_node;
        node* new_front = new node;
        new_front->data_ = new value_type(value);//&value;
        node* old_front = front_null_->next_;
        new_front->next_ = old_front;
        old_front->prev_ = new_front;
        front_null_->next_ = new_front;
        size_++;
    }

};

#endif 
#include "s21_node.hpp"
#include "s21_ListIterator.hpp"
#include <cstddef>
#include <initializer_list>

namespace s21 {
    template <class T>
    class list
    {
        typedef  T value_type; 
        typedef  T & reference;
        typedef  const T & const_reference;
        typedef  ListIterator<T> itereator; 
        typedef  size_t size_type;
        typedef  s21_node<T> node;

    private:
        s21_node<T> front_;
        s21_node<T> back_;

    public:
       list();
       list(size_type n);
       list(std::initializer_list<value_type> const &items);
       list(const list &l);
       ~list();
       list<T>& operator=(list &&l);

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
    };

    template <class T>
    inline list<T>::list()
    {
    }

    template <class T>
    inline list<T>::~list()
    {
    }
};

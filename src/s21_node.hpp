namespace s21 {

    template <class T>
    class s21_node
    {
        private:
            T* data;
            s21_node* prev;
            s21_node* next;
        public:
            s21_node(/* args */);
            ~s21_node();
    };

    template <class T>
    inline s21_node<T>::s21_node()
    {
    }

    template <class T>
    inline s21_node<T>::~s21_node()
    {
    }
}
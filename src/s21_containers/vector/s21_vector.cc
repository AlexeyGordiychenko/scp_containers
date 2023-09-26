#include "s21_vector.h"

namespace s21 {
template <typename T>
vector<T>::vector() : data_(nullptr), size_(0), capacity_(0)  {}

template <typename T>
vector<T>::~vector() {
  delete[] data_;

  size_ = 0;
  capacity_ = 0;
  data_ = nullptr;
}

}  // namespace s21

#include "s21_list.hpp"
//#include "s21_node.hpp"
#include <gtest/gtest.h>
#include <iostream> 

using namespace s21;

//int main() {

//template<T>
//s21_node<int>::i = 0;

//       list<int> l;
//       int a = 1;
//       int b = 2;
//       int c = 3;
//     l.push_back(a);
//      l.push_back(b);
//        l.push_back(c);
//    std::cout << l.front() << std::endl;
//    std::cout << l.back() << std::endl;

//    s21_node<int>* n = l.front_null_->next_;
//    while(n->data_ != nullptr) {
//     std::cout << *n->data_ << std::endl;
//     n = n->next_;
//    }
// }

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

// TEST(s21_list_test, construct_list_size) {
//     list<int> l(0);
//     EXPECT_EQ(l.back(), 0);
//     EXPECT_EQ(l.front(), 0);
// }

TEST(s21_list_test, push_back) {
    list<int> l;
    int a = 1;
    int b = 2;
    int c = 3;
    l.push_back(a);
    EXPECT_EQ(l.front(), a);
    EXPECT_EQ(l.back(), a);
    l.push_back(b);
    EXPECT_EQ(l.back(), b);
    EXPECT_EQ(l.front(), a);
    l.push_back(c);
    EXPECT_EQ(l.back(), c);
    EXPECT_EQ(l.front(), a);
}

TEST(s21_list_test, push_front) {
    list<int> l;
    //  int hh = int();
    int a = 1;
    int b = 2;
    int c = 3;
    l.push_back(a);
    EXPECT_EQ(l.front(), a);
    EXPECT_EQ(l.back(), a);
    l.push_back(b);
    EXPECT_EQ(l.back(), b);
    EXPECT_EQ(l.front(), a);
    l.push_back(c);
    EXPECT_EQ(l.back(), c);
    EXPECT_EQ(l.front(), a);
}

// TEST(Matrix_test, Default_constructor_test) {
//   int rows = 3;
//   int cols = 3;
//   S21Matrix result;
//   EXPECT_EQ(result.getRows(), rows);
//   EXPECT_EQ(result.getCols(), cols);
//   for (int i = 0; i < rows; i++)
//     for (int j = 0; j < cols; j++) EXPECT_EQ(result(i, j), 0);
// }

// TEST(Matrix_test, Copy_constructor_test) {
//   int rows = 3;
//   int cols = 3;
//   S21Matrix matrix(rows, cols);
//   for (int i = 0; i < rows; i++)
//     for (int j = 0; j < cols; j++) matrix(i, j) = i + j;
//   S21Matrix copy(matrix);
//   EXPECT_EQ(copy.getRows(), rows);
//   EXPECT_EQ(copy.getCols(), cols);
//   for (int i = 0; i < rows; i++)
//     for (int j = 0; j < cols; j++) EXPECT_EQ(copy(i, j), i + j);
// }

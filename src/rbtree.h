#include <iostream>
// #include <map>;
// template<class _Key, class _Val, class _KeyOfValue, class _Compare, class
// _Alloc = std::allocator<_Val>> class std::_Rb_tree<_Key, _Val, _KeyOfValue,
// _Compare, _Alloc> int main(void) { std::_Rb_tree; }

// RbTree class declaration
template <class T, class KeyOfValue, class Compare = std::less<T>,
          class Alloc = std::allocator<T>>
class RbTree {
 private:
  struct Node;  // forward declaration of node

 public:
  // RbTree();
  // ~RbTree();

  Node *root;

  void insert(const T &data) {
    Node *new_node = new Node(data);
    Node *a = root;
    Node *b = nullptr;
    while (a != nullptr) {
      b = a;
      if (Compare()(new_node->data, a->data)) {
        a = a->left;
      } else {
        a = a->right;
      }
    }
    new_node->parent = b;
    if (b == nullptr) {
      new_node->color = false;
      root = new_node;
    } else if (Compare()(new_node->data, b->data)) {
      b->left = new_node;
    } else {
      b->right = new_node;
    }
  }
  void remove(const T &);
  bool find(const T &) const;
  void print(const std::string &prefix, const Node *node, bool is_left) const {
    // ┌
    std::cout << prefix;
    std::cout << (is_left ? "└──" : "├──");
    if (node != nullptr) {
      // std::cout << prefix;
      // std::cout << (is_left ? "├──" : "└──");
      std::cout << node->data << std::endl;
      print(prefix + (is_left ? "   " : "│  "), node->right, false);
      print(prefix + (is_left ? "   " : "│  "), node->left, true);
    } else {
      std::cout << std::endl;
    }
  };
  void print() const { print("", root, false); };

 private:
  struct Node {
    T data;
    Node *left;
    Node *right;
    Node *parent;
    bool color;  // true if red, false if black

    Node()
        : data(nullptr),
          left(nullptr),
          right(nullptr),
          parent(nullptr),
          color(true){};
    Node(const T &data)
        : data(data),
          left(nullptr),
          right(nullptr),
          parent(nullptr),
          color(true){};
  };
};
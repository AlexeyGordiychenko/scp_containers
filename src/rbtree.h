#include <iostream>
#include <memory>
// #include <map>;
// template<class _Key, class _Val, class _KeyOfValue, class _Compare, class
// _Alloc = std::allocator<_Val>> class std::_Rb_tree<_Key, _Val, _KeyOfValue,
// _Compare, _Alloc> int main(void) { std::_Rb_tree; }

// RbTree class declaration
template <class T, class KeyOfValue, class Compare = std::less<T>>
class RbTree {
 private:
  struct Node;  // forward declaration of node

 public:
  using NodePtr = std::shared_ptr<Node>;
  using NodeParentPtr = std::weak_ptr<Node>;
  using DataPtr = std::unique_ptr<T>;
  NodePtr root;
  RbTree() = default;
  virtual ~RbTree() = default;

  void insert(const T &data, bool duplicates = false) {
    NodePtr a = root;
    NodePtr b = nullptr;

    bool is_left = false;
    while (a != nullptr) {
      b = a;
      if (!duplicates && key(data) == key(*a->data_)) {
        return;
      }
      is_left = Compare()(key(data), key(*a->data_));
      if (is_left) {
        a = a->left_;
      } else {
        a = a->right_;
      }
    }

    auto new_node = std::make_shared<Node>(data);
    new_node->parent_ = b;

    if (b == nullptr) {
      new_node->color_ = false;
      root = std::move(new_node);
    } else if (is_left) {
      b->left_ = std::move(new_node);
    } else {
      b->right_ = std::move(new_node);
    }
  }

  void remove(const T &);
  bool find(const T &) const;
  void print(const std::string &prefix, const NodePtr &node,
             bool is_left) const {
    // ┌
    std::cout << prefix;
    std::cout << (is_left ? "└──" : "├──");
    if (node != nullptr) {
      // std::cout << prefix;
      // std::cout << (is_left ? "├──" : "└──");
      std::cout << key(*node->data_) << std::endl;
      print(prefix + (is_left ? "   " : "│  "), node->right_, false);
      print(prefix + (is_left ? "   " : "│  "), node->left_, true);
    } else {
      std::cout << std::endl;
    }
  };
  void print() const { print("", root, false); };

 private:
  struct Node {
    DataPtr data_;
    NodePtr left_;
    NodePtr right_;
    NodeParentPtr parent_;
    bool color_;  // true if red, false if black

    Node() : color_(true){};
    Node(const T &data) : data_(std::make_unique<T>(data)), color_(true){};
    Node &operator=(const Node &) = delete;
    Node(const Node &) = delete;
    ~Node() = default;
  };
  auto key(const T &data) const { return KeyOfValue()(data); }
};
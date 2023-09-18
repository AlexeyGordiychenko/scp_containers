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
  // type aliases
  using NodePtr = std::shared_ptr<Node>;
  using NodeParentPtr = std::weak_ptr<Node>;
  using DataPtr = std::unique_ptr<T>;

  // fields
  NodePtr root_;

  // constructors and destructor
  RbTree() = default;
  RbTree &operator=(const RbTree &) = delete;
  RbTree(const RbTree &) = delete;
  virtual ~RbTree() = default;

  // iterator
  template <bool isConst>
  class RbTreeIterator {
   public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = std::conditional_t<isConst, const T, T>;
    using difference_type = std::ptrdiff_t;
    using pointer = value_type *;
    using reference = value_type &;

    RbTreeIterator(NodePtr node) : node_(node) {}

    reference operator*() const { return *node_->data_; }

    pointer operator->() const { return node_->data_.get(); }

    RbTreeIterator &operator++() {
      if (node_->right_) {
        node_ = node_->right_;
        while (node_->left_) {
          node_ = node_->left_;
        }
      } else {
        NodePtr temp;
        while ((temp = node_->parent_.lock()) && node_ == temp->right_) {
          node_ = temp;
        }
        node_ = temp;
      }
      return *this;
    }

    RbTreeIterator &operator--() {
      if (node_->left_) {
        node_ = node_->left_;
        while (node_->right_) {
          node_ = node_->right_;
        }
      } else {
        NodePtr temp;
        while ((temp = node_->parent_.lock()) && node_ == temp->left_) {
          node_ = temp;
        }
        node_ = temp;
      }
      return *this;
    }

    bool operator==(const RbTreeIterator &other) const {
      return node_ == other.node_;
    }

    bool operator!=(const RbTreeIterator &other) const {
      return !(*this == other);
    }

    RbTreeIterator operator++(int) {
      RbTreeIterator temp = *this;
      ++(*this);
      return temp;
    }

    RbTreeIterator operator--(int) {
      RbTreeIterator temp = *this;
      --(*this);
      return temp;
    }

   private:
    NodePtr node_;
  };

  using iterator = RbTreeIterator<false>;
  using const_iterator = RbTreeIterator<true>;

  // iterator methods
  iterator begin() const {
    NodePtr node = root_;
    while (node && node->left_) {
      node = node->left_;
    }
    return iterator(node);
  }

  iterator end() const { return iterator(sentinel_node_); }

  const_iterator cbegin() const {
    NodePtr node = root_;
    while (node && node->left_) {
      node = node->left_;
    }
    return const_iterator(node);
  }

  const_iterator cend() const { return const_iterator(sentinel_node_); }

  std::reverse_iterator<iterator> rbegin() const {
    return std::reverse_iterator<iterator>(end());
  }

  std::reverse_iterator<iterator> rend() const {
    return std::reverse_iterator<iterator>(begin());
  }

  std::reverse_iterator<const_iterator> crbegin() const {
    return std::reverse_iterator<const_iterator>(cend());
  }

  std::reverse_iterator<const_iterator> crend() const {
    return std::reverse_iterator<const_iterator>(cbegin());
  }

  // RB tree methods
  void insert(const T &data, bool duplicates = false) {
    NodePtr a = root_;
    NodePtr b = nullptr;

    bool is_left = false;
    // while (a != nullptr && a != sentinel_node_) {
    while (a != nullptr) {
      b = a;
      if (!duplicates && GetKey(data) == GetKey(*a->data_)) {
        return;
      }
      is_left = Compare()(GetKey(data), GetKey(*a->data_));
      if (is_left) {
        a = a->left_;
      } else {
        a = a->right_;
      }
    }

    auto new_node = std::make_shared<Node>(data);

    if (b == nullptr) {
      sentinel_node_ = std::make_shared<Node>();
      new_node->color_ = false;
      new_node->parent_ = sentinel_node_;
      root_ = std::move(new_node);
      sentinel_node_->left_ = root_;
    } else {
      new_node->parent_ = b;
      if (is_left) {
        b->left_ = std::move(new_node);
      } else {
        b->right_ = std::move(new_node);
      }
    }
  }

  void remove(const T &);

  iterator find(const T &data) const {
    NodePtr tnode = root_;
    while (tnode != nullptr) {
      if (GetKey(data) == GetKey(*tnode->data_)) {
        return iterator(tnode);
      }
      if (Compare()(GetKey(data), GetKey(*tnode->data_))) {
        tnode = tnode->left_;
      } else {
        tnode = tnode->right_;
      }
    }
    return end();
  };
  void print(const std::string &prefix, const NodePtr &node,
             bool is_left) const {
    // ┌
    std::cout << prefix;
    std::cout << (is_left ? "└──" : "├──");
    if (node != nullptr) {
      // std::cout << prefix;
      // std::cout << (is_left ? "├──" : "└──");
      std::cout << GetKey(*node->data_) << std::endl;
      print(prefix + (is_left ? "   " : "│  "), node->right_, false);
      print(prefix + (is_left ? "   " : "│  "), node->left_, true);
    } else {
      std::cout << std::endl;
    }
  };
  void print() const { print("", root_, false); };

 private:
  struct Node {
    DataPtr data_;
    NodePtr left_;
    NodePtr right_;
    NodeParentPtr parent_;
    bool color_ = true;  // true if red, false if black

    Node() = default;
    Node(const T &data) : data_(std::make_unique<T>(data)), color_(true){};
    Node &operator=(const Node &) = delete;
    Node(const Node &) = delete;
    ~Node() = default;
  };
  NodePtr sentinel_node_;

  auto GetKey(const T &data) const { return KeyOfValue()(data); }
};
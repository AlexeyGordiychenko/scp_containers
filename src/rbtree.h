#include <iostream>
#include <limits>
#include <memory>

// RbTree class declaration
template <class Key, class Value, class KeyOfValue,
          class Compare = std::less<Value>>
class RbTree {
 private:
  struct Node;  // forward declaration of node

 public:
  // type aliases for smart pointers to Node
  using NodePtr = std::shared_ptr<Node>;
  using NodeParentPtr = std::weak_ptr<Node>;
  using DataPtr = std::unique_ptr<Value>;

  // iterator
  template <bool isConst>
  class RbTreeIterator {
   public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = std::conditional_t<isConst, const Value, Value>;
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

    friend class RbTree;

   private:
    NodePtr node_;
  };

  // type aliases
  using key_type = Key;
  using value_type = Value;
  using difference_type = std::ptrdiff_t;
  using key_compare = Compare;
  using value_compare = Compare;
  using reference = value_type &;
  using const_reference = const value_type &;
  using pointer = value_type *;
  using const_pointer = const value_type *;
  using iterator = RbTreeIterator<false>;
  using const_iterator = RbTreeIterator<true>;

  using size_type = size_t;

  // fields
  NodePtr root_;

  // constructors and destructor
  RbTree() = default;
  RbTree &operator=(const RbTree &) = delete;
  RbTree(const RbTree &) = delete;
  virtual ~RbTree() = default;

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
  std::pair<iterator, bool> insert(const_reference data,
                                   bool duplicates = false) {
    NodePtr a = root_;
    NodePtr b = nullptr;

    bool is_left = false;
    while (a != nullptr) {
      b = a;
      if (!duplicates && get_key(data) == get_key(*a->data_)) {
        return std::make_pair(iterator(a), false);
      }
      is_left = key_compare()(get_key(data), get_key(*a->data_));
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
      root_ = new_node;
      sentinel_node_->left_ = root_;
    } else {
      new_node->parent_ = b;
      if (is_left) {
        b->left_ = new_node;
      } else {
        b->right_ = new_node;
      }
    }
    insert_balance(new_node);
    nodes_count_++;
    return std::make_pair(iterator(new_node), true);
  }

  void remove(const_reference data);

  iterator find(const key_type &key) { return iterator(find_node(key)); };
  const_iterator find(const key_type &key) const {
    return const_iterator(find_node(key));
  };

  NodePtr find_node(const key_type &key) const {
    NodePtr tnode = root_;
    while (tnode != nullptr) {
      if (key == get_key(*tnode->data_)) {
        return tnode;
      }
      if (key_compare()(key, get_key(*tnode->data_))) {
        tnode = tnode->left_;
      } else {
        tnode = tnode->right_;
      }
    }
    return sentinel_node_;
  };

  size_type size() const { return nodes_count_; }
  bool empty() const { return nodes_count_ == 0; }
  size_type max_size() {
    // this is a rough estimate
    // 3 * sizeof(void *) - because size of node doesn't include some extra
    // overhead of smart pointers (shared, weak) so we compensate it with an
    // extra 2*pointer size (estimate) for each (3 total), so 3*2 = 6
    size_t node_size = sizeof(Node) + sizeof(Value) + 6 * sizeof(void *);
    return std::numeric_limits<size_t>::max() / node_size;
  }

  void print(const std::string &prefix, const NodePtr &node, bool is_left,
             bool colored) const {
    std::cout << prefix;
    std::string left_color = "", right_color = "", reset_color = "",
                red_node_color = "", black_node_color = "";
    if (colored) {
      left_color = kCyanColor;
      right_color = kMagentaColor;
      reset_color = kResetColor;
      red_node_color = kRedColorBold;
      black_node_color = kBlackColorBold;
    }
    if (is_left) {
      std::cout << left_color + "┗━━" << reset_color;
    } else {
      std::cout << right_color + "┣━━" + reset_color;
    }

    if (node != nullptr) {
      if (node->color_) {
        std::cout << red_node_color;
      } else {
        std::cout << black_node_color;
      }
      std::cout << get_key(*node->data_) << reset_color << std::endl;
      print(prefix + (is_left ? "   " : right_color + "┃  " + reset_color),
            node->right_, false, colored);
      print(prefix + (is_left ? "   " : left_color + "┃  " + reset_color),
            node->left_, true, colored);
    } else {
      std::cout << std::endl;
    }
  };
  void print(bool colored = true) const { print("", root_, false, colored); };

  bool is_valid_tree() {
    int black_count = 0;
    // The root is always black
    if (root_ && root_->color_) {
      return false;
    }
    return is_valid_node(root_, black_count);
  }

  // balancing functions

  void insert_balance(NodePtr node) {
    NodePtr parent_node = nullptr;
    NodePtr grand_parent_node = nullptr;
    while (node && node != root_ && node->color_ &&
           (parent_node = node->parent_.lock()) && parent_node->color_ &&
           (grand_parent_node = parent_node->parent_.lock()) &&
           grand_parent_node != sentinel_node_) {
      bool is_left_parent = (parent_node == grand_parent_node->left_);
      bool is_left = (node == parent_node->left_);
      NodePtr uncle_node =
          is_left_parent ? grand_parent_node->right_ : grand_parent_node->left_;

      // Case : 1, The uncle of node is also red, only recoloring required
      if (!node_is_black(uncle_node)) {
        grand_parent_node->color_ = true;
        parent_node->color_ = false;
        uncle_node->color_ = false;
        node = grand_parent_node;
      } else {
        // Case : 2, node is right child of its parent if parent is left child
        // of grandparent and vice versa, rotation required
        if ((is_left_parent && !is_left) || (!is_left_parent && is_left)) {
          if (is_left_parent) {
            rotate_left(parent_node);
          } else {
            rotate_right(parent_node);
          }
          node = parent_node;
          parent_node = node->parent_.lock();
          grand_parent_node = parent_node->parent_.lock();
          is_left = (node == parent_node->left_);
          is_left_parent = (parent_node == grand_parent_node->left_);
          uncle_node = is_left_parent ? grand_parent_node->right_
                                      : grand_parent_node->left_;
        }

        // Case : 3, node is left child of its parent if parent is left child of
        // grandparent and vice versa, rotation required
        if ((is_left_parent && is_left) || (!is_left_parent && !is_left)) {
          if (is_left_parent) {
            rotate_right(grand_parent_node);
          } else {
            rotate_left(grand_parent_node);
          }
          std::swap(parent_node->color_, grand_parent_node->color_);
          node = parent_node;
        }
      }
    }
    root_->color_ = false;
  }

  void rotate_left(NodePtr node) {
    NodePtr right_child = node->right_;
    NodePtr parent = node->parent_.lock();

    node->right_ = right_child->left_;
    if (node->right_) {
      node->right_->parent_ = node;
    }

    right_child->parent_ = parent;

    if (!parent || parent == sentinel_node_)
      root_ = right_child;
    else if (node == parent->left_)
      parent->left_ = right_child;
    else
      parent->right_ = right_child;

    right_child->left_ = node;
    node->parent_ = right_child;
  }

  void rotate_right(NodePtr node) {
    NodePtr left_child = node->left_;
    NodePtr parent = node->parent_.lock();

    node->left_ = left_child->right_;
    if (node->left_) {
      node->left_->parent_ = node;
    }

    left_child->parent_ = parent;

    if (!parent || parent == sentinel_node_)
      root_ = left_child;
    else if (node == parent->left_)
      parent->left_ = left_child;
    else
      parent->right_ = left_child;

    left_child->right_ = node;
    node->parent_ = left_child;
  }

 private:
  struct Node {
    DataPtr data_;
    NodePtr left_;
    NodePtr right_;
    NodeParentPtr parent_;
    bool color_ = true;  // true if red, false if black

    Node() = default;
    Node(const_reference data)
        : data_(std::make_unique<value_type>(data)), color_(true){};
    Node &operator=(const Node &) = delete;
    Node(const Node &) = delete;
    ~Node() = default;
  };
  NodePtr sentinel_node_;
  size_type nodes_count_ = 0;
  const std::string kCyanColor = "\033[0;36m";
  const std::string kMagentaColor = "\033[0;35m";
  const std::string kRedColorBold = "\033[1;31m";
  const std::string kBlackColorBold = "\033[1;30m";
  const std::string kResetColor = "\033[0m";

  auto get_key(const_reference data) const { return KeyOfValue()(data); }

  bool is_valid_node(NodePtr node, int &black_count, int path_black_count = 0) {
    // Base case: we've reached a leaf node (null node)
    if (!node) {
      // All paths from root to leaf have the same number of black nodes
      if (black_count == 0) {
        black_count = path_black_count;
      }
      return path_black_count == black_count;
    }

    // Red nodes can't have red children
    if (node->color_) {
      if ((node->left_ && node->left_->color_) ||
          (node->right_ && node->right_->color_)) {
        return false;
      }
    }

    // Count black nodes along the path
    if (!node->color_) {
      path_black_count++;
    }

    // Check left and right subtrees
    return is_valid_node(node->left_, black_count, path_black_count) &&
           is_valid_node(node->right_, black_count, path_black_count);
  }
};
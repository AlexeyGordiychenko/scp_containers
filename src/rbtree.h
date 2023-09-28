#include <iostream>
#include <limits>
#include <memory>

// RbTree class declaration
template <class Key, class Value, class KeyOfValue,
          class Compare = std::less<Value>>
class RbTree {
 private:
  enum Color : bool { BLACK, RED };
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
      // we don't need here special conditions for a sentinel node, because
      // while traversing the tree we will always end up on a sentinel node
      // (parent of the root)
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
        if (temp) node_ = temp;
      }
      return *this;
    }

    RbTreeIterator &operator--() {
      if (!node_->parent_.lock()) {
        // if the parent is null it means that it's a sentinel node, so we can
        // use its right child (the rightmost node of the tree)
        node_ = node_->right_;
      } else if (node_->left_) {
        node_ = node_->left_;
        while (node_->right_) {
          node_ = node_->right_;
        }
      } else {
        NodePtr temp;
        while ((temp = node_->parent_.lock()) && node_ == temp->left_) {
          node_ = temp;
        }
        if (temp) node_ = temp;
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

  // constructors and destructor
  RbTree() = default;

  // copy constructor
  RbTree(const RbTree &other) {
    // nodes to keep track of the edges of the tree
    NodePtr leftmost = nullptr, rightmost = nullptr;
    // copy the tree
    root_ = copy_node_recursive(other.root_, leftmost, rightmost);
    nodes_count_ = other.nodes_count_;
    // if there is only one branch, set the leftmost/rightmost as root_
    if (!root_->left_ && root_ != leftmost) leftmost = root_;
    if (!root_->right_ && root_ != rightmost) rightmost = root_;
    // set the sentinel node
    sentinel_node_ = std::make_shared<Node>();
    sentinel_node_->left_ = leftmost;
    sentinel_node_->right_ = rightmost;
    root_->parent_ = sentinel_node_;
  }

  // move constructor
  RbTree(RbTree &&other) noexcept
      : root_(std::move(other.root_)),
        sentinel_node_(std::move(other.sentinel_node_)),
        nodes_count_(other.nodes_count_) {
    other.nodes_count_ = 0;
  }

  // copy operator
  RbTree &operator=(const RbTree &other) {
    if (this != &other) {
      // create a copy and move it
      *this = std::move(RbTree(other));
    }
    return *this;
  }

  // move operator
  RbTree &operator=(RbTree &&other) noexcept {
    if (this != &other) {
      std::swap(root_, other.root_);
      std::swap(sentinel_node_, other.sentinel_node_);
      std::swap(nodes_count_, other.nodes_count_);
    }
    return *this;
  }

  virtual ~RbTree() = default;

  // iterator methods
  iterator begin() const { return iterator(get_leftmost()); }

  iterator end() const { return iterator(sentinel_node_); }

  const_iterator cbegin() const { return const_iterator(get_leftmost()); }

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
      root_ = new_node;
      sentinel_node_ = std::make_shared<Node>();
      sentinel_node_->left_ = root_;
      sentinel_node_->right_ = root_;
      set_node_color(root_, BLACK);
      root_->parent_ = sentinel_node_;
    } else {
      new_node->parent_ = b;
      if (is_left) {
        b->left_ = new_node;
      } else {
        b->right_ = new_node;
      }
    }

    // Update sentinel node
    if (is_left && b == sentinel_node_->left_) {
      sentinel_node_->left_ = new_node;
    } else if (!is_left && b == sentinel_node_->right_) {
      sentinel_node_->right_ = new_node;
    }

    insert_balance(new_node);
    nodes_count_++;
    return std::make_pair(iterator(new_node), true);
  }

  void erase(iterator pos) {
    if (pos == end()) return;

    NodePtr node_to_replace, node_to_delete, node = pos.node_;

    // If the node has both children, then node_to_delete is set
    // to the inorder successor of the node. Otherwise, node_to_delete is set to
    // the node
    if (node->left_ && node->right_) {
      iterator it(node);
      ++it;
      node_to_delete = it.node_;
    } else {
      node_to_delete = node;
    }

    // Update the sentinel node
    if (node == sentinel_node_->left_) {
      sentinel_node_->left_ =
          (node->right_ ? minimum(node->right_) : node->parent_.lock());
    }
    if (node == sentinel_node_->right_) {
      sentinel_node_->right_ =
          (node->left_ ? maximum(node->left_) : node->parent_.lock());
    }

    // Set node_to_replace to the non-null child of node_to_delete, if any.
    node_to_replace = (node_to_delete->left_ ? node_to_delete->left_
                                             : node_to_delete->right_);
    // Save the parent of the node to delete
    NodePtr parent = node_to_delete->parent_.lock();

    // Update the parents
    if (node_to_replace) {
      node_to_replace->parent_ = parent;
    }
    if (parent == sentinel_node_) {
      root_ = node_to_replace;
    } else if (node_to_delete == parent->left_) {
      parent->left_ = node_to_replace;
    } else {
      parent->right_ = node_to_replace;
    }

    // Move the data of the node, if needed
    if (node_to_delete != node) {
      // Update the sentinel node
      if (sentinel_node_->left_ == node_to_delete) {
        sentinel_node_->left_ = node;
      } else if (sentinel_node_->right_ == node_to_delete) {
        sentinel_node_->right_ = node;
      }
      node->data_ = std::move(node_to_delete->data_);
    }

    // If the node to delete is black, we need to balance the tree
    if (node_is_black(node_to_delete)) {
      delete_balance(node_to_replace, parent);
    }

    nodes_count_--;
  }

  void clear() {
    clear_recursive(root_);
    root_ = nullptr;
    sentinel_node_ = nullptr;
    nodes_count_ = 0;
  }

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
      if (node_is_red(node)) {
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
    if (node_is_red(root_)) {
      return false;
    }
    return is_valid_node(root_, black_count);
  }

  // balancing functions

  void insert_balance(NodePtr node) {
    NodePtr parent_node = nullptr;
    NodePtr grand_parent_node = nullptr;
    while (node_is_red(node) && node != root_ &&
           (parent_node = node->parent_.lock()) && node_is_red(parent_node) &&
           (grand_parent_node = parent_node->parent_.lock()) &&
           grand_parent_node != sentinel_node_) {
      bool is_left_parent = (parent_node == grand_parent_node->left_);
      bool is_left = (node == parent_node->left_);
      NodePtr uncle_node =
          is_left_parent ? grand_parent_node->right_ : grand_parent_node->left_;

      // Case 1: The uncle of node is also red, only recoloring required
      if (node_is_red(uncle_node)) {
        set_node_color(grand_parent_node, RED);
        set_node_color(parent_node, BLACK);
        set_node_color(uncle_node, BLACK);
        node = grand_parent_node;
      } else {
        // Case 2: The node is right child of its parent if parent is left child
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

        // Case 3: The node is left child of its parent if parent is left child
        // of grandparent and vice versa, rotation required
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
    set_node_color(root_, BLACK);
  }

  void delete_balance(NodePtr node, NodePtr parent) {
    // Continue until the node is the root or the node becomes red
    while (node != root_ && (node_is_black(node))) {
      bool is_left = (node == parent->left_);
      NodePtr sibling = is_left ? parent->right_ : parent->left_;

      // Case 1: The sibling is red
      if (node_is_red(sibling)) {
        set_node_color(sibling, BLACK);
        set_node_color(parent, RED);
        if (is_left) {
          rotate_left(parent);
          sibling = parent->right_;
        } else {
          rotate_right(parent);
          sibling = parent->left_;
        }
      }

      // Case 2: The sibling is black, and both of its children are black
      if (node_is_black(sibling->left_) && node_is_black(sibling->right_)) {
        set_node_color(sibling, RED);
        node = parent;
        parent = parent->parent_.lock();
      } else {
        // Case 3: The sibling is black, its near child is red, and its far
        // child is black
        NodePtr near_child = is_left ? sibling->left_ : sibling->right_;
        NodePtr far_child = is_left ? sibling->right_ : sibling->left_;

        // we need to check only one child, because of the first if
        if (node_is_black(far_child)) {
          set_node_color(near_child, BLACK);
          set_node_color(sibling, RED);
          if (is_left) {
            rotate_right(sibling);
            sibling = parent->right_;
          } else {
            rotate_left(sibling);
            sibling = parent->left_;
          }
          near_child = is_left ? sibling->left_ : sibling->right_;
          far_child = is_left ? sibling->right_ : sibling->left_;
        }
        // Case 4: The sibling is black, and its far child is red
        set_node_color(sibling, parent->color_);
        set_node_color(parent, BLACK);
        set_node_color(far_child, BLACK);
        if (is_left) {
          rotate_left(parent);
        } else {
          rotate_right(parent);
        }
        node = root_;
      }
    }
    // Ensure the node is always black
    set_node_color(node, BLACK);
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
    Color color_ = RED;

    Node() = default;
    Node(const_reference data) : data_(std::make_unique<value_type>(data)){};
    Node &operator=(const Node &) = delete;
    Node(const Node &) = delete;
    ~Node() = default;
  };

  NodePtr root_, sentinel_node_;
  size_type nodes_count_ = 0;

  const std::string kCyanColor = "\033[0;36m";
  const std::string kMagentaColor = "\033[0;35m";
  const std::string kRedColorBold = "\033[1;31m";
  const std::string kBlackColorBold = "\033[1;30m";
  const std::string kResetColor = "\033[0m";

  auto get_key(const_reference data) const { return KeyOfValue()(data); }
  NodePtr get_leftmost() const {
    return (sentinel_node_) ? sentinel_node_->left_ : nullptr;
  }
  NodePtr get_rightmost() const {
    return (sentinel_node_) ? sentinel_node_->right_ : nullptr;
  }

  bool node_is_black(const NodePtr &node) const {
    return !node || node->color_ == BLACK;
  }
  bool node_is_red(const NodePtr node) const {
    return node && node->color_ == RED;
  }

  void set_node_color(NodePtr &node, Color color) {
    if (node) node->color_ = color;
  }

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
    if (node_is_red(node)) {
      if (node_is_red(node->left_) || node_is_red(node->right_)) {
        return false;
      }
    }

    // Count black nodes along the path
    if (node_is_black(node)) {
      path_black_count++;
    }

    // Check left and right subtrees
    return is_valid_node(node->left_, black_count, path_black_count) &&
           is_valid_node(node->right_, black_count, path_black_count);
  }

  void clear_recursive(NodePtr &node) {
    if (!node) return;
    clear_recursive(node->left_);
    clear_recursive(node->right_);
    node.reset();
  }

  NodePtr minimum(NodePtr node) {
    while (node->left_) {
      node = node->left_;
    }
    return node;
  }

  NodePtr maximum(NodePtr node) {
    while (node->right_) {
      node = node->right_;
    }
    return node;
  }

  NodePtr copy_node_recursive(const NodePtr &node_to_copy, NodePtr &leftmost,
                              NodePtr &rightmost) {
    if (!node_to_copy) {
      return nullptr;
    }

    NodePtr new_node = std::make_shared<Node>(*node_to_copy->data_);
    new_node->left_ =
        copy_node_recursive(node_to_copy->left_, leftmost, rightmost);
    new_node->right_ =
        copy_node_recursive(node_to_copy->right_, leftmost, rightmost);
    if (new_node->left_) {
      new_node->left_->parent_ = new_node;
    }
    if (new_node->right_) {
      new_node->right_->parent_ = new_node;
    }

    // Update leftmost and rightmost nodes
    if (!leftmost && !new_node->left_) {
      leftmost = new_node;
    }
    if (!rightmost && !new_node->right_) {
      rightmost = new_node;
    }

    return new_node;
  }
};

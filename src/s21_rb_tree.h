#ifndef S21_RBTREE_H_
#define S21_RBTREE_H_

#include <functional>
#include <iostream>
#include <memory>

namespace s21 {

// RbTree class declaration
template <class Key, class Value, class KeyOfValue,
          class Compare = std::less<Value>,
          class Allocator = std::allocator<Value>>
class RbTree {
 private:
  struct Node;  // forward declaration of node

 public:
  // type aliases
  using key_type = Key;
  using value_type = Value;
  using difference_type = std::ptrdiff_t;
  using key_compare = Compare;
  using reference = value_type &;
  using const_reference = const value_type &;
  using value_rptr = value_type *;
  using const_value_rptr = const value_type *;
  using value_ptr =
      std::unique_ptr<value_type, std::function<void(value_rptr)>>;
  using node_rptr = Node *;
  using const_node_rptr = const Node *;
  using node_ptr = std::shared_ptr<Node>;
  using node_parent_ptr = std::weak_ptr<Node>;

  using alloc_traits = std::allocator_traits<Allocator>;
  using value_alloc = typename alloc_traits::template rebind_alloc<value_type>;
  using value_alloc_reference = value_alloc &;
  using node_alloc = typename alloc_traits::template rebind_alloc<Node>;

  using size_type = size_t;

  // iterator
  template <bool isConst>
  class RbTreeIterator {
   public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = std::conditional_t<isConst, const Value, Value>;
    using difference_type = std::ptrdiff_t;
    using pointer = value_type *;
    using reference = value_type &;

    RbTreeIterator(node_ptr node) : node_(node) {}

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
        node_ptr temp;
        while ((temp = node_->parent()) && node_ == temp->right_) {
          node_ = temp;
        }
        if (temp) node_ = temp;
      }
      return *this;
    }

    RbTreeIterator &operator--() {
      if (!node_->parent()) {
        // if the parent is null it means that it's a sentinel node, so we can
        // use its right child (the rightmost node of the tree)
        node_ = node_->right_;
      } else if (node_->left_) {
        node_ = node_->left_;
        while (node_->right_) {
          node_ = node_->right_;
        }
      } else {
        node_ptr temp;
        while ((temp = node_->parent()) && node_ == temp->left_) {
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
    node_ptr node_;
  };

  // type aliases for the iterator
  using iterator = RbTreeIterator<false>;
  using const_iterator = RbTreeIterator<true>;

  // Define the opposite comparison function
  struct KeyCompareReverse {
    bool operator()(const key_type &a, const key_type &b) const {
      return !key_compare()(b, a);
    }
  };

  // constructors and destructor
  RbTree() = default;

  // copy constructor
  RbTree(const RbTree &other) {
    // nodes to keep track of the edges of the tree
    node_ptr leftmost = nullptr, rightmost = nullptr;
    // copy the tree
    root_ = copy_node_recursive(other.root_.get(), leftmost, rightmost);
    nodes_count_ = other.nodes_count_;
    if (root_) {
      sentinel_node_ = allocate_node();
      sentinel_node_->left_ = leftmost;
      sentinel_node_->right_ = rightmost;
      root_->parent_ = sentinel_node_;
    }
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
      swap(other);
    }
    return *this;
  }

  virtual ~RbTree() = default;

  // iterator methods
  iterator begin() noexcept { return iterator(get_leftmost()); }

  const_iterator begin() const noexcept {
    return const_iterator(get_leftmost());
  }

  iterator end() noexcept { return iterator(sentinel_node_); }

  const_iterator end() const noexcept { return const_iterator(sentinel_node_); }

  const_iterator cbegin() const noexcept {
    return const_iterator(get_leftmost());
  }

  const_iterator cend() const noexcept {
    return const_iterator(sentinel_node_);
  }

  std::reverse_iterator<iterator> rbegin() noexcept {
    return std::reverse_iterator<iterator>(end());
  }

  std::reverse_iterator<const_iterator> rbegin() const noexcept {
    return std::reverse_iterator<const_iterator>(end());
  }

  std::reverse_iterator<iterator> rend() noexcept {
    return std::reverse_iterator<iterator>(begin());
  }

  std::reverse_iterator<const_iterator> rend() const noexcept {
    return std::reverse_iterator<const_iterator>(begin());
  }

  std::reverse_iterator<const_iterator> crbegin() const noexcept {
    return std::reverse_iterator<const_iterator>(cend());
  }

  std::reverse_iterator<const_iterator> crend() const noexcept {
    return std::reverse_iterator<const_iterator>(cbegin());
  }

  // RB tree methods
  std::pair<iterator, bool> insert(const_reference data,
                                   const bool duplicates = false) {
    node_ptr a = root_;
    node_ptr b = nullptr;

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

    auto new_node = allocate_node(data);

    if (!b) {
      root_ = new_node;
      sentinel_node_ = allocate_node();
      sentinel_node_->left_ = root_;
      sentinel_node_->right_ = root_;
      set_node_color(root_.get(), BLACK);
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

    node_ptr node = pos.node_;

    // If the node has both children, then node_to_delete is set
    // to the inorder successor of the node. Otherwise, node_to_delete is set to
    // the node
    if (node->left_ && node->right_) {
      iterator it(node);
      ++it;
      swap_nodes_on_erase(it.node_, node);
    }

    // Update the sentinel node
    update_edges_on_erase(node.get());

    // Set node_to_replace to the non-null child of node, if any.
    node_ptr node_to_replace = (node->left_ ? node->left_ : node->right_);
    // Save the parent of the node to delete
    node_ptr parent = node->parent();

    // Update the parents
    if (node_to_replace) {
      node_to_replace->parent_ = parent;
    }
    if (parent == sentinel_node_) {
      root_ = node_to_replace;
    } else if (node == parent->left_) {
      parent->left_ = node_to_replace;
    } else {
      parent->right_ = node_to_replace;
    }

    if (node_is_black(node.get())) {
      // If the node to delete is black, we need to balance the tree
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

  iterator find(const key_type &key) noexcept {
    return iterator(find_node(key));
  };
  const_iterator find(const key_type &key) const noexcept {
    return const_iterator(find_node(key));
  };

  iterator lower_bound(const key_type &key) noexcept {
    return iterator(bound(key, key_compare()));
  };
  const_iterator lower_bound(const key_type &key) const noexcept {
    return const_iterator(bound(key, key_compare()));
  };
  iterator upper_bound(const key_type &key) noexcept {
    return iterator(bound(key, KeyCompareReverse()));
  };
  const_iterator upper_bound(const key_type &key) const noexcept {
    return const_iterator(bound(key, KeyCompareReverse()));
  };

  size_type size() const noexcept { return nodes_count_; }
  bool empty() const noexcept { return nodes_count_ == 0; }
  size_type max_size() const noexcept { return node_alloc_.max_size(); }

  void swap(RbTree &other) noexcept {
    std::swap(root_, other.root_);
    std::swap(sentinel_node_, other.sentinel_node_);
    std::swap(nodes_count_, other.nodes_count_);
  }

  void merge(RbTree &other, const bool duplicates = false) {
    if (this == &other || other.empty()) return;
    if (this->empty()) {
      *this = std::move(other);
      return;
    }

    node_ptr head = nullptr, tail = nullptr, other_head = nullptr,
             other_tail = nullptr;

    // Convert both trees to sorted doubly-linked lists
    tree_to_list(root_, head, tail);
    tree_to_list(other.root_, other_head, other_tail);
    tail = key_compare()(get_key(*tail->data_), get_key(*other_tail->data_))
               ? other_tail
               : tail;

    // Merge the two sorted lists into one
    merge_lists(head, other_head, other_tail, duplicates);

    // Convert the merged list and the rest of the other list back to balanced
    // RB trees
    list_to_tree(*this, head, tail);
    list_to_tree(other, other_head, other_tail);
  }

  void print(const std::string &prefix, const_node_rptr node,
             const bool is_left, const bool colored) const noexcept {
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

    if (node) {
      if (node_is_red(node)) {
        std::cout << red_node_color;
      } else {
        std::cout << black_node_color;
      }
      std::cout << get_key(*node->data_) << reset_color << std::endl;
      print(prefix + (is_left ? "   " : right_color + "┃  " + reset_color),
            node->right_.get(), false, colored);
      print(prefix + (is_left ? "   " : left_color + "┃  " + reset_color),
            node->left_.get(), true, colored);
    } else {
      std::cout << std::endl;
    }
  };
  void print(const bool colored = true) const noexcept {
    print("", root_.get(), false, colored);
  };

  bool is_valid_tree() const noexcept {
    size_type black_count = 0;
    // The root is always black
    const_node_rptr root_ptr = root_.get();
    if (node_is_red(root_ptr)) return false;
    return is_valid_node(root_ptr, black_count);
  }

 private:
  enum Color : bool { BLACK, RED };

  struct Node {
    value_ptr data_;
    node_ptr left_;
    node_ptr right_;
    node_parent_ptr parent_;
    Color color_ = RED;

    Node() = default;
    Node(const_reference data, value_alloc_reference value_alloc, Color color)
        : data_(allocate_value(data, value_alloc), get_deleter(value_alloc)),
          color_(color) {}
    Node &operator=(const Node &) = delete;
    Node(const Node &) = delete;
    ~Node() = default;

    // node methods
    node_ptr parent() const { return parent_.lock(); }

   private:
    value_rptr allocate_value(const_reference data,
                              value_alloc_reference value_alloc) {
      value_rptr raw_value = value_alloc.allocate(1);
      alloc_traits::construct(value_alloc, raw_value, data);
      return raw_value;
    }

    std::function<void(value_rptr)> get_deleter(
        value_alloc_reference value_alloc) {
      return [&value_alloc](value_rptr p) {
        alloc_traits::destroy(value_alloc, p);
        value_alloc.deallocate(p, 1);
      };
    }
  };

  node_ptr root_, sentinel_node_;
  size_type nodes_count_ = 0;
  value_alloc value_alloc_;
  node_alloc node_alloc_;

  using key_compare_func =
      std::function<bool(const key_type &, const key_type &)>;

  const std::string kCyanColor = "\033[0;36m";
  const std::string kMagentaColor = "\033[0;35m";
  const std::string kRedColorBold = "\033[1;31m";
  const std::string kBlackColorBold = "\033[1;30m";
  const std::string kResetColor = "\033[0m";

  auto get_key(const_reference data) const { return KeyOfValue()(data); }

  node_ptr get_leftmost() const noexcept {
    if (sentinel_node_) {
      return (sentinel_node_->left_) ? sentinel_node_->left_ : sentinel_node_;
    } else {
      return nullptr;
    }
  }

  bool node_is_black(const_node_rptr node) const noexcept {
    return !node || node->color_ == BLACK;
  }

  bool node_is_red(const_node_rptr node) const noexcept {
    return node && node->color_ == RED;
  }

  void set_node_color(node_rptr node, Color color) noexcept {
    if (node) node->color_ = color;
  }

  node_ptr find_node(const key_type &key) const noexcept {
    node_ptr result = root_;
    while (result != nullptr) {
      if (key == get_key(*result->data_)) {
        return result;
      }
      if (key_compare()(key, get_key(*result->data_))) {
        result = result->left_;
      } else {
        result = result->right_;
      }
    }
    return sentinel_node_;
  };

  bool is_valid_node(const_node_rptr node, size_type &black_count,
                     size_type path_black_count = 0) const noexcept {
    if (!node) {
      // All paths from the root to a leaf have the same number of black nodes
      if (black_count == 0) {
        black_count = path_black_count;
      }
      return path_black_count == black_count;
    }
    const_node_rptr left = node->left_.get();
    const_node_rptr right = node->right_.get();
    if (node_is_black(node)) {
      // Count black nodes along the path
      path_black_count++;
    } else {
      // Red nodes can't have red children
      if (node_is_red(left) || node_is_red(right)) return false;
    }

    // Check left and right subtrees
    return is_valid_node(left, black_count, path_black_count) &&
           is_valid_node(right, black_count, path_black_count);
  }

  void clear_recursive(node_ptr &node) {
    if (!node) return;
    clear_recursive(node->left_);
    clear_recursive(node->right_);
    node.reset();
  }

  node_ptr copy_node_recursive(const_node_rptr node_to_copy, node_ptr &leftmost,
                               node_ptr &rightmost) {
    if (!node_to_copy) {
      return nullptr;
    }

    auto new_node = allocate_node(*node_to_copy->data_, node_to_copy->color_);

    // copy the left subtree and update the leftmost
    new_node->left_ =
        copy_node_recursive(node_to_copy->left_.get(), leftmost, rightmost);
    if (!leftmost && !new_node->left_) leftmost = new_node;

    // copy the right subtree and update the rightmost
    new_node->right_ =
        copy_node_recursive(node_to_copy->right_.get(), leftmost, rightmost);
    if (!new_node->right_) rightmost = new_node;

    if (new_node->left_) {
      new_node->left_->parent_ = new_node;
    }
    if (new_node->right_) {
      new_node->right_->parent_ = new_node;
    }

    return new_node;
  }

  void swap_nodes_on_erase(node_ptr &node_to_delete, node_ptr &node) {
    if (node_to_delete->parent()->left_ == node_to_delete) {
      node_to_delete->parent()->left_ = node;
    } else {
      node_to_delete->parent()->right_ = node;
    }

    if (node != root_) {
      if (node->parent()->left_ == node) {
        node->parent()->left_ = node_to_delete;
      } else {
        node->parent()->right_ = node_to_delete;
      }
    }

    std::swap(node->parent_, node_to_delete->parent_);
    std::swap(node->left_, node_to_delete->left_);
    std::swap(node->right_, node_to_delete->right_);
    std::swap(node->color_, node_to_delete->color_);

    if (node == root_) {
      root_ = node_to_delete;
    }

    if (node->left_) node->left_->parent_ = node;
    if (node->right_) node->right_->parent_ = node;
    if (node_to_delete->left_) node_to_delete->left_->parent_ = node_to_delete;
    if (node_to_delete->right_)
      node_to_delete->right_->parent_ = node_to_delete;
  }

  void update_edges_on_erase(const_node_rptr node) {
    const bool is_root = node == root_.get();
    const bool is_leftmost = (node == sentinel_node_->left_.get());
    const bool is_rightmost = (node == sentinel_node_->right_.get());
    if (is_root && is_leftmost && is_rightmost) {
      sentinel_node_->left_ = nullptr;
      sentinel_node_->right_ = nullptr;
    } else {
      if (is_leftmost) {
        sentinel_node_->left_ = node->right_ ? node->right_ : node->parent();
      }
      if (is_rightmost) {
        sentinel_node_->right_ = node->left_ ? node->left_ : node->parent();
      }
    }
  }

  node_ptr bound(const key_type &key,
                 const key_compare_func comp) const noexcept {
    node_ptr current = root_;
    node_ptr result = sentinel_node_;

    while (current) {
      if (comp(get_key(*current->data_), key)) {
        current = current->right_;
      } else {
        result = current;
        current = current->left_;
      }
    }

    return result;
  }

  node_ptr allocate_node() { return std::allocate_shared<Node>(node_alloc_); }

  node_ptr allocate_node(const_reference data, const Color color = RED) {
    return std::allocate_shared<Node>(node_alloc_, data, value_alloc_, color);
  }

  // balancing functions

  void insert_balance(node_ptr node) {
    node_ptr parent_node = nullptr;
    node_ptr grand_parent_node = nullptr;
    while (node_is_red(node.get()) && node != root_ &&
           (parent_node = node->parent()) && node_is_red(parent_node.get()) &&
           (grand_parent_node = parent_node->parent()) &&
           grand_parent_node != sentinel_node_) {
      bool is_left_parent = (parent_node == grand_parent_node->left_);
      bool is_left = (node == parent_node->left_);
      node_ptr uncle_node =
          is_left_parent ? grand_parent_node->right_ : grand_parent_node->left_;

      // Case 1: The uncle of node is also red, only recoloring required
      if (node_is_red(uncle_node.get())) {
        set_node_color(grand_parent_node.get(), RED);
        set_node_color(parent_node.get(), BLACK);
        set_node_color(uncle_node.get(), BLACK);
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
          parent_node = node->parent();
          grand_parent_node = parent_node->parent();
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
    set_node_color(root_.get(), BLACK);
  }

  void delete_balance(node_ptr node, node_ptr parent) {
    // Continue until the node is the root or the node becomes red
    while (node != root_ && (node_is_black(node.get()))) {
      const bool is_left = (node == parent->left_);
      node_ptr sibling = is_left ? parent->right_ : parent->left_;

      // Case 1: The sibling is red
      if (node_is_red(sibling.get())) {
        set_node_color(sibling.get(), BLACK);
        set_node_color(parent.get(), RED);
        if (is_left) {
          rotate_left(parent);
          sibling = parent->right_;
        } else {
          rotate_right(parent);
          sibling = parent->left_;
        }
      }

      // Case 2: The sibling is black, and both of its children are black
      if (node_is_black(sibling->left_.get()) &&
          node_is_black(sibling->right_.get())) {
        set_node_color(sibling.get(), RED);
        node = parent;
        parent = parent->parent();
      } else {
        // Case 3: The sibling is black, its near child is red, and its far
        // child is black
        node_ptr near_child = is_left ? sibling->left_ : sibling->right_;
        node_ptr far_child = is_left ? sibling->right_ : sibling->left_;

        // we need to check only one child, because of the first if
        if (node_is_black(far_child.get())) {
          set_node_color(near_child.get(), BLACK);
          set_node_color(sibling.get(), RED);
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
        set_node_color(sibling.get(), parent->color_);
        set_node_color(parent.get(), BLACK);
        set_node_color(far_child.get(), BLACK);
        if (is_left) {
          rotate_left(parent);
        } else {
          rotate_right(parent);
        }
        node = root_;
      }
    }
    // Ensure the node is always black
    set_node_color(node.get(), BLACK);
  }

  void rotate_left(node_ptr node) {
    node_ptr right_child = node->right_;
    node_ptr parent = node->parent();

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

  void rotate_right(node_ptr node) {
    node_ptr left_child = node->left_;
    node_ptr parent = node->parent();

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

  // merge helper functions

  void tree_to_list(node_ptr node, node_ptr &first, node_ptr &last) {
    if (!node) {
      return;
    }
    tree_to_list(node->left_, first, last);
    if (last) {
      last->right_ = node;
      node->left_ = last;
    } else {
      first = node;
    }
    last = node;
    tree_to_list(node->right_, first, last);
  }

  void merge_lists(node_ptr &head, node_ptr &other_head, node_ptr &other_tail,
                   const bool duplicates) {
    node_ptr it = head;
    node_ptr other_it = other_head;
    node_ptr prev = nullptr;  // To keep track of previous node in first list
    // Continue as long as there are nodes left in both lists
    while (it && other_it) {
      if (key_compare()(get_key(*it->data_), get_key(*other_it->data_))) {
        // Move to next node in first list
        prev = it;
        it = it->right_;
      } else if (!duplicates &&
                 get_key(*it->data_) == get_key(*other_it->data_)) {
        // Move to next node in second list
        other_tail = other_it;
        other_it = other_it->right_;
      } else {
        // Detach current node from second list
        node_ptr other_next = other_it->right_;
        if (other_next) other_next->left_ = other_it->left_;
        if (other_it->left_) other_it->left_->right_ = other_next;

        // Insert the detached node into the first list
        if (prev) prev->right_ = other_it;
        other_it->left_ = prev;
        other_it->right_ = it;
        it->left_ = other_it;

        // Update head to always point to the start of first list
        if (!prev) head = other_it;

        // Move to next node in thesecond list
        prev = other_it;
        other_it = other_next;

        // Update other_head to always point to start of second list
        if (other_it && !other_it->left_) other_head = other_it;
        if (!other_it && other_head == prev) {
          other_head = nullptr;
          other_tail = nullptr;
        }
      }
    }

    // If there are still nodes left in second list, append them to the end of
    // the first list
    if (!it && other_it) {
      node_ptr other_prev = other_it->left_;
      prev->right_ = other_it;
      other_it->left_ = prev;
      if (other_prev) {
        other_tail = other_prev;
        other_prev->right_ = nullptr;
      } else {
        other_head = nullptr;
        other_tail = nullptr;
      }
    }
  }

  void list_to_tree(RbTree &tree, node_ptr head, node_ptr tail) {
    size_type max_depth = 0;
    tree.nodes_count_ = 0;
    tree.root_ =
        list_to_tree_recursive(head, nullptr, tree.nodes_count_, max_depth);
    if (tree.root_) {
      tree.root_->parent_ = tree.sentinel_node_;
      tree.sentinel_node_->left_ = head;
      tree.sentinel_node_->right_ = tail;
      adjust_tree(tree.root_.get(), max_depth);
      set_node_color(tree.root_.get(), BLACK);
    } else {
      tree.sentinel_node_ = nullptr;
    }
  }

  node_ptr list_to_tree_recursive(node_ptr head, node_ptr tail,
                                  size_type &nodes_count, size_type &max_depth,
                                  size_type current_depth = 0) {
    if (!head || head == tail) {
      return nullptr;
    }

    node_ptr slow = head;
    node_ptr fast = head;
    while (fast != tail && fast->right_ != tail) {
      slow = slow->right_;
      fast = fast->right_->right_;
    }

    node_ptr root = slow;
    root->left_ = list_to_tree_recursive(head, slow, nodes_count, max_depth,
                                         current_depth + 1);
    root->right_ = list_to_tree_recursive(slow->right_, tail, nodes_count,
                                          max_depth, current_depth + 1);
    if (root->left_) root->left_->parent_ = root;
    if (root->right_) root->right_->parent_ = root;

    max_depth = std::max(max_depth, current_depth);
    nodes_count++;

    return root;
  }

  void adjust_tree(node_rptr node, const size_type max_depth,
                   const size_type current_depth = 0) {
    if (!node) return;

    // the lowest level is red, then we alternate the other levels
    if ((max_depth - current_depth) % 2 == 0) {
      set_node_color(node, RED);
    } else {
      set_node_color(node, BLACK);
    }

    adjust_tree(node->left_.get(), max_depth, current_depth + 1);
    adjust_tree(node->right_.get(), max_depth, current_depth + 1);
  }
};
}  // namespace s21
#endif  // S21_RBTREE_H_
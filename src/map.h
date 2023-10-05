#ifndef S21_MAP_H_
#define S21_MAP_H_

#include <vector>

#include "rbtree.h"

namespace s21 {

template <class Key, class Value, class Compare = std::less<Key>>
class map final {
 private:
  struct GetKey {
    const Key& operator()(const std::pair<Key, Value>& value) const {
      return value.first;
    }
  };
  using BinaryTree = RbTree<Key, std::pair<const Key, Value>, GetKey, Compare>;

 public:
  using key_type = Key;
  using mapped_type = Value;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = class BinaryTree::iterator;
  using const_iterator = class BinaryTree::const_iterator;
  using size_type = size_t;

 public:
  // constructors and destructor
  map() : tree_() {}
  map(const std::initializer_list<value_type>& items) : tree_() {
    for (const value_type& item : items) {
      tree_.insert(item);
    }
  }
  map(const map& m) : tree_(m.tree_) {}
  map(map&& m) : tree_(std::move(m.tree_)) {}
  ~map() {}

  // assignment operator oveload for copying an object
  map& operator=(const map& m) {
    tree_ = m.tree_;
    return *this;
  }

  // assignment operator oveload for moving an object
  map& operator=(map&& m) noexcept {
    tree_ = std::move(m.tree_);
    return *this;
  }

  // access elements
  mapped_type& at(const key_type& key) {
    auto it = tree_.find(key);
    if (it == tree_.end()) {
      throw std::out_of_range("Invalid key");
    }
    return it->second;
  }

  const mapped_type& at(const key_type& key) const {
    auto it = tree_.find(key);
    if (it == tree_.cend()) {
      throw std::out_of_range("Invalid key");
    }
    return it->second;
  }

  mapped_type& operator[](const key_type& key) {
    auto it = tree_.find(key);
    if (it == tree_.end()) {
      auto result = tree_.insert(std::make_pair(key, mapped_type()));
      it = result.first;
    }
    return it->second;
  }

  // iterators
  iterator begin() noexcept { return tree_.begin(); }
  const_iterator cbegin() const noexcept { return tree_.cbegin(); }
  std::reverse_iterator<iterator> rbegin() noexcept { return tree_.rbegin(); }
  std::reverse_iterator<const_iterator> crbegin() const noexcept {
    return tree_.crbegin();
  }
  iterator end() noexcept { return tree_.end(); }
  const_iterator cend() const noexcept { return tree_.cend(); }
  std::reverse_iterator<iterator> rend() noexcept { return tree_.rend(); }
  std::reverse_iterator<const_iterator> crend() const noexcept {
    return tree_.crend();
  }

  // capacity
  bool empty() const noexcept { return tree_.empty(); }
  size_type size() const noexcept { return tree_.size(); }
  size_type max_size() const noexcept { return tree_.max_size(); }

  // map modifiers
  void clear() { tree_.clear(); }
  std::pair<iterator, bool> insert(const_reference value) {
    return tree_.insert(value);
  }
  std::pair<iterator, bool> insert(const key_type& key,
                                   const mapped_type& obj) {
    return tree_.insert(std::make_pair(key, obj));
  }
  std::pair<iterator, bool> insert_or_assign(const key_type& key,
                                             mapped_type&& obj) {
    auto it = tree_.find(key);
    if (it != tree_.end()) {
      it->second = std::forward<mapped_type>(obj);
      return std::make_pair(it, false);
    } else {
      return insert(key, std::forward<mapped_type>(obj));
    }
  }
  void erase(iterator pos) { tree_.erase(pos); }
  void swap(map& other) noexcept { tree_.swap(other.tree_); }
  void merge(map& other) { tree_.merge(other.tree_); }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    std::vector<std::pair<iterator, bool>> inserted;
    inserted.reserve(sizeof...(args));

    for (auto&& arg : {args...}) {
      inserted.push_back(insert(arg));
    }

    return inserted;
  }

  // map lookup
  iterator find(const Key& key) { return tree_.find(key); }
  const_iterator find(const Key& key) const { return tree_.find(key); }
  bool contains(const Key& key) const {
    return tree_.find(key) != tree_.cend();
  }

 private:
  BinaryTree tree_;
};

}  // namespace s21

#endif  // S21_MAP_H_
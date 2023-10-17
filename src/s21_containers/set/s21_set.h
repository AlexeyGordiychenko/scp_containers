#ifndef CPP2_S21_CONTAINERS_S21_CONTAINERS_SET_S21_SET_H_
#define CPP2_S21_CONTAINERS_S21_CONTAINERS_SET_S21_SET_H_

#include "../../s21_containers/map/s21_rb_tree.h"
#include "../vector/s21_vector.h"

namespace s21 {

template <class Key, class Compare = std::less<Key>>
class set final {
 private:
  struct GetKey {
    const Key operator()(const Key& value) const noexcept { return value; }
  };
  using BalancedTree = RbTree<Key, Key, GetKey, Compare>;

 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename BalancedTree::iterator;
  using const_iterator = typename BalancedTree::const_iterator;
  using size_type = size_t;

  // constructors and destructor
  set() : tree_() {}
  set(const std::initializer_list<value_type>& items) : tree_() {
    for (const value_type& item : items) {
      tree_.insert(item);
    }
  }
  set(const set& s) : tree_(s.tree_) {}
  set(set&& s) noexcept : tree_(std::move(s.tree_)) {}
  ~set() {}

  // assignment operator oveload for copying an object
  set& operator=(const set& s) {
    tree_ = s.tree_;
    return *this;
  }

  // assignment operator oveload for moving an object
  set& operator=(set&& s) noexcept {
    tree_ = std::move(s.tree_);
    return *this;
  }

  // iterators
  iterator begin() noexcept { return tree_.begin(); }
  const_iterator begin() const noexcept { return tree_.begin(); }
  const_iterator cbegin() const noexcept { return tree_.cbegin(); }
  std::reverse_iterator<iterator> rbegin() noexcept { return tree_.rbegin(); }
  std::reverse_iterator<const_iterator> rbegin() const noexcept {
    return tree_.rbegin();
  }
  std::reverse_iterator<const_iterator> crbegin() const noexcept {
    return tree_.crbegin();
  }
  iterator end() noexcept { return tree_.end(); }
  const_iterator end() const noexcept { return tree_.end(); }
  const_iterator cend() const noexcept { return tree_.cend(); }
  std::reverse_iterator<iterator> rend() noexcept { return tree_.rend(); }
  std::reverse_iterator<const_iterator> rend() const noexcept {
    return tree_.rend();
  }
  std::reverse_iterator<const_iterator> crend() const noexcept {
    return tree_.crend();
  }

  // capacity
  bool empty() const noexcept { return tree_.empty(); }
  size_type size() const noexcept { return tree_.size(); }
  size_type max_size() const noexcept { return tree_.max_size(); }

  // set modifiers
  void clear() { tree_.clear(); }
  std::pair<iterator, bool> insert(const_reference value) {
    return tree_.insert(value);
  }
  void erase(iterator pos) { tree_.erase(pos); }
  void swap(set& other) noexcept { tree_.swap(other.tree_); }
  void merge(set& other) { tree_.merge(other.tree_); }

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    s21::vector<std::pair<iterator, bool>> inserted;
    inserted.reserve(sizeof...(args));

    for (auto&& arg : {args...}) {
      inserted.push_back(insert(arg));
    }

    return inserted;
  }

  // set lookup
  iterator find(const Key& key) noexcept { return tree_.find(key); }
  const_iterator find(const Key& key) const noexcept { return tree_.find(key); }
  bool contains(const Key& key) const noexcept {
    return tree_.find(key) != tree_.cend();
  }

 private:
  BalancedTree tree_;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_CONTAINERS_SET_S21_SET_H_

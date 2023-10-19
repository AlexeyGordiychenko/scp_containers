#ifndef CPP2_SCP_CONTAINERS_SCP_CONTAINERSPLUS_MULTISET_SCP_MULTISET_H_
#define CPP2_SCP_CONTAINERS_SCP_CONTAINERSPLUS_MULTISET_SCP_MULTISET_H_

#include "../../scp_containers/map/scp_rb_tree.h"
#include "../../scp_containers/vector/scp_vector.h"

namespace scp {

template <class Key, class Compare = std::less<Key>,
          class Allocator = std::allocator<Key>>
class multiset final {
 private:
  struct GetKey {
    const Key operator()(const Key& value) const noexcept { return value; }
  };
  using BalancedTree = RbTree<Key, Key, GetKey, Compare, Allocator>;

 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename BalancedTree::iterator;
  using const_iterator = typename BalancedTree::const_iterator;
  using size_type = size_t;

  // constructors and destructor
  multiset() : tree_() {}
  multiset(const std::initializer_list<value_type>& items) : tree_() {
    for (const value_type& item : items) {
      tree_.insert(item, true);
    }
  }
  multiset(const multiset& ms) : tree_(ms.tree_) {}
  multiset(multiset&& ms) noexcept : tree_(std::move(ms.tree_)) {}
  ~multiset() {}

  // assignment operator oveload for copying an object
  multiset& operator=(const multiset& ms) {
    tree_ = ms.tree_;
    return *this;
  }

  // assignment operator oveload for moving an object
  multiset& operator=(multiset&& ms) noexcept {
    tree_ = std::move(ms.tree_);
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
  iterator insert(const_reference value) {
    return tree_.insert(value, true).first;
  }
  void erase(iterator pos) { tree_.erase(pos); }
  void swap(multiset& other) noexcept { tree_.swap(other.tree_); }
  void merge(multiset& other) { tree_.merge(other.tree_, true); }

  template <typename... Args>
  scp::vector<iterator> insert_many(Args&&... args) {
    scp::vector<iterator> inserted;
    inserted.reserve(sizeof...(args));

    for (auto&& arg : {args...}) {
      inserted.push_back(insert(arg));
    }

    return inserted;
  }

  // set lookup
  size_type count(const Key& key) const noexcept {
    auto it = tree_.lower_bound(key);
    size_type count = 0;
    while (it != tree_.cend() && *it == key) {
      count++;
      it++;
    }
    return count;
  }
  iterator find(const Key& key) noexcept { return tree_.find(key); }
  const_iterator find(const Key& key) const noexcept { return tree_.find(key); }
  bool contains(const Key& key) const noexcept {
    return tree_.find(key) != tree_.cend();
  }
  std::pair<const_iterator, const_iterator> equal_range(
      const Key& key) const noexcept {
    auto it_lower = tree_.lower_bound(key);
    auto it_upper = it_lower;
    while (it_upper != tree_.cend() && *it_upper == key) {
      it_upper++;
    }
    return std::make_pair(it_lower, it_upper);
  }
  iterator lower_bound(const Key& key) noexcept {
    return tree_.lower_bound(key);
  }
  const_iterator lower_bound(const Key& key) const noexcept {
    return tree_.lower_bound(key);
  }
  iterator upper_bound(const Key& key) noexcept {
    return tree_.upper_bound(key);
  }
  const_iterator upper_bound(const Key& key) const noexcept {
    return tree_.upper_bound(key);
  }

 private:
  BalancedTree tree_;
};

}  // namespace scp

#endif  // CPP2_SCP_CONTAINERS_SCP_CONTAINERSPLUS_MULTISET_SCP_MULTISET_H_

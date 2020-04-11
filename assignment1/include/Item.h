#ifndef ASSIGNMENT1_ITEM_H
#define ASSIGNMENT1_ITEM_H

#include <utility>
#include <vector>
#include <set>
#include <unordered_map>


using item_id_t = size_t;
using txn_id_t = size_t;


class ItemSet {
public:
  ~ItemSet() = default;

  size_t size() const;
  size_t num_children() const;
  size_t support();

  void add_child(const ItemSet *itemset);
  std::set<ItemSet *> get_children();
  static ItemSet *get_union(const ItemSet *l, const ItemSet *r);

  bool operator==(const ItemSet &o) const;
  bool operator<(const ItemSet &o) const;

  std::vector<item_id_t> items;     // IDs of items, in ascending order.

protected:
  ItemSet() = default;
  bool txns_updated = false;        // Lazily update transactions.
  std::vector<txn_id_t> txns;       // IDs of transactions, in ascending order.

private:
  std::set<const ItemSet *> children;
};


class Item : public ItemSet {
public:
  explicit Item(item_id_t item_id);
  ~Item() = default;

  void add_transaction(txn_id_t txn_id);
};


#endif //ASSIGNMENT1_ITEM_H

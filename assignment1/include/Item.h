#ifndef ASSIGNMENT1_ITEM_H
#define ASSIGNMENT1_ITEM_H

class AssociationRule;

#include <utility>
#include <vector>
#include <set>
#include <unordered_map>
#include <algorithm>


using item_id_t = size_t;
using txn_id_t = size_t;


class ItemSet {
public:
  ~ItemSet() = default;

  size_t size() const;
  size_t num_children() const;
  size_t support();

  void add_child(ItemSet *itemset);
  static ItemSet *get_union(ItemSet *l, ItemSet *r);
  virtual std::set<ItemSet *> get_descendants();

  bool operator==(const ItemSet &o) const;

  bool operator<(const ItemSet &o) const;

  std::vector<item_id_t> items;     // IDs of items, ascending order.
protected:
  ItemSet() = default;

  bool txns_updated = false;        // Lazily update transactions.
  std::vector<txn_id_t> txns;       // IDs of transactions, ascending order.

private:
  std::set<ItemSet *> children;
  std::set<ItemSet *> descendants;
};


class Item : public ItemSet {
public:
  explicit Item(item_id_t item_id);
  ~Item() = default;

  void add_transaction(txn_id_t txn_id);
  std::set<ItemSet *> get_descendants() override;
};


#endif //ASSIGNMENT1_ITEM_H

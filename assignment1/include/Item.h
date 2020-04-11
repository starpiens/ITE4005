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
  ItemSet() = default;
  ~ItemSet() = default;

  size_t size();
  size_t support();
  std::set<ItemSet *> get_children();
  ItemSet operator+(const ItemSet &o) const;
  bool operator==(const ItemSet &o) const;
  bool operator<(const ItemSet &o) const;

  std::vector<txn_id_t> txns;       // IDs of transactions, in ascending order.
  std::vector<item_id_t> items;     // IDs of items, in ascending order.
  bool txns_updated = false;        // Lazily update transactions.

private:
  std::vector<ItemSet *> children;
};


class Item : ItemSet {
  explicit Item(item_id_t item_id);
  ~Item() = default;

  void add_transaction(txn_id_t txn_id);
};


#endif //ASSIGNMENT1_ITEM_H

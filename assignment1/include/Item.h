#ifndef ASSIGNMENT1_ITEM_H
#define ASSIGNMENT1_ITEM_H

#include <utility>
#include <vector>
#include <set>
#include <unordered_map>


using item_id_t = size_t;
using txn_id_t = size_t;


class Item {
public:
  explicit Item(item_id_t item_id) : id(item_id) {}
  ~Item() = default;

  size_t support();
  void add_transaction(txn_id_t txn_id);
  bool operator<(const Item &o) const;
  bool operator==(const Item &o) const;

  item_id_t id;
  std::set<txn_id_t> txns;
};


class ItemSet {
public:
  explicit ItemSet(std::set<Item> items) : items(std::move(items)) {}
  ~ItemSet() = default;

  size_t size();
  size_t support();
  ItemSet operator+(const ItemSet &o) const;
  bool operator==(const ItemSet &o) const;
  bool operator<(const ItemSet &o) const;

  std::set<Item> items;
};





#endif //ASSIGNMENT1_ITEM_H

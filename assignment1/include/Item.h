#ifndef ASSIGNMENT1_ITEM_H
#define ASSIGNMENT1_ITEM_H

#include "globals.h"
#include "Transaction.h"
#include <utility>
#include <vector>
#include <set>

using item_id_t = size_t;


class Item {
public:
};


class ItemSet {
public:
  ItemSet(set<item_id_t> vec_item_id, set<txn_id_t> vec_txn_id);
  ~ItemSet() = default;

  void add_transaction_id(txn_id_t id) { txn_id.insert(id); }

private:
  set<item_id_t> item_id;
  set<txn_id_t> txn_id;
};


#endif //ASSIGNMENT1_ITEM_H

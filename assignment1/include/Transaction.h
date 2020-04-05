#ifndef ASSIGNMENT1_TRANSACTION_H
#define ASSIGNMENT1_TRANSACTION_H

#include "Item.h"
#include <set>

using txn_id_t = size_t;


class Transaction {
public:
  Transaction(txn_id_t txn_id, std::set<Item> set_item)
          : id(txn_id), set_item(std::move(set_item)) {}

  ~Transaction() = default;

  const txn_id_t id;

private:
  std::set<Item> set_item;
};


#endif //ASSIGNMENT1_TRANSACTION_H

#ifndef ASSIGNMENT1_TRANSACTION_H
#define ASSIGNMENT1_TRANSACTION_H

#include "globals.h"
#include <set>

using txn_id_t = size_t;


class Transaction {
public:
  Transaction(txn_id_t txn_id, std::set<item_id_t> set_item_id)
          : txn_id(txn_id), set_item_id(std::move(set_item_id)) {}

  ~Transaction() = default;

  const txn_id_t txn_id;

private:
  std::set<item_id_t> set_item_id;
};


#endif //ASSIGNMENT1_TRANSACTION_H

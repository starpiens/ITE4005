#ifndef ASSIGNMENT1_ITEMSET_H
#define ASSIGNMENT1_ITEMSET_H

#include "globals.h"
#include <vector>


class ItemSet {
public:
  ItemSet(vector<item_id_t> vec_item_id, vector<txn_id_t> vec_txn_id);
  ~ItemSet() = default;

private:
  unordered_set<item_id_t> item_id;
  unordered_set<txn_id_t> txn_id;
};


#endif //ASSIGNMENT1_ITEMSET_H

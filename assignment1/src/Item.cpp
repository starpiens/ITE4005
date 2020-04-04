#include "Item.h"

ItemSet::ItemSet(set<item_id_t> vec_item_id, set<txn_id_t> vec_txn_id) {
    item_id = std::move(vec_item_id);
    txn_id = std::move(vec_txn_id);
}
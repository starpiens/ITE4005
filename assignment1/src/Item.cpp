#include "Item.h"

size_t Item::support() {
    return txns.size();
}

void Item::add_transaction(txn_id_t txn_id) {
    txns.insert(txn_id);
}

bool Item::operator<(Item &o) {
    return id < o.id;
}

size_t ItemSet::support() {
    // TODO

    return 0;
}

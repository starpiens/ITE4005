#include "Item.h"
#include <algorithm>

size_t Item::support() {
    return txns.size();
}

void Item::add_transaction(txn_id_t txn_id) {
    txns.insert(txn_id);
}

bool Item::operator<(Item &o) {
    return id < o.id;
}

size_t ItemSet::size() {
    return items.size();
}

size_t ItemSet::support() {
    auto intersection = items.begin()->txns;
    for (auto it = ++items.begin(); it != items.end(); it++) {
        intersection.erase(std::remove_if(intersection.begin(),
                                          intersection.end(),
                                          [it](auto &i) {
                                            it->txns.find(i) == it->txns.end();
                                          }),
                           intersection.end());
    }

    // TODO: Faster computation

    return intersection.size();
}

bool ItemSet::operator+(Item &o) {
    return false;
}

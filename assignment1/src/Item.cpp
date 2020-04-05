#include "Item.h"
#include <algorithm>

size_t Item::support() {
    return txns.size();
}

void Item::add_transaction(txn_id_t txn_id) {
    txns.insert(txn_id);
}

bool Item::operator<(const Item &o) const {
    return id < o.id;
}

bool Item::operator==(const Item &o) const {
    return id == o.id;
}

size_t ItemSet::size() {
    return items.size();
}

size_t ItemSet::support() {
    auto intersection = items.begin()->txns;
    for (auto it = ++items.begin(); it != items.end(); it++) {
        for (auto it2 = intersection.begin(); it2 != intersection.end(); ) {
            if (it->txns.find(*it2) == it->txns.end())
                it2 = intersection.erase(it2);
            else it2++;
        }

        /*
        intersection.erase(std::remove_if(intersection.begin(),
                                          intersection.end(),
                                          [it](txn_id_t i) {
                                            return it->txns.find(i) == it->txns.end();
                                          }),
                           intersection.end());
                           */
    }

    // TODO: Faster computation

    return intersection.size();
}

ItemSet ItemSet::operator+(const ItemSet &o) const {
    ItemSet result(o);
    result.items.insert(items.begin(), items.end());
    return result;
}

bool ItemSet::operator==(const ItemSet &o) const {
    return items == o.items;
}

bool ItemSet::operator<(const ItemSet &o) const {
    return items < o.items;
}
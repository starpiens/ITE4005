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
        decltype(intersection) tmp;
        std::set_intersection(intersection.begin(), intersection.end(),
                              it->txns.begin(), it->txns.end(),
                              std::inserter(tmp, tmp.begin()));
        intersection = tmp;
    }

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
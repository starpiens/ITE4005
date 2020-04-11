#include "Item.h"
#include <algorithm>

size_t ItemSet::size() {
    return items.size();
}

size_t ItemSet::support() {
    if (!txns_updated) {
        std::set_intersection(children[0]->txns.begin(), children[0]->txns.end(),
                              children[1]->txns.begin(), children[1]->txns.end(),
                              txns);
        txns_updated = true;
    }
    return txns.size();
}

ItemSet ItemSet::operator+(const ItemSet &o) const {
    ItemSet result;
    std::set_union(this->items.begin(), this->items.end(),
                   o.items.begin(), o.items.end(),
                   result.items);
    return result;
}

bool ItemSet::operator==(const ItemSet &o) const {
    return items == o.items;
}

bool ItemSet::operator<(const ItemSet &o) const {
    return items < o.items;
}


Item::Item(item_id_t item_id) {
    items.push_back(item_id);
}

void Item::add_transaction(txn_id_t txn_id) {
    txns.push_back(txn_id);
    txns_updated = true;
}
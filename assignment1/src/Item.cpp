#include "Item.h"
#include <algorithm>


size_t ItemSet::size() const {
    return items.size();
}

size_t ItemSet::support() {
    if (!txns_updated) {
        std::set_intersection((*children.begin())->txns.begin(), (*children.begin())->txns.end(),
                              (*++children.begin())->txns.begin(), (*++children.begin())->txns.end(),
                              std::back_inserter(txns));
        txns_updated = true;
    }
    return txns.size();
}

size_t ItemSet::num_children() const {
    return children.size();
}

ItemSet *ItemSet::get_union(const ItemSet *l, const ItemSet *r) {
    auto result = new ItemSet;
    std::set_union(l->items.begin(), l->items.end(),
                   r->items.begin(), r->items.end(),
                   std::back_inserter(result->items));
    result->children.insert(l);
    result->children.insert(r);
    return result;
}


bool ItemSet::operator==(const ItemSet &o) const {
    return items == o.items;
}

bool ItemSet::operator<(const ItemSet &o) const {
    return items < o.items;
}

std::set<ItemSet *> ItemSet::get_children() {
    return std::set<ItemSet *>();
}

void ItemSet::add_child(const ItemSet *itemset) {
    children.insert(itemset);
}


Item::Item(item_id_t item_id) {
    items.push_back(item_id);
}

void Item::add_transaction(txn_id_t txn_id) {
    txns.push_back(txn_id);
    txns_updated = true;
}
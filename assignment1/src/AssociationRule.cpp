#include "AssociationRule.h"

AssociationRule::AssociationRule(ItemSet *itemset, ItemSet *assc_itemset, size_t num_support, float confidence) {
    itemset = itemset;
    assc_itemset = assc_itemset;
    num_support = num_support;
    confidence = confidence;
}
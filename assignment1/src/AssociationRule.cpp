#include "AssociationRule.h"

AssociationRule::AssociationRule(ItemSet item_set, ItemSet assc_item_set, size_t num_support, float confidence) :
        item_set(item_set), assc_item_set(assc_item_set), support(num_support), confidence(confidence) {
    ;
}

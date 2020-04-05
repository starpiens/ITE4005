#ifndef ASSIGNMENT1_ASSOCIATIONRULE_H
#define ASSIGNMENT1_ASSOCIATIONRULE_H

#include "globals.h"
#include "Item.h"


class AssociationRule {
public:
  AssociationRule(ItemSet item_set, ItemSet assc_item_set, size_t num_support, float confidence);
  ~AssociationRule() = default;

  ItemSet item_set;
  ItemSet assc_item_set;

  size_t support;
  float confidence;
};


#endif //ASSIGNMENT1_ASSOCIATIONRULE_H

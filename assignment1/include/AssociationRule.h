#ifndef ASSIGNMENT1_ASSOCIATIONRULE_H
#define ASSIGNMENT1_ASSOCIATIONRULE_H

#include "globals.h"
#include "Item.h"


class AssociationRule {
public:
  AssociationRule(ItemSet *itemset, ItemSet *assc_itemset, size_t num_support, float confidence);

  ~AssociationRule() = default;

  ItemSet *itemset;
  ItemSet *assc_itemset;
  size_t support;
  float confidence;
};


#endif //ASSIGNMENT1_ASSOCIATIONRULE_H

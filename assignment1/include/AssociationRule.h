#ifndef ASSIGNMENT1_ASSOCIATIONRULE_H
#define ASSIGNMENT1_ASSOCIATIONRULE_H

#include "globals.h"
#include "Item.h"


class AssociationRule {
public:
  AssociationRule() = default;
  ~AssociationRule() = default;

private:
  ItemSet item_set;
  ItemSet assc_item_set;
  size_t num_support;
  size_t num_confidence;
};


#endif //ASSIGNMENT1_ASSOCIATIONRULE_H

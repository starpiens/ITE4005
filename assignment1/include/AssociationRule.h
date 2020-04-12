#ifndef ASSIGNMENT1_ASSOCIATIONRULE_H
#define ASSIGNMENT1_ASSOCIATIONRULE_H

#include "globals.h"
#include "Item.h"


struct AssociationRule {
public:
  AssociationRule(ItemSet *itemset, ItemSet *assc_itemset) :
          itemset(itemset), assc_itemset(assc_itemset) {}
  ~AssociationRule() = default;

  ItemSet *itemset;
  ItemSet *assc_itemset;
};


#endif //ASSIGNMENT1_ASSOCIATIONRULE_H

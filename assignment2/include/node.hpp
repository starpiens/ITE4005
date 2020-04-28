#ifndef ASSIGNMENT2_NODE_HPP
#define ASSIGNMENT2_NODE_HPP

#include <utility>

#include "data.hpp"

struct node {
  attribute_base* _Nonnull _attr;
  std::unordered_map<attribute_base::val_id, node*> _children;
  attribute_base::val_id _label;

  explicit node() = default;
  attribute_base::val_id infer(const data& d) const;
};

node* _Nullable construct_tree(const std::vector<data>& vec_data, std::unordered_set<attribute_base*> attrs);

#endif //ASSIGNMENT2_NODE_HPP

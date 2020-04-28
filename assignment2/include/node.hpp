#ifndef ASSIGNMENT2_NODE_HPP
#define ASSIGNMENT2_NODE_HPP

#include <utility>

#include "data.hpp"

struct node {
  attribute_base* _Nonnull attr;
  std::vector<node* _Nonnull> children;

  attribute_base::val_id infer(data d) const;
};

struct train_node {
  node* _Nonnull _n;
  std::vector<data> _vec_data;
  std::vector<attribute_base*> _attrs;
  std::vector<train_node*> children;

  train_node(std::vector<data> vec_data, std::vector<attribute_base*> attrs);
  ~train_node();
};

#endif //ASSIGNMENT2_NODE_HPP

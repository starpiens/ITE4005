#ifndef ASSIGNMENT2_ATTRIBUTE_HPP
#define ASSIGNMENT2_ATTRIBUTE_HPP

#include <string>
#include <vector>
#include <algorithm>

struct attribute_base {
  size_t id;
  std::string name;
};

template <typename Val>
struct attribute : attribute_base {
  std::vector<Val> possible_values;
};

struct valued_attribute {
  attribute_base *attr;
  size_t val_idx;
};


#endif //ASSIGNMENT2_ATTRIBUTE_HPP

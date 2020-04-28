#ifndef ASSIGNMENT2_DATA_HPP
#define ASSIGNMENT2_DATA_HPP

#include "attribute.hpp"

struct data {
  std::unordered_map<attribute_base*, attribute_base::val_id> attrs;
  std::pair<attribute_base*, attribute_base::val_id> label;
};

std::vector<data>
read_data(std::ifstream& ifs,
          const std::vector<attribute_base*>& attributes,
          attribute_base* label = nullptr);

#endif //ASSIGNMENT2_DATA_HPP

#ifndef ASSIGNMENT2_DATA_HPP
#define ASSIGNMENT2_DATA_HPP

#include "attribute.hpp"

struct data {
  std::vector<valued_attribute> attrs;
  valued_attribute label;
};

std::vector<data> read_data(std::ifstream& ifs, const std::vector<attribute_base*>& attributes, attribute_base *label);

#endif //ASSIGNMENT2_DATA_HPP

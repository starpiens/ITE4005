#ifndef ASSIGNMENT2_DATA_HPP
#define ASSIGNMENT2_DATA_HPP

#include "attribute.hpp"

struct Data {
  std::vector<valued_attribute> attrs;
  valued_attribute val;
};

std::vector<Data> read_data;

#endif //ASSIGNMENT2_DATA_HPP

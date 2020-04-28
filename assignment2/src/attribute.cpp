#include <sstream>
#include "attribute.hpp"

std::vector<attribute_base*> read_attributes(std::ifstream& ifs) {
    std::vector<attribute_base*> attributes;
    using attr_val_t = std::string;

    std::string line;
    std::getline(ifs, line);
    std::istringstream iss(line);
    attr_val_t name;
    for (attribute_base::val_id id = 0; iss >> name; id++) {
        attributes.push_back(static_cast<attribute_base*>(new attribute<attr_val_t>(id, name)));
    }

    return attributes;
}
#include <sstream>

#include "data.hpp"

std::vector<data> read_data(std::ifstream& ifs, const std::vector<attribute_base*>& attributes, attribute_base* label) {
    std::vector<data> vec_data;
    std::string line;
    while (std::getline(ifs, line)) {
        data new_data;
        std::istringstream iss(line);
        for (auto attr : attributes) {
            auto val_id = attr->read_value(iss);
            new_data.attrs[attr] = val_id;
        }
        auto val_id = label->read_value(iss);
        new_data.label = {label, val_id};
        vec_data.push_back(new_data);
    }
    return vec_data;
}
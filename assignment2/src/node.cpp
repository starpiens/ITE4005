#include "node.hpp"

train_node::train_node(std::vector<data> vec_data, std::vector<attribute_base *> attrs) {
    _vec_data = std::move(vec_data);
    _attrs = std::move(attrs);
    for (auto attr : _attrs) {
        ;
    }
}
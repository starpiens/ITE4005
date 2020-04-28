#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "attribute.hpp"
#include "data.hpp"
#include "node.hpp"

int main(int argc, char* argv[]) {
    std::ifstream train_stream(argv[1]);
    std::ifstream test_stream(argv[2]);
    std::ofstream result_stream(argv[3]);

    // Train
    auto attributes = read_attributes(train_stream);
    auto label = attributes.back();
    attributes.pop_back();
    auto vec_data = read_data(train_stream, attributes, label);
    train_stream.close();

    std::unordered_set<attribute_base*> set_attrs;
    for (auto& attr : attributes)
        set_attrs.insert(attr);
    auto tree = construct_tree(vec_data, set_attrs);

    // Test

    test_stream.close();
    result_stream.close();

    return 0;
}

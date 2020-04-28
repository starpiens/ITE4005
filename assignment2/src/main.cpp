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
    if (!train_stream.good()
        || !test_stream.good()
        || !result_stream.good())
        exit(1);

    // Train
    auto train_attributes = read_attributes(train_stream);
    auto label = train_attributes.back();
    train_attributes.pop_back();
    auto vec_train_data = read_data(train_stream, train_attributes, label);
    train_stream.close();

    std::unordered_set<attribute_base*> set_attrs;
    for (auto& attr : train_attributes)
        set_attrs.insert(attr);
    auto tree = construct_tree(vec_train_data, set_attrs);

    // Test
    auto test_attributes = read_attributes(test_stream);
    for (auto i : test_attributes)
        delete i;
    auto vec_test_data = read_data(test_stream, train_attributes);
    test_stream.close();

    for (auto& attr : train_attributes)
        result_stream << attr->name() << " ";
    result_stream << std::endl;
    for (auto& d : vec_test_data) {
        for (auto& i : d.attrs) {
            i.first->write_value(result_stream, i.second);
            result_stream << " ";
        }
        auto i = tree->infer(d);
        label->write_value(result_stream, i);
        result_stream << std::endl;
    }
    result_stream.close();
    return 0;
}

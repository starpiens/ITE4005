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
    auto data = read_data(train_stream, attributes, label);
    train_stream.close();
    auto tree = node(data, attributes);

    // Test

    test_stream.close();
    result_stream.close();

    return 0;
}

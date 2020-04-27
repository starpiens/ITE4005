#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "attribute.hpp"

std::vector<attribute_base*> read_attributes(std::ifstream& ifs) {
    std::vector<attribute_base*> attributes;
    using attr_val_t = std::string;

    std::string line;
    std::getline(ifs, line);
    std::istringstream iss(line);
    attr_val_t name;
    for (int id = 0; iss >> name; id++) {
        attributes.push_back(static_cast<attribute_base*>(new attribute<attr_val_t>(id, name)));
    }

    return attributes;
}

int main(int argc, char* argv[]) {
    std::ifstream train_stream(argv[1]);
    std::ifstream test_stream(argv[2]);
    std::ofstream result_stream(argv[3]);

    // Train
    auto attributes = read_attributes(train_stream);
    train_stream.close();
    for (auto attr : attributes) {
        std::cout << attr->id() << " " << attr->name() << std::endl;
    }

    // Test

    test_stream.close();
    result_stream.close();

    return 0;
}

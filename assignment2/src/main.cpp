#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "attribute.hpp"
#include "data.hpp"

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

    //for (auto d : data) {
        for (auto a : data[0].attrs) {
            std::cout << a.get_attr()->name() << ": ";
            a.get_attr()->write_value(std::cout, a.get_val_id());
            std::cout << std::endl;
        }
        std::cout << "label = " << data[0].label.get_attr()->name() << ": ";
        data[0].label.get_attr()->write_value(std::cout, data[0].label.get_val_id());
    //}

    // Test

    test_stream.close();
    result_stream.close();

    return 0;
}

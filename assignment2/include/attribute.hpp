#ifndef ASSIGNMENT2_ATTRIBUTE_HPP
#define ASSIGNMENT2_ATTRIBUTE_HPP

#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <fstream>

class attribute_base {
  size_t __id;
  std::string __name;

public:
  attribute_base(size_t id) : __id(id) {}
  attribute_base(size_t id, std::string name) : attribute_base(id) { set_name(name); }
  ~attribute_base() = default;

  size_t id() { return __id; }
  std::string name() { return __name; }
  void set_name(std::string name) { __name = std::move(name); }

  virtual void add_value(void* value) = 0;
};

template<typename Val>
class attribute : public attribute_base {
  std::unordered_set<Val> possible_values;

public:
  attribute(size_t id) : attribute_base(id) {}
  attribute(size_t id, std::string name) : attribute_base(id, name) {}
  ~attribute() = default;

  void add_value(void* value) override;
};

template<typename Val>
void attribute<Val>::add_value(void* value) {
    possible_values.insert(*static_cast<Val*>(value));
}

struct valued_attribute {
  attribute_base* attr;
  void* val;
};


#endif //ASSIGNMENT2_ATTRIBUTE_HPP

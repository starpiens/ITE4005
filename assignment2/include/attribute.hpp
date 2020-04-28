#ifndef ASSIGNMENT2_ATTRIBUTE_HPP
#define ASSIGNMENT2_ATTRIBUTE_HPP

#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <fstream>
#include <unordered_map>

class attribute_base {
public:
  typedef size_t val_id;

protected:
  val_id _id;
  std::string _name;

public:
  explicit attribute_base(val_id id) : _id(id) {}
  attribute_base(val_id id, std::string name) : attribute_base(id) { _name = std::move(name); }
  ~attribute_base() = default;

  val_id id() const { return _id; }
  std::string name() const { return _name; }
  void set_name(std::string name) { _name = std::move(name); }

  virtual val_id get_id(void* _Nonnull value) = 0;
  virtual val_id read_value(std::istringstream& iss) = 0;
  virtual void write_value(std::ostream& ofs, val_id id) const = 0;
};

template<typename Val>
class attribute : public attribute_base {
  std::unordered_map<Val, val_id> val_to_id;
  std::vector<Val> id_to_val;

public:
  explicit attribute(val_id id) : attribute_base(id) {}
  attribute(val_id id, std::string name) : attribute_base(id, name) {}
  ~attribute() = default;

  val_id get_id(void* _Nonnull value) override;
  val_id read_value(std::istringstream&) override;
  void write_value(std::ostream& ofs, val_id id) const override;
};

template<typename Val>
attribute_base::val_id attribute<Val>::get_id(void* _Nonnull value) {
    auto& val_casted = *static_cast<Val*>(value);
    auto it = val_to_id.find(val_casted);
    if (it != val_to_id.end()) {
        return it->second;
    }
    val_to_id[val_casted] = val_to_id.size();
    id_to_val.push_back(val_casted);
    return val_to_id.size() - 1;
}

template<typename Val>
attribute_base::val_id attribute<Val>::read_value(std::istringstream& iss) {
    Val value;
    iss >> value;
    return get_id(&value);
}

template<typename Val>
void attribute<Val>::write_value(std::ostream& ofs, val_id id) const {
    ofs << id_to_val[id];
}

class valued_attribute {
  attribute_base* _Nonnull _attr;
  attribute_base::val_id _val_id;

public:
  valued_attribute() = default;
  valued_attribute(attribute_base* _Nonnull attr, attribute_base::val_id val_id);
  valued_attribute(attribute_base* _Nonnull attr, void* _Nonnull val);
  ~valued_attribute() = default;

  void set(attribute_base* _Nonnull attr, attribute_base::val_id val_id);

  const attribute_base* _Nonnull get_attr() const { return _attr; }
  attribute_base::val_id get_val_id() const { return _val_id; }
};

std::vector<attribute_base*> read_attributes(std::ifstream& ifs);

#endif //ASSIGNMENT2_ATTRIBUTE_HPP

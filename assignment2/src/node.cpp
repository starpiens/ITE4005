#include "node.hpp"

static std::unordered_map<attribute_base::val_id, size_t>
count_label(const std::vector<data>& vec_data) {
    std::unordered_map<attribute_base::val_id, size_t> count;
    for (auto& d : vec_data) {
        count[d.label.second]++;
    }
    return count;
}

static double
info(const std::vector<data>& vec_data) {
    auto count = count_label(vec_data);
    double ret = 0;
    for (auto& i : count) {
        double pi = (double) i.second / vec_data.size();
        ret -= pi * log(pi);
    }
    return ret;
}

static double
info(const std::unordered_map<attribute_base::val_id, std::vector<data>>& categorized_data) {
    double ret = 0;
    for (auto& i : categorized_data) {
        double w = (double) i.second.size() / categorized_data.size();
        ret += w * info(i.second);
    }
    return ret;
}

static std::unordered_map<attribute_base::val_id, std::vector<data>>
categorize_data(const std::vector<data>& vec_data, attribute_base* attr) {
    std::unordered_map<attribute_base::val_id, std::vector<data>> categorized_data;
    for (auto& d : vec_data) {
        categorized_data[d.attrs.at(attr)].push_back(d);
    }
    return categorized_data;
}

node* construct_tree(const std::vector<data>& vec_data, std::unordered_set<attribute_base*> attrs) {
    auto count = count_label(vec_data);
    if (count.size() == 1) return nullptr;

    node *n = new node();
    size_t max_count = 0;
    for (auto& c : count) {
        if (max_count < c.second) {
            max_count = c.second;
            n->_label = c.first;
        }
    }

    double min_info = std::numeric_limits<double>::max();
    attribute_base* selected_attr = nullptr;
    std::unordered_map<attribute_base::val_id, std::vector<data>> selected_attr_categorized_data;

    for (auto attr : attrs) {
        auto categorized_data = categorize_data(vec_data, attr);
        double current_info = info(categorized_data);
        if (min_info > current_info) {
            min_info = current_info;
            selected_attr = attr;
            selected_attr_categorized_data = categorized_data;
        }
    }
    n->_attr = selected_attr;
    attrs.erase(selected_attr);
    if (!attrs.empty() && selected_attr_categorized_data.size() > 1) {
        for (auto& i : selected_attr_categorized_data) {
            n->_children[i.first] = construct_tree(i.second, attrs);
        }
    }
    return n;
}
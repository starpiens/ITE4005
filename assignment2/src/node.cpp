#include "node.hpp"

node::~node() {
    for (auto& i : _children) {
        delete i.second;
    }
}

attribute_base::val_id node::infer(const data& d) const {
    if (_attr == nullptr)
        return _label;
    auto val = d.attrs.at(_attr);
    try {
        return _children.at(val)->infer(d);
    } catch (std::out_of_range& e) {}   // Not learned from train data
    return _label;
}

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
        ret -= pi * log2(pi);
    }
    return ret;
}

static double
info(
        const std::unordered_map<attribute_base::val_id,
                std::vector<data>>& categorized_data,
        size_t total_sz) {
    double ret = 0;
    for (auto& i : categorized_data) {
        double w = (double) i.second.size() / total_sz;
        ret += w * info(i.second);
    }
    return ret;
}

static std::unordered_map<attribute_base::val_id, std::vector<data>>
categorize_data(
        const std::vector<data>& vec_data,
        attribute_base* attr) {
    std::unordered_map<attribute_base::val_id, std::vector<data>> categorized_data;
    for (auto& d : vec_data) {
        categorized_data[d.attrs.at(attr)].push_back(d);
    }
    return categorized_data;
}

__unused static
std::pair<
        attribute_base*,
        std::unordered_map<
                attribute_base::val_id, std::vector<data>>>
select_attribute_info_gain(const std::vector<data>& vec_data, const std::unordered_set<attribute_base*>& attrs) {

    double min_info = std::numeric_limits<double>::max();
    attribute_base* selected_attr = nullptr;
    std::unordered_map<attribute_base::val_id, std::vector<data>> selected_attr_categorized_data;
    for (auto attr : attrs) {
        auto categorized_data = categorize_data(vec_data, attr);
        double current_info = info(categorized_data, vec_data.size());
        if (min_info > current_info) {
            min_info = current_info;
            selected_attr = attr;
            selected_attr_categorized_data = categorized_data;
        }
    }
    return {selected_attr, selected_attr_categorized_data};
}

static double
split_info(
        const std::unordered_map<attribute_base::val_id, std::vector<data>>& categorized_data,
        size_t total_sz) {
    double ret = 0;
    for (auto& i : categorized_data) {
        double tmp = (double) i.second.size() / total_sz;
        ret -= tmp * log2(tmp);
    }
    return ret;
}

static double
compute_gain_ratio(
        const std::vector<data>& vec_data,
        const std::unordered_map<attribute_base::val_id, std::vector<data>>& categorized_data) {
    double gain = info(vec_data) - info(categorized_data, vec_data.size());
    return gain / split_info(categorized_data, vec_data.size());
}

static
std::pair<
        attribute_base*,
        std::unordered_map<
                attribute_base::val_id, std::vector<data>>>
select_attribute_gain_ratio(
        const std::vector<data>& vec_data,
        const std::unordered_set<attribute_base*>& attrs) {

    double max_gain_ratio = -1;
    attribute_base* selected_attr = nullptr;
    std::unordered_map<attribute_base::val_id, std::vector<data>> selected_attr_categorized_data;
    for (auto attr : attrs) {
        auto categorized_data = categorize_data(vec_data, attr);
        double gain_ratio = compute_gain_ratio(vec_data, categorized_data);
        if (max_gain_ratio < gain_ratio) {
            max_gain_ratio = gain_ratio;
            selected_attr = attr;
            selected_attr_categorized_data = categorized_data;
        }
    }
    return {selected_attr, selected_attr_categorized_data};
}


node* construct_tree(const std::vector<data>& vec_data, std::unordered_set<attribute_base*> attrs) {
    node* n = new node();

    auto count = count_label(vec_data);
    size_t max_count = 0;
    for (auto& c : count) {
        if (max_count < c.second) {
            max_count = c.second;
            n->_label = c.first;
        }
    }
    if (info(vec_data) < .4)
        return n;

    auto selected_attr = select_attribute_gain_ratio(vec_data, attrs);
    if (selected_attr.second.size() <= 1 || attrs.size() <= 1
        || compute_gain_ratio(vec_data, selected_attr.second) < .1)
        return n;
    n->_attr = selected_attr.first;
    attrs.erase(selected_attr.first);
    for (auto& i : selected_attr.second) {
        if (i.second.size() > vec_data.size() * .05)
            n->_children[i.first] = construct_tree(i.second, attrs);
    }
    return n;
}
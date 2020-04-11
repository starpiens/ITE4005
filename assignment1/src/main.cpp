#include <exception>
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <map>

#include "Item.h"
#include "AssociationRule.h"

using namespace std;

/**
 * Read transactions from input file stream.
 *
 * @param ifs Input file stream.
 * @return Vector of items.
 */
vector<Item *> read_items(ifstream &ifs) {
    unordered_map<item_id_t, Item *> map_item;
    string txn_str;
    num_txns = 0;
    while (getline(ifs, txn_str)) {
        istringstream iss(txn_str);
        item_id_t item_id;
        while (iss >> item_id) {
            if (!map_item[item_id]) {
                map_item[item_id] = new Item(item_id);
            }
            map_item[item_id]->add_transaction(num_txns);
        }
        num_txns++;
    }
    vector<Item *> vec_items;
    vec_items.reserve(map_item.size());
    for (auto &item : map_item) {
        vec_items.push_back(item.second);
    }
    return vec_items;
}

/**
 * Find frequent item sets using Apriori algorithm.
 *
 * @param txns Vector of transactions.
 * @param min_support Minimum support count.
 * @return Vector of pointer of frequent item sets.
 */
// TODO: find only max patterns
vector<const ItemSet *> find_frequent_patterns(vector<Item *> items, const int min_support) {

    auto freq_end = remove_if(items.begin(),
                              items.end(),
                              [min_support](auto &i) { return i->support() < min_support; });

    vector<const ItemSet *> freq_item_sets;
    map<vector<item_id_t>, ItemSet *> candidate_item_sets;
    for (auto it = items.begin(); it != freq_end; it++) {
        freq_item_sets.push_back(*it);
    }

    int cnt = 0;
    size_t prev_begin = 0;
    for (int k = 2; prev_begin != freq_item_sets.size(); k++) {
        // Generate
        for (auto i = prev_begin; i != freq_item_sets.size(); i++) {
            for (auto j = i + 1; j != freq_item_sets.size(); j++) {
                auto uni = Item::get_union(freq_item_sets[i], freq_item_sets[j]);
                if (uni->size() == k) {
                    cnt++;
                    auto &tmp = candidate_item_sets[uni->items];
                    if (tmp == nullptr) {
                        tmp = uni;
                    } else {
                        tmp->add_child(freq_item_sets[i]);
                        tmp->add_child(freq_item_sets[j]);
                    }
                } else {
                    delete uni;
                }
            }
        }
        // Test
        prev_begin = freq_item_sets.size();
        for (auto &i : candidate_item_sets) {
            if (i.second->num_children() == k && i.second->support() >= min_support) {
                freq_item_sets.push_back(i.second);
            } else {
                delete i.second;
            }
        }
        candidate_item_sets.clear();
    }

    return freq_item_sets;
}

/**
 * Find association rules.
 * @param items Vector of items.
 * @param min_support Minimum support value.
 * @return Vector of association rules.
 */
 /*
vector<AssociationRule> find_association_rules(const vector<Item> &items, const int min_support) {
    vector<AssociationRule> assc_rules;

    auto time_start = chrono::steady_clock::now();
    auto freq_item_sets = find_frequent_patterns(items, min_support);
    auto time_end = chrono::steady_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(time_end - time_start).count() << endl;

    for (size_t sz = freq_item_sets.size() - 1; sz >= 2; sz--) {
        for (auto i : freq_item_sets[sz]) {
            vector<unsigned int> bit_mask((sz + 1) / (8 * sizeof(unsigned int)) + 1);

            while (!is_on(bit_mask, sz)) {
                auto it = i.items.begin();
                ItemSet set_i({}), set_j({});
                for (int j = 0; j < sz; j++) {
                    if (is_on(bit_mask, j)) {
                        set_i = set_i + ItemSet({*it});
                    } else {
                        set_j = set_j + ItemSet({*it});
                    }
                    it++;
                }
                increment(bit_mask);
                if (!set_i.size() || !set_j.size()) continue;

                auto found_i = freq_item_sets[set_i.size()].find(set_i);
                auto found_j = freq_item_sets[set_j.size()].find(set_j);
                assc_rules.emplace_back(*found_i, *found_j, i.support(), (float) i.support() / found_i->support());
            }
        }
    }

    return assc_rules;
}
  */

/**
 * Overloads operator<< to write association rules on file stream.
 * @param ofs Output file stream.
 * @param rules Vector of association rules.
 * @return `ofs`.
 */
 /*
ofstream &operator<<(ofstream &ofs, const vector<AssociationRule> &rules) {
    for (const auto &rule : rules) {
        ofs << "{" << rule.item_set.items.cbegin()->id;
        for (auto it = ++rule.item_set.items.cbegin(); it != rule.item_set.items.cend(); it++) {
            ofs << "," << it->id;
        }
        ofs << "}\t";
        ofs << "{" << rule.assc_item_set.items.cbegin()->id;
        for (auto it = ++rule.assc_item_set.items.cbegin(); it != rule.assc_item_set.items.cend(); it++) {
            ofs << "," << it->id;
        }
        ofs << "}\t";
        auto ori_precision = ofs.precision();
        ofs << fixed;
        ofs.precision(2);
        ofs << 100. * rule.support / num_txns << "\t";
        ofs << 100. * rule.confidence << "\n";
        ofs.unsetf(ios::fixed);
        ofs.precision(ori_precision);
    }
    return ofs;
}
  */

/**
 * Solves assignment1, finding association rules of given transactions.
 * @param argc Argument count, which must be 4.
 * @param argv[1] Minimum support value in percentage.
 * @param argv[2] Input file path.
 * @param argv[3] Output file path.
 * @return Returns 0 if no error occurred, non-zero value otherwise.
 */
int main(int argc, char *argv[]) {
    if (argc != 4) {
        cerr << "usage: apriori [0-100] input_file output_file" << endl;
        return 1;
    }

    char *tmp_ptr = argv[1];
    const int min_support_percent = (int) strtol(argv[1], &tmp_ptr, 0);
    ifstream ifs(argv[2]);
    ofstream ofs(argv[3]);
    if (min_support_percent < 0 || min_support_percent > 100 || argv[1] == tmp_ptr) {
        cerr << "minimum support must be integer [0-100]. (%)";
        return EINVAL;
    } else if (!ifs.good()) {
        cerr << "cannot open input file: " << argv[2];
        return 1;
    } else if (!ofs.good()) {
        cerr << "cannot open output file: " << argv[3];
        return 1;
    }

    cout << "Running.." << endl;
    auto time_start = chrono::steady_clock::now();

    auto items = read_items(ifs);
    int min_support = ceil(min_support_percent * num_txns / 100.);
    auto fp = find_frequent_patterns(items, min_support);
    cout << fp.size() << endl;
    for (auto i : fp) {
        for (auto j : i->items)
            cout << j << " ";
        cout << endl;
    }
    /*
    auto assc_rules = find_association_rules(items, min_support);
    ofs << assc_rules;
     */

    auto time_end = chrono::steady_clock::now();
    cout << "Done.\nTotal Time elapsed: "
         << chrono::duration_cast<chrono::milliseconds>(time_end - time_start).count()
         << "ms";

    ifs.close();
    ofs.close();
    return 0;
}
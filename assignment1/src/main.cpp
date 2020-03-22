#include <exception>
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <unordered_set>
#include <unordered_map>

using namespace std;

using item_id_t = int;
using txn_t = vector<item_id_t>;
using item_set_t = unordered_set<item_id_t>;

using AssociationRule = struct {
  item_set_t item_set;
  item_set_t associative_item_set;
  float support;
  float confidence;
};

vector<txn_t> read_transactions(ifstream &ifs) {
    vector<txn_t> txns;
    string txn_str;
    while (getline(ifs, txn_str)) {
        txns.resize(txns.size() + 1);
        istringstream iss(txn_str);
        item_id_t item;
        while (iss >> item) {
            txns.back().push_back(item);
        }
    }
    return txns;
}

vector<item_set_t> find_frequent_item_sets(const vector<txn_t> &txns, const int min_support) {
    vector<item_set_t> freq_item_sets;
    const int support_threshold = (int)ceil(min_support * txns.size() / 100.);

    unordered_map<item_id_t, int> item_cnt;
    for (const auto &txn : txns) {
        for (const auto &item : txn) {
            item_cnt[item]++;
        }
    }
    unordered_set<item_id_t> freq_item_set;
    for (const auto &item : item_cnt) {
        if (item.second >= support_threshold) {
            freq_item_set.insert(item.first);
        }
    }

    // TODO

    return freq_item_sets;
}

vector<AssociationRule> find_association_rules(const vector<txn_t> &txns, const int min_support) {
    vector<AssociationRule> assc_rules;

    // TODO
    auto freq_item_sets = find_frequent_item_sets(txns, min_support);
    assc_rules.push_back({{1, 2, 3}, {4, 5}, .319, .1415});

    return assc_rules;
}

ofstream &operator<<(ofstream &ofs, const vector<AssociationRule> &rules) {
    for (const auto &rule : rules) {
        ofs << "{" << *rule.item_set.begin();
        for (auto it = ++rule.item_set.begin(); it != rule.item_set.end(); ++it) {
            ofs << "," << *it;
        }
        ofs << "}\t";
        ofs << "{" << *rule.associative_item_set.begin();
        for (auto it = ++rule.associative_item_set.begin(); it != rule.associative_item_set.end(); ++it) {
            ofs << "," << *it;
        }
        ofs << "}\t";
        auto ori_precision = ofs.precision();
        ofs.precision(2);
        ofs << rule.support << "\t";
        ofs << rule.confidence << "\n";
        ofs.precision(ori_precision);
    }
    return ofs;
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        cerr << "usage: apriori [0-100] input_file output_file" << endl;
        return 1;
    }

    char *tmp_ptr = argv[1];
    const int min_support = (int) strtol(argv[1], &tmp_ptr, 0);
    ifstream ifs(argv[2]);
    ofstream ofs(argv[3]);
    if (min_support < 0 || min_support > 100 || argv[1] == tmp_ptr) {
        cerr << "minimum support must be integer [0-100]. (%)";
        return EINVAL;
    } else if (!ifs.good()) {
        cerr << "cannot open input file: " << argv[2];
        return 1;
    } else if (!ofs.good()) {
        cerr << "cannot open output file: " << argv[3];
        return 1;
    }

    auto txns = read_transactions(ifs);
    auto assc_rules = find_association_rules(txns, min_support);
    ofs << assc_rules;

    ifs.close();
    ofs.close();
    return 0;
}
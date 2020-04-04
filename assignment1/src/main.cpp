#include <exception>
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <unordered_set>
#include <unordered_map>

#include "globals.h"
#include "ItemSet.h"
#include "AssociationRule.h"

using namespace std;

/**
 * Read transactions from `ifs`.
 * @param ifs Input file stream.
 * @return Vector of transaction.
 */
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

vector<ItemSet> transactions_to_itemsets(const vector<txn_t> &txns) {
    unordered_map<item_id_t, vector<size_t>> um;
    for (txn_id_t txn_id = 0; txn_id < txns.size(); txn_id++) {
        for (auto item_id : txns[txn_id]) {
            um[item_id].push_back(txn_id);
        }
    }

}

/**
 * Find frequent item sets using Apriori algorithm.
 * @param txns Vector of transaction.
 * @param min_support Minimum support value in percentage.
 * @return Vector of frequent item set.
 */
vector<ItemSet> find_frequent_item_sets(const vector<txn_t> &txns, const int min_support) {
    vector<ItemSet> freq_item_sets;

    unordered_set<item_set_t, > candidate_sets;
    for (const auto &txn : txns) {
        for (int i = 0; i < txn.size(); i++) {

            txn[i]
        }
    }
    unordered_set<item_id_t> freq_item_set;
    for (const auto &item : item_cnt) {
        if (item.second >= min_support) {
            freq_item_set.insert(item.first);
        }
    }

    // TODO

    return freq_item_sets;
}

/**
 * Find association rules.
 * @param txns Vector of transactions.
 * @param min_support Minimum support value in percentage.
 * @return Vector of association rule.
 */
vector<AssociationRule> find_association_rules(const vector<txn_t> &txns, const int min_support) {
    vector<AssociationRule> assc_rules;

    // TODO
    auto freq_item_sets = find_frequent_item_sets(txns, min_support);
    for (const auto &i : freq_item_sets) {
        for (const auto &j: freq_item_sets) {
            size_t cnt = 0;
            for (auto id = i.txn_id.cbegin(); id != i.txn_id.cend(); id++)

            i.txn_id;
            j.txn_id;
        }
    }

    return assc_rules;
}

/**
 * Overloads operator<< to write association rules on file stream.
 * @param ofs Output file stream.
 * @param rules Vector of association rule.
 * @return `ofs`.
 */
ofstream &operator<<(ofstream &ofs, const vector<AssociationRule> &rules) {
    for (const auto &rule : rules) {
        ofs << "{" << *rule.item_set.item_id.begin();
        for (auto it = ++rule.item_set.item_id.cbegin(); it != rule.item_set.item_id.cend(); it++) {
            ofs << *it;
        }
        ofs << "}\t";
        ofs << "{" << *rule.associative_item_set.item_id.begin();
        for (auto it = ++rule.associative_item_set.item_id.cbegin(); it != rule.associative_item_set.item_id.cend(); it++) {
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

    auto txns = read_transactions(ifs);
    int min_support = ceil(min_support_percent * txns.size() / 100.);
    auto assc_rules = find_association_rules(txns, min_support);
    ofs << assc_rules;

    ifs.close();
    ofs.close();
    return 0;
}
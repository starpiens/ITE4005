#include <exception>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <map>
#include <set>
#include <cmath>

using namespace std;

using item_id_t = int;
using txn_t = vector<item_id_t>;

typedef struct AssociationRule {
  set<item_id_t> item_set;
  set<item_id_t> associative_item_set;
  float support;
  float confidence;
} AssociationRule;

vector<txn_t> read_transactions(ifstream &ifs) {
    vector<txn_t> ret;
    string txn_str;
    while (getline(ifs, txn_str)) {
        istringstream iss(txn_str);
        item_id_t item;
        txn_t txn;
        while (iss >> item) {
            txn.push_back(item);
        }
        ret.push_back(txn);
    }
    return ret;
}

vector<AssociationRule> find_association_rules(const vector<txn_t>& txns, int min_support) {
    vector<AssociationRule> ret;

    // TODO
    ret.push_back({{1, 2, 3}, {4, 5}, .319, .1415});

    return ret;
}

ofstream& operator<<(ofstream &ofs, const vector<AssociationRule> &rules) {
    for (auto rule : rules) {
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

int main(int argc, const char *argv[]) {
    if (argc < 4) {
        cerr << "usage: apriori [0-100] input_file output_file" << endl;
        return 1;
    }

    const int min_support = (int) strtol(argv[1], nullptr, 0);
    ifstream ifs(argv[2]);
    ofstream ofs(argv[3]);
    if (min_support < 0 || min_support > 100) {
        cerr << "minimum support must be [0-100].";
        return 1;
    } else if (!ifs.good()) {
        cerr << "cannot open input file: " << argv[2];
        return 1;
    } else if (!ofs.good()) {
        cerr << "cannot open output file: " << argv[3];
        return 1;
    }

    auto txns = read_transactions(ifs);
    auto asc_rules = find_association_rules(txns, min_support);
    ofs << asc_rules;

    ifs.close();
    ofs.close();
    return 0;
}
#include <exception>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

using item_id_t     = int;
using txn_t = vector<item_id_t>;

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

int main(int argc, const char *argv[]) {
    if (argc < 4) {
        cerr << "usage: apriori [0-100] input_file output_file" << endl;
        return 1;
    }

    long min_support = strtol(argv[1], nullptr, 10);
    ifstream ifs(argv[2]);
    ifstream ofs(argv[3]);
    if (!ifs.good()) {
        cerr << "cannot open file: " << argv[2];
        return 1;
    } else if (!ofs.good()) {
        cerr << "cannot open file: " << argv[3];
        return 1;
    }

    auto vec_txn = read_transactions(ifs);

    for (auto i : vec_txn) {
        for (auto j : i)
            cout << j << " ";
        cout << endl;
    }

    return 0;
}
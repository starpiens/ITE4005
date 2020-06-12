import argparse


def read_records(path: str):
    f = open(path, 'r')
    records = []
    while True:
        line = f.readline()
        if not line: break
        line = line.split('\t')
        records.append({
            'user_id': int(line[0]),
            'item_id': int(line[1]),
            'rating': int(line[2]),
            'time_stamp': int(line[3])
        })
    return records


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("train_path", help="path of training data file", type=str)
    parser.add_argument("test_path", help="path of test data file", type=str)
    args = parser.parse_args()

    train_records = read_records(args.train_path)
    test_records = read_records(args.test_path)

    for i in range(5):
        print(train_records[i])
    print()
    for i in range(5):
        print(test_records[i])


if __name__ == '__main__':
    main()

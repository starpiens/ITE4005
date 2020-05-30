import argparse

class point:
    def __init__(self, id, x, y):
        self.id = int(id)
        self.x = float(x)
        self.y = float(y)

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument("data_path", help="path of input data file", type=str)
    parser.add_argument("n", help="number of clusters for the corresponding input data", type=int)
    parser.add_argument("eps", help="maximum radius of the neighborhood", type=float)
    parser.add_argument("min_pts", help="minimum number of points in an Eps-neighborhood of a given point", type=int)
    args = parser.parse_args()

    f = open(args.data_path, "r")
    point_list = []
    while True:
        str = f.readline()
        if str == '':
            break
        point_list.append(point(*str.split('\t')))
    f.close()

    print(point_list[0].id)
    print(point_list[0].x)
    print(point_list[0].y)
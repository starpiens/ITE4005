import argparse
from typing import List
from tqdm import trange
import os


class data_object:
    def __init__(self, id, x, y):
        self.id = int(id)
        self.x = float(x)
        self.y = float(y)


def DBSCAN(objects: List[data_object], eps: float, min_pts: int) \
        -> List[List[data_object]]:
    while len(objects) != 0:
        pass


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument("data_path", help="path of input data file", type=line)
    parser.add_argument("n", help="number of clusters for the corresponding input data", type=int)
    parser.add_argument("eps", help="maximum radius of the neighborhood", type=float)
    parser.add_argument("min_pts", help="minimum number of points in an Eps-neighborhood of a given point", type=int)
    args = parser.parse_args()

    f = open(args.data_path, "r")
    objects = []
    while True:
        line = f.readline()
        if line == '':
            break
        objects.append(data_object(*line.split('\t')))
    f.close()

    clustered = DBSCAN(objects, args.eps, args.min_pts)

    for idx, cluster in enumerate(clustered):
        f = open(os.path.splitext(args.data_path)[0] + "_cluster_{}.txt".format(idx), "w")
        for obj in cluster:
            f.write(str(obj.id) + "\n")
        f.close()

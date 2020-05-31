import argparse
from typing import List
from tqdm import trange
import os


class data_object:
    def __init__(self, id, x, y):
        self.id = int(id)
        self.x = float(x)
        self.y = float(y)


def DBSCAN(data_objects: List[data_object], eps: float, min_pts: int) \
        -> List[List[data_object]]:
    """
    Cluster `data_objects` using DBSCAN algorithm.
    :param data_objects: List of data objects.
    :param eps: Maximum distance of the neighborhood.
    :param min_pts: Minimum number of neighbors to be core point.
    :return: List of clusters which contains data objects.
    """
    clusters = []
    is_clustered = [False] * len(data_objects)

    for idx, obj in enumerate(data_objects):
        # If clustered already, continue.
        if is_clustered[idx]:
            continue

        neighbors = find_neighbors(data_objects, obj, eps)
        # If it is not core point, it cannot be seed point.
        if len(neighbors) <= min_pts:
            continue

        # Seed found, now form cluster.
        clusters.append(form_cluster(data_objects, obj, is_clustered, eps, min_pts))

    return clusters


def find_neighbors(data_objects: List[data_object], center: data_object, eps: float) \
        -> List[data_object]:
    """
    Find list of neighbors, include itself.
    :param data_objects: List of candidate of neighbors.
    :param center: Center object.
    :param eps: Maximum distance of the neighborhood.
    :return: List of neighbors.
    """
    neighbors = []
    for obj in data_objects:
        if (center.x - obj.x) ** 2 + (center.y - obj.y) ** 2 <= eps ** 2:
            neighbors.append(obj)
    return neighbors


def form_cluster(data_objects, seed, is_clustered, eps, min_pts) \
        -> List[data_object]:
    return []


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument("data_path", help="path of input data file", type=str)
    parser.add_argument("n", help="number of clusters for the corresponding input data", type=int)
    parser.add_argument("eps", help="maximum radius of the neighborhood", type=float)
    parser.add_argument("min_pts", help="minimum number of points in an Eps-neighborhood of a given point", type=int)
    args = parser.parse_args()

    # Read unclustered data.
    f = open(args.data_path, "r")
    objects = []
    while True:
        line = f.readline()
        if line == '':
            break
        objects.append(data_object(*line.split('\t')))
    f.close()

    # Get clustered data with DBSCAN.
    clustered = DBSCAN(objects, args.eps, args.min_pts)

    # Write clustered data.
    for idx, cluster in enumerate(clustered):
        f = open(os.path.splitext(args.data_path)[0] + "_cluster_{}.txt".format(idx), "w")
        for obj in cluster:
            f.write(str(obj.id) + "\n")
        f.close()

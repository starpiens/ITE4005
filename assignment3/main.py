import argparse
from typing import List
from tqdm import trange
import os
from multipledispatch import dispatch


class DataObject(object):
    def __init__(self, id, x, y):
        self.id = int(id)
        self.x = float(x)
        self.y = float(y)


class DBSCAN_Object(DataObject):
    @dispatch(int, float, float)
    def __init__(self, id: int, x: float, y: float):
        super().__init__(id, x, y)
        self.clustered = False

    @dispatch(DataObject)
    def __init__(self, obj: DataObject):
        super().__init__(obj.id, obj.x, obj.y)
        self.clustered = False



def DBSCAN(data_objects: List[DataObject], eps: float, min_pts: int) \
        -> List[List[DataObject]]:
    """
    Cluster `data_objects` using DBSCAN algorithm.
    :param data_objects: List of data objects.
    :param eps: Maximum distance of the neighborhood.
    :param min_pts: Minimum number of neighbors to be core point.
    :return: List of clusters which contains data objects.
    """
    clusters = []
    objects = []
    for obj in data_objects:
        objects.append(DBSCAN_Object(obj))

    for idx, obj in enumerate(objects):
        # If a object belongs to another cluster already, continue.
        if obj.clustered:
            continue

        print(idx)
        # If a cluster formed, append it.
        cluster = form_cluster(objects, obj, eps, min_pts)
        if cluster:
            clusters.append(cluster)

    return clusters


def find_neighbors(objects: List[DBSCAN_Object], center: DBSCAN_Object, eps: float) \
        -> List[DBSCAN_Object]:
    """
    Find list of neighbors, include itself.
    :param objects: List of candidate of neighbors.
    :param center: Center object.
    :param eps: Maximum distance of the neighborhood.
    :return: List of neighbors.
    """
    neighbors = []
    for obj in objects:
        if (center.x - obj.x) ** 2 + (center.y - obj.y) ** 2 <= eps ** 2:
            neighbors.append(obj)
    return neighbors


def form_cluster(objects: List[DBSCAN_Object], seed: DBSCAN_Object, eps: float, min_pts: int) \
        -> List[DBSCAN_Object]:
    neighbors = find_neighbors(objects, seed, eps)

    # It cannot be seed unless it is dense enough.
    if len(neighbors) <= min_pts:
        return []

    cluster = []

    # Prepare queue for BFS
    queue = neighbors
    for n in queue:
        n.clustered = True
    cluster += queue

    # Run BFS
    while queue:
        neighbors = find_neighbors(objects, queue.pop(0), eps)
        if len(neighbors) <= min_pts:
            continue
        for n in neighbors:
            if not n.clustered:
                n.clustered = True
                cluster.append(n)
                queue.append(n)

    return cluster


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
        objects.append(DataObject(*line.split('\t')))
    f.close()

    # Get clustered data with DBSCAN.
    clustered = DBSCAN(objects, args.eps, args.min_pts)

    # Write clustered data.
    for idx, cluster in enumerate(clustered):
        f = open(os.path.splitext(args.data_path)[0] + "_cluster_{}.txt".format(idx), "w")
        for obj in cluster:
            f.write(str(obj.id) + "\n")
        f.close()

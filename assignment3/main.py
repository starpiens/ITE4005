import argparse
from typing import List
import os
from multipledispatch import dispatch

import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from tqdm import tqdm


def main():
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
    clustered = DBSCAN(objects, args.eps, args.min_pts, args.n)

    # Write clustered data.
    t = tqdm(desc="Writing results", total=len(clustered)-1)
    for idx, cluster in enumerate(clustered):
        # Last cluster is unclustered objects.
        if idx == len(clustered) - 1:
            break
        f = open(os.path.splitext(args.data_path)[0] + "_cluster_{}.txt".format(idx), "w")
        for obj in cluster:
            f.write(str(obj.id) + "\n")
        f.close()
        t.update(1)
    t.close()

    draw_scatter(clustered)


class DataObject(object):
    def __init__(self, id, x, y):
        self.id = int(id)
        self.x = float(x)
        self.y = float(y)


class DBSCAN_Object(DataObject):

    @dispatch(int, float, float)
    def __init__(self, id: int, x: float, y: float):
        super().__init__(id, x, y)
        self._init()

    @dispatch(DataObject)
    def __init__(self, obj: DataObject):
        super().__init__(obj.id, obj.x, obj.y)
        self._init()

    def _init(self):
        self.cluster = -1
        self.is_core = False

    def get_neighbors(self, objects, eps):
        """
        Find list of neighbors, including itself.
        :param objects: List of candidate of neighbors.
        :param center: Center object.
        :param eps: Maximum distance of the neighborhood.
        :return: List of neighbors.
        """
        if hasattr(self, "neighbors") and (self.objects is objects):
            return self.neighbors
        self.objects = objects
        self.neighbors = []
        for obj in objects:
            if distance(self, obj) <= eps:
                self.neighbors.append(obj)
        return self.neighbors


def distance(i, j):
    return ((i.x - j.x) ** 2 + (i.y - j.y) ** 2) ** .5


def DBSCAN(data_objects: List[DataObject], eps: float, min_pts: int, n: int) \
        -> List[List[DBSCAN_Object]]:
    """
    Cluster `data_objects` using DBSCAN algorithm.
    :param data_objects: List of data objects.
    :param eps: Maximum distance of the neighborhood.
    :param min_pts: Minimum number of neighbors to be core point.
    :param n: Number of clusters.
    :return: List of clusters which contains data objects. Last cluster contains unclustered objects.
    """
    t = tqdm(total=len(data_objects), desc="Clustering")

    clusters = []
    objects = []
    for obj in data_objects:
        objects.append(DBSCAN_Object(obj))

    for idx, obj in enumerate(objects):
        # If a object belongs to another cluster already, continue.
        if obj.cluster != -1:
            continue

        # Try to form cluster.
        obj.cluster = len(clusters)
        new_cluster = form_cluster(objects, obj, eps, min_pts, t)
        # If a cluster formed, append it.
        if new_cluster:
            clusters.append(new_cluster)
        else:
            obj.cluster = -1

    # post-process for unclustered.
    expand_cluster(objects, clusters, eps, min_pts)

    # Append empty cluster.
    clusters.append([])
    for obj in objects:
        if obj.cluster == -1:
            clusters[-1].append(obj)
            t.update(1)

    t.close()

    # Merge some clusters.
    merge(objects, clusters, n)

    return clusters


def form_cluster(objects: List[DBSCAN_Object], seed: DBSCAN_Object,
                 eps: float, min_pts: int, t: tqdm = None) \
        -> List[DBSCAN_Object]:
    # It cannot be seed unless it is dense enough.
    if len(seed.get_neighbors(objects, eps)) <= min_pts:
        return []

    # Run BFS
    cluster = []
    queue = [seed]
    while queue:
        cluster.append(queue.pop())
        if t is not None:
            t.update(1)
        neighbors = cluster[-1].get_neighbors(objects, eps)
        if len(neighbors) <= min_pts:
            continue
        cluster[-1].is_core = True
        for n in neighbors:
            if n.cluster == -1:
                n.cluster = seed.cluster
                cluster.append(n)
                queue.append(n)

    return cluster


def expand_cluster(objects: List[DBSCAN_Object], clusters: List[List[DBSCAN_Object]], eps: float, min_pts: int):
    for obj in objects:
        if obj.cluster != -1:
            new_cluster = form_cluster(objects, obj, eps, min_pts // 2)
            if len(new_cluster) > 1:
                new_cluster.pop(0)
                clusters[obj.cluster] += new_cluster


def merge(objects: List[DBSCAN_Object], clusters: List[List[DBSCAN_Object]], n: int) \
        -> None:
    n_clst = len(clusters)
    t = tqdm(desc="Merging clusters",
             total=int((n_clst - 1 - n) * (len(objects) - 1) * len(objects) / 2))

    # While number of clusters exceeds the target number, `n`:
    while len(clusters) - 1 > n:
        # Merge via single link method between core points.
        min_single_link = (0, 0, 0)
        for i in range(len(objects) - 1):
            for j in range(i + 1, len(objects)):
                if objects[i].cluster != objects[j].cluster \
                        and objects[i].is_core and objects[j].is_core:
                    dist = distance(objects[i], objects[j])
                    if min_single_link[0] > dist or min_single_link[0] == 0:
                        min_single_link = (dist, objects[i].cluster, objects[j].cluster)
                t.update(1)
        clusters[min_single_link[1]] += clusters[min_single_link[2]]
        clusters.pop(min_single_link[2])
    t.close()


def draw_scatter(clustered: List[List[DataObject]]):
    palette = np.array(sns.color_palette("hls", len(clustered) - 1))
    palette = np.append(palette, [[.7, .7, .7]], axis=0)
    x, y, c = [], [], []
    for i, c_i in reversed(list(enumerate(clustered))):
        for obj in c_i:
            x.append(obj.x)
            y.append(obj.y)
            c.append(i)

    plt.scatter(x, y, c=palette[c], s=5)
    plt.show()


if __name__ == '__main__':
    main()
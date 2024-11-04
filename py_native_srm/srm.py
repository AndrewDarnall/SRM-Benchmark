"""
    Python Native Implementation of the
    Statistical Region Merging Algorithm
"""

from math import log
from sys import argv
from os.path import basename

from cv2 import imread, imwrite
from numpy import (
    arange as np_arange,
    float32 as np_float32,
    ones as np_ones,
    max as np_max,
    abs as np_abs,
    unique as np_unique,
)

class SRM:
    """SRM Algorithm Driver Class"""

    def __init__(self):
        """The constructor, it initializes all the required variables"""
        self.image = None
        self.parent = None
        self.shape = None
        self.q = None
        self.g = None
        self.delta = None
        self.size = None
        self.min_size = None
        self.max_regions = None

    def run(self, image, _q=32, _max_regions=15, _min_size=0.001):
        """
        run: Main method that runs the SRM Algorithm
             on the input image

        @param image: PATH to the image to segment
        @param q: Modulates the segmentation granularity
        @param max_regions: Limits the undersegmentaion
        @param min_size: Limits oversegmentation
        """

        self.shape = image.shape
        (h, w) = self.shape
        self.size = w * h
        self.image = np_float32(image.reshape(self.size, -1))
        self.parent = np_arange(self.size)
        self.rank = np_ones(self.size)
        self.q = _q
        self.g = 256
        self.max_regions = _max_regions if _max_regions > 0 else self.size
        self.min_size = _min_size * self.size
        self.delta = log(6) + 2 * log(self.size)

        edge_list = self.make_edge_pairs_list()

        for _parent_a, _parent_b in edge_list[0:]:
            parent_a = self.get_parent(_parent_a)
            parent_b = self.get_parent(_parent_b)
            if parent_a != parent_b and self.predicate(parent_a, parent_b):
                self.merge(parent_a, parent_b)

        if self.max_regions > 0:
            self.merge_occlusions()

        if self.min_size > 0:
            self.merge_smaller_regions()

        for i in range(self.size):
            color = self.image[self.get_parent(i)]
            self.image[i] = color

        return self.image.reshape(self.shape[0], self.shape[1], -1)

    def make_edge_pairs_list(self):
        """Creates a list of the 4-connected pairs"""
        (h, w) = self.shape
        pairs = []

        for i in range(0, h):
            for j in range(0, w):
                index = i * w + j
                if i != h - 1:
                    pairs.append((index, index + w))
                if j != w - 1:
                    pairs.append((index, index + 1))

        return self.sort_edge_pairs(pairs)

    def sort_edge_pairs(self, pairs):
        """Sorts the edge pairs based on the Radix of the RGB tuples"""
        img = self.image

        def diff(p):
            """Pixel comparator (the f(.,.) in the paper)"""
            (r1, r2) = p
            diff = np_max(np_abs(img[r1] - img[r2]))
            return diff

        return sorted(pairs, key=diff)

    def evaluate_predicate(self, parent_a):
        """Predicate evaluation (based on the relaxed formula in the paper)"""
        return (self.g**2 / float(2 * self.q * self.rank[parent_a])) * (
            min(self.g, self.rank[parent_a]) *
            log(self.rank[parent_a] + 1) + self.delta
        )

    def predicate(self, parent_a, parent_b):
        """The P() predicate formula from the paper"""
        predicate_a = self.evaluate_predicate(parent_a)
        predicate_b = self.evaluate_predicate(parent_b)
        comp = (self.image[parent_a] - self.image[parent_b]) ** 2
        return (comp <= (predicate_a + predicate_b)).all()

    def merge(self, parent_a, parent_b):
        """The merging procedure"""
        s1 = self.rank[parent_a]
        s2 = self.rank[parent_b]
        color = (self.image[parent_a] * s1 +
                 self.image[parent_b] * s2) / float(s1 + s2)

        if s1 < s2:
            parent_a, parent_b = parent_b, parent_a

        self.parent[parent_b] = parent_a
        self.rank[parent_a] += self.rank[parent_b]
        self.image[parent_a] = color

    def get_parent(self, parent_a):
        """Self explanatory"""
        if self.parent[parent_a] == parent_a:
            return parent_a
        p = self.get_parent(self.parent[parent_a])
        # lazy propogation
        self.parent[parent_a] = p
        return p

    def merge_occlusions(self):
        """Merges occluded portions in the image"""
        for i in range(1, self.size):
            r1 = self.get_parent(i)
            r2 = self.get_parent(i - 1)
            if (
                r1 != r2 and self.rank[r1] <= self.min_size
            ):  # +self.rank[r2] <= self.min_size:
                self.merge(r1, r2)

    def merge_smaller_regions(self):
        """Merges smaller regions to avoid under merging"""
        max_parents = self.retrieve_max_parents()
        if len(max_parents) > self.max_regions:
            allowed_parents = max_parents[: self.max_regions]
            for i in range(1, self.size):
                r1 = self.get_parent(i)
                r2 = self.get_parent(i - 1)
                if r1 != r2 and r1 not in allowed_parents:
                    self.merge(r1, r2)

    def retrieve_max_parents(self):
        """Self explenatory"""
        unique, counts = np_unique(self.parent, return_counts=True)
        parents_counts = dict(zip(unique, counts))
        return [
            k
            for k, v in sorted(
                parents_counts.items(), key=lambda item: item[1], reverse=True
            )
        ]


if __name__ == "__main__":

    FILE_NAME =     argv[1]
    Q =             int(argv[2])
    MAX_REGIONS =   int(argv[3])
    MIN_SIZE =      float(argv[4])

    if MIN_SIZE > 1:
        MIN_SIZE = 1
    elif MIN_SIZE < 0:
        MIN_SIZE = 0

    print(" ---- Running the SRM Algorithm ---- ")

    raw = imread(f"{FILE_NAME}")
    srm_algo = SRM()
    segmented = srm_algo.run(raw, Q, MAX_REGIONS, MIN_SIZE)

    base_name = basename(FILE_NAME)

    imwrite(f"Segmented_{base_name}", segmented)

    print(" <!-!> Finished running the Algorithm <!-!> ")

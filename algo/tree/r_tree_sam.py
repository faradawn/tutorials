from __future__ import annotations

from functools import cached_property
from typing import Iterable

from shapely.geometry.base import BaseGeometry


class Node:
    def __init__(self, min_degree: int, parent: InternalNode | None = None):
        self.min_degree = min_degree
        self.parent = parent
        self.bbox = BaseGeometry()

    def update_ancestors(self):
        """Update the bounding boxes of each ancestor to reflect changes to self.bbox"""
        if(self.parent == None or self.parent == self):
            return
        self.parent.bbox = self.parent.bbox.union(self.bbox).envelope
        self.parent.update_ancestors()

    @property
    def max_degree(self) -> int:
        return 2 * self.min_degree

    @property
    def is_leaf(self) -> bool:
        raise NotImplementedError

    @property
    def is_full(self) -> bool:
        raise NotImplementedError

    def split(self, payload):
        raise NotImplementedError


class LeafNode(Node):
    """A leaf node stores some geometries."""

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.geometries: list[BaseGeometry] = []

    @cached_property
    def is_leaf(self) -> bool:
        return True

    @property
    def is_full(self) -> bool:
        return len(self.geometries) >= self.max_degree

    def __repr__(self) -> str:
        return f"{self.__class__.__name__}({', '.join(str(geom) for geom in self.geometries)})"

    def add(self, payload: BaseGeometry):
        """Adds the given geometry to this leaf node."""
        if self.is_full:
            self.split(payload)
        else:
            self.geometries.append(payload)
        self.bbox = self.bbox.union(payload).envelope
        self.update_ancestors()

    def split(self, payload: BaseGeometry):
        """Splits this leaf node into two new leaf nodes."""
        p = self.parent
        l = self.geometries
        print(len(l))
        if self.parent != None and self.parent != self:
            print("appending")
            l.append(payload)
        min_dist = -1.0
        i1 = 0
        i2 = 0
        for i in range(len(l)):
            for j in range(i + 1, len(l)):
                dist = l[i].distance(l[j])
                if(min_dist < -0.5 or dist < min_dist):
                    print(i, j)
                    min_dist = dist
                    i1 = i
                    i2 = j
        print(l[i1], l[i2], i1, i2)
        l1 = [l[i1]]
        l2 = [l[i2]]
        print("BBBBBBBB")
        print(l[i1], l[i2])
        l.pop(i2)
        l.pop(i1)

        p.remove(self)
        node1 = LeafNode(min_degree = self.min_degree)
        node2 = LeafNode(min_degree = self.min_degree)
        node1.geometries = l1
        node2.geometries = l2
        node1.bbox = l1[0].envelope
        node2.bbox = l2[0].envelope
        node1.parent = p
        node2.parent = p
        while(len(l1) < self.min_degree and len(l2) < self.min_degree):
            node1_enlarged = node1.bbox.union(l[0]).envelope
            node2_enlarged = node2.bbox.union(l[0]).envelope
            diff1 = node1_enlarged.area - node1.bbox.area
            diff2 = node2_enlarged.area - node2.bbox.area
            if(diff1 < diff2 - 1e-8 or (abs(diff1 - diff2) < 1e-8 and (node1.bbox.area < node2.bbox.area - 1e-8 or (abs(node1.bbox.area - node2.bbox.area) < 1e-8 and len(l1) < len(l2))))):
                l1.append(l[0])
                node1.bbox = node1.bbox.union(l[0]).envelope
            else:
                l2.append(l[0])
                node2.bbox = node2.bbox.union(l[0]).envelope
            l.pop(0)
        while(len(l1) < self.min_degree):
            l1.append(l[0])
            node1.bbox = node1.bbox.union(l[0]).envelope
            l.pop(0)
        while(len(l2) < self.min_degree):
            l2.append(l[0])
            node2.bbox = node2.bbox.union(l[0]).envelope
            l.pop(0)
        if(len(l) > 0):
            node1_enlarged = node1.bbox.union(l[0]).envelope
            node2_enlarged = node2.bbox.union(l[0]).envelope
            diff1 = node1_enlarged.area - node1.bbox.area
            diff2 = node2_enlarged.area - node2.bbox.area
            if(diff1 < diff2 - 1e-8 or (abs(diff1 - diff2) < 1e-8 and (node1.bbox.area < node2.bbox.area - 1e-8 or (abs(node1.bbox.area - node2.bbox.area) < 1e-8 and len(l1) < len(l2))))):
                l1.append(l[0])
                node1.bbox = node1.bbox.union(l[0]).envelope
            else:
                l2.append(l[0])
                node2.bbox = node2.bbox.union(l[0]).envelope
            l.pop(0)
        print(len(node1.geometries))
        print(len(node2.geometries))
        p.add(node1)
        p.add(node2)

        #if(p.is_full):
        #    p.split(self)

        # TODO
        # Find the two geometries which are farthest apart (including the payload).
        # Create two new leaf nodes, seeded with these geometries.
        # Split the remaining geometries between these two nodes.
        # Assign each to the node requiring the minimum enlargement to accommodate it.
        # Ensure that both new nodes have at least self.min_degree geometries.
        # Remove old node from parent and add new nodes.


class InternalNode(Node):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.children: list[Node] = []

    def __repr__(self) -> str:
        return f"{self.__class__.__name__}(bbox={self.bbox}, children={len(self.children)})"

    @cached_property
    def is_leaf(self) -> bool:
        return False

    @property
    def is_full(self) -> bool:
        return len(self.children) >= self.max_degree

    def add(self, payload: Node):
        """Adds the given node to this internal node."""
        if self.is_full:
            self.split(payload)
        else:
            self.children.append(payload)
        self.bbox = self.bbox.union(payload.bbox).envelope
        self.update_ancestors()

    def remove(self, child: Node):
        self.children.remove(child)

    def split(self, payload: Node):
        """Splits this internal node into two new internal nodes."""
        p = self.parent
        l = self.children
        #l.append(payload)
        min_dist = -1.0
        i1 = 0
        i2 = 0
        for i in range(len(l)):
            for j in range(i + 1, len(l)):
                dist = l[i].bbox.distance(l[j].bbox)
                if(dist < min_dist or min_dist < -0.5):
                    min_dist = dist
                    i1 = i
                    i2 = j
        l1 = [l[i1]]
        l2 = [l[i2]]
        print("AAAAAAAA")
        print(l[i1], l[i2])
        l.pop(i2)
        l.pop(i1)

        p.remove(self)
        node1 = InternalNode(min_degree = self.min_degree)
        node2 = InternalNode(min_degree = self.min_degree)
        node1.children = l1
        node2.children = l2
        node1.parent = p
        node2.parent = p

        node1.bbox = l1[0].bbox
        node2.bbox = l2[0].bbox

        while(len(l1) < self.min_degree and len(l2) < self.min_degree):
            node1_enlarged = node1.bbox.union(l[0].bbox).envelope
            node2_enlarged = node2.bbox.union(l[0].bbox).envelope
            diff1 = node1_enlarged.area - node1.bbox.area
            diff2 = node2_enlarged.area - node2.bbox.area
            if(diff1 < diff2 - 1e-8 or (abs(diff1 - diff2) < 1e-8 and (node1.bbox.area < node2.bbox.area - 1e-8 or (abs(node1.bbox.area - node2.bbox.area) < 1e-8 and len(l1) < len(l2))))):
                l1.append(l[0])
                node1.bbox = node1.bbox.union(l[0].bbox).envelope
            else:
                l2.append(l[0])
                node2.bbox = node2.bbox.union(l[0].bbox).envelope
            l.pop(0)
        while(len(l1) < self.min_degree):
            l1.append(l[0])
            node1.bbox = node1.bbox.union(l[0].bbox).envelope
            l.pop(0)
        while(len(l2) < self.min_degree):
            l2.append(l[0])
            node2.bbox = node2.bbox.union(l[0].bbox).envelope
            l.pop(0)
        if(len(l) > 0):
            node1_enlarged = node1.bbox.union(l[0].bbox).envelope
            node2_enlarged = node2.bbox.union(l[0].bbox).envelope
            diff1 = node1_enlarged.area - node1.bbox.area
            diff2 = node2_enlarged.area - node2.bbox.area
            if(diff1 < diff2 - 1e-8 or (abs(diff1 - diff2) < 1e-8 and (node1.bbox.area < node2.bbox.area - 1e-8 or (abs(node1.bbox.area - node2.bbox.area) < 1e-8 and len(l1) < len(l2))))):
                l1.append(l[0])
                node1.bbox = node1.bbox.union(l[0].bbox).envelope
            else:
                l2.append(l[0])
                node2.bbox = node2.bbox.union(l[0].bbox).envelope
            l.pop(0)

        p.add(node1)
        p.add(node2)
        #if(p.is_full):
        #    self.split(p)
        # TODO
        # Find the two nodes which are farthest apart (including the payload).
        # Create two new internal nodes, seeded with these children.
        # Split the remaining children between these two nodes.
        # Assign each child to the node requiring the minimum enlargement to accommodate it.
        # Ensure that both new nodes have at least self.min_degree children.
        # Remove old node from parent and add new nodes.


class RTree:
    def __init__(self, min_degree: int):
        self.min_degree = min_degree
        self.root: Node = LeafNode(min_degree=min_degree)

    def insert_find_leaf(self, payload: BaseGeometry, node):
        if node.is_leaf:
            return node
        min_area_enlarge = -1.0
        min_area = -1.0
        child = None
        for c in node.children:
            bbox_unioned = c.bbox.union(payload).envelope
            area = bbox_unioned.area
            area_enlarge = area - c.bbox.area
            if min_area < -0.5 or (area_enlarge < min_area_enlarge - 1e-8 or (area_enlarge < min_area_enlarge + 1e-8 and area_enlarge > min_area_enlarge - 1e-8 and area < min_area - 1e-8)):
                min_area = area
                min_area_enlarge = area_enlarge
                child = c
        return self.insert_find_leaf(payload, child)

    def insert(self, payload: BaseGeometry):
        """Inserts the given geometry into the tree."""

        leaf = self.insert_find_leaf(payload, self.root)
        p = leaf.parent
        if(leaf != self.root):
            leaf.add(payload)
        else:
            self.root.geometries.append(payload)
            self.root.bbox = self.root.bbox.union(payload).envelope

        '''
        while(p != self.root and p != None):
            if(p.is_full):
                p.split(leaf)
                leaf = p
                p = leaf.parent
            else:
                break
        '''

        node = self.root
        if node.is_full:
            if(node.is_leaf):
                node.geometries.pop(-1)
            new_root = InternalNode(min_degree = self.min_degree)
            new_root.children.append(self.root)
            self.root.parent = new_root
            # node is being set to the node containing the ranges we want for payload insertion.
            #self.root.geometries.pop(-1)
            #self.display()
            node.split(payload)
            self.root = new_root
        # If root is full, create a new root
        # Add the old root as a child
        # Split the old root using the payload (wrapped in a new leaf node if needed)

        # Otherwise, descend until reaching a leaf
        # At each level, select the child that requires the minimum enlargement to cover the payload
        # Once you reach a leaf, add the payload geometry
    def search_helper(self, query: BaseGeometry, node):
        l = []
        if not node.is_leaf:
            for c in node.children:
                if c.bbox.intersects(query):
                    l += self.search_helper(query, c)
        else:
            for g in node.geometries:
                if(query.contains(g)):
                    l.append(g)
        return l

    def search(self, query: BaseGeometry, start_node: Node | None = None) -> Iterable[BaseGeometry]:
        """Searches the tree for geometries contained by the query geometry."""
        if start_node is None:
            start_node = self.root
        return self.search_helper(query, start_node)
        # TODO: Search recursively. Only check subtrees which intersect the query region.
        # When reaching a leaf, yield any geometry contained in the query region.

    def display(self, level=0, node: Node | None = None):
        """Prints the tree structure to the command line."""
        if node is None:
            node = self.root

        print(f"{'|   ' * level}|-- {node}")
        if not node.is_leaf:
            for child in node.children:
                self.display(level=level + 1, node=child)


if __name__ == "__main__":
    import random

    from shapely.geometry import Point, Polygon

    random.seed(6)


    points = [
        Point(0.79, 0.82),  # top right
        Point(0.49, 0.26),  # bottom left
        Point(0.01, 0.66),  # top left
        Point(0.47, 0.76),  # top left
        Point(0.37, 0.77),  # top left
        Point(0.27, 0.80),  # top left
        Point(0.73, 0.41),  # bottom right
        Point(0.54, 0.68),  # top right
        Point(0.19, 0.55),  # top left
        Point(0.80, 0.69),  # top right
        Point(0.84, 0.34),  # bottom right
    ]
    rtree = RTree(min_degree=2)
    for point in points:
        rtree.insert(point)
        rtree.display()
        print()
        print()

    polygon = Polygon([(1, 1), (1, 0.5), (0.5, 0.5), (0.5, 1)])
    results = list(rtree.search(polygon))
    assert all(polygon.contains(result) for result in results)
    #import pprint
    #pprint.pprint([str(res) for res in results])

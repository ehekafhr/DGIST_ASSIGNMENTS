from _collections import deque
import heapq
import math as m
import copy


class Edge:
    def __init__(self, start=None, final=None):
        self.s = start
        self.f = final
        self.d = 0


class Node:
    def __init__(self, distance=m.inf):
        self.distance = distance
        self.edge = []
        self.pi = None
        self.color = "w"

    def add_edge(self, e):
        self.edge.append(e)

    def adj(self):
        for i in range(len(self.edge)):
            yield self.edge[i]


class Graph:
    def __init__(self):
        self.Node = []

    def add(self, N):
        self.Node.append(N)


def relax(u, v, w):
    if v.distance > u.distance + w:
        v.distance = u.distance + w


def DIJKSTRA(G, w=None, s=None):
    """init"""
    Q = []
    for V in G.Node:
        V.pi = None
        V.distance = m.inf
        Q.append(V)
        V.color = "w"
    w.distance = 0
    for e in w.adj():
        relax(e[0], e[1], int(e[2]))
    for i in range(len(G.Node)):
        minial = m.inf
        minind = 0
        minnode = Node()
        for V in range(len(G.Node)):
            if minial >= G.Node[V].distance and G.Node[V].color == "w":
                minial = G.Node[V].distance
                minind = V
                minnode = G.Node[V]
        G.Node[minind].color = "b"
        if G.Node[minind] == s:
            return int(s.distance)

        for e in minnode.adj():
            relax(e[0], e[1], int(e[2]))
    return 0


n = int(input())
sec=list(map(int,input().split()))

G = Graph()
for i in range(n):
    N = Node()
    N.key = i
    G.add(N)

for i in range(n):
    lst = input()
    lst = lst.split(' ')
    for v in lst:
        v = int(v)
    for j in range(n):
        if lst[j] != '0' and lst[j] != '-1':
            G.Node[i].add_edge([G.Node[i], G.Node[j], lst[j]])
        else:
            G.Node[i].add_edge([G.Node[i], G.Node[j], 20000001])


def cal(G, sec):
    P = copy.deepcopy(G)
    dis = 0
    for i in range(len(sec) - 1):
        dij = DIJKSTRA(P, P.Node[sec[i]], P.Node[sec[i + 1]])
        if dij > 2000000:
            return "impossible"
        dis += dij
    endd = DIJKSTRA(G, G.Node[sec[-1]], G.Node[sec[0]])
    if endd > 2000000:
        return "impossible"
    dis += endd
    if dis < 0:
        return "impossible"
    return dis


print(cal(G, sec))

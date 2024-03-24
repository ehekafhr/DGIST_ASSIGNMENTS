from _collections import deque
import copy


class Edge:
    def __init__(self, start=None, final=None, distance=None):
        self.s = start
        self.f = final
        self.d = distance


class Node:
    def __init__(self, distance=1000000000):
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
    try:
        if v.distance > u.distance + w:
            v.distance = u.distance + w
    except:
        pass

def DIJKSTRA(G, w=None, s=None):
    Start=G.Node[w]
    End=G.Node[s]
    Q = []
    for V in G.Node:
        V.pi = None
        V.distance = 10000000000
        Q.append(V)
        V.color = "w"
    Start.distance = 0
    for e in Start.adj():
        relax(Start, e.f, int(e.d))
    Start.color="b"
    for i in range(len(G.Node)):
        minial = 1000000000
        minind = 0
        minnode = Node()
        for V in range(len(G.Node)):
            if minial >= G.Node[V].distance and G.Node[V].color == "w":
                minial = G.Node[V].distance
                minind = V
                minnode = G.Node[V]
        G.Node[minind].color = "b"
        if G.Node[minind] == End:
            try:
                return int(s.distance)
            except:
                return int(G.Node[s].distance)
        for e in minnode.adj():
            try:
                relax(minnode, G.Node[e.f], int(e.d))
            except:
                relax(minnode, e.f, int(e.d))
    return 0

"""input받기"""
n, m, f, s, t = map(int, input().split())
G = Graph()
for i in range(n):
    N = Node()
    N.key = i
    G.add(N)
for i in range(m):
    start, end, distance = map(int, input().split())
    S = G.Node[start]
    e = G.Node[end]
    E = Edge(s, e, distance)
    F = Edge(e, s, distance)
    G.Node[start].add_edge(E)
    G.Node[end].add_edge(F)
flight=[]
for i in range(f):
    start, end = map(int, input().split())
    flight.append([start , end])
"""실행"""

min=DIJKSTRA(G,s,t)
for i in range(f):
    distance = DIJKSTRA(G,s,flight[i][0])+DIJKSTRA(G,t,flight[i][1])
    if distance<min:
        min=distance
print(min)
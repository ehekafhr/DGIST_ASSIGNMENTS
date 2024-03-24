from _collections import deque
import heapq
import math as m
from _collections import deque

n, m = map(int, input().split())
edge = []
u=list(map(int,input().split()))
for i in range(len(u) // 2):
    edg=[int(u[2 * i]), int(u[2 * i + 1])]
    edge.append(edg)
ver = []
rever = []
for i in range(n):
    ver.append([])
    rever.append([])
for i in range(m):
    ver[edge[i][0] - 1].append(edge[i][1])
for i in range(m):
    rever[edge[i][1] - 1].append(edge[i][0])
start_time = [None] * n
end_time = [None] * n
cur_time = 0
vcolor = ['w'] * n


def DFS(ver):
    for i in range(n):
        if vcolor[i] == 'w':
            DFS_VISIT(ver, i)


def DFS_VISIT(ver, s):
    global cur_time
    cur_time += 1
    start_time[s] = cur_time
    vcolor[s] = 'g'
    for v in ver[s]:
        if vcolor[v - 1] == 'w':
            DFS_VISIT(ver, v - 1)
    vcolor[s] = 'b'
    cur_time += 1
    end_time[s] = cur_time


def rev_visit(ver,s,lst):
    lst.append(s+1)
    vcolor[s]='g'
    for v in ver[s]:
        if vcolor[v - 1] == 'w':
            rev_visit(ver, v - 1,lst)
    vcolor[s] = 'b'


def DFS_count(ver):
    for v in returnval:
        v=int(v)-1
        global lst
        lst=[]
        if vcolor[v]=='w':
            rev_visit(ver,v,lst)
        if lst!=[]:
            dfs.append(lst)


def RevDFS(ver):
    for i in range(n):
        if vcolor[i] == 'w':
            DFS_VISIT(ver, i)


DFS(ver)
returnval = []
for i in range(n):
    max = 0
    max_index = 0
    for j in range(n):
        if max < end_time[j]:
            max = end_time[j]
            max_index = j
    end_time[max_index] = -1
    returnval.append(max_index + 1)
dfs=[]
vcolor = ['w'] * n
DFS_count(rever)
print(len(dfs))
for i in dfs:
    print(len(i),end=" ")
    for j in range(len(i)):
        print(i[j],end=" ")
    print()

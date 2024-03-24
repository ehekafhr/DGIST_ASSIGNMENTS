import sys
import heapq
import math as m
sys.setrecursionlimit(10000)
n, m = map(int, input().split())
edge = []
for i in range(m):
    s, e = map(int, input().split())
    edge.append([s, e])
ver = []
for i in range(n):
    ver.append([])
for i in range(m):
    ver[edge[i][0] - 1].append(edge[i][1])
start_time=[None]*n
end_time=[None]*n
cur_time=0
vcolor = ['w'] * n
def DFS(ver):

    for i in range(n):
        if vcolor[i] == 'w':
            DFS_VISIT(ver, i)

def DFS_VISIT(ver, s):
    global cur_time
    cur_time+=1
    start_time[s]=cur_time
    vcolor[s]='g'
    for v in ver[s]:
        if vcolor[v-1] == 'w':
            DFS_VISIT(ver,v-1)
    vcolor[s]='b'
    cur_time+=1
    end_time[s]=cur_time
DFS(ver)
returnval=[]
for i in range(n):
    max=0
    max_index=0
    for j in range(n):
        if max<end_time[j]:
            max=end_time[j]
            max_index=j
    end_time[max_index]=-1
    returnval.append(max_index+1)
for i in returnval:
    print(i,end=" ")


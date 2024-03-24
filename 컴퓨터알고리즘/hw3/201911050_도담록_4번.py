def counter(sx, sy, fx, fy, n):
    if sy>n/2:
        sy=n-1-sy
        fy=n-1-fy
    if sx>n/2:
        sx=n-1-sx
        fx=n-1-fx
    dx = abs(sx - fx)
    dy = abs(sy - fy)
    if dx < dy: #전체 문제의 1/8로 축소(1사분면의 x=y 밑만 남김)
        dx, dy = dy, dx
        fx, fy = fy, fx
        sx, sy = sy, sx
    if n == 2:
        if sx == fx and sy == fy:
            return 0
        return -1
    if n == 3: #n=3짜리 edge case
        if (sx == 1 and sy == 1) or (fx == 1 and fy == 1):
            if sx == fx and sy == fy:
                return 0
            return -1
    if dx < 3 and dy < 3:
        if dx + dy == 1:
            return 3
        if dx + dy == 2:
            if (sx == sy == 0 and fx == fy) or (fx == fy == 0 and sx == sy):
                return 4
            else:
                return 2
        if dx + dy == 3:
            return 1
        if dx + dy == 4:
            return 4
        pass
    if dx == 3 and dy == 0:
        if (sx == sy == 0 or fx == fy == 0) and n<5:
            return 5
        return 3
    if dx >= 2 * dy:
        if dy==1 and dx==5:
            return 4

        if (dx - 2 * dy) % 4 == 0:
            return dx / 2
        elif (dx - 2 * dy) % 2 == 0:
            return dx / 2 + 1
        if dx % 4 == 3 and dy%2==0:
            return dx // 2 + 2
        if dx % 4 == 1 and dy%2==1:
            return dx//2+2
        else:
            return dx//2+1
    if dx < 2 * dy:
        if (dx + dy) % 3 == 0:
            return (dx + dy) / 3
        else:
            return (2 * dx - dy) // 3 + (2 * dy - dx) // 3 + 2

j=int(input())
sX, sY = map(int, input().split())
fX, fY = map(int, input().split())
print(int(counter(sX,sY,fX,fY,j)))
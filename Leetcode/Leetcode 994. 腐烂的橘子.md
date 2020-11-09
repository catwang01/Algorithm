[toc]

# Leetcode 994. 腐烂的橘子

## 问题描述

[994. 腐烂的橘子](https://leetcode-cn.com/problems/rotting-oranges/)

## 算法

### 解法1

##### 解法1：实现：多源bfs

```
from collections import deque

class Solution:
    def orangesRotting(self, grid: List[List[int]]) -> int:
        EMPTY, FRESH, ROT, SEEN = 0, 1, 2, 3
        if len(grid)==0 or len(grid[0])==0: 
            return 0

        nrow, ncol = len(grid), len(grid[0])
        q = deque()

        nfresh = 0 # 计算新鲜橘子的数量，用以判断是否所有新鲜橘子都被传染
        for i in range(nrow):
            for j in range(ncol):
                if grid[i][j] == FRESH: 
                    nfresh+=1
                elif grid[i][j] == ROT: # 腐烂橘子是传染源，入队列
                    q.append((i, j))

        if nfresh == 0: return 0 # 一开始就没有新鲜橘子

        minutes = -1
        directions = [[0, 1], [0, -1], [1, 0], [-1, 0]]
        while len(q):
            minutes += 1
            levelsize = len(q)
            for _ in range(levelsize):
                i, j = q.popleft()
                if grid[i][j] == SEEN:
                    nfresh -= 1
                    if nfresh == 0:
                        return minutes
                for dx, dy in directions:
                    x, y = i + dx, j + dy
                    if 0<= x < nrow and 0<= y < ncol and grid[x][y] == FRESH:
                        q.append((x,y))
                        grid[x][y] = SEEN
        return -1
```
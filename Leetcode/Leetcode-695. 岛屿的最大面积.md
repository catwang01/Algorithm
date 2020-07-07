
[toc]

# Leetcode 695. 岛屿的最大面积

## 问题描述

[695. 岛屿的最大面积 - 力扣（LeetCode）](https://leetcode-cn.com/problems/max-area-of-island/)

## 算法

### 解法1: bfs

#### 解法1:

##### 解法1: python

```
from collections import deque
class Solution:
    def __init__(self):
        self.directions = [[0, -1], [-1, 0], [0, 1], [1, 0]]
        
    def maxAreaOfIsland(self, grid: List[List[int]]) -> int:
        nrow = len(grid)
        if nrow ==  0: return 0
        ncol = len(grid[0])
        ret = 0
        for i in range(nrow):
            for j in range(ncol):
                if grid[i][j]:
                    ret = max(ret, self.bfs(i, j, nrow, ncol, grid))
        return ret
    
    def bfs(self, i, j, nrow, ncol, grid):
        # 入队列前变色
        grid[i][j] = 0
        q = deque([(i,j)])
        ret = 0
        while q:
            x, y = q.popleft()
            ret += 1
            for dx, dy in self.directions:
                new_x = x + dx
                new_y = y + dy
                if 0 <= new_x < nrow and 0 <= new_y < ncol and grid[new_x][new_y]:
                    # 入队列前变色
                    grid[new_x][new_y] = 0
                    q.append((new_x, new_y))
        return ret
```


### 解法2：dfs

#### 解法2：实现

##### 解法2: python 非递归

只是将 bfs 中的 queue 变成 stack

```py
from collections import deque
class Solution:
    def __init__(self):
        self.directions = [[0, -1], [-1, 0], [0, 1], [1, 0]]
        
    def maxAreaOfIsland(self, grid: List[List[int]]) -> int:
        nrow = len(grid)
        if nrow ==  0: return 0
        ncol = len(grid[0])
        ret = 0
        for i in range(nrow):
            for j in range(ncol):
                if grid[i][j]:
                    ret = max(ret, self.bfs(i, j, nrow, ncol, grid))
        return ret
    
    def bfs(self, i, j, nrow, ncol, grid):
        # 入栈前变色
        grid[i][j] = 0
        stack = [(i, j)]
        ret = 0
        while stack:
            x, y = stack.pop()
            ret += 1
            for dx, dy in self.directions:
                new_x = x + dx
                new_y = y + dy
                if 0 <= new_x < nrow and 0 <= new_y < ncol and grid[new_x][new_y]:
                    # 入栈前变色
                    grid[new_x][new_y] = 0
                    stack.append((new_x, new_y))
        return ret
```
##### 解法2: c++ 递归

```cpp
 int directions[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int nrow = grid.size();
        if (nrow == 0 ) return 0;
        int ncol = grid[0].size();

        int ret = 0;
        for (int i=0; i<nrow; i++) 
        {
            for (int j=0; j<ncol; j++) 
            {
                if (grid[i][j]) 
                {
                    ret = max(ret, dfs(i, j, grid));
                }
            }
        }
        return ret;
    }
    
    int dfs(int i, int j, vector<vector<int>>& grid) {
        int nrow = grid.size(), ncol = grid[0].size();
        grid[i][j] = 0;
        int ret = 1;
        for (auto& direc: directions) 
        {
            int x = i + direc[0], y = j + direc[1];
            if (x >=0 && x < nrow && y >= 0 && y < ncol && grid[x][y])
                ret += dfs(x, y, grid);
        }
        return ret;
    }
};
```

##### 解法2：python

```
class Solution:
    def __init__(self):
        self.directions = [[0, -1], [-1, 0], [0, 1], [1, 0]]
        
    def maxAreaOfIsland(self, grid: List[List[int]]) -> int:
        nrow = len(grid)
        if nrow ==  0: return 0
        ncol = len(grid[0])
        ret = 0
        for i in range(nrow):
            for j in range(ncol):
                if grid[i][j]:
                    ret = max(ret, self.dfs(i,j, nrow, ncol, grid))
        return ret
    
    def dfs(self, i, j, nrow, ncol, grid):
        grid[i][j] = 0
        ret = 1
        for dx, dy in self.directions:
            x = dx + i
            y = dy + j
            if 0 <= x < nrow and 0 <= y < ncol and grid[x][y]:
                ret += self.dfs(x, y, nrow, ncol, grid)
        return ret
```

### 解法3： 并查集

1. 每个网格点都对应图上的一个结点。为了给每个网格点给定一个唯一的 id，可以使用 i * nrow + ncol 来表示 grid[i][j]

2. 虽然一共有四个方向，在 union 的时候只需要检查下方和右方就可以了，这样可以减少一些重复判断。

#### 解法3：实现

##### 解法3: python

```
class UF:
    def __init__(self, n):
        self.size = n
        self.parent = list(range(n))
        self.weight = [1] * self.size
        self.max_weight = 1
        
    def find(self, x):
        if x == self.parent[x]:
            return x
        else:
            root = self.find(self.parent[x])
            self.parent[x] = root 
            return root
    
    def union(self, i, j):
        parenti = self.find(i)
        parentj = self.find(j)
        if parenti==parentj: 
            return
        else:
            if self.weight[parenti] <= self.weight[parentj]:
                self.parent[parenti] = parentj
                self.weight[parentj] += self.weight[parenti]
                self.max_weight = max(self.max_weight, self.weight[parentj])
            else:
                self.parent[parentj] = parenti
                self.weight[parenti] += self.weight[parentj]
                self.max_weight = max(self.max_weight, self.weight[parenti])
            self.size -= 1
    

class Solution:
    def maxAreaOfIsland(self, grid: List[List[int]]) -> int:
        n = len(grid)
        if n == 0: return 0
        m = len(grid[0])
        uf = UF(n * m)
        allzero = True
        for i in range(n):
            for j in range(m):
                if grid[i][j]:
                    allzero = False
                    if i+1 < n and grid[i+1][j]:
                        uf.union(i * m + j, (i+1) * m + j)
                    if j+1 < m and grid[i][j+1]:
                        uf.union(i * m + j, i * m + (j+1))
        return 0 if allzero else uf.max_weight
```



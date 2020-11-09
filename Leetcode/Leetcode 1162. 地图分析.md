[toc]

# Leetcode 1162. 地图分析

## 问题描述

[1162. 地图分析 - 力扣（LeetCode）](https://leetcode-cn.com/problems/as-far-from-land-as-possible/)

## 算法

### 解法1:bruteforce

时间复杂度： $O(n^2)$ 每一个海洋都和每一个陆地计算了距离

#### 解法1:实现

##### 解法1: python 超时

```
class Solution:

    def maxDistance(self, grid: List[List[int]]) -> int:
        nrow, ncol = len(grid), len(grid[0])
        oceans = {(i,j) for i in range(nrow) for j in range(ncol) if grid[i][j]==0}
        lands = {(i,j) for i in range(nrow) for j in range(ncol) if grid[i][j]==1}
        maxDis = 0
        if not oceans or not lands:
            return -1
        for ocean in oceans:
            curDis = min(self.distance(ocean, land) for land in lands)
            maxDis = max(maxDis, curDis)
        return maxDis

    def distance(self, ocean, land):
        return abs(ocean[0] - land[0]) + abs(ocean[1] - land[1])
```

### 解法2:bfs

要求 `这个海洋区域到离它最近的陆地区域的距离是最大的。` 也就是说，计算所有的`海洋到陆地的距离`，再在这些距离中求最大。

而`海洋到陆地的距离`是海洋到其`最近的陆地的距离`，这个距离可以用 bfs 来求解。

因此，问题可以转换为以所有的海洋为起点，分别做bfs，并更新最大距离即可。

#### 复杂度分析

- 时间复杂度： 最多做 $O(n^2)$ 次 BFS，每个 BFS 用时 $O(n^2)$，因此总用时 $O(n^4)$

- 空间复杂度：使用了一个 `seen` 数组，因此空间复杂度为 $O(n^2)$

#### 解法2:实现

##### 解法2:c++ 超时

代码参考 [1]

```
class Solution {
public:
    pair<int, int> directions[4] = {
        {1, 0},{-1, 0},
        {0, 1},{0, -1} 
    };

    int ret = 0;
    bool seen[100][100];
    int nrow, ncol;
    int maxDistance(vector<vector<int>>& grid) {
        nrow = grid.size(), ncol = grid[0].size();
        for (int i=0; i<nrow; i++) {
            for (int j=0; j<ncol; j++) {
                if (grid[i][j] == 0) {
                    bfs(i, j, grid);
                }
            }
        }
        return ret==0 ? -1 : ret;
    }

    void bfs(int i, int j, vector<vector<int>>& grid) {
        
        memset(seen, true, sizeof seen);
        seen[i][j] = false;
        queue<pair<int, int>> q;
        q.push(make_pair(i, j));
        int dis = -1;
        while (!q.empty()) {
            int size = q.size();
            dis++;
            while (size--) {
                int i = q.front().first, j = q.front().second;
                q.pop();
                if (grid[i][j]==1) {
                    ret = max(ret, dis);
                    return;
                }
                for (auto [di, dj]: directions) {
                    int newi = i + di, newj = j + dj;
                    if (newi < 0 || newi >= nrow || newj < 0|| newj >= ncol) continue; 
                    if (seen[i+di][j+dj]) {
                        q.push(make_pair(i+di, j+dj));
                        seen[i+di][j+dj] = false;
                    }
                }
            }
        }
    }

};
```

### 解法3: 多源 bfs

可以通过添加一个超级源节点，连接所有的岛屿，然后从岛屿进行 bfs。

但是我们不是为了求最短距离，而是为了求最大距离，因此可以考虑使用层次遍历，最后一层就是最大距离。

关于多源bfs 的解释，可以参考 [ 2 ]，讲得十分清楚


```
from collections import deque
class Solution:
    def maxDistance(self, grid: List[List[int]]) -> int:
        OCCEAN, ISLAND, SEEN = 0, 1, -1
        n = len(grid)
        if n == 0: return -1
        q = deque()
        for i in range(n):
            for j in range(n):
                if grid[i][j] == ISLAND:
                    q.append((i, j))
        if len(q) == n * n or len(q) == 0:  # 避免都是岛屿或者都是海洋的情况
            return -1 
        directions = [[0, 1], [0, -1], [1, 0], [-1, 0]]
        level = -1 # level 表示当前是多少层。也表示陆地到海洋到距离
        while len(q):
            level += 1
            levelsize = len(q)
            for _ in range(levelsize):
                i, j = q.popleft()
                for dx, dy in directions:
                    x = i + dx
                    y = j + dy
                    if 0<= x < n and 0 <= y < n and grid[x][y] == OCCEAN:
                        q.append((x, y))
                        grid[x][y] = SEEN
        return level
```

# References

1. [地图分析 - 地图分析 - 力扣（LeetCode）](https://leetcode-cn.com/problems/as-far-from-land-as-possible/solution/di-tu-fen-xi-by-leetcode-solution/)
2. [吃鲸🐳！广搜还能多源？看完秒懂! - 地图分析 - 力扣（LeetCode）](https://leetcode-cn.com/problems/as-far-from-land-as-possible/solution/zhen-liang-yan-sou-huan-neng-duo-yuan-kan-wan-miao/)
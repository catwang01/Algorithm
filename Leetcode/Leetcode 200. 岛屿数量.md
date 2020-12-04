[toc]

# Leetcode 200. 岛屿数量

## 问题描述

[200. 岛屿数量 - 力扣（LeetCode）](https://leetcode-cn.com/problems/number-of-islands/)

## 算法

### 解法1:bfs

遍历过的格子，在原数组上修改为 '0'。

#### 解法1:实现

##### 解法1:c++

```
class Solution {
public:
    int directions[4][2] = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};
    int numIslands(vector<vector<char>>& grid) {
        if (grid.size()==0 || grid[0].size()==0) return 0;
        int nrow = grid.size(), ncol = grid[0].size();
        int ret = 0;
        for (int i=0; i<nrow; i++) {
            for (int j=0; j<ncol; j++) {
                if (grid[i][j]=='1') {
                    bfs(i, j, grid);
                    ret += 1;
                }
            }
        }
        return ret;
    }

    void bfs(int i, int j, vector<vector<char>>& grid) {
        int nrow = grid.size(), ncol = grid[0].size();
        deque<pair<int, int>> q;
        q.push_back({i, j});
        grid[i][j] = '0';

        pair<int, int> cur;
        int x, y, nx, ny;
        while(!q.empty()) {
            auto cur = q.front(); q.pop_front();
            x = cur.first, y = cur.second;
            for (int i=0; i<4; i++) {
                nx = x + directions[i][0];
                ny = y + directions[i][1];
                if (nx<0 || ny<0 || nx>=nrow || ny>=ncol || grid[nx][ny]=='0') continue;
                q.push_back({nx, ny});
                grid[nx][ny] = '0';
            }
        }
    }
};
```


### 解法1.2: dfs

将上面的bfs的队列修改为栈。

#### 解法2: 实现1: 非递归

##### 解法2: 实现1: c++

```
class Solution {
public:
    int directions[4][2] = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};
    int numIslands(vector<vector<char>>& grid) {
        if (grid.size()==0 || grid[0].size()==0) return 0;
        int nrow = grid.size(), ncol = grid[0].size();
        int ret = 0;
        for (int i=0; i<nrow; i++) {
            for (int j=0; j<ncol; j++) {
                if (grid[i][j]=='1') {
                    dfs(i, j, grid);
                    ret += 1;
                }
            }
        }
        return ret;
    }

    void dfs(int i, int j, vector<vector<char>>& grid) {
        int nrow = grid.size(), ncol = grid[0].size();
        stack<pair<int, int>> s;
        s.push({i, j});
        grid[i][j] = '0';

        pair<int, int> cur;
        int x, y, nx, ny;
        while(!s.empty()) {
            auto cur = s.top(); s.pop();
            x = cur.first, y = cur.second;
            for (int i=0; i<4; i++) {
                nx = x + directions[i][0];
                ny = y + directions[i][1];
                if (nx<0 || ny<0 || nx>=nrow || ny>=ncol || grid[nx][ny]=='0') continue;
                s.push({nx, ny});
                grid[nx][ny] = '0';
            }
        }
    }
};
```

##### 解法2: 实现1: python

```
DIRECETIONS = [[0, 1], [0, -1], [1, 0], [-1, 0]]
ISLAND, OCEAN, SEEN = '1', '0', '2'

class Solution:
    def numIslands(self, grid: List[List[str]]) -> int:
        if (len(grid)==0 or len(grid[0])==0):
            return 0
        nrow, ncol = len(grid), len(grid[0])
        ret = 0
        for i in range(nrow):
            for j in range(ncol):
                if grid[i][j] == ISLAND:
                    self.dfs(i, j, grid)
                    ret += 1
        return ret

    def dfs(self, i, j, grid):
        st = []
        st.append((i, j))
        grid[i][j] = SEEN
        while st:
            i, j = st.pop()
            for dx, dy in DIRECETIONS:
                x, y = i + dx, j + dy
                if 0 <= x < len(grid) and 0 <= y < len(grid[0]) and grid[x][y] == ISLAND:
                    st.append((x, y))
                    grid[x][y] = SEEN
```


#### 解法2: 实现2: 递归

##### 解法2: 实现2: python

```
DIRECETIONS = [[0, 1], [0, -1], [1, 0], [-1, 0]]
ISLAND, OCEAN, SEEN = '1', '0', '2'

class Solution:
    def numIslands(self, grid: List[List[str]]) -> int:
        if (len(grid)==0 or len(grid[0])==0):
            return 0
        nrow, ncol = len(grid), len(grid[0])
        ret = 0
        for i in range(nrow):
            for j in range(ncol):
                if grid[i][j] == ISLAND:
                    self.dfs(i, j, grid)
                    ret += 1
        return ret

    def dfs(self, i, j, grid):
        grid[i][j] = SEEN
        for dx, dy in DIRECETIONS:
            x, y = i + dx, j + dy
            if 0 <= x < len(grid) and 0 <= y < len(grid[0]) and grid[x][y] == ISLAND:
                grid[x][y] = SEEN
                self.dfs(x, y, grid)
```

### 解法2：并查集

#### 解法2:实现

##### 解法2:c++

```
class UFS {
    public:
    vector<int> parent;
    vector<int> weight;
    int size;
    UFS(int n=0) {
        parent.resize(n);
        weight.resize(n);
        size=0;
    }

    void add(int x) {
        parent[x] = x;
        weight[x] = 1;
        size++;
    }

    int find(int p) {
        if (parent[p]==p) return p;
        return parent[p] = find(parent[p]);
    }

    void connect(int p, int q) {
        int parentp = find(p);
        int parentq = find(q);
        if (parentp==parentq) return;
        if (weight[parentp] < weight[parentq]) {
            parent[parentp] = parentq;
            weight[parentq] += weight[parentp];
        } else {
            parent[parentq] = parentp;
            weight[parentp] += weight[parentq];
        }
        size--;
    }
};

inline int Index(int i, int j, int ncol) {
    return i * ncol + j;
}
class Solution {
public:
    bool check(int i, int j, const vector<vector<char>>& grid) {
        int nrow = grid.size(), ncol = grid[0].size();
        if (i<0 || i>=nrow || j< 0 || j>ncol) return false;
        return grid[i][j]=='1';
    }

    int numIslands(vector<vector<char>>& grid) {
        if (grid.size() ==0 || grid[0].size()==0) return 0;
        int nrow = grid.size(), ncol = grid[0].size();
        UFS ufs(nrow * ncol);
        for (int i=0; i<nrow; i++) {
            for (int j=0; j<ncol; j++) {
                if (grid[i][j]=='1') {
                    ufs.add(Index(i, j, ncol));
                    if (check(i, j-1, grid)) 
                        ufs.connect(Index(i, j, ncol), Index(i, j-1, ncol));
                    if (check(i-1, j, grid)) 
                        ufs.connect(Index(i, j, ncol), Index(i-1, j, ncol));
                }
            }
        } 
        return ufs.size;
    }
};
```

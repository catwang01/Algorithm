[toc]

# Leetcode 1254. 统计封闭岛屿的数目

## 问题描述

[1254. 统计封闭岛屿的数目 - 力扣（LeetCode）](https://leetcode-cn.com/problems/number-of-closed-islands/)


## 解法

### 解法1: bfs

实际上和 [200. 岛屿数量 - 力扣（LeetCode）](https://leetcode-cn.com/problems/number-of-islands/) 相同。只不过这次处于边界位置的岛屿不会被计算在内，所以需要有一个状态变量来记录岛屿是否处于边界位置。只要在 bfs 的过程中有一个岛屿处于边界位置，那么就修改这个状态变量。

##### 解法1: c++

```
class Solution {
public:
    int closedIsland(vector<vector<int>>& grid) {
        if (grid.size()==0 || grid[0].size()==0) return 0;
        int nrow = grid.size(), ncol = grid[0].size();
        int ret = 0;
        int is_closed;
        for (int i=0; i<nrow; i++)
        {
            for (int j=0; j<ncol; j++)
            {
                if (grid[i][j] == 0)
                {
                    is_closed = 1;
                    // cout <<　"ｉ: " << i << " j: " << j << endl;
                    bfs(i, j, grid, is_closed);
                    ret += is_closed;
                }
            }
        }
        return ret;
    }

    int directions[4][2] = {0, 1, 0, -1, 1, 0, -1, 0};

    void bfs(int i, int j, vector<vector<int>>& grid, int& is_closed)
    {
        queue<pair<int, int>> q;
        q.push({i, j});
        grid[i][j] = 1;
        int x, y, next_x, next_y;
        while (q.size())
        {
            x = q.front().first;
            y = q.front().second;
            q.pop();
            for (auto p: directions)
            {
                next_x =  x + p[0];  next_y = y + p[1];

                if (next_x >= 0 && next_x < grid.size() && next_y >= 0 && next_y < grid[0].size())
                {
                    if (grid[next_x][next_y] == 0)
                    {
                        // cout << "next_x: " << next_x << " next_y: " << next_y << endl;
                        q.push({next_x, next_y});
                        grid[next_x][next_y] = 1;
                    }                    
                } // boarder
                else
                {
                    is_closed = 0;
                }
            }
        }
    }
};  
```

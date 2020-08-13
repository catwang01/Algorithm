
[toc]

# Leetcode 130 被围绕的区域

## 问题描述

[130. 被围绕的区域 - 力扣（LeetCode）](https://leetcode-cn.com/problems/surrounded-regions/)

## 算法

### 解法1: dfs

从四个边界点中的 "O" 开始遍历，

#### 解法1:实现

##### 解法1：c++

```
class Solution {
public:
    int directions[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};
    void solve(vector<vector<char>>& board) {
        if (board.empty() || board[0].empty()) return ;
        int nrow = board.size(), ncol = board[0].size();
        vector<vector<int>> seen(nrow, vector<int>(ncol, 0));

        for (int i: {0, nrow-1})
        {
            for (int j=0; j<ncol; j++)
            {
                if (board[i][j]=='O' && seen[i][j]==0)
                {
                    dfs(i, j, board, seen);
                }
            }
        }

        for (int j: {0, ncol-1})
        {
            for (int i=0; i<nrow; i++)
            {
               if (board[i][j]=='O' && seen[i][j]==0)
                {
                    dfs(i, j, board, seen);
                } 
            }
        }

        for (int i=0; i<nrow; i++)
        {
            for (int j=0; j<ncol; j++)
            {
                if (board[i][j]=='O' && seen[i][j]==0)
                {
                    board[i][j] = 'X';
                }
            }
        }
    }

    void dfs(int i, int j, const vector<vector<char>>& board, vector<vector<int>>& seen)
    {
        int nrow = board.size(), ncol = board[0].size();
        seen[i][j] = 1;
        for(auto [dx,dy]: directions)
        {
            int x = i + dx, y = j + dy;
            if (x >= 0 && x < nrow && y >= 0 && y < ncol && seen[x][y]==0 && board[x][y] == 'O')
            {
                dfs(x, y, board, seen);
            }
        }
    }
};
```
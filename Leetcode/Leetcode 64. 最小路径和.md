
[toc]

# Leetcode 64. 最小路径和

## 问题描述

[64. 最小路径和 - 力扣（LeetCode）](https://leetcode-cn.com/problems/minimum-path-sum/submissions/)

## 算法

### 解法一：dp


定义 $dp[i][j]$ 表示从 $(0,0)$ 处开始到 $(i, j)$ 处的最小路径。则有最优子结构如下：

$$dp[i][j] = \begin{cases} 
min(dp[i-1][j], dp[i][j-1]) + grid[i][j]  \quad & 1 \leq i \leq m, 1 \leq j \leq n \\

dp[i][j-1] + grid[i][j] \quad &  i=0, 1 \leq j \leq n \\
dp[i-1][j] + grid[i][j] \quad & 1 \leq i \leq m, j=0 \\
grid[0][0] \quad & i=j=0

\end{cases}$$


#### 解法1：实现：c++

```
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size(); 
        int dp[m][n] = {grid[0][0]};
        // 初始化第一列
        for (int i=1; i<m; i++) {
            dp[i][0] = dp[i-1][0] + grid[i][0];
        }
        //初始化第一行
        for (int j=1; j<n; j++) {
            dp[0][j] = dp[0][j-1] + grid[0][j];
        }
        for (int i=1; i<m; i++) {
            for (int j=1; j<n; j++) {
                    dp[i][j] = min(dp[i][j-1], dp[i-1][j]) + grid[i][j];
                }
            }
        return dp[m-1][n-1];
    }
};
```

#### 解法1：python：实现

```
class Solution:
    def minPathSum(self, grid: List[List[int]]) -> int:
        # dp[i][j] 表示到 i,j 到最小路径
        if len(grid)==0 or len(grid[0]) == 0: return 0
        nrow, ncol = len(grid), len(grid[0])
        dp = [[0] * ncol for _ in range(nrow)]
        dp[0][0] = grid[0][0]
        for row in range(1, nrow):
            dp[row][0] = dp[row-1][0] + grid[row][0]
        for col in range(1, ncol):
            dp[0][col] = dp[0][col-1] + grid[0][col]
        
        for row in range(1, nrow):
            for col in range(1, ncol):
                dp[row][col] = min(dp[row-1][col], dp[row][col-1]) + grid[row][col]
        return dp[nrow-1][ncol-1]
```

### 解法一空间优化

从递归表达式中可以看出， $dp[i-1][j]$ 在计算完 $dp[i][j]$ 后就没有用了，因此可以直接将 $dp[i][j]$ 保存在 $dp[i-1][j]$ 的位置上，因此可以压缩成一维 n 个元素的dp数组。

此时递归式变成了

$$
dp[j] = \begin{cases} 
min(dp[j], dp[j-1]) + grid[i][j]  \quad & 1 \leq i \leq m, 1 \leq j \leq n \\
dp[j] + grid[i][j] \quad & 1 \leq i \leq m, j=0 \\
grid[0][0] \quad & i=j=0 \\ 
dp[j-1] + grid[0][j] \quad &  i=0, 1 \leq j \leq n \\

\end{cases}
$$

### 解法一c++

```
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size(); 
        int dp[n] = {grid[0][0]};
        for (int j=1; j<n; j++) {
            dp[j] = dp[j-1] + grid[0][j];
        }
        for (int i=1; i<m; i++) {
            for (int j=0; j<n; j++) {
                if (j==0) {
                    dp[j] = dp[j] + grid[i][j];
                } else {
                    dp[j] = min(dp[j-1], dp[j]) + grid[i][j];
                }
            }
        }
        return dp[n-1];
    }
};
```

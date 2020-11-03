[toc]

## 问题描述

[63. 不同路径 II - 力扣（LeetCode）](https://leetcode-cn.com/problems/unique-paths-ii/)

## 算法

### 解法1： dp

##### 解法1： 实现： python

```
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        // dp[i][j] = dp[i-1][j] + dp[i][j-1]
        if (!obstacleGrid.size() || ! obstacleGrid[0].size()) return 0;
        int nrow = obstacleGrid.size(), ncol = obstacleGrid[0].size();
        // 起点或终点是障碍
        if (obstacleGrid[0][0]==1 || obstacleGrid[nrow-1][ncol-1]==1) return 0;

        vector<vector<int>> dp(nrow, vector<int>(ncol));
        for (int col=0; col<ncol; col++)
        {
            if (obstacleGrid[0][col] == 0)
                dp[0][col] = 1;
            else break; 
        }
        for (int row=1; row<nrow; row++)
        {
            if (obstacleGrid[row][0] == 0) dp[row][0] = 1;
            else break;

        }
            
        for (int row=1; row <nrow; row++)
        {
            for (int col=1; col < ncol; col++)
            {
                if (obstacleGrid[row][col] == 0) 
                {
                    dp[row][col] = dp[row-1][col] + dp[row][col-1];
                }
            }
        }
        return dp[nrow-1][ncol-1];
    }
};
```

### 解法2： dp 优化行

##### 解法2： dp 优化行: 实现

```
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        // dp[i][j] = dp[i-1][j] + dp[i][j-1]
        if (!obstacleGrid.size() || ! obstacleGrid[0].size()) return 0;
        int nrow = obstacleGrid.size(), ncol = obstacleGrid[0].size();

        // 起点或终点是障碍
        if (obstacleGrid[0][0]==1 || obstacleGrid[nrow-1][ncol-1]==1) return 0;

        vector<int> dp(ncol);
        // 第一行
        for (int col=0; col<ncol; col++)
        {
            if (obstacleGrid[0][col] == 0)
                dp[col] = 1;
            else break; 
        }
        
        for (int row=1; row <nrow; row++)
        {
            for (int col=0; col < ncol; col++)
            {
                if (col==0) {
                    if (dp[col]==1 && obstacleGrid[row][col]==0) 
                        dp[col] = 1;
                    else 
                        dp[col] = 0; 
                }
                else {
                    if (obstacleGrid[row][col] == 0) 
                        dp[col] = dp[col] + dp[col-1];
                    else 
                        dp[col] = 0;
                }
            }
        }
        return dp[ncol-1];
    }
};
```
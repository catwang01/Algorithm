[toc]

# Leetcode 688. “马”在棋盘上的概率

## 问题描述

[688. “马”在棋盘上的概率 - 力扣（LeetCode）](https://leetcode-cn.com/problems/knight-probability-in-chessboard/)

## 算法

### 解法1: dp

#### 解法1: 实现

##### 解法1:

```
class Solution:
    def knightProbability(self, N: int, K: int, r: int, c: int) -> float:
        # dp[i][j][k] ==> 移动了k次到达 [i-2, j-2] 的总可能数

        dp = [[[0] * (K+1) for j in range(N)]for i in range(N)]
        dp[r][c][0] = 1
        directions = [[1,2], [-1, 2], [1, -2], [-1, -2], [2, 1], [2, -1], [-2, 1], [-2, -1]]

        mul = 1 / 8
        for k in range(1, K+1):
            for i in range(N):
                for j in range(N):
                    for x, y in directions:
                        if 0<= i+x < N and 0<= j+y < N:
                            dp[i][j][k] += dp[i+x][j+y][k-1] * mul
        prob = 0
        for i in range(N):
            for j in range(N):
                prob += dp[i][j][K]
        return prob
```

#### 解法1: 实现2: 加边

上面的实现中，循环内部有许多判断，效率不高，可以通过加边来是减少判断。

##### 解法1: 实现2: python

```
class Solution:
    def knightProbability(self, N: int, K: int, r: int, c: int) -> float:
        # dp[i][j][k] ==> 移动了k次到达 [i-2, j-2] 的总可能数

        dp = [[[0] * (K+1) for j in range(N+4)]for i in range(N+4)]
        dp[r+2][c+2][0] = 1
        directions = [[1,2], [-1, 2], [1, -2], [-1, -2], [2, 1], [2, -1], [-2, 1], [-2, -1]]

        mul = 1 / 8
        for k in range(1, K+1):
            for i in range(2, N+2):
                for j in range(2, N+2):
                    for x, y in directions:
                        dp[i][j][k] += dp[i+x][j+y][k-1] * mul
        prob = 0
        for i in range(2, N+2):
            for j in range(2, N+2):
                prob += dp[i][j][K]
        return prob
```

### 解法1:空间优化

#### 解法1: 空间优化：实现

##### 解法1:空间优化：实现

```
class Solution:
    def knightProbability(self, N: int, K: int, r: int, c: int) -> float:
        # dp[i][j][k] ==> 移动了k次到达 [i, j] 的概率

        dp1 = [[0] * N for i in range(N)]
        dp2 = [[0] * N for i in range(N)]
        dp1[r][c] = 1
        directions = [[1,2], [-1, 2], [1, -2], [-1, -2], [2, 1], [2, -1], [-2, 1], [-2, -1]]

        mul = 1 / 8
        for k in range(1, K+1):
            for i in range(N):
                for j in range(N):
                    dp2[i][j] = 0
                    for x, y in directions:
                        if 0<= i+x < N and 0 <= j+y < N:
                            dp2[i][j] += dp1[i+x][j+y] * mul
            dp1, dp2 = dp2, dp1
            
        prob = 0
        for i in range(N):
            for j in range(N):
                prob += dp1[i][j]
        return prob
```
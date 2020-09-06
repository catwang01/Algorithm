[toc]


# Leetcode 576. 出界的路径数 

## 问题描述 

[576. 出界的路径数 - 力扣（LeetCode）](https://leetcode-cn.com/problems/out-of-boundary-paths/)

## 算法

### 解法1: 三维 dp

由于 1-2 和 1-2-2-1 是不同的路径，为区分这两个，除了空间维度的坐标 x 和 y 之外，还需要引入一个时间维度。

#### 解法1: 实现1：不加边

##### 解法1: 实现1: python

```cpp
class Solution:
    def findPaths(self, m: int, n: int, N: int, i: int, j: int) -> int:
        dp = [ [[0] * (N+1) for j in range(n)] for i in range(m)]
        # dp[i][j][k] 表示 移动了 k 步 最终到 (i, j) 位置的路径数
        dp[i][j][0] = 1
        directions = [[0, 1], [1, 0], [-1, 0], [0, -1]]
        ret = 0
        for k in range(1, N+1):
            for x in range(m):
                for y in range(n):
                    for dx, dy in directions:
                        if 0<=x+dx<m and 0<=y+dy<n:
                            dp[x][y][k] += dp[x+dx][y+dy][k-1]

            for y in range(n):
                ret += dp[0][y][k-1]
                ret += dp[m-1][y][k-1]

            for x in range(m):
                ret += dp[x][0][k-1]
                ret += dp[x][n-1][k-1]
                
        return ret % (10**9+7)
```

#### 解法1: 实现2: 加边

##### 

                    

        

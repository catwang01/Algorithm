[toc]

# Leetcode 1277. 统计全为 1 的正方形子矩阵

## 问题描述

[1277. 统计全为 1 的正方形子矩阵 - 力扣（LeetCode）](https://leetcode-cn.com/problems/count-square-submatrices-with-all-ones/)

## 算法

### 解法1: 三维 dp

#### 解法1: 实现

##### 解法1: python

```
class Solution:
    def countSquares(self, matrix: List[List[int]]) -> int:
        if not matrix or not matrix[0]: return 0
        nrow, ncol = len(matrix), len(matrix[0])
        dp = [ [ [False] * min(nrow, ncol) for j in range(ncol)] for i in range(nrow)]
        ret = 0

        for i in range(nrow):
            for j in range(ncol):
                dp[i][j][0] = matrix[i][j]
                ret += dp[i][j][0]

        for k in range(1, min(nrow, ncol)):
            for i in range(nrow - k):
                for j in range(ncol - k):
                    dp[i][j][k] = dp[i][j][k-1] and dp[i][j+1][k-1] and dp[i+1][j][k-1] and dp[i+1][j+1][k-1]
                    ret += dp[i][j][k]
        return ret
```

### 解法1: 三维dp空间优化

时间复杂度：$O(m * n * min(m,n))$
空间复杂度： $O(mn)$

#### 解法1: 三维dp空间优化实现

##### 解法1: 三维dp空间优化 python

```
class Solution:
    def countSquares(self, matrix: List[List[int]]) -> int:
        if not matrix or not matrix[0]: return 0
        nrow, ncol = len(matrix), len(matrix[0])
        dp = [ [False] * ncol for i in range(nrow)]
        ret = 0

        for i in range(nrow):
            for j in range(ncol):
                dp[i][j]= matrix[i][j]
                ret += dp[i][j]

        for k in range(1, min(nrow, ncol)):
            for i in range(nrow - k):
                for j in range(ncol - k):
                    dp[i][j] = dp[i][j] and dp[i][j+1] and dp[i+1][j] and dp[i+1][j+1]
                    ret += dp[i][j]
        return ret
```

### 解法2: 二维 dp

这个 dp 思路可以参考 [Leetcode-221. 最大正方形.md](Leetcode/Leetcode-221.%20最大正方形.md)

盗 [ 1 ] 中的一张图来说明问题：
![](https://gitee.com/EdwardElric_1683260718/picture_bed/raw/master/img/20200709150534.png)

这种方法可以不重不漏的遍历所有正方形。

#### 解法2: 实现

##### 解法2: 

```cpp
class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        if (!matrix.size() || !matrix[0].size()) return 0;
        int nrow = matrix.size(), ncol = matrix[0].size();

        vector<vector<int>> dp(nrow, vector<int>(ncol));
        int ret = 0;
        for (int i=0; i<nrow; i++) 
        {
            dp[i][0] = matrix[i][0];
            ret += dp[i][0];
        }

        for (int j=1; j<ncol; j++) 
        {
            dp[0][j] = matrix[0][j];
            ret += dp[0][j];
        }

        for (int i=1; i<nrow; i++)
        {
            for (int j=1; j<ncol; j++)
            {
                if (matrix[i][j]) 
                {
                    dp[i][j] = 1 + min(min(dp[i][j-1], dp[i-1][j]), dp[i-1][j-1]);
                    ret += dp[i][j];
                }
            }
        }
        return ret;
    }
};
```

# References
1. [【统计全为 1 的正方形子矩阵】非常朴素（暴力）的dp及优化 - 统计全为 1 的正方形子矩阵 - 力扣（LeetCode）](https://leetcode-cn.com/problems/count-square-submatrices-with-all-ones/solution/tong-ji-quan-wei-1-de-zheng-fang-xing-zi-ju-zhen-f/)
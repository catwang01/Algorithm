[toc]

# Leetcode 97. 交错字符串

## 问题描述

[97. 交错字符串 - 力扣（LeetCode）](https://leetcode-cn.com/problems/interleaving-string/)

## 算法

### 解法1：回溯

#### 解法1：实现

##### 解法1: 实现：python

```
class Solution:
    def isInterleave(self, s1: str, s2: str, s3: str) -> bool:
        n1, n2, n3 = len(s1), len(s2), len(s3)

        def dfs(i, j, k):
            nonlocal n1, n2, n3

            if i > n1 or j > n2:
                return False
            elif i == n1 and j == n2 and k == n3:
                return True
            if i < n1 and k < n3 and s1[i] == s3[k]:
                if dfs(i+1, j, k+1):
                    return True
            if j < n2 and k < n3 and s2[j] == s3[k]:
                if dfs(i, j+1, k+1):
                    return True
            return False
        return dfs(0, 0, 0)
```

### 解法2：dp

这个 dp 思想看 [ 1 ]，十分直观

#### 解法2: 实现

##### 解法2: 实现：python

```
class Solution:
    def isInterleave(self, s1: str, s2: str, s3: str) -> bool:
        n1, n2, n3 = len(s1), len(s2), len(s3)
        if n1 + n2 != n3: 
            return False
        dp = [[False] * (n2+1) for _ in range(n1+1)]
        for i in range(n1+1):
            for j in range(n2+1):
                if i == j == 0:
                    dp[i][j] = True
                else:
                    dp[i][j] = (i-1 >= 0 and dp[i-1][j] and s1[i-1] == s3[i - 1 + j]) or \
                (j-1 >= 0 and dp[i][j-1] and s2[j-1] == s3[i + j - 1])       
        return dp[n1][n2]
```

# References
1. [类似路径问题，找准状态方程快速求解 - 交错字符串 - 力扣（LeetCode）](https://leetcode-cn.com/problems/interleaving-string/solution/lei-si-lu-jing-wen-ti-zhao-zhun-zhuang-tai-fang-ch/)
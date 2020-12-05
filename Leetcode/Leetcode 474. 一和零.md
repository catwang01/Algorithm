[toc]

# Leetcode 474. 一和零

## 问题描述

[474. 一和零 - 力扣（LeetCode）](https://leetcode-cn.com/problems/ones-and-zeroes/)

## 算法

### 解法1   

```
class Solution:
    def findMaxForm(self, strs: List[str], m: int, n: int) -> int:
        dp = [[[0] * (n + 1) for j in range(m+1)] for i in range(len(strs) + 1)]
        count0 = [s.count("0") for s in strs]
        count1 = [len(strs[i]) - count0[i] for i in range(len(strs))]
        # dp[i][x][y] 表示当最多有 x 个0 和 y 个 1是 strs[:i] 的最大子集的大小
        for i in range(1, len(strs)+1):
            for x in range(m+1):
                for y in range(n+1):
                    dp[i][x][y] = dp[i-1][x][y]
                    if x - count0[i-1] >= 0 and y - count1[i-1] >= 0:
                        dp[i][x][y] = max(dp[i][x][y], dp[i-1][x-count0[i-1]][y-count1[i-1]] + 1)
        return dp[len(strs)][m][n]
```
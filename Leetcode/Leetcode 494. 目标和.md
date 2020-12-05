[toc]

# Leetcode 494. 目标和

## 问题描述

[494. 目标和 - 力扣（LeetCode）](https://leetcode-cn.com/problems/target-sum/)

## 算法

### 解法

```
class Solution:
    def findTargetSumWays(self, nums: List[int], S: int) -> int:
        n = len(nums)
        maxSum = sum(nums) # [-maxSum, maxSum] ==> x + maxSum 变换到 [0, 2 * maxSum]
        if not -maxSum <= S <= maxSum: 
            return 0
        dp = [[0] * (2 * maxSum + 1) for i in range(n+1)]
        dp[0][maxSum] = 1
        for i in range(1, n+1):
            for j in range(2 * maxSum + 1):
                if j + nums[i-1] <= 2 * maxSum:
                    dp[i][j] += dp[i-1][j + nums[i-1]]
                if j - nums[i-1] >= 0:
                    dp[i][j] += dp[i-1][j - nums[i-1]]
        return dp[n][S + maxSum] 
```

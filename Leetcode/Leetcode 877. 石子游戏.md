[toc]

# Leetcode 877. 石子游戏

## 问题描述

[877. 石子游戏 - 力扣（LeetCode）](https://leetcode-cn.com/problems/stone-game/)

## 算法

### 解法1：递归 + 记忆化

##### 解法1: 实现：python

```
class Solution:
    def stoneGame(self, piles: List[int]) -> bool:
        n = len(piles)
        preSum = [0] * (n + 1)
        for i in range(1, n+1):
            preSum[i] = preSum[i-1] + piles[i-1]

        memo = {}
        def helper(i, j): # helper(i,j) 表示当石子是 piles[i:j] 时 alex 获得当最大值。
            if (i, j) not in memo:
                if j - i == 1: 
                    return piles[i]
                memo[(i, j)] = max(
                    piles[i] + preSum[j] - preSum[i+1] - helper(i+1, j),
                    piles[j-1] + preSum[j-1] - preSum[i] - helper(i, j-1)
                )
            return memo[(i, j)]

        alex = helper(0, n)
        return alex >  preSum[n] - alex
```
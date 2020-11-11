[toc]

# Leetcode 312. 戳气球

## 问题描述

[312. 戳气球 - 力扣（LeetCode）](https://leetcode-cn.com/problems/burst-balloons/)

## 算法

### 解法1: 递归 + 记忆化搜索

这个这个递归的思路比较难想到。因为每次戳破气球会导致相邻气球变化，因此我们希望可以固定一些东西让这个变化是容易被表达出来的。

我们注意到，对于区间 [i, j] 且 j > i，只要 i，j 位置的气球没有戳破，那么计算结果时只设计到 [i, j] 内的元素，而不涉及 [i, j] 区间之外的元素，这就保证了我们可以将 [i, j] 区间上的计算当作一个子问题。

我们保证 [i, j] 不变，然后考虑最后一个戳破的气球可能的位置是 [i+1, ..., j-1]，区间 [i, j] 假设最后一个戳破的气球是位置 k ，那么，戳破 k 带来的收益是 nums[i] * nums[j] * nums[k]，而戳破 区间内其他气球带来的收益为戳破 [i, k] 区间上的气球带来的收益与戳破区间 [k, j] 内气球带来的收益。

这样，我们得到了递推方程

```
dfs(i, j) = max(dfs(i, k) + dfs(k, j) + nums[i] * nums[k] * nums[j]) for k in [i+1, ..., j-1]
```

同时，可以使用记忆化来减少重复计算。这个还可以修改为dp

时间复杂度为 $O(n^3)$

##### 解法1: 实现：python


```
class Solution:
    def maxCoins(self, nums: List[int]) -> int:

        n = len(nums)
        memo = {}
        def dfs(i, j): # [i, j]
            if (i, j) not in memo:
                nonlocal n
                if i + 1 == j:
                    return 0

                ret = 0
                left = nums[i] if i >= 0 else 1
                right = nums[j] if j < n else 1
                for k in range(i+1, j):
                    ret = max(ret, dfs(i, k) + dfs(k, j) + nums[k] * left * right)
                memo[(i, j)] = ret
            return memo[(i, j)]

        return dfs(-1, n)
```
                


[toc]

# Leetcode 416. 分割等和子集

## 问题描述

[416. 分割等和子集 - 力扣（LeetCode）](https://leetcode-cn.com/problems/partition-equal-subset-sum/)

### 解法1: 回溯（超时）

```
class Solution:
    def canPartition(self, nums: List[int]) -> bool:
        
        s = sum(nums)
        if s & 1: return False
        target = s // 2
        n = len(nums)

        def dfs(i, curSum):
            nonlocal n, target
            if i == n:
                return curSum == target
            return dfs(i+1, curSum + nums[i]) or dfs(i+1, curSum)

        return dfs(0, 0)
```


### 解法2: 01背包

这个问题是 0-1 背包问题

#### 解法1: 实现1

##### 解法1: 实现1：python

```
def cache(func):
    memo = {}
    def wrapper(*args):
        if args not in memo:
            memo[args] = func(*args)
        return memo[args]
    return wrapper

class Solution:
    def canPartition(self, nums: List[int]) -> bool:
        s = sum(nums)
        if s & 1 or len(nums) < 2: return False
        target = s // 2

        @cache
        def helper(i, target):
            if i < 0 or target < 0: 
                return False
            if target == 0:
                return True
            return helper(i-1, target - nums[i]) or helper(i-1, target)

        return helper(len(nums)-1, target)
```

#### 解法1: 实现2

##### 解法1: 实现2：python


```
class Solution:
    def canPartition(self, nums: List[int]) -> bool:
        s = sum(nums)
        if s & 1: return False
        target = s // 2
        n = len(nums)
        dp = [[False] * (target+1) for _ in range(n+1)]
        # dp[i][j] 表示 nums[:i] 是否可以分出一个子集和为 j
        # 注意这里 dp[0][0] = True 
        # 这样设置主要是希望递推时类似于 dp[1][nums[i-1]] 这样的值可以转移到 True
        for i in range(n+1): # j = 0 时，总能达到
            dp[i][0] = True
        for i in range(1, n+1):
            for j in range(1, target+1):
                dp[i][j] = dp[i-1][j] or (j - nums[i-1] >= 0 and dp[i-1][j-nums[i-1]])
        return dp[n][target]
```
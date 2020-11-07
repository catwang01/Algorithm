[toc]

# Leetcode 491. 递增子序列

## 问题描述

[491. 递增子序列 - 力扣（LeetCode）](https://leetcode-cn.com/problems/increasing-subsequences/)

## 算法

### 解法1： 递归 + hash 去重

不用 hash 去重的还没有看懂

#### 解法1： 实现： python

```
class Solution:
    def findSubsequences(self, nums: List[int]) -> List[List[int]]:
        ret = set()
        if len(nums) <= 1: 
            return []

        def dfs(i, cur):
            if i == len(nums):
                if len(cur) >= 2:
                    ret.add(tuple(cur))
                return 
            if cur == [] or nums[i] >= cur[-1]:
                cur.append(nums[i])
                dfs(i+1, cur)
                cur.pop()
            dfs(i+1, cur)

        dfs(0, [])
        return [list(x) for x in ret]
```


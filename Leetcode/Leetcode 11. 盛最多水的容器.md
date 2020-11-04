[toc]

# Leetcode 11. 盛最多水的容器 

## 问题描述

[11. 盛最多水的容器 - 力扣（LeetCode）](https://leetcode-cn.com/problems/container-with-most-water/)

## 算法

### 解法1: bruteforce

遍历所有的 i，j。计算 

### 解法2: 贪心 + 双指针

我们需要计算 `max((j-i) * min(height[i], height[j]))`

假设我们现在 `i, j` 处，我们要如何才有可能让这值变大呢？ 我们可以考虑将 i++ 或 j--。不管是那种情况，j - i 都会变小，要让目标值变大，就需要让 `min(height[i], heigth[j])` 这一项变大。因此，我们选择 height[i] 和 height[j] 中最小的那个，把它“优化”掉


```
class Solution:
    def maxArea(self, height: List[int]) -> int:
        n = len(height)
        # [i, j] --> 可能候选集
        ret = 0
        i, j = 0, n-1
        while i != j:
            ret = max(ret, min(height[i], height[j]) * (j-i))
            if height[i] > height[j]:
                j -= 1
            else:
                i += 1
        return ret
```
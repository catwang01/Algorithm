[toc]


# Leetcode 673. 最长递增子序列的个数

## 问题描述

[673. 最长递增子序列的个数 - 力扣（LeetCode）](https://leetcode-cn.com/problems/number-of-longest-increasing-subsequence/)

给定一个未排序的整数数组，找到最长递增子序列的个数。

**示例 1:**

**输入:** \[1,3,5,4,7\]
**输出:** 2
**解释:** 有两个最长递增子序列，分别是 \[1, 3, 4, 7\] 和\[1, 3, 5, 7\]。

**示例 2:**

**输入:** \[2,2,2,2,2\]
**输出:** 5
**解释:** 最长递增子序列的长度是1，并且存在5个子序列的长度为1，因此输出5。

## 算法

### 解法1: dp


```
class Solution:
    def findNumberOfLIS(self, nums: List[int]) -> int:
        n = len(nums)
        if n <= 1: return n
        dp = [1] * n
        dp_count = [1] * n # 注意这个要初始化为 1
        maxlen = 1
        count = 0
        for i in range(n):
            for j in range(i):
                if nums[i] > nums[j]: # 构成最长递增子序列
                    if dp[i] < dp[j] + 1:
                        dp[i] = dp[j] + 1
                        dp_count[i] = dp_count[j]
                    elif dp[i] == dp[j] + 1:
                        dp_count[i] += dp_count[j]
            if dp[i] > maxlen: # 更新最大长度
                maxlen = dp[i]
                count = dp_count[i] 
            elif dp[i] == maxlen: # 当前最长递增子序列数量增加
                count += dp_count[i]
        return count
```
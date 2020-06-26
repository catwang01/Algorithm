[toc]

#  Leetcode 41. 缺失的第一个正数

## 问题描述

[41. 缺失的第一个正数 - 力扣（LeetCode）](https://leetcode-cn.com/problems/first-missing-positive/)

## 算法

### 解法1: 原地 hash

#### 解法1: python

```
class Solution:
    def firstMissingPositive(self, nums: List[int]) -> int:
        n = len(nums)

        for i in range(n):
            # 1. 当前的格子中的数需要 hash（即在 [1,n] 之间）
            # 2. 并且当前格子中的数不匹配 nums[i] != i+1
            # 3. 并且目标格子中的值不匹配 nums[nums[i]-1] != nums[i]
            while 0 < nums[i] <= n and nums[i] != i+1 and nums[nums[i]-1] != nums[i]:
                nums[nums[i]-1], nums[i] = nums[i], nums[nums[i]-1]
        for i in range(n):
            if (nums[i] != i + 1):
                return i + 1
        # 能跳出这个for循环，说明数组中所有的元素都找到了对应的位置，即数组中的元素为 [1, n]
        # 因此缺失的第一个正数为 n+1
        return n + 1 
```
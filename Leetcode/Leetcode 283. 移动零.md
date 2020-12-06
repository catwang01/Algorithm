[toc]

# Leetcode 283. 移动零

## 问题描述

[283. 移动零 - 力扣（LeetCode）](https://leetcode-cn.com/problems/move-zeroes/)

## 算法

### 解法1: 

#### 解法1: 实现

##### 解法1: 实现：python

```
class Solution:
    def moveZeroes(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        # [0, i) nonzero
        # [i, j) zero
        # [j, n) unprocessed
        i = j = 0
        while j < len(nums):
            if nums[j] != 0:
                nums[i], nums[j] = nums[j], nums[i]
                i += 1
            j += 1
```
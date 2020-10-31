[toc]

# Leetcode 

## 问题描述

[704. 二分查找 - 力扣（LeetCode）](https://leetcode-cn.com/problems/binary-search/)

## 算法

### 解法1: 左开右闭区间

#### 解法1：实现

##### 解法1: python

```
class Solution:
    def search(self, nums: List[int], target: int) -> int:
        low, high = 0, len(nums)
        while low < high:
            mid = (low + high) // 2
            if nums[mid] == target:
                return mid
            elif nums[mid] < target:
                low = mid + 1
            elif nums[mid] > target:
                high = mid
        return -1
```
        
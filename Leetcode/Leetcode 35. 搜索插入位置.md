[toc]

# Leetcode 35. 搜索插入位置

## 问题描述

[35. 搜索插入位置 - 力扣（LeetCode）](https://leetcode-cn.com/problems/search-insert-position/submissions/)

给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。

你可以假设数组中无重复元素。

示例 1:
输入: [1,3,5,6], 5
输出: 2

示例 2:
输入: [1,3,5,6], 2
输出: 1

示例 3:
输入: [1,3,5,6], 7
输出: 4

示例 4:
输入: [1,3,5,6], 0
输出: 0


## 算法

### 解法一：二分法

![1b08589bbf19862920f92ac079651398.jpeg](evernotecid://8E200321-31A9-427B-BECA-CC44235980BC/appyinxiangcom/22483756/ENResource/p10441)

#### 解法1: 实现1: python实现

```
class Solution:
    def searchInsert(self, nums: List[int], target: int) -> int:
        n = len(nums)
        return self.bisearch(nums, 0, n-1, target)
    
    def bisearch(self, A, low, high, target):
        if target > A[high]: return high + 1
        while low < high:
            mid = low + high >> 1
            if A[mid] < target:
                low = mid + 1
            else:
                high = mid
        return low
```

#### 解法1:实现2: 闭区间 剩两个元素时退出


##### 解法1:实现2: python

```
class Solution:
    def searchInsert(self, nums: List[int], target: int) -> int:
        if not nums: return 0
        if target > nums[-1]: return len(nums)
        low, high = 0, len(nums) - 1
        while low + 1 < high:
            mid = (low + high) // 2
            if nums[mid] >= target:
                high = mid
            else:
                low = mid + 1
        # 剩最后两个，依次判断，注意先判断 low
        if nums[low] >= target:
            return low
        else:
            return high
```

#### 解法1:实现3:开区间 剩两个元素退出

##### 解法1:实现3:python

```
class Solution:
    def searchInsert(self, nums: List[int], target: int) -> int:
        low, high = 0, len(nums)
        if low == high: return 0
        if target > nums[high-1]: return high
        # [low, high)
        while high - low > 2:
            mid = (low + high) // 2
            if nums[mid] >= target:
                high = mid + 1 # [low, mid]
            else:
                low = mid + 1  # [mid+1, high)
        if nums[low] >= target:
            return low
        if nums[high-1] >= target:
            return high-1
        return -1
```
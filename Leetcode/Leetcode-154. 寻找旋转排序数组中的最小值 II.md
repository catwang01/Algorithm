[toc]

# Leetcode 154. 寻找旋转排序数组中的最小值 II 

## 问题描述

[154. 寻找旋转排序数组中的最小值 II - 力扣（LeetCode）](https://leetcode-cn.com/problems/find-minimum-in-rotated-sorted-array-ii/)

## 算法

### 解法1: 二分法 + 预处理

这道题和 153 题的一个区别是允许有重复值。因此，当 nums[mid] == nums[0] 时，并不能判断是在最小值的左侧还是右侧。因此，可以先进行预处理，如果 nums[high] == nums[low]，就收缩 nums[high]，直到 nums[high] != nums[low]，此时就可以当作 153 题处理了。

#### 解法1:实现

##### 解法1: python

```
class Solution:
    def findMin(self, nums: List[int]) -> int:
        n = len(nums)
        if n == 0: return -1
        if n == 1: return nums[0]

        low, high = 0, n - 1

        if nums[0] == nums[high]: # 预处理
            while low < high and nums[high] == nums[0]:
                high -= 1
            # low > high or nums[high] < head
            if low > high:
                return head

        if nums[0] < nums[high]: # 单调递增时返回最左侧的值
            return nums[0]
            
        while low + 1 < high: # 区间长度为2时返回
            mid = (low + high) // 2
            if nums[mid] >= nums[0]:
                low = mid + 1
            else:
                high = mid
        # 此时 low + 1 == high
        return min(nums[low], nums[high])
```

### 解法2：二分法 

这种方法和 解法1 的区别在于，这解法不使用预处理，而是在遇到 nums[mid] == nums[right] 时右边界收缩。

todo 其实为什么遇到 nums[mid] == nums[right] 时右边界收缩也不是很清楚。

#### 解法2:实现

##### 解法2: python

```
class Solution:
    def findMin(self, nums: List[int]) -> int:
        n = len(nums)
        if n == 0: return -1
        if n == 1: return nums[0]

        low, high = 0, n - 1

        if nums[0] < nums[high]: # 单调递增
            return nums[0]
            
        while low + 1 < high:
            mid = (low + high) // 2
            if nums[mid] > nums[high]:
                low = mid + 1
            elif nums[mid] == nums[high]:
                high -= 1
            else:
                high = mid
        # 此时 low + 1 == high
        return min(nums[low], nums[high])
```
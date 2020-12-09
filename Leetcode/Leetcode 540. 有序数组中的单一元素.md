[toc]

# Leetcode 540. 有序数组中的单一元素

## 问题描述

[540. 有序数组中的单一元素 - 力扣（LeetCode）](https://leetcode-cn.com/problems/single-element-in-a-sorted-array/)

## 算法

### 解法1：二分法

由于要求时间复杂度为 $log(N)$，只可能是二分法。

主要看有什么逻辑可以用来辅助二分。
我们看到，假设 i 是我们要求的数的下标，那么 对于 j < i，即 i 左边的数都会满足

```
if j 为奇数:
    then nums[j] == nums[j-1]
else:
    then nums[j] == nums[j+1]
```

而这个条件在 i 左边即 j >= i 时是不满足的。我们把这个条件抽象为一个函数 condition，那么我们实际上是在求不满足 condition 的最小值。

```
j = argmin(not condition(i))
```

#### 解法1: 实现：左闭右开区间

##### 解法1: 实现：python

```
class Solution:
    def singleNonDuplicate(self, nums: List[int]) -> int:
        def condition(i):
            if i & 1:
                return i - 1 >= 0 and nums[i] == nums[i-1]
            else:
                return i+1 < len(nums) and nums[i] == nums[i+1]
        
        low, high = 0, len(nums)
        while high - low > 2:
            mid = (low + high) // 2
            if condition(mid):
                low = mid + 1
            else:
                high = mid + 1
        if condition(low):
            return nums[high-1]
        return nums[low]
```

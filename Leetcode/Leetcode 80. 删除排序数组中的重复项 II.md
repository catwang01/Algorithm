[toc]

# Leetcode 80. 删除排序数组中的重复项 II

## 问题描述

[80. 删除排序数组中的重复项 II - 力扣（LeetCode）](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-array-ii/)

## 算法

### 解法1

类似于快速排序的思路。用两个指针 i, j 满足 i <= j 将数组分为三个部分：
1. [0, i) 最终需要返回的部分
2. [i, j) 被删除的元素
3. [j, n) 还没有遍历的元素

关键是如何移动 i 指针，有下面三种情况下 i 指针会移动（相当于往返回的数组 append 一个元素）

1. i < 2，此时 [0, i) 中的元素个数小于2，因此 nums[i] 不可能重复两次
2. nums[j] != nums[i-1] ，表示 nums[j] 没有和之前的元素重复
3. nums[j] == nums[i-1] && nums[i-1] != nums[i-2] ，表示 nums[j] 只和 nums[i-1] 重复，而没有和 nums[i-2] 重复，此时 nums[j] 重复次数为2，满足条件，不被删除。


```
class Solution:
    def removeDuplicates(self, nums: List[int]) -> int:
        i = j = 0
        n = len(nums)
        # [0, i) 返回值 [i, j) 删除
        while j < n:
            if i < 2 or \
                nums[j] != nums[i-1] or \
                nums[j] == nums[i-1] and nums[i-1] != nums[i-2]:
                nums[i], nums[j] = nums[j], nums[i]
                i += 1
            j += 1
        return i
```
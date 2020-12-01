
[toc]

# Leetcode 34. 在排序数组中查找元素的第一个和最后一个位置

## 问题描述

[34. 在排序数组中查找元素的第一个和最后一个位置 - 力扣（LeetCode）](https://leetcode-cn.com/problems/find-first-and-last-position-of-element-in-sorted-array/)

给定一个按照升序排列的整数数组 nums，和一个目标值 target。找出给定目标值在数组中的开始位置和结束位置。

你的算法时间复杂度必须是 $O(logn)$ 级别。

如果数组中不存在目标值，返回 [-1, -1]。

示例 1:
输入: nums = [5,7,7,8,8,10], target = 8
输出: [3,4]

示例 2:
输入: nums = [5,7,7,8,8,10], target = 6
输出: [-1,-1]

## 算法

### 解法1： 二分法1 + 线性查找

二分法，当找到 A[mid] == target 时，向两侧检查是否还有等于 target 的值

时间复杂度： 当数组中所有的数都相等时，退化为线性情况，时间复杂度为： $O(n)$
空间复杂度： $O(1)$

#### 解法一： 实现1

##### 解法一： 实现1:  python

```
class Solution:
    def searchRange(self, nums: List[int], target: int) -> List[int]:
        return self.bisearch(nums, 0, len(nums)-1, target)
    
    def bisearch(self, A, low, high, target):
        while low <= high:
            mid = low + high >> 1
            if A[mid] == target:
                first, last = mid, mid
                while first>=low and A[first]==target:
                    first -= 1
                first += 1
                while last <= high and A[last] == target:
                    last += 1
                last -= 1
                return [first, last]
            else:
                if target < A[mid]:
                    high = mid - 1
                else:
                    low = mid + 1
        return [-1, -1]
```

### 解法二：二分法2

#### 解法2: 实现1: 闭区间 + 剩一个退出

二分法，找到 upper_bound 和 low_bound 后，检查 A[upper_bound] 或 A[low_bound] 是否等于 target：如果是，说明 target 在数组中，则返回 low；如果不是，说明 target 不在数组中，此时返回 -1

##### 解法2: 实现1: python

```
class Solution:
    def searchRange(self, nums: List[int], target: int) -> List[int]:
        if len(nums)==0: return [-1, -1]
        return [self.bisearch_left(nums, 0, len(nums)-1, target), self.bisearch_right(nums, 0, len(nums)-1, target)]
    
    def bisearch_right(self, A, low, high, target):
        while low < high:
            mid = low + high + 1 >> 1
            if A[mid] > target:
                high = mid - 1
            else:
                low = mid
        return low if A[low] == target else -1

    def bisearch_left(self, A, low, high, target):
        while low < high:
            mid = low + high >> 1
            if A[mid] < target:
                low = mid + 1
            else:
                high = mid
        return low if A[low] == target else -1
```

#### 解法2: 实现2: 闭区间 + 剩两个退出
##### 解法2:实现2: python

```
class Solution:
    def searchRange(self, nums: List[int], target: int) -> List[int]:
        if not nums: return [-1, -1]
        ret = [
            self.bisearch_left(nums, 0, len(nums)-1, target),
            self.bisearch_right(nums, 0, len(nums)-1, target)
        ]
        return ret

    def bisearch_left(self, A, low, high, target):
        while low + 1 < high:
            mid = (low + high) // 2
            if A[mid]==target:
                high = mid
            elif A[mid] > target:
                high = mid - 1
            elif A[mid] < target:
                low = mid + 1
        if A[low] == target:
            return low
        if A[high] == target:
            return high
        return -1
    
    def bisearch_right(self, A, low, high, target):
        while low + 1 < high:
            mid = (low + high) // 2
            if A[mid] == target:
                low = mid
            elif A[mid] > target:
                high = mid - 1
            elif A[mid] < target:
                low = mid + 1
        if A[high] == target:
            return high
        if A[low] == target:
            return low
        return -1
```

#### 解法2: 实现3: 开区间 + 剩两个退出
##### 解法2: 实现3: c++

```
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        return {upper_bound(nums, 0, nums.size(), target), lower_bound(nums, 0, nums.size(), target)};
    }

    int lower_bound(vector<int>&nums, int low, int high, int target)
    // max_i(nums[i] <= target)
    {
        if (high - low == 0) return -1;
        auto condition = [&](int i){ return nums[i] <= target;};
        while (high - low > 2)
        {
            int mid = low + (high - low) / 2;
            if (condition(mid))
                low = mid;
            else
                high = mid;
        }
        if (nums[high-1] == target) return high-1;
        if (nums[low] == target) return low;
        return -1;
    }

    int upper_bound(vector<int>&nums, int low, int high, int target)
    // min_i(nums[i] >= target)
    {
        if (high - low == 0) return -1;
        auto condition = [&](int i){ return nums[i] >= target;};
        while (high - low > 2)
        {
            int mid = low + (high - low) / 2;
            if (condition(mid))
                high = mid + 1;
            else
                low = mid + 1;
        }
        if (nums[low] == target) return low;
        if (nums[high-1] == target) return high-1;
        return -1;
    }
};
```
[toc]

# Leetcode 153. 寻找旋转排序数组中的最小值

## 问题描述

- leetcode： [153. 寻找旋转排序数组中的最小值 - 力扣（LeetCode）](https://leetcode-cn.com/problems/find-minimum-in-rotated-sorted-array/submissions/)

假设按照升序排序的数组在预先未知的某个点上进行了旋转。

( 例如，数组 `[0,1,2,4,5,6,7]` 可能变为 `[4,5,6,7,0,1,2]` )。

请找出其中最小的元素。

你可以假设数组中不存在重复元素。

**示例 1:**
**输入:** [3,4,5,1,2]
**输出:** 1

**示例 2:**
**输入:** [4,5,6,7,0,1,2]
**输出:** 0

相关题目：
1. [Leetcode 33. 搜索旋转排序数组](https://app.yinxiang.com/shard/s54/nl/22483756/7bfc6ed9-8ffc-42f1-86c2-c8972599d92f/)

## 算法

### 法一：bruteforce

逐项和前项比较，如果遇到下降的，说明是最小值。

时间复杂度 $O(n)$ 空间复杂度 $O(1)$

#### 法一c++实现

```
class Solution {
public:
    int findMin(vector<int>& nums) {
        for(int i=1; i<nums.size(); i++)
        {
            if(nums[i-1] > nums[i])
            {
                return nums[i];
            }
        }
        return nums[0];
    }
};
```

### 法二：二分法

![9d04ff3178bdc44d7dd90a518827afaa.png](evernotecid://8E200321-31A9-427B-BECA-CC44235980BC/appyinxiangcom/22483756/ENResource/p10442)

#### 法二c++实现

```
class Solution {
public:
    int findMin(vector<int>& nums) {
        int low=0, high=nums.size()-1;
        // bisearch
        while (low < high) {
            int mid = (low + high) >> 1;
            if (nums[mid] > nums[high]) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }
        return nums[low];
    }
};
```

#### 法二python

```
class Solution:
    def findMin(self, nums: List[int]) -> int:
        return self.bisearch(nums, 0, len(nums)-1)

    def bisearch(self, A, low, high):
        while low < high:
            mid = low + high >> 1
            if A[mid] > A[-1]:
                low = mid + 1
            else:
                high = mid
        return A[low]
```

### 解法3: 二分法

#### 解法3: 实现

##### 解法3: C++


```
class Solution {
public:
    int findMin(vector<int>& nums) {
        int n = nums.size();
        // 特判
        if (n == 0) return -1;
        if (n == 1) return nums[0];

        // 如果第一个数比最后一个数小，说明是单调增的，没有旋转
        if (nums[0] < nums[n-1]) return nums[0];

        // 二分
        int low = 0, high = n-1;
        while (low + 1 < high) 
        {
            int mid = low + (high - low) / 2;
            if (nums[mid] > nums[0])
            {
                low = mid + 1;
            }
            else 
            {
                high = mid;
            }
        }
        return nums[low] < nums[high] ? nums[low] : nums[high];
    }
};
```

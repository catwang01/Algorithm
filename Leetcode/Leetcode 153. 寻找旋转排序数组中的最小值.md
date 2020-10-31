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

### 解法1：bruteforce

逐项和前项比较，如果遇到下降的，说明是最小值。

时间复杂度 $O(n)$
空间复杂度 $O(1)$

#### 解法1: c++实现

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

### 解法2：二分法 和右侧比大小

![9d04ff3178bdc44d7dd90a518827afaa.png](evernotecid://8E200321-31A9-427B-BECA-CC44235980BC/appyinxiangcom/22483756/ENResource/p10442)

#### 解法2: 实现1 闭区间 剩一个元素退出

##### 解法2: 实现1 c++

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

##### 解法2: python 实现1

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

### 解法3: 二分法 和左侧比大小

和左侧比大小要注意先排除序列是递增序列的情况，而和右侧比大小不需要。

#### 解法3: 实现1 闭区间 区间剩两个元素时退出

##### 解法3: 实现1 C++

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

### 解法四：二分法 左闭右开 剩两个元素退出

#### 解法四：实现1

由于 mid 在左边和右边的单调性不同，因此需要分开讨论。

得到一个 mid 后，看这个mid是否满足条件，如果满足条件，就 return。否则收缩边界。

这个思想和最原始的二分法的思想类似，其中都有一个判断 mid 是否**满足条件**的操作。而下面的实现2，并没有这个操作。相反，它只关心 mid 是否**不满足**条件。

##### 解法四：实现1: c++

```
class Solution {
public:
    int findMin(vector<int>& nums) {
        int low = 0, high = nums.size();
        // 只有一个元素 或者没有旋转
        if (high-low==1 || nums[0] <= nums[high-1]) return nums[0];

        while (high - low > 2)
        {
            int mid = low + (high - low) / 2;
            if (nums[mid] < nums[0]) // mid在左边
            {
                if (nums[mid-1] > nums[mid])
                    return nums[mid];
                else
                    high = mid;
            }
            else // mid 在右边
            {
                if (nums[mid+1] < nums[mid])
                    return nums[mid+1];
                else
                    low = mid + 1;
            }
        }
        return (nums[low] <= nums[high-1]) ? nums[low] : nums[high-1];
    }
};
```

#### 解法四：实现2；

实现2和实现1有所不同。实现2是减治的思想，在得到一个 mid 后不关心它是否满足条件，而是看它是否不满足条件，如果不满足，则收缩边界。反正可以保证一定是有解的，那么排除完剩下的就是解。

##### 解法四：实现2: c++

```
class Solution {
public:
    int findMin(vector<int>& nums) {
        int low = 0, high = nums.size();
        if (high-low==1 || nums[0] < nums[high-1]) return nums[0];

        while (high - low > 2)
        {
            int mid = low + (high - low) / 2;
            if (nums[mid] < nums[0]) // mid在右边
            {
                high = mid + 1;
            }
            else // mid 在左边
            {
                low = mid + 1;
            }
        }
        return min(nums[low], nums[high-1]);
    }
};
```

对于有些问题，判断满足条件比较困难时，就需要使用减治法（或者称为排除法更亲切一些）
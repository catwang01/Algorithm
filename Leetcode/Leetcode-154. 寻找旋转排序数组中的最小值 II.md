[toc]

# Leetcode 154. 寻找旋转排序数组中的最小值 II 

## 问题描述

[154. 寻找旋转排序数组中的最小值 II - 力扣（LeetCode）](https://leetcode-cn.com/problems/find-minimum-in-rotated-sorted-array-ii/)

## 算法

### 解法1: 二分法 + 预处理

这道题和 153 题的一个区别是允许有重复值。因此，当 nums[mid] == nums[0] 时，并不能判断是在最小值的左侧还是右侧。因此，可以先进行预处理，如果 nums[high] == nums[low]，就收缩 nums[high]，直到 nums[high] != nums[low]，此时就可以当作 153 题处理了。


时间复杂度：$O(n)$ 最坏情况数组中所有元素都相等。
空间复杂度：$O(1)$

#### 解法1:实现

##### 解法1: python

```
class Solution:
    def findMin(self, nums: List[int]) -> int:
        n = len(nums)
        if n == 0: return -1
        if n == 1: return nums[0]

        low, high = 0, n - 1

        while low < high and nums[high] == nums[0]:
            high -= 1

        if nums[0] < nums[high]: # 单调递增时返回最左侧的值
            return nums[0]
            
        while high - low > 1: # 区间长度小于2时返回
            mid = (low + high) // 2
            if nums[mid] >= nums[0]:
                low = mid + 1
            else:
                high = mid
        return min(nums[low], nums[high])
```

#### 解法1:实现2

##### 解法1: 实现2: c++

```
class Solution {
public:
    int findMin(vector<int>& nums) {
        int low = 0, high = nums.size();
        while (low < high && nums[low]==nums[high-1])
        {
            high--;
        }
        if (low == high) return nums[0]; // 说明nums中所有元素都相等
        if (nums[0] < nums[high-1]) return nums[0]; //  说明删除掉末尾和nums[0] 相同掉数字后，剩下的是一个单调递增的。
        while (high - low > 2)
        {
            int mid = low + (high - low) / 2;
            if (nums[mid] < nums[0]) // 左侧
            {
                high = mid + 1;
            }
            else  // 右侧
            {
                low = mid + 1;
            }
        }
        return min(nums[low], nums[high-1]);
    }
};
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

### 解法三：暴力法

#### 解法三：实现

最暴力的方法，逐个比较 nums[i] 和 nums[i-1]， 如果 nums[i-1] 小于 nums[i] 那么就是最小值。

##### 解法三：实现：c++

```
class Solution {
public:
    int findMin(vector<int>& nums) {
        for (int i=1; i<nums.size(); i++)
            if (nums[i] < nums[i-1]) return nums[i];
        return nums[0]; // nums 只有一个元素 or nums 单调
    }
};
```

[toc]

# Leetcode 33. 搜索旋转排序数组

## 问题描述

[33. 搜索旋转排序数组 - 力扣（LeetCode）](https://leetcode-cn.com/problems/search-in-rotated-sorted-array/)

假设按照升序排序的数组在预先未知的某个点上进行了旋转。

( 例如，数组 [0,1,2,4,5,6,7] 可能变为 [4,5,6,7,0,1,2] )。

搜索一个给定的目标值，如果数组中存在这个目标值，则返回它的索引，否则返回 -1 。

你可以假设数组中不存在重复的元素。

你的算法时间复杂度必须是 $O(logn)$ 级别。

示例 1:
输入: nums = [4,5,6,7,0,1,2], target = 0
输出: 4

示例 2:
输入: nums = [4,5,6,7,0,1,2], target = 3
输出: -1

## 算法

### 解法一：二分法1

1. 先寻找分割点，用时 $O(logn)$
2. 再在两段中分别进行二分查找，用时 $O(logn)$

寻找分割点的二分法可参考 [Leetcode 153. 寻找旋转排序数组中的最小值](https://app.yinxiang.com/shard/s54/nl/22483756/431d5197-d099-4462-a1cb-51dce3cddd13/)

分割过程可用下面的图示表示

![a58b54f47de2b26c98cea348261d531a.jpeg](evernotecid://7E3AE0DC-DC71-4DDC-9CC8-0C832D6C11C2/appyinxiangcom/22483756/ENResource/p10718)

时间复杂度： $O(logn)$
空间复杂度： $O(1)$

#### 解法一

#### 解法一: python

```
class Solution:
    def search(self, nums: List[int], target: int) -> int:
        n = len(nums)
        if n ==0: return -1
        split_point = self.find_split_point(nums, 0, n-1)
        result = self.bisearch(nums, 0, split_point, target)
        if result != -1: 
            return result
        else:
            result = self.bisearch(nums, split_point+1, n-1, target)
            if result != -1: 
                return result
            else: 
                return -1

    def bisearch(self, A, low, high, x):
        while low <= high:
            mid = low + high >> 1
            if A[mid] == x:
                return mid
            elif x < A[mid]:
                high = mid - 1
            elif x > A[mid]:
                low = mid + 1
        return -1

    def find_split_point(self, A, low, high):
        while low < high:
            mid = low + high + 1 >> 1
            if A[mid] > A[-1]:
                low = mid
            else:
                high = mid - 1
        return low
```

##### 解法1: c++

```
class Solution {
public:
    int search(vector<int>& nums, int target) {
        if (nums.empty()) return -1;
        int split_point = find_split_point(0, nums.size()-1, nums);
        int ret = bisearch(0, split_point-1, target, nums);
        if (ret != -1) return ret;
        return bisearch(split_point, nums.size()-1, target, nums);
    }

    int find_split_point(int low, int high, const vector<int>& A) {
        while (low < high) {
            int mid = low + ((high - low) >> 1);
            if (A[mid] >= A[0]) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }
        return low;
    }

    int bisearch(int low, int high, int target, const vector<int>& A) {
        while (low <= high) {
            int mid = low + ((high - low ) >> 1);
            if (A[mid]==target) {
                return mid;
            } else {
                if (A[mid] > target){
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }
        }
        return -1;
    }
};
``` 

### 解法二：二分法2

上面的解法将问题分成了两步，一步是使用二分法寻找分割点，一步是对两个有序数组分别使用二分法。相当于使用了三次二分法。

下面的思路只需要使用一次二分法，只是分支判断的条件比较复杂

![4257de31bea20df78e07c1273b9e5fe7.jpeg](evernotecid://7E3AE0DC-DC71-4DDC-9CC8-0C832D6C11C2/appyinxiangcom/22483756/ENResource/p10719)

时间复杂度：$O(logn)$
空间复杂度： $O(1)$

#### 解法二: 实现

##### 解法二: python

```
class Solution:
    def search(self, nums: List[int], target: int) -> int:
        # 将二分法的条件判断抽象成一个check函数
        def check(A, low, high, mid, target):
            # 返回 -1: high = mid - 1  
            # 返回 1: low = mid + 1
            # 返回 0 代表在nums中找到target
            if A[mid] == target:
                return 0
            if A[mid] > A[-1]: 
                if A[mid] > target:
                    if target > A[-1]:  # [low, mid-1]
                        return -1
                    else: # [mid+1, high]
                        return 1 
                else: # [mid+1, high]
                    return 1
            else: # A[mid] <= A[-1]
                if A[mid] > target: # [low, mid-1]
                    return -1
                else:
                    if target > A[-1]:  # [low, mid-1]
                        return -1
                    else: # [mid+1, high]
                        return 1
        n = len(nums)
        if n==0: return -1
        low, high = 0, n-1
        if target == nums[0]: return 0
        if target == nums[-1]: return n-1
        # 下面是二分的逻辑，模板是最原始的二分法
        while low <= high:
            mid = low + high >> 1
            flag = check(nums, low, high, mid, target)
            if flag == 0: return mid
            elif flag == -1:
                high = mid - 1
            elif flag == 1:
                low = mid + 1
        return -1
```


下面是比较通俗的实现方式

```
class Solution:
    def search(self, nums: List[int], target: int) -> int:
        low, high = 0, len(nums)
        while high - low > 2:
            mid =(low + high) // 2
            if nums[mid] >= nums[0]:        # nums[mid] 在左侧
                if nums[mid] == target:
                    return mid
                elif target < nums[mid]:    # 此时有两种情况
                    if target >= nums[0]:   # target 在左侧
                        high = mid
                    else:                   # target 在右侧
                        low = mid + 1
                else:
                    low = mid + 1
            else:                           # nums[mid] 在右侧
                if nums[mid] == target:
                    return mid
                elif target < nums[mid]:
                    high = mid
                else:                       # 此时有两种情况
                    if target >= nums[0]:   # target 在左侧
                        high = mid
                    else:                   # target 在右侧
                        low = mid + 1
        if nums[low] == target: 
            return low
        if nums[high-1]==target: 
            return high-1
        return -1
```
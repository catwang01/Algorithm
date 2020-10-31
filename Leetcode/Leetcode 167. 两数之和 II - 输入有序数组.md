[toc]

# Leetcode 167. 两数之和 II - 输入有序数组

## 问题描述

[167. 两数之和 II - 输入有序数组 - 力扣（LeetCode）](https://leetcode-cn.com/problems/two-sum-ii-input-array-is-sorted/)

给定一个已按照**升序排列**的有序数组，找到两个数使得它们相加之和等于目标数。

函数应该返回这两个下标值  index1 和 index2，其中 index1 必须小于 index2

**说明:**

- 返回的下标值 (index1 和 index2不是从零开始的。
- 你可以假设每个输入只对应唯一的答案，而且你不可以重复使用相同的元素。

**示例:**
**输入:** numbers = [2, 7, 11, 15], target = 9
**输出:** [1,2]
**解释:** 2 与 7 之和等于目标数 9 。因此 index1 = 1, index2 = 2 。

## 算法

### 解法一：二分法

时间复杂度： $O(nlogn)$
空间复杂度： $O(n)$

#### 解法一二分法python

```
class Solution:
    def twoSum(self, numbers: List[int], target: int) -> List[int]:
        i, high = 0, len(numbers)-1
        # target - numbers[i] < numbers[i] 表示需要查找的值在 numbers[i] 之前
        # 但是比 numbers[i] 小的数在 numbers[i] 之前已经遍历过了
        while i < high and target-numbers[i] >= numbers[i]:
            # 在 i 的右侧进行二分查找 target-numbers[i]
            j = self.bisearch(numbers, i+1, high, target-numbers[i])
            if j != -1:
                return [i+1, j+1]
            i += 1
            
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
```

### 解法二：双指针

#### 解法二双指针python

```
class Solution:
    def twoSum(self, numbers: List[int], target: int) -> List[int]:
        # [0, i) (j, n-1] 遍历过的
        # [i, j] => 没有遍历 的 i > j 时，停止=> i <= j 时，继续
        n = len(numbers)
        if n <= 1: 
            return [-1, -1]
        i, j =0, n-1
        while i <= j:
            s = numbers[i] + numbers[j]
            if s == target: 
                return [i+1, j+1]
            elif s > target:
                j -= 1
            elif s < target:
                i += 1
        return [-1, -1]
```

### 解法三：hashtab


#### 解法三python hashtab

```
class Solution:
    def twoSum(self, numbers: List[int], target: int) -> List[int]:
        n = len(numbers)
        hashtab = {}
        for i in range(len(numbers)):
            # 处理 numbers[i] * 2 == target 的情况
            if numbers[i] == target/2 and i<n-1 and numbers[i+1] == numbers[i]: 
                return [i+1, i+2]
            else:
                if target - numbers[i] in hashtab:
                    return [1+hashtab[target-numbers[i]], 1+i]
                else:
                    hashtab[numbers[i]] = i
```

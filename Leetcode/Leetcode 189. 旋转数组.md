[toc]

# Leetcode 189. 旋转数组

## 问题描述

[189. 旋转数组 - 力扣（LeetCode）](https://leetcode-cn.com/problems/rotate-array/)

## 算法

### 解法1:  brute force

先实现 shift() 函数向右移动一次。然后执行 k 次 shift 函数。

#### 解法1: 实现

```
class Solution:
    def rotate(self, nums: List[int], k: int) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        n = len(nums)
        if n <= 1: return
        k = k % n

        def shift():
            tmp = nums[n-1]
            for i in range(n-1, 0, -1):
                nums[i] = nums[i-1]
            nums[0] = tmp

        for i in range(k): shift()
```

### 解法2: 冒泡法

类似于冒泡排序。将 [n-k, ..., n-1] 这些数字冒泡到 [0, .., k-1] 去

时间复杂度：$O(nk)$

#### 解法2： 实现

##### 解法2: 实现：python

```
class Solution:
    def rotate(self, nums: List[int], k: int) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        n = len(nums)
        if n <= 1: return 
        k = k % n
        for i in range(n-k, n):
            j = i # 将第 i 个位置第数字向左冒泡到 (i+k) % n 这个位置
            while j != (i + k) % n:
                nums[j], nums[j-1] = nums[j-1], nums[j]
                j -= 1
```

### 解法3: 三次reverse

#### 解法3: 实现

```
原始数组                  : 1 2 3 4 5 6 7
反转所有数字后             : 7 6 5 4 3 2 1
反转前 k 个数字后          : 5 6 7 4 3 2 1
反转后 n-k 个数字后        : 5 6 7 1 2 3 4 --> 结果
```

时间复杂度：$O(n)$

#####  解法3: 实现：python

```
class Solution:
    def rotate(self, nums: List[int], k: int) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        n = len(nums)
        if n <= 1: return 
        k = k % n
        self.reverse(nums, 0, n)
        self.reverse(nums, 0, k)
        self.reverse(nums, k, n)
        
    def reverse(self, nums, i, j):
        # [i, j) i >= j 时退出
        while i < j:
            nums[i], nums[j-1] = nums[j-1], nums[i]
            i += 1
            j -= 1
```

# References
1. [旋转数组 - 旋转数组 - 力扣（LeetCode）](https://leetcode-cn.com/problems/rotate-array/solution/xuan-zhuan-shu-zu-by-leetcode/)


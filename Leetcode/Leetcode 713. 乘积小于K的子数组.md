[toc]

# Leetcode 713. 乘积小于K的子数组

## 问题描述

[713. 乘积小于K的子数组 - 力扣（LeetCode）](https://leetcode-cn.com/problems/subarray-product-less-than-k/)

## 算法

### 解法1: 

### 解法2: dp

用 `dp[i]` 来表示以 `nums[i]` 结尾的子数组的乘积，注意 `dp[i]` 是一个数组！

时间复杂度： $O(n^2)$
空间复杂度： $O(n^2)$

##### 解法2：实现


```
class Solution:
    def numSubarrayProductLessThanK(self, nums: List[int], k: int) -> int:
        n = len(nums)
        ret = 0
        dp = [[] for _ in range(n)]
        ret = 0
        for i in range(n):
            if nums[i] < k:
                dp[i].append(nums[i])
            if i >= 1:
                for x in dp[i-1]:
                    s = x * nums[i]
                    if s < k:
                        dp[i].append(s)
            ret += len(dp[i])
        return ret
```

### 解法3: 滑动窗口

实际上和 [209. 长度最小的子数组 - 力扣（LeetCode）](https://leetcode-cn.com/problems/minimum-size-subarray-sum/)
思路相同

注意 0 和 1 的特判

##### 解法3: 实现：python

```
class Solution:
    def numSubarrayProductLessThanK(self, nums: List[int], k: int) -> int:
        if k <= 1: return 0
        n = len(nums)
        left = right = 0
        windowRet = 1
        ret = 0 
        while right < n:
            windowRet *= nums[right]
            while windowRet >= k:
                windowRet //= nums[left]
                left += 1
            ret += right - left + 1
            right += 1
        return ret
```
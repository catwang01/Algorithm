[toc]

# Leetcode 45. 跳跃游戏 II.md

## 问题描述

## 算法

### 解法1: dp

时间复杂度：$O(n^2)$

##### 解法1:实现：python 超时

```
class Solution:
    def jump(self, nums: List[int]) -> int:
        n = len(nums)
        if n <= 1: return 0
        dp = [float("inf")] * n
        dp[n-1] = 0
        for i in range(n-2, -1, -1):
            for k in range(1, min(nums[i]+1, n - i)): # i + k < n --> k < n - i
                dp[i] = min(dp[i], dp[i+k] + 1)
        return dp[0]
```

### 解法2: 贪心

这个问题实际上就是 [1024. 视频拼接 - 力扣（LeetCode）](https://leetcode-cn.com/problems/video-stitching/)

其中 T = len(nums) - 1，clips[i][0] = i, clips[i][1] = i + nums[i]。

直接套用就可以。

##### 解法2: 实现：python

```
class Solution:
    def jump(self, nums: List[int]) -> int:
        n = len(nums)
        if n <= 1: return 0

        left = right = 0
        i = 0
        ret = 0
        while i < n:
            j = i
            isupdated = False
            while j < n and j <= left:
                if j + nums[j] > right:
                    isupdated = True
                    right = j + nums[j]
                j += 1
            if isupdated:
                ret += 1
                left = right
                if right >= n-1:
                    return ret
                i = j
            else:
                return -1
        
        return ret
```
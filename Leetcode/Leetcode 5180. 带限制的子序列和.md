[toc]

# Leetcode 5180. 带限制的子序列和

## 问题描述

[5180. 带限制的子序列和 - 力扣（LeetCode）](https://leetcode-cn.com/problems/constrained-subset-sum/)

## 算法

### 解法1: 滑动窗口

参考：来维护一个窗宽为k 的滑动窗口的最大值

[239. 滑动窗口最大值 - 力扣（LeetCode）](https://leetcode-cn.com/problems/sliding-window-maximum/)

#### 解法1:实现

##### 解法1: python

```
from collections import deque

class Solution:
    def constrainedSubsetSum(self, nums: List[int], k: int) -> int:
        dp = nums
        n = len(nums)
        window = deque()
        left, right = 0, 0
        ret = dp[0]
        for j in range(1, n):
            if right - left == k:
                if window[0] == dp[left]:
                    window.popleft()
                    left += 1
            right += 1
            while len(window) != 0 and window[-1] < dp[j-1]:
                window.pop()
            window.append(dp[j-1])
            dp[j] = nums[j] + max(0, window[0])
            ret = max(ret, dp[j])
        return ret
```


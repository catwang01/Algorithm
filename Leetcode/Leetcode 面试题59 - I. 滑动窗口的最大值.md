[toc]

# Leetcode 面试题59 - I. 滑动窗口的最大值

## 问题描述

[面试题59 - I. 滑动窗口的最大值 - 力扣（LeetCode）](https://leetcode-cn.com/problems/hua-dong-chuang-kou-de-zui-da-zhi-lcof/)

## 算法

### 解法1: 单调栈

#### 解法1:实现

##### 解法1: python

```
from collections import deque
class Solution:
    def maxSlidingWindow(self, nums: List[int], k: int) -> List[int]:
        n = len(nums)
        if n == 0: return []
        ret = []
        window = deque()
        for i in range(k):
            while len(window)>0 and window[-1] < nums[i]:
                window.pop()
            window.append(nums[i])

        ret.append(window[0])
        for i in range(k, n):
            if window[0] == nums[i-k]:
                window.popleft()
            while len(window)>0 and window[-1] < nums[i]:
                window.pop()
            window.append(nums[i])
            ret.append(window[0])
        return ret
```




[toc]

# Leetcode 435. 无重叠区间

## 问题描述

[435. 无重叠区间 - 力扣（LeetCode）](https://leetcode-cn.com/problems/non-overlapping-intervals/)

## 算法

### 解法1： 贪心

这个实际上是活动选择问题，详细可以看算法导论。

#### 解法1: 实现： python

```
class Solution:
    def eraseOverlapIntervals(self, intervals: List[List[int]]) -> int:
        intervals.sort(key=lambda interval: (interval[1], -interval[0]))
        n = len(intervals)
        curStart = -float("inf")
        ret = 0
        for i in range(n):
            if intervals[i][0] >= curStart: 
                curStart = intervals[i][1] # 选择
            else:
                ret += 1  # 不选择，丢弃掉
        return ret
```
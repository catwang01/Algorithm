[toc]

# Leetcode 452. 用最少数量的箭引爆气球


## 问题描述

[452. 用最少数量的箭引爆气球 - 力扣（LeetCode）](https://leetcode-cn.com/problems/minimum-number-of-arrows-to-burst-balloons/)

## 算法

### 解法1: 贪心

将所有的点按照 x 从小到大的顺序排序。然后使用滑动窗口的技巧寻找重叠的部分。几个有重合部分的气球值需要一次射击。

##### 解法1: 实现：python

```
class Solution:
    def findMinArrowShots(self, points: List[List[int]]) -> int:
        # 相当于找到重叠的
        n = len(points)
        points.sort()
        i = 0
        ret = 0
        while i < n:
            overlap = points[i][:]
            j = i + 1
            while j < n and points[j][0] <= overlap[1]:
                overlap[0] = max(overlap[0], points[j][0])
                overlap[1] = min(overlap[1], points[j][1])
                j += 1
            ret += 1
            if j == n: 
                return ret
            else:
                i = j
        return ret
```

### 解法2: 贪心

实际上这个问题也是活动选择问题。重复的区间会被其他的箭射掉。

##### 解法2：实现：python

```
class Solution:
    def findMinArrowShots(self, points: List[List[int]]) -> int:
        points.sort(key=lambda point: (point[1], -point[0]))
        curStart = -float("inf")
        n = len(points)
        ret = 0
        for i in range(n):
            if points[i][0] > curStart:
                curStart = points[i][1]
                ret += 1
        return ret
```
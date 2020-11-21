[toc]

# Leetcode 1024. 视频拼接

## 问题描述

[1024. 视频拼接 - 力扣（LeetCode）](https://leetcode-cn.com/problems/video-stitching/)

## 算法

### 解法1: dp

`dp[i]` 表示 `[0, i)` 区间被覆盖的最少片段数

则得到递推式

```
for j in range(0, len(clips)):
    if clips[j][0] <= i <= clips[j][1]:
        dp[i] = min(dp[i], dp[clips[j][0]] + 1) 
```

时间复杂度： $O(nT)$， n 是片段数
空间复杂度： $O(T)$


##### 解法1：实现：python

```
class Solution:
    def videoStitching(self, clips: List[List[int]], T: int) -> int:
        dp = [float('inf')] * (T + 1)
        dp[0] = 0
        for i in range(1, T+1):
            for clip in clips:
                if clip[0] <= i <= clip[1]:
                    dp[i] = min(dp[i], dp[clip[0]] + 1)
        return dp[T] if dp[T] != float('inf') else -1
```

### 解法1：贪心

```
class Solution:
    def videoStitching(self, clips: List[List[int]], T: int) -> int:
        clips.sort()
        if clips[0][0] != 0: 
            return -1
        left = right = 0
        i = 0
        ret = 0
        while i < len(clips):
            isupdated = False # 用来标记区间是否扩张
                            # 如果没有扩张，[left, right] 这一段没有被覆盖
            j = i
            while j < len(clips) and clips[j][0] <= left: # 在满足 left 被覆盖的条件下尽量去扩张 right
                if clips[j][1] > right:
                    isupdated = True
                    right = clips[j][1]
                j += 1
            if isupdated:
                ret += 1
                i = j
                left = right
                if right >= T:
                    return ret
            else:
                return -1 
        return ret if right >= T else -1
```

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

### 解法2：贪心

```
1. start = 0, ret = 空集
2. 找到 idx = argmax(clips[j][1] | clips[j][0] <= start)
    if 能找到这样的 idx:
        clips[idx] 添加到 ret 中，更新 start = clips[idx][1]
    else:
        无法完成任务，返回 0
3. 
    if start >= T: 
        返回 len(ret)
    else:
        回到 2
```

我们固定 start = 0，我们每次都去满足 `clips[j][1] <= start` 的区间中找那个 `clips[j][1]` 最大的，然后添加到结果中。并且更新 start = `clips[j][1]`
#### 贪心法证明

我们仿照算法导论中对于活动问题的证明。为了清晰起见，我们用 .start 表示区间的起点，即 clips[j][0]，用 .end 表示区间的终点即 clips[j][1]

1. 令 $S_j = \{clip \in clips | clip.end >= j \}$ 表示满足的终点大于 j 的所有区间的集合。假设 $S_j$ 上的最优解为 $A_j = \{a_1, ..., a_k\}$（其中 $a_1, \dots, a_k$ 是根据 .start 排序好序的。再令 $m$ 表示 $S_j$ 中终点最大的区间

2. 如果 $m = a_1$，那么说明 m 一定在最优解中
3. 如果 $m \neq a_1$，根据 m 的定义，一定有 $m.end >= a_1.end$，那么 $A'_j = A_j - \{a_1\} + {m_1}$ 必然也是解。由于  $| A_j' | = | A_j |$，说明 $A_j'$ 也是最优解。

这说明，$S_j$ 中终点最大的区间，必然在最优解中。


#### 解法2: 实现1： bruteforce 版

时间复杂度： $O(n^2)$
空间复杂度：$O(1)$

##### 解法2: 实现1: python

```
class Solution:
    def videoStitching(self, clips: List[List[int]], T: int) -> int:
        start = 0
        ret = 0
        while start < T:
            end = -float("inf")
            for clip in clips: # 这个时间复杂度为 O(n)
                if clip[0] <= start and clip[1] >= end:
                    end = clip[1]
            if end == start:
                return -1
            else:
                ret += 1
                start = end
        return ret
```

#### 解法2: 实现： 滑动窗口


因为在上一个实现中每次都需要对于 clip[0] <= start 的那些区间求最大终点。我们可以将 clips 按照起点升序的方式排序，这样我们就不需要考虑那些 clip[0] > start 的区间了。

##### 解法2: 实现：python

```
class Solution:
    def videoStitching(self, clips: List[List[int]], T: int) -> int:
        clips.sort(key=lambda clip: (clip[0], -clip[1]))
        if T == 0:
            return 0
        start = end = 0 
        ret = 0 
        i = 0  
        while i < len(clips):
            j = i 
            end = start
            # 求满足 clips[j][0] <= start 的最大终点
            while j < len(clips) and clips[j][0] <= start:
                if clips[j][1] > end:
                    end = clips[j][1]
                j += 1
            if start == end:
                return -1
            ret += 1
            if end >= T:
                return ret
            start = end
            i = j
        return -1
```

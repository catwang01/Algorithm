[toc]

# Leetcode 1024. 视频拼接

## 问题描述

[1024. 视频拼接 - 力扣（LeetCode）](https://leetcode-cn.com/problems/video-stitching/)

## 算法

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

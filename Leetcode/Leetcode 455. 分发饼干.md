[toc]

# Leetcode 455. 分发饼干

## 问题描述

[455. 分发饼干 - 力扣（LeetCode）](https://leetcode-cn.com/problems/assign-cookies/)

## 算法

### 解法1：贪心

```
class Solution:
    def findContentChildren(self, g: List[int], s: List[int]) -> int:
        g.sort()
        s.sort()
        i = j = 0
        while i < len(g) and j < len(s):
            if s[j] >= g[i]:
                i += 1
            j += 1
        return i
```
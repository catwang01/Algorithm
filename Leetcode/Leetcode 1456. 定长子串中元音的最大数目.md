[toc]

# Leetcode 1456. 定长子串中元音的最大数目

## 问题描述

[1456. 定长子串中元音的最大数目 - 力扣（LeetCode）](https://leetcode-cn.com/problems/maximum-number-of-vowels-in-a-substring-of-given-length/)

## 解法

### 算法：滑动窗口

##### 解法1: 实现：python

```
class Solution:
    def maxVowels(self, s: str, k: int) -> int:
        n = len(s)
        if k == 0: return 0
        left = right = 0
        window = 0
        ret = 0
        while right < n:
            if s[right] in {"a", 'e', 'i', 'o', 'u'}:
                window += 1
            if right - left + 1 == k: # 只在窗口 大小 k 时记录
                ret = max(ret, window)
                if s[left] in  {"a", 'e', 'i', 'o', 'u'}:
                    window -= 1
                left += 1
            right += 1
        return ret
```
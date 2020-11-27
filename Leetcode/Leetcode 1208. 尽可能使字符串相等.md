[toc]

# Leetcode 1208. 尽可能使字符串相等

## 问题描述

[1208. 尽可能使字符串相等 - 力扣（LeetCode）](https://leetcode-cn.com/problems/get-equal-substrings-within-budget/)

## 算法

### 解法1：滑动窗口

这个问题相当于求满足 `window_cost <= maxCost` 的最长子串，可以使用滑动窗口，由于这个条件具有单调性，因此可以使用滑动窗口。

##### 解法1: 实现：python

```
class Solution:
    def equalSubstring(self, s: str, t: str, maxCost: int) -> int:
        n = len(s)
        left = right = 0
        window_cost = 0

        def condition(window_cost): # 是否满足条件
            nonlocal maxCost
            return window_cost <= maxCost

        ret = 0
        while right  < n:
            window_cost += abs(ord(s[right]) - ord(t[right]))
            while not condition(window_cost):
                window_cost -= abs(ord(s[left]) - ord(t[left]))
                left += 1
            ret = max(ret, right - left + 1)
            right += 1
        return ret
```
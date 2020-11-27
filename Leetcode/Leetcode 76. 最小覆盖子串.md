[toc]

# Leetcode 76. 最小覆盖子串

## 问题描述

[76. 最小覆盖子串 - 力扣（LeetCode）](https://leetcode-cn.com/problems/minimum-window-substring/)

给你一个字符串 S、一个字符串 T，请在字符串 S 里面找出：包含 T 所有字母的最小子串。

**示例：**

**输入: S** = "ADOBECODEBANC", **T** = "ABC"
**输出:** "BANC"

**说明：**

*   如果 S 中不存这样的子串，则返回空字符串 `""`。
*   如果 S 中存在这样的子串，我们保证它是唯一的答案。

## 算法

### 解法一：滑动窗口

#### 解法1：实现1: python

```
class Solution:
    def minWindow(self, s: str, t: str) -> str:
        n = len(s)
        i = j = 0
        target = Counter(t)
        window = {}
        finished = 0
        ret = ""
        while j < n: # [i, j)
            while j < n and finished < len(target):
                if s[j] in target:
                    window[s[j]] = window.get(s[j], 0) + 1
                    if window[s[j]] == target[s[j]]:
                        finished += 1
                j += 1
            # j == n or finished == len(target)
            if finished == len(target):
                while finished == len(target):
                    if s[i] in target:
                        window[s[i]] -= 1
                        if window[s[i]] < target[s[i]]:
                            finished -= 1
                    i += 1
                # 此时 finished == len(target) - 1
                # s[i:j] 不满足条件 s[i-1:j] 满足条件
                if ret == "" or j - (i - 1) < len(ret):
                    ret = s[i-1:j]
            if j == n: break
        return ret
```

#### 解法1：实现2: python

```
class Solution:
    def minWindow(self, s: str, t: str) -> str:
        target = {}
        window = {}
        for ch in t: 
            target[ch] = target.get(ch, 0) + 1
            window[ch] = 0

        nonincluded = len(window)
        n = len(s)
        left = right = 0
        ret = ""
        while right < n:
            if s[right] in window:
                window[s[right]] += 1
                if window[s[right]] == target[s[right]]:
                    nonincluded -= 1
            # 右指针移动
            while nonincluded == 0: # 左指针移动
                if ret == "" or len(ret) > right - left + 1:
                    ret = s[left: right+1]
                if s[left] in window:
                    if window[s[left]] == target[s[left]]:
                        nonincluded += 1
                    window[s[left]] -= 1
                left += 1
            right += 1
        return ret
```
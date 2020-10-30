
[toc]

# Leetcode 3. 无重复字符的最长子串

## 问题描述

[3. 无重复字符的最长子串 - 力扣（LeetCode）](https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/)

给定一个字符串，请你找出其中不含有重复字符的 **最长子串 **的长度。

**示例 1:**
**输入:** "abcabcbb"
**输出:** 3
**解释:** 因为无重复字符的最长子串是 `"abc"`，所以其长度为 3。

**示例 2:**
**输入:** "bbbbb"
**输出:** 1
**解释:** 因为无重复字符的最长子串是 `"b"`，所以其长度为 1。

**示例 3:**
**输入:** "pwwkew"
**输出:** 3
**解释:** 因为无重复字符的最长子串是 `"wke"`，所以其长度为 3。
     请注意，你的答案必须是 **子串** 的长度，`"pwke"` 是一个子序列，不是子串。
     
## 算法

### 解法一：bruteforce

时间复杂度： $O(n^3)$
空间复杂度： $O(1)$

这个解法一可以通过优化 check 函数来降低时间复杂度为 $O(n^2)$


#### 解法一python

```
class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        n = len(s)
        if n <= 1: return n
        maxLen = 0
        check = lambda x: len(x) == len(set(x))
        for i in range(n):
            for j in range(i,n):
                if check(s[i:j+1]):
                    maxLen = max(maxLen, j-i+1)
        return maxLen
```


### 解法二：滑动窗口

时间复杂度：$O(n^2)$ 平摊分析，有两个指针，每个指针移动 $O(n)$ 次，因此时间复杂度为 $O(n)$，而check函数判断的时间复杂度为 $O(n)$，因此总的时间复杂度为 $O(n^2)$
空间复杂度：$O(1)$

#### 解法二python

```
class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        n = len(s)
        if n <= 1: return n
        maxLen = 0
        check = lambda x: len(x) == len(set(x))
        i = j = 0
        while j < n:
            while not check(s[i:j+1]):
                i += 1
            maxLen = max(maxLen, j-i+1)
            j += 1
        return maxLen
```

### 解法二优化

用一个字典来记录字母出现的个数，

时间复杂度： $O(n)$ 
空间复杂度： $O(1)$ 字典的键为26个字母，因此字典最大为 26 个键值对，和问题规模无关

#### 解法二优化python

```
class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        n = len(s)
        if n <= 1: return n
        maxLen = 0
        d = {}
        i = j = 0
        while j < n:
            d[s[j]] = d.get(s[j], 0) + 1
            while d[s[j]]>1: # 这个相当于check函数的功能
                d[s[i]] -= 1
                i += 1
            maxLen = max(maxLen, j-i+1)
            j += 1
        return maxLen
```

### 解法二：优化2

#### 解法二：优化2：实现

优化1 中是通过 d[s[j]] 的个数来确定 i 的位置的。我们还可以直接用一个 dict 来保存 s[j]，使得我们可以直接通过 s[j] 来在 dict 中查到之前的 s[j] 的位置，从而直接确定下次 i 的位置。

##### 解法2：优化2: python

```
class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        # window=[i, j)
        i = j = 0
        maxlen = 0
        n = len(s)
        window = {}
        while i < n:
            while j < n and s[j] not in window:
                window[s[j]] = j
                j += 1
            # j == n or s[j] in window
            maxlen = max(maxlen, j - i)
            if j < n:
                next_i = window[s[j]] + 1 # 下次 i 不包括第一个 s[j]，第一个 s[j] 的位置是 window[s[j]]。
                for k in range(i, next_i):
                    del window[s[k]]
                i = next_i
            else:
                break
        return maxlen
```                 

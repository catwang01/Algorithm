
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


### 解法2：滑动窗口：求最大窗口

需要求满足无重复窗口（子串）大最大大小。其中，无重复这个特征具有“单调性”。

```
如果：s[i:j] 中没有重复则
1. s[i-1:j] 中没有重复
2. s[i:j+1] 中可能有重复
```

或者从另一个角度

```
如果 s[i:j] 有重复，则
1. s[i:j+1] 有重复
2. s[i+1:j] 可能有重复，可能无重复
```

我们通过下面的方式来判读是否有重复元素

```
check = lambda window: len(window) == len(set(window)) # 这个函数 O(n) 复杂度
```

时间复杂度：$O(n^2)$ 平摊分析，有两个指针，每个指针移动 $O(n)$ 次，因此时间复杂度为 $O(n)$，而check函数判断的时间复杂度为 $O(n)$，因此总的时间复杂度为 $O(n^2)$
空间复杂度：$O(1)$

#### 解法2: 实现
##### 解法2：实现：python

```
class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        n = len(s)
        if n <= 1: return n
        ret = 0
        check = lambda window: len(window) == len(set(window)) # 这个函数 O(n) 复杂度
        i = j = 0
        while j < n:
            while not check(s[i:j+1]):
                i += 1
            ret = mawindow(ret, j-i+1)
            j += 1
        return ret
```

### 解法二优化

用一个字典来记录字母出现的个数，

时间复杂度： $O(n)$ 
空间复杂度： $O(1)$ 字典的键为26个字母，因此字典最大为 26 个键值对，和问题规模无关

#### 解法2：实现：python

```
class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        n = len(s)
        if n <= 1: return n
        ret = 0
        window = {}
        i = j = 0
        while j < n:
            window[s[j]] = window.get(s[j], 0) + 1
            while window[s[j]]>1: # 这个相当于check函数的功能
                window[s[i]] -= 1
                i += 1
            ret = max(ret, j-i+1)
            j += 1
        return ret
```

##### 解法2: 实现：c++

```
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> window;
        auto check = [](unordered_map<char, int>& window, char ch) { return window[ch] <= 1; };
        int left = 0, 
            right = 0, 
            n = s.size(),
            ret = 0;
        while (right < n)
        {
            window[s[right]]++;
            while (!check(window, s[right]))
            {
                window[s[left]]--;
                left++;
            }
            ret = max(ret, right - left + 1);
            right++;
        }
        return ret;
    }
};
```


### 解法2：优化2

#### 解法2：优化2：实现

优化1 中是通过 d[s[j]] 的个数来确定 i 的位置的。我们还可以直接用一个 dict 来保存 s[j]，使得我们可以直接通过 s[j] 来在 dict 中查到之前的 s[j] 的位置，从而直接确定下次 i 的位置。

##### 解法2：优化2: python

```
class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        n = len(s)
        if n <= 1: return n
        # [i, j)
        window = {}
        i = j = 0
        maxlen = 1
        while j < n:
            while j < n and s[j] not in window:
                window[s[j]] = j
                j += 1
            # j==n or s[j] in window
            maxlen = max(maxlen, j - i)
            if j != n: # s[j] in window
                next_i = window[s[j]] + 1
                for k in range(i, next_i):
                    del window[s[k]]
                i = next_i
                window[s[j]] = j
                j += 1
        return maxlen
```                 
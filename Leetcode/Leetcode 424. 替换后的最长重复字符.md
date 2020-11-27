[toc]

# Leetcode 424. 替换后的最长重复字符

## 问题描述

## 算法

[424. 替换后的最长重复字符 - 力扣（LeetCode）](https://leetcode-cn.com/problems/longest-repeating-character-replacement/)


### 解法1: 滑动窗口


#### 解法1: 实现

这个问题是最长子串问题，首先考虑滑动窗口。

滑动窗口问题一定要弄清楚问题的特征：问题是考虑满足那种特征（或者说条件）的子串中的最长/最短的？

这里问题的特征是：经过替换后包含重复字符的子串

再考虑这个问题的特征是否具有单调性：

```
1. 如果某个子串 s[i:j] 
    1. s[i:j+1] 经过替换后可能包含非重复字符
    2. s[i+1:j] 经过替换后一定包含重复字符
2. 如果某个子串 s[i:j] 经过替换后包含非重复字符
    1. s[i:j+1] 经过替换后一定包含非重复字符
    2. s[i+1:j] 经过替换后可能包含重复字符
```

这个问题满足单调递减的特征，因此可以用滑动窗口求最大值。

之后我们就要考虑如何判断某个子串 s[i:j] 是否满足 `经过替换后包含重复字符` 这个特征

这里我们用下面的 check 函数来判断

```
def check(window): # window 是一个 dict
    if len(window) < 2:
        return True
    else:
        return sum(window.values()) - max(window.values()) <= k
```

如果 window 中至多只有一中字符，那么这个窗口对应的子串一定是满足 `经过替换后包含重复字符`
如果 window 中有两个以上的字符，我们挑出其中出现次数最多的，然后将其他字符都变成这个字符。其他字符 `sum(window.values()) - max(window.values())` 这么多个。如果这个数字 <= k，说明可以用 k 次变换将 window 对应的子串变成重复子串。否则不行。

##### 解法1: 实现：python

```
class Solution:
    def characterReplacement(self, s: str, k: int) -> int:
        n = len(s)
        left = right = 0
        window = {}

        def check(window):
            if len(window) < 2:
                return True
            else:
                return sum(window.values()) - max(window.values()) <= k
    
        ret = 0
        while right < n:
            window[s[right]] = window.get(s[right], 0) + 1
            while not check(window):
                print(window)
                window[s[left]] -= 1
                if window[s[left]] == 0:
                    del window[s[left]]
                left += 1
            ret = max(ret, right - left + 1)
            right += 1
        return ret
```
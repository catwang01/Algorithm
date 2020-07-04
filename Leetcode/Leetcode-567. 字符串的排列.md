[toc]

# Leetcode 567. 字符串的排列

## 问题描述

[567. 字符串的排列 - 力扣（LeetCode）](https://leetcode-cn.com/problems/permutation-in-string/)

给定两个字符串 **s1** 和 **s2**，写一个函数来判断 **s2** 是否包含 **s1 **的排列。

换句话说，第一个字符串的排列之一是第二个字符串的子串。

**示例1:**

**输入:** s1 = "ab" s2 = "eidbaooo"
**输出:** True
**解释:** s2 包含 s1 的排列之一 ("ba").

**示例2:**

**输入:** s1= "ab" s2 = "eidboaoo"
**输出:** False

**注意：**

1.  输入的字符串只包含小写字母
2.  两个字符串的长度都在 [1, 10,000] 之间


## 算法


### 解法一： hashtab

时间复杂度： $O(nm)$
空间复杂度： $O(m)$

#### 解法1:python

```
from collections import Counter
class Solution:
    def checkInclusion(self, s1: str, s2: str) -> bool:
        m, n = len(s1), len(s2)
        s1 = Counter(s1)
        for i in range(n-m+1):
            if Counter(s2[i:i+m]) == s1:
                return True
        return False
```

#### 解法1:c++

```
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int n1 = s1.size(), n2 = s2.size();
        if (n1 == 0) return true;
        if (n2 < n1) return false;
        unordered_map<char, int> target, window;
        for (char s: s1) target[s]++;
        for (int i=0; i<n1; i++) window[s2[i]]++;
        int j = n1;
        while (target!=window && j < n2) {
            window[s2[j]]++;
            window[s2[j-n1]]--;
            if (window[s2[j-n1]]==0) 
                window.erase(s2[j-n1]);
            j++;
        }
        return window == target;
    }
};
```

### 解法一优化

用一个 n_needs 来记录需要满足的条件的个数，用 n_valid 记录已经满足的条件的个数

时间复杂度： $O(n)$
空间复杂度： $O(m)$

#### 解法一优化

```
from collections import Counter
class Solution:
    def checkInclusion(self, s1: str, s2: str) -> bool:
        m, n = len(s1), len(s2)
        s1 = Counter(s1)
        n_needs, n_valid = len(s1), 0

        d = {}
        for i in range(n):
            print(n_valid)
            d[s2[i]] = d.get(s2[i], 0) + 1
            if d[s2[i]] == s1[s2[i]]:
                n_valid += 1
            if i >= m:
                if d[s2[i-m]] == s1[s2[i-m]]:
                    n_valid -= 1
                d[s2[i-m]] -= 1
            if n_valid == n_needs:
                return True
        return False
```


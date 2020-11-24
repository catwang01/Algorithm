[toc]

# Leetcode 451. 根据字符出现频率排序

## 问题描述

[451. 根据字符出现频率排序 - 力扣（LeetCode）](https://leetcode-cn.com/problems/sort-characters-by-frequency/)

## 算法

### 解法1： 计数排序

```
from collections import Counter 

class Solution:
    def frequencySort(self, s: str) -> str:
        counter = Counter(s)
        ret = ""
        for ch, i in counter.most_common():
            ret += ch * i

        return ret
```

### 解法2：排序

计算每个字符的频率，然后按照频率倒序排列。其中有一点需要注意，排序的 key 除了 -counter[ch] 之外，还有 ch。这是为了排除下面的情况

```
s = "aabb"
ret = "abab"
```

如果 key 只用 -counter[ch]，那么就有可能出现上面那种情况。a 和 b 的频率相同，我们需要保证 a 在 b 之前（或者 b 在 a 之前）

```
from collections import Counter 

class Solution:
    def frequencySort(self, s: str) -> str:
        counter = Counter(s)
        return "".join(sorted(s, key=lambda ch: (-counter[ch], ch)))
```
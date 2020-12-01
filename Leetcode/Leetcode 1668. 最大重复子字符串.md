[toc]

# Leetcode 1668. 最大重复子字符串

## 问题描述

[1668. 最大重复子字符串 - 力扣（LeetCode）](https://leetcode-cn.com/problems/maximum-repeating-substring/)

## 算法

### 解法1: 二分法


#### 解法1: 实现1:

k 是单调递增的，因此可以使用二分法。

condition 函数用来判断 word * k 是否在 sequence 中，时间复杂度为 $O(n)$

因此总的时间复杂度为 $O(n * log(n / m))$ 其中 n = len(sequence), m = len(word)
空间复杂度为: $O(n)$

##### 解法1: 实现: python


```
class Solution:
    def maxRepeating(self, sequence: str, word: str) -> int:
        ns = len(sequence)
        nw = len(word)
        low, high = 0, ns // nw + 1
        condition = lambda k: k * word in sequence
        while high - low > 2:
            mid = (low + high) // 2
            if condition(mid):
                low = mid
            else:
                high = mid
        if condition(high-1): 
            return high - 1
        return low
```

##### 解法1: 实现: c++

```
class Solution {
public:
    int maxRepeating(string sequence, string word) {
        int low = 0, high = sequence.size() / word.size() + 1;
        auto condition = [&](int k) { 
            string s; 
            for (int i=0; i<k; i++) s += word;
            return sequence.find(s) != string::npos;
        };
        while (high - low > 2)
        {
            int mid = low + (high - low) / 2;
            if (condition(mid)) 
                low = mid;
            else
                high = mid;
        }
        if (condition(high-1)) return high-1;
        return low;
    }
};
```


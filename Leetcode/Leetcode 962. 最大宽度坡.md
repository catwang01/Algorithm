[toc]

# Leetcode 962. 最大宽度坡

## 问题描述

[962. 最大宽度坡 - 力扣（LeetCode）](https://leetcode-cn.com/problems/maximum-width-ramp/)

## 算法

### 解法1：数学法

这个题不太好理解，感觉不算中等难度的。

虽然许多题解里面都说这个解法是“单调栈”法，但是我认为，这个所谓的单调栈只是用来保存结果的，并没有太多用到单调栈的性质。因此我觉得这个不算是单调栈。

为什么是数学法呢？因为这的一个关键推断是需要数学证明的，这个推断是

```
形成最大宽度的坡底只可能是以 A[0] 开始的一个递减序列中的值。
```

[ 1 ] 中有一些论证。

##### 解法1: 实现： python

```
class Solution:
    def maxWidthRamp(self, A: List[int]) -> int:
        n = len(A)
        candidate = []
        for i in range(n):
            if i == 0 or A[candidate[-1]] > A[i]:
                candidate.append(i)
        ret = 0

        j = n - 1
        while j > 0:
            while candidate != [] and j > candidate[-1]:
                if A[j] >= A[candidate[-1]]: 
                    ret = max(ret, j - candidate[-1])
                    candidate.pop()
                else:
                    j -= 1
            if candidate == []: 
                return ret
            if j <= candidate[-1]: 
                candidate.pop()
        return ret
```

# References
1. [Java 单调栈&二分解法 (尝试解释下单调栈的做法) - 最大宽度坡 - 力扣（LeetCode）](https://leetcode-cn.com/problems/maximum-width-ramp/solution/java-dan-diao-zhan-er-fen-jie-fa-chang-shi-jie-shi/)
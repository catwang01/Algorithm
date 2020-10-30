[toc]


## Leetcode LCP 18. 早餐组合


## 问题描述

[LCP 18. 早餐组合 - 力扣（LeetCode）](https://leetcode-cn.com/problems/2vYnGI/)

## 算法

这个题优点类似于 [1. 两数之和 - 力扣（LeetCode）](https://leetcode-cn.com/problems/two-sum/)

### 解法1: 二分法

#### 解法1：实现

```
class Solution:
    def breakfastNumber(self, staple: List[int], drinks: List[int], x: int) -> int:
        nstaples = len(staple)
        ndrinks = len(drinks)
        if nstaples==0 or ndrinks == 0: return 0
        staple.sort()
        drinks.sort()
        ret = 0
        for i in range(nstaples):
            j = self.bisearch(drinks, 0, ndrinks, x - staple[i])
            if j == -1:
                break
            else:
                ret += j + 1
        return ret % int(1e9+7)
    
    def bisearch(self, drinks, low, high, target):
        condition = lambda i: drinks[i] <= target
        # max{i: drinks[i] <= target}
        if not condition(low): return -1
        # [low, high)
        while high - low > 2:
            mid = (low + high) // 2
            if condition(mid):
                low = mid
            else:
                high = mid
        if condition(high - 1):
            return high - 1
        if condition(low):
            return low
        return -1
```

### 解法2:双指针

#### 解法2: 实现

##### 解法2: 实现：python

```
class Solution:
    def breakfastNumber(self, staple: List[int], drinks: List[int], x: int) -> int:
        nstaple = len(staple)
        ndrinks = len(drinks)
        if nstaple == 0 or ndrinks == 0: return 0
        ret = 0
        i = 0
        j = ndrinks - 1 # [0, j] 
        staple.sort()
        drinks.sort()
        condition = lambda i, j: drinks[j] <= x - staple[i]
        while i < nstaple and j >= 0:
            while j >= 0 and not condition(i, j):
                j -= 1
            if j >= 0: 
                ret += j + 1
                i += 1
        return ret % int(1e9 + 7)
```
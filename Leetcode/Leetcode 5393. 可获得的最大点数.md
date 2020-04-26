[toc]

# Leetcode 5393. 可获得的最大点数

## 问题描述

[5393. 可获得的最大点数 - 力扣（LeetCode）](https://leetcode-cn.com/problems/maximum-points-you-can-obtain-from-cards/)

## 算法

### 解法1: 递归

#### 解法1:实现

##### 解法1: python 超时

```
class Solution:
    def maxScore(self, cardPoints: List[int], k: int) -> int:
        if len(cardPoints) <= k:
            return sum(cardPoints)
        if k == 0:
            return 0
        return max(cardPoints[0] + self.maxScore(cardPoints[1:], k-1),
                  cardPoints[-1] + self.maxScore(cardPoints[:-1], k-1))
```

### 解法2: 双指针

#### 解法2:实现

##### 解法2: 

```
class Solution:
    def maxScore(self, cardPoints: List[int], k: int) -> int:
        if len(cardPoints) <= k:
            return sum(cardPoints)
        s = sum(cardPoints[:k])
        ret = s
        i, j = k-1, len(cardPoints)-1
        while i >= 0:
            s -= cardPoints[i]
            s += cardPoints[j]
            ret = max(s, ret)
            i -= 1
            j -= 1
        return ret
```


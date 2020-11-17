[toc]

# Leetcode 848. 字母移位

## 问题描述

[848. 字母移位 - 力扣（LeetCode）](https://leetcode-cn.com/problems/shifting-letters/)

## 算法

### 解法1： 计算后缀和

时间复杂度：$O(n)$
空间复杂度： $O(n)$

##### 解法1: 实现：python

```
class Solution:
    def shiftingLetters(self, S: str, shifts: List[int]) -> str:

        def shift(s, dis):
            return chr((ord(s) - ord('a') + dis) % 26 + ord('a'))
        
        listS = list(S)
        n = len(shifts)
        postSum = [0] * (n + 1)

        for i in range(n-1, -1, -1):
            postSum[i] = postSum[i+1] + shifts[i]
        for i in range(n):
            listS[i] = shift(listS[i], postSum[i])
        return "".join(listS)
```

### 解法2: 解法1 优化

可以将计算后缀和和 shift 的两个循环合并在一起，同时可以用滚动数组优化后缀数组

时间复杂度：$O(n)$
空间复杂度：$O(1)$

##### 解法2: 实现：python

```
class Solution:
    def shiftingLetters(self, S: str, shifts: List[int]) -> str:

        def shift(s, dis):
            return chr((ord(s) - ord('a') + dis) % 26 + ord('a'))
        
        listS = list(S)
        n = len(shifts)
        postSum = 0
        for i in range(n-1, -1, -1):
            postSum = postSum + shifts[i]
            listS[i] = shift(listS[i], postSum)
        return "".join(listS)
```
[toc]

# Leetcode 869. 重新排序得到 2 的幂

## 问题描述

[869. 重新排序得到 2 的幂 - 力扣（LeetCode）](https://leetcode-cn.com/problems/reordered-power-of-2/)

## 算法

### 解法1 比较个数

实际上，我们希望不同排列映射到同一个值，因此采用统计每个数字出现的次数来代表这个数字。如 "116" 可以表示为：{1: 2, 6: 1}

#### 复杂度分析

对于 N 来说，有 $O(logN)$ 位。

时间复杂度：$O(log^2n)$
空间复杂度：$O(logn)$

```
class Solution:
    def myhash(self, N):
        hashtab = [0] * 10
        while N:
            N, i = N // 10, N % 10
            hashtab[i] += 1
        return hashtab

    def reorderedPowerOf2(self, N):
        target = self.myhash(N)
        for i in range(32):
            if target == self.myhash(1 << i):
                return True 
        return False
```


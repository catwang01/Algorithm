[toc]


# Leetcode 190. 颠倒二进制位

## 问题描述

[190. 颠倒二进制位 - 力扣（LeetCode）](https://leetcode-cn.com/problems/reverse-bits/)

## 算法

### 解法1

```
class Solution:
    def reverseBits(self, n: int) -> int:
        ret = 0
        for i in range(32):
            ret += ((n >> i) & 1) << (31 - i)
        return ret
```
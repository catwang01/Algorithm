[toc]

# Leetcode 1497. 检查数组对是否可以被 k 整除

## 问题描述

[1497. 检查数组对是否可以被 k 整除 - 力扣（LeetCode）](https://leetcode-cn.com/problems/check-if-array-pairs-are-divisible-by-k/)

## 算法

### 解法1: hash

##### 解法1: 实现：python

```
class Solution:
    def canArrange(self, arr: List[int], k: int) -> bool:
        hashtab = {}
        for x in arr:
            key = x % k
            target = k - key
            if target==k:
                target=0
            if target in hashtab:
                hashtab[target] -= 1
                if hashtab[target] == 0:
                    del hashtab[target]
            else:
                hashtab[key] = hashtab.get(key, 0) + 1
        
        return len(hashtab) == 0
```

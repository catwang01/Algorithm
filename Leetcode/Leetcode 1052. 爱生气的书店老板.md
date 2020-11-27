[toc]

# Leetcode 1052. 爱生气的书店老板

## 问题描述

[1052. 爱生气的书店老板 - 力扣（LeetCode）](https://leetcode-cn.com/problems/grumpy-bookstore-owner/)

## 算法

### 解法1：滑动窗口

窗口固定，大小为 X

##### 解法1：实现：python

```
class Solution:
    def maxSatisfied(self, customers: List[int], grumpy: List[int], X: int) -> int:
        n = len(customers)
        nsatisfied = 0 
        for i in range(n):
            if grumpy[i] == 0: nsatisfied += customers[i]
        # 此时 nsatisfied 是不忍耐时的满意的顾客
        ret = 0 
        left = right = 0
        while right < n:
            if grumpy[right] == 1:
                nsatisfied += customers[right]
            if right - left + 1 > X:
                if grumpy[left] == 1:
                    nsatisfied -= customers[left]
                left += 1
            ret = max(ret, nsatisfied)
            right += 1
        return ret
```